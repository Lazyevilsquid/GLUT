//
//  main.cpp
//  01_Rectangle
//
//  Created by sun on 2017. 10. 9..
//  Copyright © 2017년 sun. All rights reserved.
//

// OpenGL 랜더링 파이프라인 (도형을 이루는 정점의 대해)
// 모델뷰 변환 (시야 공간)
// 투영 변환 (투영 공간)
// 뷰포트 변환 (화면 공간)
// 정점의 픽셀위치 결정!

#include <iostream>
#include <GLUT/GLUT.h>

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	// 빨간색 색상의
	glColor3f(0.f, 1.f, 0.f);
	
	// 사각형 크기~
	glRectf(-50.f,50.f,50.f,-50.f);

	glFlush();
}

void SetupRenderContext()
{
	glClearColor(1.f, 0.f, 0.f, 1.f);
}

void ChangeWindowSize(GLsizei width, GLsizei height)
{
	// 높이가 0일때 나누는에러 방지 (예외 처리)
	if(height == 0) height = 1;

	// 투영 행렬 설정 모드
	glMatrixMode(GL_PROJECTION);
	// 단위 행렬로 초기화
	glLoadIdentity();
	
	// 클리핑 영역 설정 ----
	// 화면 비율 구하기 가로 / 새로
	GLfloat glfAspect = (GLfloat)width / (GLfloat)height;
	
	// 클리핑 영역 계산
	// 클리핑 영역(시야)의 높이를 200f 기준으로 한다면
	// fClipHalfheight = 100; , fClipHalfWidth = 150;
	GLfloat fWantHeight = 200.f;
	GLfloat fClipHalfheight = fWantHeight * 0.5f;
	GLfloat fClipHalfWidth = fClipHalfheight * glfAspect;
	
	// viewport를 변경하게 되었을 때 일어날 수 있는 왜곡현상을 막는데 사용
	glOrtho(-fClipHalfWidth, fClipHalfWidth, -fClipHalfheight, fClipHalfheight, 1.f, -1.f);
	
	// 뷰 포트 설정
	// 뷰 포트란 정규화된 정점을 실제 화면 픽셀 위치로 치환할때 필요한 정보
	glViewport(0, 0, width, height);
}

int main(int argc, char * arg[])
{
	glutInit(&argc, arg);
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(600, 400);
	glutCreateWindow("01_Rectangle");
	
	// ==================CallBackFunc==================
	glutDisplayFunc(RenderScene);
	
	// 윈도우 크기가 변경될때 호출되는 CallBack 함수~
	glutReshapeFunc(ChangeWindowSize);
	// ================================================
	SetupRenderContext();

	glutMainLoop();
	return 0;
}
