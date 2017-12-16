#pragma once

#include <windows.h>
#include <windowsx.h>
#include <GdiPlus.h>
using namespace Gdiplus;

#include "z_math.h"

class GdiPlusIniter{
public:
	GdiPlusIniter();
	~GdiPlusIniter(); 
	Graphics * get_graphics_from_hdc(HDC hdc);
	bool ok();
private:
	ULONG_PTR m_gdiplusToken;
	Gdiplus::Status m_ok;
}; 

class Z_HandwritingRender {
public:
	Z_HandwritingRender(float min_pen_width, float max_pen_width);
	~Z_HandwritingRender(); 

	// ʹ��ͼ��˫����, ���ڲ���'��'
	void init_memHdc(unsigned int cx, unsigned int cy);
	void copy_to_hdc(HDC hdc, RECT r);

	void insert_first(int x, int y);
	void insert(int x, int y);
	void insert_last(int x, int y); 

	z_point get_last_inserted() {
		z_point p = { 0, 0 };
		if (m_cur_path) {
			p = m_cur_path->last_point;
		} 
		return p;
	}

	bool draw_to_hdc(HDC hdc, RECT *r);
private:
	z_fpoint_arraylist *m_arr_list = NULL;
	z_fpoint_array *m_cur_path = NULL;
	unsigned int m_cur_last_index = 0;
	float m_w_max, m_w_min; 
// Todo: ��HandwritingRender�ڲ������봰��client rectһ����С��memory hdc,
//	ÿ�δ���OnPaintʱ, ֻ��Ҫ����Rect ������Ҫ���µĲ��ֵ�����hdc��.  
	HBITMAP m_mem_bmp = NULL;
	HDC m_mem_hdc = NULL;
	unsigned int m_cx = 0, m_cy = 0;
};