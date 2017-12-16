// #include "bezier.h"
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <iostream>
#include "Resource.h"

#include "math/z_gdi+_render.h"

#pragma warning(disable:4244)
using namespace Gdiplus;
#define MAX_LOADSTRING 100
// ȫ�ֱ���:
HINSTANCE hInst;							// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];			// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];		// ����������

Z_HandwritingRender g_hw_render(1.0f, 6.0f);

// AlpointsList g_points(200, 100);
// �˴���ģ���а����ĺ�����ǰ������:
ATOM		MyRegisterClass(HINSTANCE hInstance);
BOOL		InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HDC hdc, RECT r);
void OnMouseMove(WPARAM wparam, LPARAM lparam);


HWND g_hwnd = NULL;
int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;
	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BEZIER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BEZIER));
	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} 
	return (int) msg.wParam;
} 

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	DWORD dwStyle = CS_HREDRAW | CS_VREDRAW;
	dwStyle &= ~(WS_SIZEBOX);     
	dwStyle &= ~(WS_MAXIMIZEBOX);
	dwStyle &= ~(WS_MINIMIZEBOX);
	wcex.style = dwStyle;
	wcex.lpfnWndProc		= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BEZIER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BEZIER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����
   DWORD style = WS_OVERLAPPEDWINDOW;
   style &= ~(WS_SIZEBOX);
   style &= ~(WS_MAXIMIZEBOX);
   style &= ~(WS_MINIMIZEBOX);
   hWnd = CreateWindow(szWindowClass, szTitle, style,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT: {
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc, ps.rcPaint);
		EndPaint(hWnd, &ps);
		}
		break;
	case WM_CREATE:{
		g_hwnd = hWnd;
		RECT r;
		GetClientRect(hWnd, &r);
		g_hw_render.init_memHdc(r.right - r.left, r.bottom - r.top);
		}
		break;
	case WM_MOUSEMOVE:{
		OnMouseMove(wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		g_hw_render.insert_first(GET_X_LPARAM(lParam), -GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONUP: {
			RECT update_rect;
			g_hw_render.insert_last(GET_X_LPARAM(lParam), -GET_Y_LPARAM(lParam));
			g_hw_render.draw_to_hdc(NULL, &update_rect);
			InflateRect(&update_rect, 5, 5);
			InvalidateRect(g_hwnd, NULL, true);
			UpdateWindow(g_hwnd);
		}
		break; 
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
} 

int main(int argcount, void *args){
	HINSTANCE instance = GetModuleHandle(NULL);
	return wWinMain(instance,NULL,NULL,SW_SHOW);
}

void OnPaint(HDC hdc, RECT r) {
	g_hw_render.copy_to_hdc(hdc, r);
}

void OnMouseMove(WPARAM wparam, LPARAM lparam) {
	if( (wparam & MK_LBUTTON)!=MK_LBUTTON ) {
		return;
	} 
	// �ڲ�ʹ�õ�������ϵ, Y�ķ����Ǵ��ϵ���,
	// ������Ҫ ��Yֵ��ȡ���ٴ���
	g_hw_render.insert(GET_X_LPARAM(lparam), -GET_Y_LPARAM(lparam)); 
	RECT update_rect;
	g_hw_render.draw_to_hdc(NULL, &update_rect); 
	InflateRect(&update_rect, 5, 5);
	InvalidateRect(g_hwnd, &update_rect, true);
	UpdateWindow(g_hwnd);
}
#pragma warning(default:4244)
