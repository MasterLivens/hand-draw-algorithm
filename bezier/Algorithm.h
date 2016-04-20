#pragma once
 struct ALPoint {
	float x,y;
	int w; // ��¼��һ����,�ߵĿ��!!!!
}; 
class ALArrPoints {
public:
	ALArrPoints(int initSize, int increaseSize);
	~ALArrPoints();
	bool isEmpty(){return m_count==0?true:false;};
	int count(){return m_count;};
	bool append(ALPoint point);
	bool append(float x,float y);
	bool append(float x,float y,float w);
	ALPoint *getPoint(int index);
	float distanceTo(ALPoint point);
	ALPoint& operator[](unsigned int i);
private: 
	bool increase();
private:
	int m_capability;
	int m_count;
	int m_increaseSize;
	ALPoint *m_points;
};
class AlLine{
public:
	AlLine(float radian, ALPoint point);
	AlLine(ALPoint p1, ALPoint p2);
	~AlLine(){};
	ALPoint* distancePointsTo(float x, float dist);
private:
	float m_r;
	ALPoint m_point;
};
// ����bezier���ߵ����,�յ�,��һ�����Ƶ�,��һ��bezier���ߵ��յ�,�Լ�һ��(0-0.5)������ϳ̶ȵ�����
// ����������,���п��������յ�������Ϊ��ǰbezier���ߵĵڶ������Ƶ�,����һ��Ϊ��һ��bezier���ߵ�
// ���ʼ��ʱ��,����ʼ����Ϊ��һ�����Ƶ�!!!  // �ڽ�β��ʱ��,�ѽ�������Ϊ�ڶ������Ƶ�!!!
ALPoint bezierControlPoint(ALPoint b,ALPoint e,ALPoint n,ALPoint *c,float f);
float distance(ALPoint p1, ALPoint p2);
float square(float f);
float cubic(float f);
void doDraw(ALArrPoints points, float f);
