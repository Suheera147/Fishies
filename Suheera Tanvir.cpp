/*********
   CTIS164 - Homework 1
----------
STUDENT : Suheera Tanvir
STUDENT NUMBER : 21801211
SECTION :164-02
HOMEWORK: 1
----------
PROBLEMS:
1) Each object has a different set of code. That is why this code is long and inefficient
2) Objects can be made on top of each other. There is no check that does not allow an Object to be made on Top of another.
----------
ADDITIONAL FEATURES:
Just a lot of Background*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1200
#define WINDOW_HEIGHT 650

#define TIMER_PERIOD 9   //period for the timer. 9 for fast speed of the object
#define TIMER_ON      1   //0:disable timer, 1:enable timer

#define D2R 0.0174532

bool activeTimer = false;  //set this to false to ensure object is inanimate at first, and you need to animate it later
//the remaining variables are for the other Fishes
bool activeTimer2 = false;
bool activeTimer3 = false;
bool activeTimer4 = false;
bool activeTimer5 = false;
bool activeTimer6 = false;
bool activeTimer7 = false;
bool activeTimer8 = false;
bool activeTimer9 = false;
bool activeTimer10 = false;

int counter = 0,
wx, wy; //variables for coordinates

bool up = false, down = false, right = false, left = false;

int  winWidth, winHeight; //current Window width and height

int xFish = 5000, yFish = 5000; //Initial coordinates of the fish. Fish one. Outside screen range.
int xFish2 = -5000, yFish2 = -5000; //Coordinates for the remaining Fishes
int xFish3 = -4545, yFish3 = -6565;
int xFish4 = -6565, yFish4 = -5654;
int xFish5 = -5465, yFish5 = -5466;
int xFish6 = -4566, yFish6 = -4566;
int xFish7 = -4465, yFish7 = -6456;
int xFish8 = -5480, yFish8 = -5456;
int xFish9 = -5660, yFish9 = -5646;
int xFish10 = -5550, yFish10 = -5560;

int fishCount = 0;   //Number of Fishes on window



void circle(int x, int y, int r)  //function for making circles
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)  //function for outlining circles
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI*i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char *string, void *font)    
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}


void vprint(int x, int y, void *font, const char *string, ...)  
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

void vprint2(int x, int y, float size, const char *string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}


void drawFish()    //my Complex Object
{
	//Polygon Body of the Fish
	glColor3f(0.101, 0.635, 0.250);
	glBegin(GL_POLYGON);
	glVertex2f(xFish - 30, yFish + 30);
	glVertex2f(xFish + 20, yFish + 30);
	glVertex2f(xFish + 20, yFish - 30);
	glVertex2f(xFish - 30, yFish - 30);
	glVertex2f(xFish - 50, yFish);
	glEnd();

	//Outline of body
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xFish - 30, yFish + 30);
	glVertex2f(xFish + 20, yFish + 30);
	glVertex2f(xFish + 20, yFish - 30);
	glVertex2f(xFish - 30, yFish - 30);
	glVertex2f(xFish - 50, yFish);
	glEnd();


	//Triangle Tail of the Fish
	glColor3f(0.011, 0.388, 0.113);
	glBegin(GL_TRIANGLES);
	glVertex2f(xFish - 50, yFish);
	glVertex2f(xFish - 70, yFish + 30);
	glVertex2f(xFish - 70, yFish - 30);
	glEnd();

	//outline of tail
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xFish - 50, yFish);
	glVertex2f(xFish - 70, yFish + 30);
	glVertex2f(xFish - 70, yFish - 30);
	glEnd();


	//Polygon mouth of the Fish
	glColor3f(0.784, 0.956, 0.403);
	glBegin(GL_POLYGON);
	glVertex2f(xFish + 20, yFish + 30);
	glVertex2f(xFish + 40, yFish + 10);
	glVertex2f(xFish + 30, yFish);
	glVertex2f(xFish + 40, yFish - 10);
	glVertex2f(xFish + 20, yFish - 30);
	glEnd();

	//outline of mouth
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xFish + 20, yFish + 30);
	glVertex2f(xFish + 40, yFish + 10);
	glVertex2f(xFish + 30, yFish);
	glVertex2f(xFish + 40, yFish - 10);
	glVertex2f(xFish + 20, yFish - 30);
	glEnd();

	//Rectangle on the Face of the Fish
	glColor3f(0.403, 0.956, 0.556);
	glRectf(xFish, yFish + 30, xFish + 20, yFish - 30);

	//Polygon Top Fin of the Fish
	glColor3f(0.262, 0.584, 0.254);
	glBegin(GL_POLYGON);
	glVertex2f(xFish - 20, yFish + 30);
	glVertex2f(xFish - 30, yFish + 40);
	glVertex2f(xFish + 10, yFish + 40);
	glVertex2f(xFish + 20, yFish + 30);
	glEnd();

	//outline of top fin
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xFish - 20, yFish + 30);
	glVertex2f(xFish - 30, yFish + 40);
	glVertex2f(xFish + 10, yFish + 40);
	glVertex2f(xFish + 20, yFish + 30);
	glEnd();

	//Polygon Bottom Fin of the Fish
	glColor3f(0.262, 0.584, 0.254);
	glBegin(GL_POLYGON);
	glVertex2f(xFish - 20, yFish - 30);
	glVertex2f(xFish - 30, yFish - 40);
	glVertex2f(xFish + 10, yFish - 40);
	glVertex2f(xFish + 20, yFish - 30);
	glEnd();

	//outline of bottom fin
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xFish - 20, yFish - 30);
	glVertex2f(xFish - 30, yFish - 40);
	glVertex2f(xFish + 10, yFish - 40);
	glVertex2f(xFish + 20, yFish - 30);
	glEnd();

	//Vertical line on the mouth of the Fish
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(xFish + 30, yFish + 20);
	glVertex2f(xFish + 30, yFish - 20);
	glEnd();

	//Outer Circle eye
	glColor3f(1, 1, 1);
	circle(xFish + 10, yFish + 15, 8);

	//Inner Circle eye
	glColor3f(0, 0, 0);
	circle(xFish + 10, yFish + 15, 3);

	//Number of The Fish
	glColor3f(0, 0, 0);
	vprint(xFish - 20, yFish, GLUT_BITMAP_TIMES_ROMAN_24, "1");  //numbering the fish

	if (xFish2 <= winHeight && yFish2 <= winWidth)   //nested if statements to make multiple objects
	{
		glColor3f(0.101, 0.635, 0.250);
		glBegin(GL_POLYGON);
		glVertex2f(xFish2 - 30, yFish2 + 30);
		glVertex2f(xFish2 + 20, yFish2 + 30);
		glVertex2f(xFish2 + 20, yFish2 - 30);
		glVertex2f(xFish2 - 30, yFish2 - 30);
		glVertex2f(xFish2 - 50, yFish2);
		glEnd();

		//Outline of body
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xFish2 - 30, yFish2 + 30);
		glVertex2f(xFish2 + 20, yFish2 + 30);
		glVertex2f(xFish2 + 20, yFish2 - 30);
		glVertex2f(xFish2 - 30, yFish2 - 30);
		glVertex2f(xFish2 - 50, yFish2);
		glEnd();


		//Triangle Tail of the Fish
		glColor3f(0.011, 0.388, 0.113);
		glBegin(GL_TRIANGLES);
		glVertex2f(xFish2 - 50, yFish2);
		glVertex2f(xFish2 - 70, yFish2 + 30);
		glVertex2f(xFish2 - 70, yFish2 - 30);
		glEnd();

		//outline of tail
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xFish2 - 50, yFish2);
		glVertex2f(xFish2 - 70, yFish2 + 30);
		glVertex2f(xFish2 - 70, yFish2 - 30);
		glEnd();


		//Polygon mouth of the Fish
		glColor3f(0.784, 0.956, 0.403);
		glBegin(GL_POLYGON);
		glVertex2f(xFish2 + 20, yFish2 + 30);
		glVertex2f(xFish2 + 40, yFish2 + 10);
		glVertex2f(xFish2 + 30, yFish2);
		glVertex2f(xFish2 + 40, yFish2 - 10);
		glVertex2f(xFish2 + 20, yFish2 - 30);
		glEnd();

		//outline of mouth
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xFish2 + 20, yFish2 + 30);
		glVertex2f(xFish2 + 40, yFish2 + 10);
		glVertex2f(xFish2 + 30, yFish2);
		glVertex2f(xFish2 + 40, yFish2 - 10);
		glVertex2f(xFish2 + 20, yFish2 - 30);
		glEnd();

		//Rectangle on the Face of the Fish
		glColor3f(0.403, 0.956, 0.556);
		glRectf(xFish2, yFish2 + 30, xFish2 + 20, yFish2 - 30);

		//Polygon Top Fin of the Fish
		glColor3f(0.262, 0.584, 0.254);
		glBegin(GL_POLYGON);
		glVertex2f(xFish2 - 20, yFish2 + 30);
		glVertex2f(xFish2 - 30, yFish2 + 40);
		glVertex2f(xFish2 + 10, yFish2 + 40);
		glVertex2f(xFish2 + 20, yFish2 + 30);
		glEnd();

		//outline of top fin
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xFish2 - 20, yFish2 + 30);
		glVertex2f(xFish2 - 30, yFish2 + 40);
		glVertex2f(xFish2 + 10, yFish2 + 40);
		glVertex2f(xFish2 + 20, yFish2 + 30);
		glEnd();

		//Polygon Bottom Fin of the Fish
		glColor3f(0.262, 0.584, 0.254);
		glBegin(GL_POLYGON);
		glVertex2f(xFish2 - 20, yFish2 - 30);
		glVertex2f(xFish2 - 30, yFish2 - 40);
		glVertex2f(xFish2 + 10, yFish2 - 40);
		glVertex2f(xFish2 + 20, yFish2 - 30);
		glEnd();

		//outline of bottom fin
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex2f(xFish2 - 20, yFish2 - 30);
		glVertex2f(xFish2 - 30, yFish2 - 40);
		glVertex2f(xFish2 + 10, yFish2 - 40);
		glVertex2f(xFish2 + 20, yFish2 - 30);
		glEnd();

		//Vertical line on the mouth of the Fish
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_STRIP);
		glVertex2f(xFish2 + 30, yFish2 + 20);
		glVertex2f(xFish2 + 30, yFish2 - 20);
		glEnd();

		//Outer Circle eye
		glColor3f(1, 1, 1);
		circle(xFish2 + 10, yFish2 + 15, 8);

		//Inner Circle eye
		glColor3f(0, 0, 0);
		circle(xFish2 + 10, yFish2 + 15, 3);

		//Number of The Fish
		glColor3f(0, 0, 0);
		vprint(xFish2 - 20, yFish2, GLUT_BITMAP_TIMES_ROMAN_24, "2");

		if (xFish3 <= winHeight && yFish3 <= winWidth)
		{
			glColor3f(0.101, 0.635, 0.250);
			glBegin(GL_POLYGON);
			glVertex2f(xFish3 - 30, yFish3 + 30);
			glVertex2f(xFish3 + 20, yFish3 + 30);
			glVertex2f(xFish3 + 20, yFish3 - 30);
			glVertex2f(xFish3 - 30, yFish3 - 30);
			glVertex2f(xFish3 - 50, yFish3);
			glEnd();

			//Outline of body
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(xFish3 - 30, yFish3 + 30);
			glVertex2f(xFish3 + 20, yFish3 + 30);
			glVertex2f(xFish3 + 20, yFish3 - 30);
			glVertex2f(xFish3 - 30, yFish3 - 30);
			glVertex2f(xFish3 - 50, yFish3);
			glEnd();


			//Triangle Tail of the Fish
			glColor3f(0.011, 0.388, 0.113);
			glBegin(GL_TRIANGLES);
			glVertex2f(xFish3 - 50, yFish3);
			glVertex2f(xFish3 - 70, yFish3 + 30);
			glVertex2f(xFish3 - 70, yFish3 - 30);
			glEnd();

			//outline of tail
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(xFish3 - 50, yFish3);
			glVertex2f(xFish3 - 70, yFish3 + 30);
			glVertex2f(xFish3 - 70, yFish3 - 30);
			glEnd();


			//Polygon mouth of the Fish
			glColor3f(0.784, 0.956, 0.403);
			glBegin(GL_POLYGON);
			glVertex2f(xFish3 + 20, yFish3 + 30);
			glVertex2f(xFish3 + 40, yFish3 + 10);
			glVertex2f(xFish3 + 30, yFish3);
			glVertex2f(xFish3 + 40, yFish3 - 10);
			glVertex2f(xFish3 + 20, yFish3 - 30);
			glEnd();

			//outline of mouth
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(xFish3 + 20, yFish3 + 30);
			glVertex2f(xFish3 + 40, yFish3 + 10);
			glVertex2f(xFish3 + 30, yFish3);
			glVertex2f(xFish3 + 40, yFish3 - 10);
			glVertex2f(xFish3 + 20, yFish3 - 30);
			glEnd();

			//Rectangle on the Face of the Fish
			glColor3f(0.403, 0.956, 0.556);
			glRectf(xFish3, yFish3 + 30, xFish3 + 20, yFish3 - 30);

			//Polygon Top Fin of the Fish
			glColor3f(0.262, 0.584, 0.254);
			glBegin(GL_POLYGON);
			glVertex2f(xFish3 - 20, yFish3 + 30);
			glVertex2f(xFish3 - 30, yFish3 + 40);
			glVertex2f(xFish3 + 10, yFish3 + 40);
			glVertex2f(xFish3 + 20, yFish3 + 30);
			glEnd();

			//outline of top fin
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(xFish3 - 20, yFish3 + 30);
			glVertex2f(xFish3 - 30, yFish3 + 40);
			glVertex2f(xFish3 + 10, yFish3 + 40);
			glVertex2f(xFish3 + 20, yFish3 + 30);
			glEnd();

			//Polygon Bottom Fin of the Fish
			glColor3f(0.262, 0.584, 0.254);
			glBegin(GL_POLYGON);
			glVertex2f(xFish3 - 20, yFish3 - 30);
			glVertex2f(xFish3 - 30, yFish3 - 40);
			glVertex2f(xFish3 + 10, yFish3 - 40);
			glVertex2f(xFish3 + 20, yFish3 - 30);
			glEnd();

			//outline of bottom fin
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(xFish3 - 20, yFish3 - 30);
			glVertex2f(xFish3 - 30, yFish3 - 40);
			glVertex2f(xFish3 + 10, yFish3 - 40);
			glVertex2f(xFish3 + 20, yFish3 - 30);
			glEnd();

			//Vertical line on the mouth of the Fish
			glColor3f(0, 0, 0);
			glBegin(GL_LINE_STRIP);
			glVertex2f(xFish3 + 30, yFish3 + 20);
			glVertex2f(xFish3 + 30, yFish3 - 20);
			glEnd();

			//Outer Circle eye
			glColor3f(1, 1, 1);
			circle(xFish3 + 10, yFish3 + 15, 8);

			//Inner Circle eye
			glColor3f(0, 0, 0);
			circle(xFish3 + 10, yFish3 + 15, 3);

			//Number of the Fish
			glColor3f(0, 0, 0);
			vprint(xFish3 - 20, yFish3, GLUT_BITMAP_TIMES_ROMAN_24, "3");

			if (xFish4 <= winHeight && yFish4 <= winWidth)
			{
				glColor3f(0.101, 0.635, 0.250);
				glBegin(GL_POLYGON);
				glVertex2f(xFish4 - 30, yFish4 + 30);
				glVertex2f(xFish4 + 20, yFish4 + 30);
				glVertex2f(xFish4 + 20, yFish4 - 30);
				glVertex2f(xFish4 - 30, yFish4 - 30);
				glVertex2f(xFish4 - 50, yFish4);
				glEnd();

				//Outline of body
				glColor3f(0, 0, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(xFish4 - 30, yFish4 + 30);
				glVertex2f(xFish4 + 20, yFish4 + 30);
				glVertex2f(xFish4 + 20, yFish4 - 30);
				glVertex2f(xFish4 - 30, yFish4 - 30);
				glVertex2f(xFish4 - 50, yFish4);
				glEnd();


				//Triangle Tail of the Fish
				glColor3f(0.011, 0.388, 0.113);
				glBegin(GL_TRIANGLES);
				glVertex2f(xFish4 - 50, yFish4);
				glVertex2f(xFish4 - 70, yFish4 + 30);
				glVertex2f(xFish4 - 70, yFish4 - 30);
				glEnd();

				//outline of tail
				glColor3f(0, 0, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(xFish4 - 50, yFish4);
				glVertex2f(xFish4 - 70, yFish4 + 30);
				glVertex2f(xFish4 - 70, yFish4 - 30);
				glEnd();


				//Polygon mouth of the Fish
				glColor3f(0.784, 0.956, 0.403);
				glBegin(GL_POLYGON);
				glVertex2f(xFish4 + 20, yFish4 + 30);
				glVertex2f(xFish4 + 40, yFish4 + 10);
				glVertex2f(xFish4 + 30, yFish4);
				glVertex2f(xFish4 + 40, yFish4 - 10);
				glVertex2f(xFish4 + 20, yFish4 - 30);
				glEnd();

				//outline of mouth
				glColor3f(0, 0, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(xFish4 + 20, yFish4 + 30);
				glVertex2f(xFish4 + 40, yFish4 + 10);
				glVertex2f(xFish4 + 30, yFish4);
				glVertex2f(xFish4 + 40, yFish4 - 10);
				glVertex2f(xFish4 + 20, yFish4 - 30);
				glEnd();

				//Rectangle on the Face of the Fish
				glColor3f(0.403, 0.956, 0.556);
				glRectf(xFish4, yFish4 + 30, xFish4 + 20, yFish4 - 30);

				//Polygon Top Fin of the Fish
				glColor3f(0.262, 0.584, 0.254);
				glBegin(GL_POLYGON);
				glVertex2f(xFish4 - 20, yFish4 + 30);
				glVertex2f(xFish4 - 30, yFish4 + 40);
				glVertex2f(xFish4 + 10, yFish4 + 40);
				glVertex2f(xFish4 + 20, yFish4 + 30);
				glEnd();

				//outline of top fin
				glColor3f(0, 0, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(xFish4 - 20, yFish4 + 30);
				glVertex2f(xFish4 - 30, yFish4 + 40);
				glVertex2f(xFish4 + 10, yFish4 + 40);
				glVertex2f(xFish4 + 20, yFish4 + 30);
				glEnd();

				//Polygon Bottom Fin of the Fish
				glColor3f(0.262, 0.584, 0.254);
				glBegin(GL_POLYGON);
				glVertex2f(xFish4 - 20, yFish4 - 30);
				glVertex2f(xFish4 - 30, yFish4 - 40);
				glVertex2f(xFish4 + 10, yFish4 - 40);
				glVertex2f(xFish4 + 20, yFish4 - 30);
				glEnd();

				//outline of bottom fin
				glColor3f(0, 0, 0);
				glBegin(GL_LINE_LOOP);
				glVertex2f(xFish4 - 20, yFish4 - 30);
				glVertex2f(xFish4 - 30, yFish4 - 40);
				glVertex2f(xFish4 + 10, yFish4 - 40);
				glVertex2f(xFish4 + 20, yFish4 - 30);
				glEnd();

				//Vertical line on the mouth of the Fish
				glColor3f(0, 0, 0);
				glBegin(GL_LINE_STRIP);
				glVertex2f(xFish4 + 30, yFish4 + 20);
				glVertex2f(xFish4 + 30, yFish4 - 20);
				glEnd();

				//Outer Circle eye
				glColor3f(1, 1, 1);
				circle(xFish4 + 10, yFish4 + 15, 8);

				//Inner Circle eye
				glColor3f(0, 0, 0);
				circle(xFish4 + 10, yFish4 + 15, 3);

				//Number of The Fish
				glColor3f(0, 0, 0);
				vprint(xFish4 - 20, yFish4, GLUT_BITMAP_TIMES_ROMAN_24, "4");


				if (xFish5 <= winHeight && yFish5 <= winWidth)
				{
					glColor3f(0.101, 0.635, 0.250);
					glBegin(GL_POLYGON);
					glVertex2f(xFish5 - 30, yFish5 + 30);
					glVertex2f(xFish5 + 20, yFish5 + 30);
					glVertex2f(xFish5 + 20, yFish5 - 30);
					glVertex2f(xFish5 - 30, yFish5 - 30);
					glVertex2f(xFish5 - 50, yFish5);
					glEnd();

					//Outline of body
					glColor3f(0, 0, 0);
					glBegin(GL_LINE_LOOP);
					glVertex2f(xFish5 - 30, yFish5 + 30);
					glVertex2f(xFish5 + 20, yFish5 + 30);
					glVertex2f(xFish5 + 20, yFish5 - 30);
					glVertex2f(xFish5 - 30, yFish5 - 30);
					glVertex2f(xFish5 - 50, yFish5);
					glEnd();


					//Triangle Tail of the Fish
					glColor3f(0.011, 0.388, 0.113);
					glBegin(GL_TRIANGLES);
					glVertex2f(xFish5 - 50, yFish5);
					glVertex2f(xFish5 - 70, yFish5 + 30);
					glVertex2f(xFish5 - 70, yFish5 - 30);
					glEnd();

					//outline of tail
					glColor3f(0, 0, 0);
					glBegin(GL_LINE_LOOP);
					glVertex2f(xFish5 - 50, yFish5);
					glVertex2f(xFish5 - 70, yFish5 + 30);
					glVertex2f(xFish5 - 70, yFish5 - 30);
					glEnd();


					//Polygon mouth of the Fish
					glColor3f(0.784, 0.956, 0.403);
					glBegin(GL_POLYGON);
					glVertex2f(xFish5 + 20, yFish5 + 30);
					glVertex2f(xFish5 + 40, yFish5 + 10);
					glVertex2f(xFish5 + 30, yFish5);
					glVertex2f(xFish5 + 40, yFish5 - 10);
					glVertex2f(xFish5 + 20, yFish5 - 30);
					glEnd();

					//outline of mouth
					glColor3f(0, 0, 0);
					glBegin(GL_LINE_LOOP);
					glVertex2f(xFish5 + 20, yFish5 + 30);
					glVertex2f(xFish5 + 40, yFish5 + 10);
					glVertex2f(xFish5 + 30, yFish5);
					glVertex2f(xFish5 + 40, yFish5 - 10);
					glVertex2f(xFish5 + 20, yFish5 - 30);
					glEnd();

					//Rectangle on the Face of the Fish
					glColor3f(0.403, 0.956, 0.556);
					glRectf(xFish5, yFish5 + 30, xFish5 + 20, yFish5 - 30);

					//Polygon Top Fin of the Fish
					glColor3f(0.262, 0.584, 0.254);
					glBegin(GL_POLYGON);
					glVertex2f(xFish5 - 20, yFish5 + 30);
					glVertex2f(xFish5 - 30, yFish5 + 40);
					glVertex2f(xFish5 + 10, yFish5 + 40);
					glVertex2f(xFish5 + 20, yFish5 + 30);
					glEnd();

					//outline of top fin
					glColor3f(0, 0, 0);
					glBegin(GL_LINE_LOOP);
					glVertex2f(xFish5 - 20, yFish5 + 30);
					glVertex2f(xFish5 - 30, yFish5 + 40);
					glVertex2f(xFish5 + 10, yFish5 + 40);
					glVertex2f(xFish5 + 20, yFish5 + 30);
					glEnd();

					//Polygon Bottom Fin of the Fish
					glColor3f(0.262, 0.584, 0.254);
					glBegin(GL_POLYGON);
					glVertex2f(xFish5 - 20, yFish5 - 30);
					glVertex2f(xFish5 - 30, yFish5 - 40);
					glVertex2f(xFish5 + 10, yFish5 - 40);
					glVertex2f(xFish5 + 20, yFish5 - 30);
					glEnd();

					//outline of bottom fin
					glColor3f(0, 0, 0);
					glBegin(GL_LINE_LOOP);
					glVertex2f(xFish5 - 20, yFish5 - 30);
					glVertex2f(xFish5 - 30, yFish5 - 40);
					glVertex2f(xFish5 + 10, yFish5 - 40);
					glVertex2f(xFish5 + 20, yFish5 - 30);
					glEnd();

					//Vertical line on the mouth of the Fish
					glColor3f(0, 0, 0);
					glBegin(GL_LINE_STRIP);
					glVertex2f(xFish5 + 30, yFish5 + 20);
					glVertex2f(xFish5 + 30, yFish5 - 20);
					glEnd();

					//Outer Circle eye
					glColor3f(1, 1, 1);
					circle(xFish5 + 10, yFish5 + 15, 8);

					//Inner Circle eye
					glColor3f(0, 0, 0);
					circle(xFish5 + 10, yFish5 + 15, 3);

					//Number of The Fish
					glColor3f(0, 0, 0);
					vprint(xFish5 - 20, yFish5, GLUT_BITMAP_TIMES_ROMAN_24, "5");

					if (xFish6 <= winHeight && yFish6 <= winWidth)
					{
						glColor3f(0.101, 0.635, 0.250);
						glBegin(GL_POLYGON);
						glVertex2f(xFish6 - 30, yFish6 + 30);
						glVertex2f(xFish6 + 20, yFish6 + 30);
						glVertex2f(xFish6 + 20, yFish6 - 30);
						glVertex2f(xFish6 - 30, yFish6 - 30);
						glVertex2f(xFish6 - 50, yFish6);
						glEnd();

						//Outline of body
						glColor3f(0, 0, 0);
						glBegin(GL_LINE_LOOP);
						glVertex2f(xFish6 - 30, yFish6 + 30);
						glVertex2f(xFish6 + 20, yFish6 + 30);
						glVertex2f(xFish6 + 20, yFish6 - 30);
						glVertex2f(xFish6 - 30, yFish6 - 30);
						glVertex2f(xFish6 - 50, yFish6);
						glEnd();


						//Triangle Tail of the Fish
						glColor3f(0.011, 0.388, 0.113);
						glBegin(GL_TRIANGLES);
						glVertex2f(xFish6 - 50, yFish6);
						glVertex2f(xFish6 - 70, yFish6 + 30);
						glVertex2f(xFish6 - 70, yFish6 - 30);
						glEnd();

						//outline of tail
						glColor3f(0, 0, 0);
						glBegin(GL_LINE_LOOP);
						glVertex2f(xFish6 - 50, yFish6);
						glVertex2f(xFish6 - 70, yFish6 + 30);
						glVertex2f(xFish6 - 70, yFish6 - 30);
						glEnd();


						//Polygon mouth of the Fish
						glColor3f(0.784, 0.956, 0.403);
						glBegin(GL_POLYGON);
						glVertex2f(xFish6 + 20, yFish6 + 30);
						glVertex2f(xFish6 + 40, yFish6 + 10);
						glVertex2f(xFish6 + 30, yFish6);
						glVertex2f(xFish6 + 40, yFish6 - 10);
						glVertex2f(xFish6 + 20, yFish6 - 30);
						glEnd();

						//outline of mouth
						glColor3f(0, 0, 0);
						glBegin(GL_LINE_LOOP);
						glVertex2f(xFish6 + 20, yFish6 + 30);
						glVertex2f(xFish6 + 40, yFish6 + 10);
						glVertex2f(xFish6 + 30, yFish6);
						glVertex2f(xFish6 + 40, yFish6 - 10);
						glVertex2f(xFish6 + 20, yFish6 - 30);
						glEnd();

						//Rectangle on the Face of the Fish
						glColor3f(0.403, 0.956, 0.556);
						glRectf(xFish6, yFish6 + 30, xFish6 + 20, yFish6 - 30);

						//Polygon Top Fin of the Fish
						glColor3f(0.262, 0.584, 0.254);
						glBegin(GL_POLYGON);
						glVertex2f(xFish6 - 20, yFish6 + 30);
						glVertex2f(xFish6 - 30, yFish6 + 40);
						glVertex2f(xFish6 + 10, yFish6 + 40);
						glVertex2f(xFish6 + 20, yFish6 + 30);
						glEnd();

						//outline of top fin
						glColor3f(0, 0, 0);
						glBegin(GL_LINE_LOOP);
						glVertex2f(xFish6 - 20, yFish6 + 30);
						glVertex2f(xFish6 - 30, yFish6 + 40);
						glVertex2f(xFish6 + 10, yFish6 + 40);
						glVertex2f(xFish6 + 20, yFish6 + 30);
						glEnd();

						//Polygon Bottom Fin of the Fish
						glColor3f(0.262, 0.584, 0.254);
						glBegin(GL_POLYGON);
						glVertex2f(xFish6 - 20, yFish6 - 30);
						glVertex2f(xFish6 - 30, yFish6 - 40);
						glVertex2f(xFish6 + 10, yFish6 - 40);
						glVertex2f(xFish6 + 20, yFish6 - 30);
						glEnd();

						//outline of bottom fin
						glColor3f(0, 0, 0);
						glBegin(GL_LINE_LOOP);
						glVertex2f(xFish6 - 20, yFish6 - 30);
						glVertex2f(xFish6 - 30, yFish6 - 40);
						glVertex2f(xFish6 + 10, yFish6 - 40);
						glVertex2f(xFish6 + 20, yFish6 - 30);
						glEnd();

						//Vertical line on the mouth of the Fish
						glColor3f(0, 0, 0);
						glBegin(GL_LINE_STRIP);
						glVertex2f(xFish6 + 30, yFish6 + 20);
						glVertex2f(xFish6 + 30, yFish6 - 20);
						glEnd();

						//Outer Circle eye
						glColor3f(1, 1, 1);
						circle(xFish6 + 10, yFish6 + 15, 8);

						//Inner Circle eye
						glColor3f(0, 0, 0);
						circle(xFish6 + 10, yFish6 + 15, 3);

						//Number of The Fish
						glColor3f(0, 0, 0);
						vprint(xFish6 - 20, yFish6, GLUT_BITMAP_TIMES_ROMAN_24, "6");

						if (xFish7 <= winHeight && yFish7 <= winWidth)
						{
							glColor3f(0.101, 0.635, 0.250);
							glBegin(GL_POLYGON);
							glVertex2f(xFish7 - 30, yFish7 + 30);
							glVertex2f(xFish7 + 20, yFish7 + 30);
							glVertex2f(xFish7 + 20, yFish7 - 30);
							glVertex2f(xFish7 - 30, yFish7 - 30);
							glVertex2f(xFish7 - 50, yFish7);
							glEnd();

							//Outline of body
							glColor3f(0, 0, 0);
							glBegin(GL_LINE_LOOP);
							glVertex2f(xFish7 - 30, yFish7 + 30);
							glVertex2f(xFish7 + 20, yFish7 + 30);
							glVertex2f(xFish7 + 20, yFish7 - 30);
							glVertex2f(xFish7 - 30, yFish7 - 30);
							glVertex2f(xFish7 - 50, yFish7);
							glEnd();


							//Triangle Tail of the Fish
							glColor3f(0.011, 0.388, 0.113);
							glBegin(GL_TRIANGLES);
							glVertex2f(xFish7 - 50, yFish7);
							glVertex2f(xFish7 - 70, yFish7 + 30);
							glVertex2f(xFish7 - 70, yFish7 - 30);
							glEnd();

							//outline of tail
							glColor3f(0, 0, 0);
							glBegin(GL_LINE_LOOP);
							glVertex2f(xFish7 - 50, yFish7);
							glVertex2f(xFish7 - 70, yFish7 + 30);
							glVertex2f(xFish7 - 70, yFish7 - 30);
							glEnd();


							//Polygon mouth of the Fish
							glColor3f(0.784, 0.956, 0.403);
							glBegin(GL_POLYGON);
							glVertex2f(xFish7 + 20, yFish7 + 30);
							glVertex2f(xFish7 + 40, yFish7 + 10);
							glVertex2f(xFish7 + 30, yFish7);
							glVertex2f(xFish7 + 40, yFish7 - 10);
							glVertex2f(xFish7 + 20, yFish7 - 30);
							glEnd();

							//outline of mouth
							glColor3f(0, 0, 0);
							glBegin(GL_LINE_LOOP);
							glVertex2f(xFish7 + 20, yFish7 + 30);
							glVertex2f(xFish7 + 40, yFish7 + 10);
							glVertex2f(xFish7 + 30, yFish7);
							glVertex2f(xFish7 + 40, yFish7 - 10);
							glVertex2f(xFish7 + 20, yFish7 - 30);
							glEnd();

							//Rectangle on the Face of the Fish
							glColor3f(0.403, 0.956, 0.556);
							glRectf(xFish7, yFish7 + 30, xFish7 + 20, yFish7 - 30);

							//Polygon Top Fin of the Fish
							glColor3f(0.262, 0.584, 0.254);
							glBegin(GL_POLYGON);
							glVertex2f(xFish7 - 20, yFish7 + 30);
							glVertex2f(xFish7 - 30, yFish7 + 40);
							glVertex2f(xFish7 + 10, yFish7 + 40);
							glVertex2f(xFish7 + 20, yFish7 + 30);
							glEnd();

							//outline of top fin
							glColor3f(0, 0, 0);
							glBegin(GL_LINE_LOOP);
							glVertex2f(xFish7 - 20, yFish7 + 30);
							glVertex2f(xFish7 - 30, yFish7 + 40);
							glVertex2f(xFish7 + 10, yFish7 + 40);
							glVertex2f(xFish7 + 20, yFish7 + 30);
							glEnd();

							//Polygon Bottom Fin of the Fish
							glColor3f(0.262, 0.584, 0.254);
							glBegin(GL_POLYGON);
							glVertex2f(xFish7 - 20, yFish7 - 30);
							glVertex2f(xFish7 - 30, yFish7 - 40);
							glVertex2f(xFish7 + 10, yFish7 - 40);
							glVertex2f(xFish7 + 20, yFish7 - 30);
							glEnd();

							//outline of bottom fin
							glColor3f(0, 0, 0);
							glBegin(GL_LINE_LOOP);
							glVertex2f(xFish7 - 20, yFish7 - 30);
							glVertex2f(xFish7 - 30, yFish7 - 40);
							glVertex2f(xFish7 + 10, yFish7 - 40);
							glVertex2f(xFish7 + 20, yFish7 - 30);
							glEnd();

							//Vertical line on the mouth of the Fish
							glColor3f(0, 0, 0);
							glBegin(GL_LINE_STRIP);
							glVertex2f(xFish7 + 30, yFish7 + 20);
							glVertex2f(xFish7 + 30, yFish7 - 20);
							glEnd();

							//Outer Circle eye
							glColor3f(1, 1, 1);
							circle(xFish7 + 10, yFish7 + 15, 8);

							//Inner Circle eye
							glColor3f(0, 0, 0);
							circle(xFish7 + 10, yFish7 + 15, 3);

							//Number of The Fish
							glColor3f(0, 0, 0);
							vprint(xFish7 - 20, yFish7, GLUT_BITMAP_TIMES_ROMAN_24, "7");


							if (xFish8 <= winHeight && yFish8 <= winWidth)
							{
								glColor3f(0.101, 0.635, 0.250);
								glBegin(GL_POLYGON);
								glVertex2f(xFish8 - 30, yFish8 + 30);
								glVertex2f(xFish8 + 20, yFish8 + 30);
								glVertex2f(xFish8 + 20, yFish8 - 30);
								glVertex2f(xFish8 - 30, yFish8 - 30);
								glVertex2f(xFish8 - 50, yFish8);
								glEnd();

								//Outline of body
								glColor3f(0, 0, 0);
								glBegin(GL_LINE_LOOP);
								glVertex2f(xFish8 - 30, yFish8 + 30);
								glVertex2f(xFish8 + 20, yFish8 + 30);
								glVertex2f(xFish8 + 20, yFish8 - 30);
								glVertex2f(xFish8 - 30, yFish8 - 30);
								glVertex2f(xFish8 - 50, yFish8);
								glEnd();


								//Triangle Tail of the Fish
								glColor3f(0.011, 0.388, 0.113);
								glBegin(GL_TRIANGLES);
								glVertex2f(xFish8 - 50, yFish8);
								glVertex2f(xFish8 - 70, yFish8 + 30);
								glVertex2f(xFish8 - 70, yFish8 - 30);
								glEnd();

								//outline of tail
								glColor3f(0, 0, 0);
								glBegin(GL_LINE_LOOP);
								glVertex2f(xFish8 - 50, yFish8);
								glVertex2f(xFish8 - 70, yFish8 + 30);
								glVertex2f(xFish8 - 70, yFish8 - 30);
								glEnd();


								//Polygon mouth of the Fish
								glColor3f(0.784, 0.956, 0.403);
								glBegin(GL_POLYGON);
								glVertex2f(xFish8 + 20, yFish8 + 30);
								glVertex2f(xFish8 + 40, yFish8 + 10);
								glVertex2f(xFish8 + 30, yFish8);
								glVertex2f(xFish8 + 40, yFish8 - 10);
								glVertex2f(xFish8 + 20, yFish8 - 30);
								glEnd();

								//outline of mouth
								glColor3f(0, 0, 0);
								glBegin(GL_LINE_LOOP);
								glVertex2f(xFish8 + 20, yFish8 + 30);
								glVertex2f(xFish8 + 40, yFish8 + 10);
								glVertex2f(xFish8 + 30, yFish8);
								glVertex2f(xFish8 + 40, yFish8 - 10);
								glVertex2f(xFish8 + 20, yFish8 - 30);
								glEnd();

								//Rectangle on the Face of the Fish
								glColor3f(0.403, 0.956, 0.556);
								glRectf(xFish8, yFish8 + 30, xFish8 + 20, yFish8 - 30);

								//Polygon Top Fin of the Fish
								glColor3f(0.262, 0.584, 0.254);
								glBegin(GL_POLYGON);
								glVertex2f(xFish8 - 20, yFish8 + 30);
								glVertex2f(xFish8 - 30, yFish8 + 40);
								glVertex2f(xFish8 + 10, yFish8 + 40);
								glVertex2f(xFish8 + 20, yFish8 + 30);
								glEnd();

								//outline of top fin
								glColor3f(0, 0, 0);
								glBegin(GL_LINE_LOOP);
								glVertex2f(xFish8 - 20, yFish8 + 30);
								glVertex2f(xFish8 - 30, yFish8 + 40);
								glVertex2f(xFish8 + 10, yFish8 + 40);
								glVertex2f(xFish8 + 20, yFish8 + 30);
								glEnd();

								//Polygon Bottom Fin of the Fish
								glColor3f(0.262, 0.584, 0.254);
								glBegin(GL_POLYGON);
								glVertex2f(xFish8 - 20, yFish8 - 30);
								glVertex2f(xFish8 - 30, yFish8 - 40);
								glVertex2f(xFish8 + 10, yFish8 - 40);
								glVertex2f(xFish8 + 20, yFish8 - 30);
								glEnd();

								//outline of bottom fin
								glColor3f(0, 0, 0);
								glBegin(GL_LINE_LOOP);
								glVertex2f(xFish8 - 20, yFish8 - 30);
								glVertex2f(xFish8 - 30, yFish8 - 40);
								glVertex2f(xFish8 + 10, yFish8 - 40);
								glVertex2f(xFish8 + 20, yFish8 - 30);
								glEnd();

								//Vertical line on the mouth of the Fish
								glColor3f(0, 0, 0);
								glBegin(GL_LINE_STRIP);
								glVertex2f(xFish8 + 30, yFish8 + 20);
								glVertex2f(xFish8 + 30, yFish8 - 20);
								glEnd();

								//Outer Circle eye
								glColor3f(1, 1, 1);
								circle(xFish8 + 10, yFish8 + 15, 8);

								//Inner Circle eye
								glColor3f(0, 0, 0);
								circle(xFish8 + 10, yFish8 + 15, 3);

								//Number of The Fish
								glColor3f(0, 0, 0);
								vprint(xFish8 - 20, yFish8, GLUT_BITMAP_TIMES_ROMAN_24, "8");

								if (xFish9 <= winHeight && yFish9 <= winWidth)
								{
									glColor3f(0.101, 0.635, 0.250);
									glBegin(GL_POLYGON);
									glVertex2f(xFish9 - 30, yFish9 + 30);
									glVertex2f(xFish9 + 20, yFish9 + 30);
									glVertex2f(xFish9 + 20, yFish9 - 30);
									glVertex2f(xFish9 - 30, yFish9 - 30);
									glVertex2f(xFish9 - 50, yFish9);
									glEnd();

									//Outline of body
									glColor3f(0, 0, 0);
									glBegin(GL_LINE_LOOP);
									glVertex2f(xFish9 - 30, yFish9 + 30);
									glVertex2f(xFish9 + 20, yFish9 + 30);
									glVertex2f(xFish9 + 20, yFish9 - 30);
									glVertex2f(xFish9 - 30, yFish9 - 30);
									glVertex2f(xFish9 - 50, yFish9);
									glEnd();


									//Triangle Tail of the Fish
									glColor3f(0.011, 0.388, 0.113);
									glBegin(GL_TRIANGLES);
									glVertex2f(xFish9 - 50, yFish9);
									glVertex2f(xFish9 - 70, yFish9 + 30);
									glVertex2f(xFish9 - 70, yFish9 - 30);
									glEnd();

									//outline of tail
									glColor3f(0, 0, 0);
									glBegin(GL_LINE_LOOP);
									glVertex2f(xFish9 - 50, yFish9);
									glVertex2f(xFish9 - 70, yFish9 + 30);
									glVertex2f(xFish9 - 70, yFish9 - 30);
									glEnd();

									
									//Polygon mouth of the Fish
									glColor3f(0.784, 0.956, 0.403);
									glBegin(GL_POLYGON);
									glVertex2f(xFish9 + 20, yFish9 + 30);
									glVertex2f(xFish9 + 40, yFish9 + 10);
									glVertex2f(xFish9 + 30, yFish9);
									glVertex2f(xFish9 + 40, yFish9 - 10);
									glVertex2f(xFish9 + 20, yFish9 - 30);
									glEnd();

									//outline of mouth
									glColor3f(0, 0, 0);
									glBegin(GL_LINE_LOOP);
									glVertex2f(xFish9 + 20, yFish9 + 30);
									glVertex2f(xFish9 + 40, yFish9 + 10);
									glVertex2f(xFish9 + 30, yFish9);
									glVertex2f(xFish9 + 40, yFish9 - 10);
									glVertex2f(xFish9 + 20, yFish9 - 30);
									glEnd();

									//Rectangle on the Face of the Fish
									glColor3f(0.403, 0.956, 0.556);
									glRectf(xFish9, yFish9 + 30, xFish9 + 20, yFish9 - 30);

									//Polygon Top Fin of the Fish
									glColor3f(0.262, 0.584, 0.254);
									glBegin(GL_POLYGON);
									glVertex2f(xFish9 - 20, yFish9 + 30);
									glVertex2f(xFish9 - 30, yFish9 + 40);
									glVertex2f(xFish9 + 10, yFish9 + 40);
									glVertex2f(xFish9 + 20, yFish9 + 30);
									glEnd();

									//outline of top fin
									glColor3f(0, 0, 0);
									glBegin(GL_LINE_LOOP);
									glVertex2f(xFish9 - 20, yFish9 + 30);
									glVertex2f(xFish9 - 30, yFish9 + 40);
									glVertex2f(xFish9 + 10, yFish9 + 40);
									glVertex2f(xFish9 + 20, yFish9 + 30);
									glEnd();

									//Polygon Bottom Fin of the Fish
									glColor3f(0.262, 0.584, 0.254);
									glBegin(GL_POLYGON);
									glVertex2f(xFish9 - 20, yFish9 - 30);
									glVertex2f(xFish9 - 30, yFish9 - 40);
									glVertex2f(xFish9 + 10, yFish9 - 40);
									glVertex2f(xFish9 + 20, yFish9 - 30);
									glEnd();

									//outline of bottom fin
									glColor3f(0, 0, 0);
									glBegin(GL_LINE_LOOP);
									glVertex2f(xFish9 - 20, yFish9 - 30);
									glVertex2f(xFish9 - 30, yFish9 - 40);
									glVertex2f(xFish9 + 10, yFish9 - 40);
									glVertex2f(xFish9 + 20, yFish9 - 30);
									glEnd();

									//Vertical line on the mouth of the Fish
									glColor3f(0, 0, 0);
									glBegin(GL_LINE_STRIP);
									glVertex2f(xFish9 + 30, yFish9 + 20);
									glVertex2f(xFish9 + 30, yFish9 - 20);
									glEnd();

									//Outer Circle eye
									glColor3f(1, 1, 1);
									circle(xFish9 + 10, yFish9 + 15, 8);

									//Inner Circle eye
									glColor3f(0, 0, 0);
									circle(xFish9 + 10, yFish9 + 15, 3);

									//Number of The Fish
									glColor3f(0, 0, 0);
									vprint(xFish9 - 20, yFish9, GLUT_BITMAP_TIMES_ROMAN_24, "9");


									if (xFish10 <= winHeight && yFish10 <= winWidth)
									{
										glColor3f(0.101, 0.635, 0.250);
										glBegin(GL_POLYGON);
										glVertex2f(xFish10 - 30, yFish10 + 30);
										glVertex2f(xFish10 + 20, yFish10 + 30);
										glVertex2f(xFish10 + 20, yFish10 - 30);
										glVertex2f(xFish10 - 30, yFish10 - 30);
										glVertex2f(xFish10 - 50, yFish10);
										glEnd();

										//Outline of body
										glColor3f(0, 0, 0);
										glBegin(GL_LINE_LOOP);
										glVertex2f(xFish10 - 30, yFish10 + 30);
										glVertex2f(xFish10 + 20, yFish10 + 30);
										glVertex2f(xFish10 + 20, yFish10 - 30);
										glVertex2f(xFish10 - 30, yFish10 - 30);
										glVertex2f(xFish10 - 50, yFish10);
										glEnd();


										//Triangle Tail of the Fish
										glColor3f(0.011, 0.388, 0.113);
										glBegin(GL_TRIANGLES);
										glVertex2f(xFish10 - 50, yFish10);
										glVertex2f(xFish10 - 70, yFish10 + 30);
										glVertex2f(xFish10 - 70, yFish10 - 30);
										glEnd();

										//outline of tail
										glColor3f(0, 0, 0);
										glBegin(GL_LINE_LOOP);
										glVertex2f(xFish10 - 50, yFish10);
										glVertex2f(xFish10 - 70, yFish10 + 30);
										glVertex2f(xFish10 - 70, yFish10 - 30);
										glEnd();


										//Polygon mouth of the Fish
										glColor3f(0.784, 0.956, 0.403);
										glBegin(GL_POLYGON);
										glVertex2f(xFish10 + 20, yFish10 + 30);
										glVertex2f(xFish10 + 40, yFish10 + 10);
										glVertex2f(xFish10 + 30, yFish10);
										glVertex2f(xFish10 + 40, yFish10 - 10);
										glVertex2f(xFish10 + 20, yFish10 - 30);
										glEnd();

										//outline of mouth
										glColor3f(0, 0, 0);
										glBegin(GL_LINE_LOOP);
										glVertex2f(xFish10 + 20, yFish10 + 30);
										glVertex2f(xFish10 + 40, yFish10 + 10);
										glVertex2f(xFish10 + 30, yFish10);
										glVertex2f(xFish10 + 40, yFish10 - 10);
										glVertex2f(xFish10 + 20, yFish10 - 30);
										glEnd();

										//Rectangle on the Face of the Fish
										glColor3f(0.403, 0.956, 0.556);
										glRectf(xFish10, yFish10 + 30, xFish10 + 20, yFish10 - 30);

										//Polygon Top Fin of the Fish
										glColor3f(0.262, 0.584, 0.254);
										glBegin(GL_POLYGON);
										glVertex2f(xFish10 - 20, yFish10 + 30);
										glVertex2f(xFish10 - 30, yFish10 + 40);
										glVertex2f(xFish10 + 10, yFish10 + 40);
										glVertex2f(xFish10 + 20, yFish10 + 30);
										glEnd();

										//outline of top fin
										glColor3f(0, 0, 0);
										glBegin(GL_LINE_LOOP);
										glVertex2f(xFish10 - 20, yFish10 + 30);
										glVertex2f(xFish10 - 30, yFish10 + 40);
										glVertex2f(xFish10 + 10, yFish10 + 40);
										glVertex2f(xFish10 + 20, yFish10 + 30);
										glEnd();

										//Polygon Bottom Fin of the Fish
										glColor3f(0.262, 0.584, 0.254);
										glBegin(GL_POLYGON);
										glVertex2f(xFish10 - 20, yFish10 - 30);
										glVertex2f(xFish10 - 30, yFish10 - 40);
										glVertex2f(xFish10 + 10, yFish10 - 40);
										glVertex2f(xFish10 + 20, yFish10 - 30);
										glEnd();

										//outline of bottom fin
										glColor3f(0, 0, 0);
										glBegin(GL_LINE_LOOP);
										glVertex2f(xFish10 - 20, yFish10 - 30);
										glVertex2f(xFish10 - 30, yFish10 - 40);
										glVertex2f(xFish10 + 10, yFish10 - 40);
										glVertex2f(xFish10 + 20, yFish10 - 30);
										glEnd();

										//Vertical line on the mouth of the Fish
										glColor3f(0, 0, 0);
										glBegin(GL_LINE_STRIP);
										glVertex2f(xFish10 + 30, yFish10 + 20);
										glVertex2f(xFish10 + 30, yFish10 - 20);
										glEnd();

										//Outer Circle eye
										glColor3f(1, 1, 1);
										circle(xFish10 + 10, yFish10 + 15, 8);

										//Inner Circle eye
										glColor3f(0, 0, 0);
										circle(xFish10 + 10, yFish10 + 15, 3);

										//Number of The Fish
										glColor3f(0, 0, 0);
										vprint(xFish10 - 20, yFish10, GLUT_BITMAP_TIMES_ROMAN_24, "10");

									}

								}

							}

						}

					}

				}

			}

		}

	}

}


void display()
{
	glClearColor(0.945, 0.282, 0.035, 0); //setting the desirable color to show the sunset sky as a background
	glClear(GL_COLOR_BUFFER_BIT);

	// This is the sun CIRCLE
	glColor3f(0.917, 0.909, 0.062);
	circle(0, 0, 315);

	//This is the seabed QUAD
	glColor3f(0.301, 0.105, 0);
	glBegin(GL_QUADS);
	glVertex2f(-(winWidth / 2), -292.5);
	glVertex2f((winWidth / 2), -292.5);
	glVertex2f((winWidth / 2), -325);
	glVertex2f(-(winWidth / 2), -325);
	glEnd();


	//This is the sea QUAD
	glColor3f(0.152, 0.309, 0.768);
	glBegin(GL_QUADS);
	glVertex2f(-(winWidth / 2), 195);
	glVertex2f((winWidth / 2), 195);
	glVertex2f((winWidth / 2), -292.5);
	glVertex2f(-(winWidth / 2), -292.5);
	glEnd();


	//This is the boat base QUAD
	glColor3f(0.658, 0.180, 0);
	glBegin(GL_QUADS);
	glVertex2f(-420, 195);
	glVertex2f(-440, 227.5);
	glVertex2f(-180, 227.5);
	glVertex2f(-200, 195);
	glEnd();

	//This is the boat base outline
	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-420, 195);
	glVertex2f(-440, 227.5);
	glVertex2f(-180, 227.5);
	glVertex2f(-200, 195);
	glEnd();


	//This is the boat sail Triangle
	glColor3f(0.086, 0.635, 0.243);
	glBegin(GL_TRIANGLES);
	glVertex2f(-210, 230);
	glVertex2f(-410, 230);
	glVertex2f(-300, 308.5);
	glEnd();

	//This is the boat sail outline
	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-210, 230);
	glVertex2f(-410, 230);
	glVertex2f(-300, 308.5);
	glVertex2f(-300, 308.5);
	glEnd();


	//This is the boat sail Rod rectangle
	glColor3f(0.027, 0.031, 0.027);
	glRectf(-305, 227.5, -295, 315);

	//bubbles in the background
	glColor3f(0.572, 0.792, 0.827);
	circle(-570, -110, 6.5);

	glColor3f(0.572, 0.792, 0.827);
	circle(-540, -75, 6);

	glColor3f(0.572, 0.792, 0.827);
	circle(-440, -120, 4);

	glColor3f(0.572, 0.792, 0.827);
	circle(-385, -150, 6.75);


	//Coral QUADS
	glColor3f(0.905, 0.596, 0.450);
	glBegin(GL_QUADS);
	glVertex2f(-550, -292.5);
	glVertex2f(-570, -161);
	glVertex2f(-540, -148);
	glVertex2f(-530, -292.5);
	glEnd();

	glColor3f(0.803, 0.419, 0.337);
	glBegin(GL_QUADS);
	glVertex2f(-530, -292.5);
	glVertex2f(-500, -120);
	glVertex2f(-460, -100);
	glVertex2f(-515, -292.5);
	glEnd();

	glColor3f(0.935, 0.596, 0.450);
	glBegin(GL_QUADS);
	glVertex2f(-500, -292.5);
	glVertex2f(-460, -175);
	glVertex2f(-435, -180);
	glVertex2f(-480, -292.5);
	glEnd();

	glColor3f(0.803, 0.419, 0.337);
	glBegin(GL_QUADS);
	glVertex2f(405, -292.5);
	glVertex2f(380, -164);
	glVertex2f(420, -150);
	glVertex2f(440, -292.5);
	glEnd();

	glColor3f(0.874, 0.474, 0.286);
	glBegin(GL_QUADS);
	glVertex2f(440, -292.5);
	glVertex2f(450, -110);
	glVertex2f(485, -115);
	glVertex2f(460, -292.5);
	glEnd();

	glColor3f(0.874, 0.474, 0.286);
	glBegin(GL_QUADS);
	glVertex2f(465, -292.5);
	glVertex2f(520, -185);
	glVertex2f(562, -192);
	glVertex2f(490, -292.5);
	glEnd();

	//Coral Quads outlines
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-550, -292.5);
	glVertex2f(-570, -161);
	glVertex2f(-540, -148);
	glVertex2f(-530, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-530, -292.5);
	glVertex2f(-500, -120);
	glVertex2f(-460, -100);
	glVertex2f(-515, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-500, -292.5);
	glVertex2f(-460, -175);
	glVertex2f(-435, -180);
	glVertex2f(-480, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(405, -292.5);
	glVertex2f(380, -164);
	glVertex2f(420, -150);
	glVertex2f(440, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(440, -292.5);
	glVertex2f(450, -110);
	glVertex2f(485, -115);
	glVertex2f(460, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(465, -292.5);
	glVertex2f(520, -185);
	glVertex2f(562, -192);
	glVertex2f(490, -292.5);
	glEnd();

	//Coral Triangle Fan
	glColor3f(0.831, 0.168, 0.176);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(-120, -292.5);
	glVertex2f(-240, -292.5);
	glVertex2f(-280, -269);
	glVertex2f(-240, -245);
	glVertex2f(-255, -210);
	glVertex2f(-205, -218);
	glVertex2f(-200, -185);
	glVertex2f(-160, -195);
	glVertex2f(-120, -162.5);
	glVertex2f(-80, -195);
	glVertex2f(-40, -185);
	glVertex2f(-35, -218);
	glVertex2f(15, -210);
	glVertex2f(0, -245);
	glVertex2f(40, -269);
	glVertex2f(0, -292.5);
	glEnd();

	//Coral Fan outlines
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-240, -292.5);
	glVertex2f(-280, -269);
	glVertex2f(-240, -245);
	glVertex2f(-120, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-240, -245);
	glVertex2f(-255, -210);
	glVertex2f(-205, -218);
	glVertex2f(-120, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-205, -218);
	glVertex2f(-200, -185);
	glVertex2f(-160, -195);
	glVertex2f(-120, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-160, -195);
	glVertex2f(-120, -162.5);
	glVertex2f(-80, -195);
	glVertex2f(-120, -292.5);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-80, -195);
	glVertex2f(-40, -185);
	glVertex2f(-35, -218);
	glVertex2f(-120, -292.5);
	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-35, -218);
	glVertex2f(15, -210);
	glVertex2f(0, -245);
	glVertex2f(-120, -292.5);
	glEnd();


	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0, -245);
	glVertex2f(40, -269);
	glVertex2f(0, -292.5);
	glVertex2f(-120, -292.5);
	glEnd();


	//more bubbles in the background
	glColor3f(0.572, 0.792, 0.827);
	circle(-280, -195, 6.5);

	glColor3f(0.572, 0.792, 0.827);
	circle(-240, -162, 6);

	glColor3f(0.572, 0.792, 0.827);
	circle(-160, -90, 6);

	glColor3f(0.572, 0.792, 0.827);
	circle(-240, -112, 5);

	glColor3f(0.572, 0.792, 0.827);
	circle(-120, -135, 4);

	glColor3f(0.572, 0.792, 0.827);
	circle(-40, -150, 6);

	glColor3f(0.572, 0.792, 0.827);
	circle(370, -227, 6);

	glColor3f(0.572, 0.792, 0.827);
	circle(385, -140, 6.75);

	glColor3f(0.572, 0.792, 0.827);
	circle(310, -180, 5);

	glColor3f(0.572, 0.792, 0.827);
	circle(500, -100, 4);

	glColor3f(0.572, 0.792, 0.827);
	circle(530, -157, 6);

	glColor3f(0.572, 0.792, 0.827);
	circle(580, -178, 5);

	glColor3f(0.572, 0.792, 0.827);
	circle(520, -97, 6);

	//These are the submarine shapes
	glColor3f(0.133, 0.274, 0.368);   //rectangle
	glRectf(120, 0, 320, 65);
	glColor3f(0.105, 0.274, 0.274);   //Quad
	glBegin(GL_QUADS);
	glVertex2f(320, 65);
	glVertex2f(355, 65);
	glVertex2f(400, 0);
	glVertex2f(320, 0);
	glEnd();
	glColor3f(0.105, 0.274, 0.274);   //rectangle
	glRectf(80, 0, 120, 16);
	glColor3f(0.003, 0.152, 0.152);   //triangle
	glBegin(GL_TRIANGLES);
	glVertex2f(120, 16);
	glVertex2f(90, 16);
	glVertex2f(120, 32.5);
	glEnd();
	glColor3f(0.105, 0.274, 0.274);   //Quad
	glBegin(GL_QUADS);
	glVertex2f(320, 65);
	glVertex2f(310, 120);
	glVertex2f(248, 120);
	glVertex2f(208, 65);
	glEnd();
	glColor3f(0.003, 0.152, 0.152);   //rectangle
	glRectf(302, 120, 295, 155);
	glColor3f(0.682, 0.956, 0.956);   //rectangle Window1
	glRectf(160, 32.5, 200, 48.5);
	glColor3f(0.682, 0.956, 0.956);   //rectangle Window2
	glRectf(240, 32.5, 280, 48.5);
	glColor3f(0.074, 0.086, 0.086);   //circle Window
	circle(278, 92.5, 17);
	glColor3f(0.572, 0.792, 0.827);   //circle Window
	circle(278, 92.5, 15);
	glColor3f(0.572, 0.792, 0.827);   //submarine bubbles
	circle(100, 50, 6.5);
	glColor3f(0.572, 0.792, 0.827);
	circle(80, 70, 5);
	glColor3f(0.572, 0.792, 0.827);
	circle(85, 27, 3.5);
	glColor3f(0, 0, 0);               //lines
	glBegin(GL_LINE_STRIP);
	glVertex2f(280, 120);
	glVertex2f(280, 150);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(310, 12);
	glVertex2f(330, 12);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(310, 24);
	glVertex2f(330, 24);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(310, 36);
	glVertex2f(330, 36);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex2f(310, 48);
	glVertex2f(330, 48);
	glEnd();


	//These are the submarine outlines
	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(320, 65);
	glVertex2f(355, 65);
	glVertex2f(400, 0);
	glVertex2f(320, 0);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(120, 16);
	glVertex2f(90, 16);
	glVertex2f(120, 32.5);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(320, 65);
	glVertex2f(310, 120);
	glVertex2f(248, 120);
	glVertex2f(208, 65);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(120, 0);
	glVertex2f(120, 65);
	glVertex2f(320, 65);
	glVertex2f(320, 0);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(80, 0);
	glVertex2f(80, 16);
	glVertex2f(120, 16);
	glVertex2f(120, 0);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(302, 120);
	glVertex2f(302, 155);
	glVertex2f(295, 155);
	glVertex2f(295, 120);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(160, 32.5);
	glVertex2f(160, 48.5);
	glVertex2f(200, 48.5);
	glVertex2f(200, 32.5);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	glBegin(GL_LINE_LOOP);
	glVertex2f(240, 32.5);
	glVertex2f(240, 48.5);
	glVertex2f(280, 48.5);
	glVertex2f(280, 32.5);
	glEnd();

	glColor3f(0.027, 0.031, 0.027);
	vprint((winWidth / 2) - 110, -((winHeight / 2) - 15), GLUT_BITMAP_HELVETICA_18, "(%4d, %4d)", wx, wy);   //displaying cursor position at the bottom right of the screen

	//Label with name and ID
	glColor3f(0.8, 0.741, 0.741);
	glRectf(-((winWidth / 2) - 10), (winHeight / 2) - 8, -((winWidth / 2) - 235), (winHeight / 2) - 55);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-((winWidth / 2) - 10), (winHeight / 2) - 8);
	glVertex2f(-((winWidth / 2) - 10), (winHeight / 2) - 55);
	glVertex2f(-((winWidth / 2) - 235), (winHeight / 2) - 55);
	glVertex2f(-((winWidth / 2) - 235), (winHeight / 2) - 8);
	glEnd();
	glColor3f(0.2, 0.1, 0.2);
	vprint(-((winWidth / 2) - 20), (winHeight / 2) - 32.5, GLUT_BITMAP_TIMES_ROMAN_24, "SUHEERA TANVIR");
	vprint(-((winWidth / 2) - 20), (winHeight / 2) - 50, GLUT_BITMAP_HELVETICA_18, "            21801211");

	drawFish();  

	glutSwapBuffers();

}

void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	glutPostRedisplay();
}


void onSpecialKeyDown(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: up = true; break;
	case GLUT_KEY_DOWN: down = true; break;
	case GLUT_KEY_LEFT: left = true; break;
	case GLUT_KEY_RIGHT: right = true; break;

	}
	glutPostRedisplay();
}


void onSpecialKeyUp(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}
	glutPostRedisplay();
}



void onClick(int button, int stat, int x, int y)
{
	//last two conditions are for restricting area where you can click to make object. MEaning, only  making an object when the user clicks in the water, not above or below
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish >= winWidth/2 || xFish <= -(winWidth/2) && yFish >= winHeight/2 || yFish <= -(winHeight / 2)) && fishCount == 0 )
	{

		xFish = x - winWidth / 2;   
		yFish = winHeight / 2 - y;
		fishCount++;
		return;

	}
	//if statements for the remaining fishes
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish2 >= winWidth / 2 || xFish2 <= -(winWidth / 2) && yFish2 >= winHeight / 2 || yFish2 <= -(winHeight / 2)) && fishCount == 1 )
	{
		xFish2 = x - winWidth / 2;   
		yFish2 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish3 >= winWidth / 2 || xFish3 <= -(winWidth / 2) && yFish3 >= winHeight / 2 || yFish3 <= -(winHeight / 2)) && fishCount == 2)
	{
		xFish3 = x - winWidth / 2;   
		yFish3 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish4 >= winWidth / 2 || xFish4 <= -(winWidth / 2) && yFish4 >= winHeight / 2 || yFish4 <= -(winHeight / 2)) && fishCount == 3)
	{
		xFish4 = x - winWidth / 2;   
		yFish4 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish5 >= winWidth / 2 || xFish5 <= -(winWidth / 2) && yFish5 >= winHeight / 2 || yFish5 <= -(winHeight / 2)) && fishCount == 4)
	{
		xFish5 = x - winWidth / 2;   
		yFish5 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish6 >= winWidth / 2 || xFish6 <= -(winWidth / 2) && yFish6 >= winHeight / 2 || yFish6 <= -(winHeight / 2)) && fishCount == 5)
	{
		xFish6 = x - winWidth / 2;   
		yFish6 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish7 >= winWidth / 2 || xFish7 <= -(winWidth / 2) && yFish7 >= winHeight / 2 || yFish7 <= -(winHeight / 2)) && fishCount == 6)
	{
		xFish7 = x - winWidth / 2;   
		yFish7 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish8 >= winWidth / 2 || xFish8 <= -(winWidth / 2) && yFish8 >= winHeight / 2 || yFish8 <= -(winHeight / 2)) && fishCount == 7)
	{
		xFish8 = x - winWidth / 2;   
		yFish8 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish9 >= winWidth / 2 || xFish9 <= -(winWidth / 2) && yFish9 >= winHeight / 2 || yFish9 <= -(winHeight / 2)) && fishCount == 8)
	{
		xFish9 = x - winWidth / 2;  
		yFish9 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && (winHeight / 2 - y) <= 155 && (winHeight / 2 - y) >= -258.5 && (xFish10 >= winWidth / 2 || xFish10 <= -(winWidth / 2) && yFish10 >= winHeight / 2 || yFish10 <= -(winHeight / 2)) && fishCount == 9)
	{
		xFish10 = x - winWidth / 2;   
		yFish10 = winHeight / 2 - y;
		fishCount++;
		return;
	}
	//these remaining conditions are to ensure that clicking ONLY the respective object itself makes it move. Nowhere else.
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish + 40) && ((x - winWidth / 2) > xFish - 40) && ((winHeight / 2 - y) < yFish + 40) && ((winHeight / 2 - y) > yFish - 40))
		activeTimer = !activeTimer;   
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish2 + 40) && ((x - winWidth / 2) > xFish2 - 40) && ((winHeight / 2 - y) < yFish2 + 40) && ((winHeight / 2 - y) > yFish2 - 40))
		activeTimer2 = !activeTimer2;  
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish3 + 40) && ((x - winWidth / 2) > xFish3 - 40) && ((winHeight / 2 - y) < yFish3 + 40) && ((winHeight / 2 - y) > yFish3 - 40))
		activeTimer3 = !activeTimer3;
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish4 + 40) && ((x - winWidth / 2) > xFish4 - 40) && ((winHeight / 2 - y) < yFish4 + 40) && ((winHeight / 2 - y) > yFish4 - 40))
		activeTimer4 = !activeTimer4;
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish5 + 40) && ((x - winWidth / 2) > xFish5 - 40) && ((winHeight / 2 - y) < yFish5 + 40) && ((winHeight / 2 - y) > yFish5 - 40))
		activeTimer5 = !activeTimer5;
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish6 + 40) && ((x - winWidth / 2) > xFish6 - 40) && ((winHeight / 2 - y) < yFish6 + 40) && ((winHeight / 2 - y) > yFish6 - 40))
		activeTimer6 = !activeTimer6;
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish7 + 40) && ((x - winWidth / 2) > xFish7 - 40) && ((winHeight / 2 - y) < yFish7 + 40) && ((winHeight / 2 - y) > yFish7 - 40))
		activeTimer7 = !activeTimer7;
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish8 + 40) && ((x - winWidth / 2) > xFish8 - 40) && ((winHeight / 2 - y) < yFish8 + 40) && ((winHeight / 2 - y) > yFish8 - 40))
		activeTimer8 = !activeTimer8;
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish9 + 40) && ((x - winWidth / 2) > xFish9 - 40) && ((winHeight / 2 - y) < yFish9 + 40) && ((winHeight / 2 - y) > yFish9 - 40))
		activeTimer9 = !activeTimer9;
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN && ((x - winWidth / 2) < xFish10 + 40) && ((x - winWidth / 2) > xFish10 - 40) && ((winHeight / 2 - y) < yFish10 + 40) && ((winHeight / 2 - y) > yFish10 - 40))
		activeTimer10 = !activeTimer10;
	
	glutPostRedisplay();
}

// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
void onResize(int w, int h) {    //this function helps with resize
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); 
}

void onMoveDown(int x, int y)
{

	glutPostRedisplay();
}

void onMove(int x, int y)  //for help in displaying coordinates
{
	glColor3f(1, 1, 1);

	wx = x - winWidth / 2;   //adapt to resize
	wy = winHeight / 2 - y;

	glutPostRedisplay();
}


#if TIMER_ON == 1
void onTimer(int v) {
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);

	if (activeTimer)
	{
		if (-xFish + 40 / 2 < winWidth / 2)
			xFish++;   //moving the object forward, animating it. 
		if (xFish - 40 >= winWidth / 2)   //condition to move moving object to the beginning of the screen if it reaches the end of the window
		{
			xFish = -((winWidth / 2) - 40);
			xFish++;
		}

	}
	//The remaining IF statements are for the other fishes

	if (activeTimer2)
	{
		if (-xFish2 + 40 / 2 < winWidth / 2)
			xFish2++;   

		if (xFish2 - 40 >= winWidth / 2)   
		{
			xFish2 = -((winWidth / 2) - 40);
			xFish2++;
		}
	}

	if (activeTimer3)
	{
		if (-xFish3 + 40 / 2 < winWidth / 2)
			xFish3++;   

		if (xFish3 - 40 >= winWidth / 2)   
		{
			xFish3 = -((winWidth / 2) - 40);
			xFish3++;
		}
	
	}
	if (activeTimer4)
	{
		if (-xFish4 + 40 / 2 < winWidth / 2)
			xFish4++;   

		if (xFish4 - 40 >= winWidth / 2)   
		{
			xFish4 = -((winWidth / 2) - 40);
			xFish4++;
		}

	}
	if (activeTimer5)
	{
		if (-xFish5 + 40 / 2 < winWidth / 2)
			xFish5++;   

		if (xFish5 - 40 >= winWidth / 2)   
		{
			xFish5 = -((winWidth / 2) - 40);
			xFish5++;
		}    

	}
	if (activeTimer6)
	{
		if (-xFish6 + 40 / 2 < winWidth / 2)
			xFish6++;   

		if (xFish6 - 40 >= winWidth / 2)   
		{
			xFish6 = -((winWidth / 2) - 40);
			xFish6++;
		}

	}
	if (activeTimer7)
	{
		if (-xFish7 + 40 / 2 < winWidth / 2)
			xFish7++;   

		if (xFish7 - 40 >= winWidth / 2)   
		{
			xFish7 = -((winWidth / 2) - 40);
			xFish7++;
		}

	}
	if (activeTimer8)
	{
		if (-xFish8 + 40 / 2 < winWidth / 2)
			xFish8++;   

		if (xFish8 - 40 >= winWidth / 2)   
		{
			xFish8 = -((winWidth / 2) - 40);
			xFish8++;
		}

	}
	if (activeTimer9)
	{
		if (-xFish9 + 40 / 2 < winWidth / 2)
			xFish9++;   

		if (xFish9 - 40 >= winWidth / 2)   
		{
			xFish9 = -((winWidth / 2) - 40);
			xFish9++;
		}

	}
	if (activeTimer10)
	{
		if (-xFish10 + 40 / 2 < winWidth / 2)
			xFish10++;   

		if (xFish10 - 40 >= winWidth / 2)  
		{
			xFish10 = -((winWidth / 2) - 40);
			xFish10++;
		} 

	}

	glutPostRedisplay(); 
}
#endif

void init()
{

}


void main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Catch the FISH!!");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	
	// keyboard registration

	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	// mouse registration
	
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	init();

	glutMainLoop();
}
