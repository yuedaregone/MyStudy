#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include <windows.h>
#include <gdiplus.h>
#include "../classes/MNode.h"
#include "../classes/MScene.h"
#include "../classes/MSprite.h"

#define BALL_MAX_NUM 1
class Ball;
class HelloWorld : public MNode
{
public:
	HelloWorld() {};
	~HelloWorld();
	CreateFunc(HelloWorld);
	virtual void init();
public:
	static MScene* scene();
	virtual void draw();
	void updateBallPos(float dt);
private:
	MPoint m_pBottom[3];	
	Gdiplus::Pen* m_pen;
	int m_maxW;
	int m_maxH;
	Ball* m_ball[BALL_MAX_NUM];
};

class Ball : public MSprite
{
public:
	typedef enum _WallType
	{
		e_type_up,
		e_type_down,
		e_type_left,
		e_type_right,
		e_type_unkown
	}WallType;
	static Ball* createBall(int _key);
	void initBall(int _key);
	void resetBallPosition(Ball* _ball[], int n);
	void updatePosition(Ball* _ball[], int n);	
	void updateCrash(Ball* _ball[], int n);
	MPoint getMidPoint();
	float m_r;
	float m_speedX;
	float m_speedY;
private:
	void checkIsCrashWall(WallType _t);
	bool isCrashOtherBall(Ball* _otherBall);	
	void crashBall(Ball* _otherBall);
};
#endif