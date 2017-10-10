//
//  main.cpp
//  03_MoveRect
//
//  Created by sun on 2017. 10. 10..
//  Copyright © 2017년 sun. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>

// 자 화면사이즈(윈도우 사이즈) 가져오자아
GLfloat g_fWantHeight = 200.f;
GLfloat g_fClipHalfWidth = g_fWantHeight;
GLfloat g_fClipHalfHeight = g_fWantHeight;

// 사각형 정보
GLfloat g_fRectx = 0.f;
GLfloat g_fRecty = 0.f;
GLfloat g_fSize = 25.f;

// 움직이는 속도
GLfloat g_fSpeed = 3.f;

// 현재 속도
GLfloat g_fxCurStep = g_fSpeed;
GLfloat g_fyCurStep = g_fSpeed;

void TimerFunc(int nValue)
{
	// 사각형 이동시키자아
	g_fRectx += g_fxCurStep;
	g_fRecty += g_fyCurStep;
	
	// # 경계 검사 : 경계에 사각형이 부딪히면 방향을 바꾼다.
	// 사각형 왼쪽이나 오른쪽이 클립공간을 벗어났으면
	// 좌우 이동 벡터를 바꾼다.
	if( g_fRectx < -g_fClipHalfWidth )
	{
		g_fRectx = -g_fClipHalfWidth;
		g_fxCurStep = g_fSpeed;
	}
	else if( g_fRectx > g_fClipHalfWidth - g_fSize )
	{
		g_fRectx = g_fClipHalfWidth - g_fSize;
		g_fxCurStep = -g_fSpeed;
	}
	
	// 사각형 윗쪽이나 아래쪽이 클립공간을 벗어났으면
	// 상하 이동 벡터를 바꾼다.
	if( g_fRecty < -g_fClipHalfHeight + g_fSize )
	{
		g_fRecty = -g_fClipHalfHeight + g_fSize;
		g_fyCurStep = g_fSpeed;
	}
	else if( g_fRecty > g_fClipHalfHeight )
	{
		g_fRecty = g_fClipHalfHeight;
		g_fyCurStep = -g_fSpeed;
	}
	
	// 장면을 다시 그린다.
	glutPostRedisplay();
	
	// 다시 타임스탭 이후에 현재 함수가 불릴 수 있도록 설정할다.
	glutTimerFunc(3.f, TimerFunc, 1);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.f, 0.f, 0.f);
	
	glRectf(g_fRectx, g_fRecty, g_fRectx + g_fSize, g_fRecty - g_fSize);
	
	glFlush();
	
	// 스왑버퍼 (더블버퍼)
	glutSwapBuffers();
}

void SetupRenderContext()
{
	glClearColor(0.f, 0.f, 1.f, 1.f);
}

void ChangeWindowSize(GLsizei width, GLsizei height)
{
	if(height == 0) height = 1;
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	
	GLfloat fAspect = (GLfloat)width / (GLfloat)height;
	
	g_fClipHalfHeight = g_fWantHeight * 0.5f;
	g_fClipHalfWidth = g_fClipHalfHeight * fAspect;
	
	glOrtho(-g_fClipHalfWidth, g_fClipHalfWidth, -g_fClipHalfHeight, g_fClipHalfHeight, 1.f, -1.f);
	
	glViewport(0, 0, width, height);
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("03_MoveRect");
	
	glutDisplayFunc(RenderScene);
	
	glutReshapeFunc(ChangeWindowSize);
	
	glutTimerFunc(3.f, TimerFunc, 1);
	
	SetupRenderContext();
	
	glutMainLoop();
	
	return 0;
}
