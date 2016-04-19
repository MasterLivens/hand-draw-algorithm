#pragma once
 struct AlPoint {
	float x,y;
	int w; // ��¼��һ����,�ߵĿ��!!!!
}; 
class Points {
public:
	Points(int initSize, int increaseSize);
	~Points();
	bool isEmpty(){return m_count==0?true:false;};
	int count(){return m_count;};
	bool append(AlPoint point);
	bool append(float x,float y);
	AlPoint *getPoint(int index);
	float distanceTo(AlPoint point);
	AlPoint& operator[](unsigned int i);
private: 
	bool Increase();
private:
	int m_capability;
	int m_count;
	int m_increaseSize;
	AlPoint *m_points;
};

class AlLine{
public:
	AlLine(float radian, AlPoint point);
	AlLine(AlPoint p1, AlPoint p2);
	~AlLine(){};
	AlPoint* distancePointsTo(float x, float dist);
private:
	float m_r;
	AlPoint m_point;
};

// ����bezier���ߵ����,�յ�,��һ�����Ƶ�,��һ��bezier���ߵ��յ�,�Լ�һ��(0-0.5)������ϳ̶ȵ�����
// ����������,���п��������յ�������Ϊ��ǰbezier���ߵĵڶ������Ƶ�,����һ��Ϊ��һ��bezier���ߵ�
// ���ʼ��ʱ��,����ʼ����Ϊ��һ�����Ƶ�!!!  // �ڽ�β��ʱ��,�ѽ�������Ϊ�ڶ������Ƶ�!!!
AlPoint bezierControlPoint(AlPoint b,AlPoint e,AlPoint n,AlPoint *c,float f);
float distance(AlPoint p1, AlPoint p2);
float square(float f);
void doDraw(Points points, float f);
