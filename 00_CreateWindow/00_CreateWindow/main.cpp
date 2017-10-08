//
//  main.cpp
//  00_CreateWindow
//
//  Created by sun on 2017. 10. 8..
//  Copyright © 2017년 sun. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>

void RenderScene()
{
	// 화면 지우기(컬러만in)
	glClear(GL_COLOR_BUFFER_BIT);
	
	// 화면 출력
	glFlush();
}

void SetupRenderContext()
{
	glClearColor(1.f, 0.f, 0.f, 1.f);
}

int main(int argc, char * arg[])
{
	// GLUT 초기화
	glutInit(&argc, arg);
	// 단일버퍼,rgb사용
	glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(400, 300);
	glutCreateWindow("00_CreateWindow");
	
	// 그려주는부분(Callback함수)
	glutDisplayFunc(RenderScene);
	
	// 랜더 문맥 설정
	SetupRenderContext();
	
	// 프로그램 루프 시작
	glutMainLoop();
	return 0;
}
