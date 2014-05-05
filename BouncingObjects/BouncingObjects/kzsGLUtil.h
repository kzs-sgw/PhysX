#pragma once

#include <stdlib.h>
#include <stdio.h>


#ifdef __APPLE__
	#include <GLUT/glut.h>
	#include <OpenGL/OpenGL.h>
#elif defined _WIN32 || defined _WIN64
	#include <GL\glut.h>
#endif 


// classes
class kzsGLUtil;
class GLColor;


// **kzsGLUtil**
class kzsGLUtil
{
public:
	kzsGLUtil(void);
	~kzsGLUtil(void);

	void setOrthoForFont( int WINDOW_WIDTH, int WINDOW_HEIGHT );
	void RenderSpacedBitmapString( int x, int y, int spacing, void* font, char* string );
	void drawAxes();
	void drawGrid( int GRID_SIZE );
	void drawGrid( int GRID_SIZE, GLColor clr );
	void toggleFaceDirection();

};


// ** GLColor**
class GLColor
{
private:
	static const int R = 0;
    static const int G = 1;
    static const int B = 2;
    static const int A = 3;
	GLfloat color_[ 4 ];

public:
	GLColor(void);
	GLColor( GLfloat r, GLfloat g, GLfloat b ); //アルファ値を指定しない場合は1.0
    GLColor( GLfloat r, GLfloat g, GLfloat b, GLfloat a );
	~GLColor(void);

	GLfloat r();
	GLfloat g();
	GLfloat b();
	GLfloat a();

	GLfloat* pointer();

};