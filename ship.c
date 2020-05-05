/*  ship.c
 *
 *  Created on: 16th April 2020
 *  Author: Dhruv Shetty, Shiva Reddy
 *
 *  Description: 
 *  1st Frame: Ship crosses view frame
 *  2nd Frame: Ship comes in contact with Iceberg
 *  3rd Frame: Ship starts sinking
 */

#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<time.h>
#include<GL/gl.h>


struct timespec tim, tim2;

void ice();
void display1();
void display2();
void display3();
void ship();
void water();

int day=1,plane=0,comet=0;

GLint a=0,b=0,c=0,d=0,e=0,f=0,g=500,h=600,x=0,i=0;
GLfloat theta=0.0;
float p=0.0,n=0.0,m=0.0,o=0.0,q=0.0;

void update(int value)
{
	// a used for ship movement
	a+=20.0;
	// n,o used for plane movement
	n-=20;
	o+=2.5;
	// q used for comet movement
	q+=20;
	// m used for cloud movement
	m+=1;
	glutPostRedisplay();
	glutTimerFunc(200,update,0);	// 200ms gap between further movements
}

// Turning on an individual pixel
void draw_pixel(GLint cx, GLint cy)
{

	glBegin(GL_POINTS);
		glVertex2i(cx,cy);
	glEnd();
}

// Drawing a circle using 8 way symmetry
void plotpixels(GLint h,GLint k, GLint x,GLint y)
{
	draw_pixel(x+h,y+k);
	draw_pixel(-x+h,y+k);
	draw_pixel(x+h,-y+k);
	draw_pixel(-x+h,-y+k);
	draw_pixel(y+h,x+k);
	draw_pixel(-y+h,x+k);
	draw_pixel(y+h,-x+k);
	draw_pixel(-y+h,-x+k);
}

// h-> x coordinate, k-> y coordinate, r-> radius of circle
void draw_circle(GLint h, GLint k, GLint r)
{
	// r changes to create a solid circle
	GLint d=1-r, x=0, y=r;
	while(y>x)
	{
		plotpixels(h,k,x,y);
		if(d<0) d+=2*x+3;
		else
		{
			d+=2*(x-y)+5;
			--y;
		}
		++x;
	}
	plotpixels(h,k,x,y);
}



void draw_object(){
	
	int l;
	if(day==1) {
		// Day Sky
		glColor3f(0.0, 1.0, 1.0);
		glBegin(GL_POLYGON);	// Inputs in Anti-Clockwise direction
		glVertex2f(0,100);	// Bottom Left Point
		glVertex2f(0,1500);	// Top Left
		glVertex2f(1100,100);	// Bottom Right
		glVertex2f(1100,1500);	// Top Right
		glEnd();

		// Sun
		for(l=0;l<=35;l++)
		{
				glColor3f(1.0,0.9,0.0);
				draw_circle(100,625,l);
		}


		// Plane
		if(plane==1){
				// Body of the plane
				glColor3f(1.0,0.0,0.0);
				glBegin(GL_POLYGON);
				glVertex2f(925+n,625+o);
				glVertex2f(950+n,640+o);
				glVertex2f(1015+n,640+o);
				glVertex2f(1030+n,650+o);
				glVertex2f(1050+n,650+o);
				glVertex2f(1010+n,625+o);
				glEnd();
				
				// Wings of the plane
				glColor3f(0.8,0.8,0.8);
				glBegin(GL_LINE_LOOP);
				glVertex2f(925+n,625+o);
				glVertex2f(950+n,640+o);
				glVertex2f(1015+n,640+o);
				glVertex2f(1030+n,650+o);
				glVertex2f(1050+n,650+o);
				glVertex2f(1010+n,625+o);
				glEnd();	
		}
		// Cloud 1
		for(l=0;l<=20;l++)
		{
			glColor3f(1.0,1.0,1.0);
			draw_circle(260+m,625,l);

		}

		for(l=0;l<=35;l++)
		{
			glColor3f(1.0,1.0,1.0);
			draw_circle(300+m,625,l);
			draw_circle(325+m,625,l);
		}

		for(l=0;l<=20;l++)
		{
			glColor3f(1.0,1.0,1.0);
			draw_circle(365+m,625,l);
		}

		// Cloud 2
		for(l=0;l<=20;l++)
		{
			glColor3f(1.0,1.0,1.0);
			draw_circle(570+m,615,l);
		}
		
		for(l=0;l<=35;l++)
		{
			glColor3f(1.0,1.0,1.0);
			draw_circle(610+m,615,l);
			draw_circle(635+m,615,l);
			draw_circle(670+m,615,l);
		}

		for(l=0;l<=20;l++)
		{
			glColor3f(1.0,1.0,1.0);
			draw_circle(700+m,615,l);
		}
	}


	else {
		// Night Sky
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_POLYGON);	// Inputs in Anti-Clockwise direction
		glVertex2f(0,100);	// Bottom Left Point
		glVertex2f(0,1500);	// Top Left
		glVertex2f(1100,100);	// Bottom Right
		glVertex2f(1100,1500);	// Top Right
		glEnd();

		// Moon
		int l;
		for(l=0;l<=35;l++)
		{
			glColor3f(1.0,1.0,1.0);
			draw_circle(100,625,l);
		}

		// Star1
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(575,653);
		glVertex2f(570,645);
		glVertex2f(580,645);
		glVertex2f(575,642);
		glVertex2f(570,650);
		glVertex2f(580,650);
		glEnd();

		// Star2
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(975,643);
		glVertex2f(970,635);
		glVertex2f(980,635);
		glVertex2f(975,632);
		glVertex2f(970,640);
		glVertex2f(980,640);
		glEnd();

		// Star3
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(875,543);
		glVertex2f(870,535);
		glVertex2f(880,535);
		glVertex2f(875,532);
		glVertex2f(870,540);
		glVertex2f(880,540);
		glEnd();

		// Star4
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(375,598);
		glVertex2f(370,590);
		glVertex2f(380,590);
		glVertex2f(375,587);
		glVertex2f(370,595);
		glVertex2f(380,595);
		glEnd();

		// Star5
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(750,628);
		glVertex2f(745,620);
		glVertex2f(755,620);
		glVertex2f(750,618);
		glVertex2f(745,625);
		glVertex2f(755,625);
		glEnd();

		// Star6
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(200,628);
		glVertex2f(195,620);
		glVertex2f(205,620);
		glVertex2f(200,618);
		glVertex2f(195,625);
		glVertex2f(205,625);
		glEnd();

		// Star7
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(100,528);
		glVertex2f(95,520);
		glVertex2f(105,520);
		glVertex2f(100,518);
		glVertex2f(95,525);
		glVertex2f(105,525);
		glEnd();

		// Star8
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(300,468);
		glVertex2f(295,460);
		glVertex2f(305,460);
		glVertex2f(300,458);
		glVertex2f(295,465);
		glVertex2f(305,465);
		glEnd();

		// Star9
		glColor3f(1.0,1.0,1.0);
		glBegin(GL_TRIANGLES);
		glVertex2f(500,543);
		glVertex2f(495,535);
		glVertex2f(505,535);
		glVertex2f(500,532);
		glVertex2f(495,540);
		glVertex2f(505,540);
		glEnd();


		// Drawing a comet structure
		if(comet==1){
			for(l=0;l<=7;l++)
			{
				glColor3f(1.0,1.0,1.0);
				draw_circle(300+q,675,l);
			}
			glColor3f(1.0,1.0,1.0);
			glBegin(GL_TRIANGLES);
			glVertex2f(200+q,675);
			glVertex2f(300+q,682);
			glVertex2f(300+q,668);
			glEnd();
		}
	}
}

// Doc: https://www.opengl.org/resources/libraries/glut/spec3/node49.html
// key-> ASCII value of character input, x&y-> Mouse position
void keyboardFunc( unsigned char key, int x, int y )
{
	switch( key )
	{
		case 'd':
		case 'D':
			day=1;
			break;

		case 'n':
		case 'N':
			day=0;
			break;
	 };
}

void main_menu(int index)
{
	switch(index)
	{
	case 1:
	if(index==1)
	 {
		plane=1;
		o=n=0.0;
	 }
	break;

	case 2:
	if(index==2)
	 {
		comet=1;
		 q=0.0;
	 }
	break;
	}
}




// Displaying 3 cases
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_object();	
	display1();
	
	// Ship and Ice in Frame
	if(a>950)
	{
		b+=20;
		draw_object();
		display2();
		
	}
	// Time delay after ship hits ice
	if(b==180)
	{
		tim.tv_sec = 2;
		tim.tv_nsec = 500000000L;
		// int nanosleep(const struct timespec *req, struct timespec *rem)
		// Doc: http://man7.org/linux/man-pages/man2/nanosleep.2.html
		nanosleep(&tim , &tim2);	
	}
	// Ship starts sinking
	if(b>250)
	{

		c+=10;
		draw_object();
		display3();
	}
	glFlush();
	glutSwapBuffers();	// Indicating end of frame, swap for next frame
}


void display1()
{
	// glPushMatrix copies the top matrix and pushes it onto the stack
	// glPopMatrix pops the top matrix off the stack
	glPushMatrix();
	glTranslated(a,75,0.0);
	ship();
	glPopMatrix();
	water();
}

void display2()
{	
	// glCLear() is not added since we want the previous fram to continue (background)
	ice();
	glPushMatrix();
	glTranslated(b,75,0.0);
	ship();
	glPopMatrix();
	water();
}

void display3()
{
	x-=1;
	ice();
	glPushMatrix();	
	glTranslated(c,100+x*5,0.0);
	glRotated(-15,0,0,1);
	ship();	
	glPopMatrix();
	water();
}

/* DRAW WATER */
void water()
{

	glColor3f(0.0, 0.0, 0.5);
	glBegin(GL_POLYGON);
		glVertex2f(0,0);
		glVertex2f(1000,0);
		glVertex2f(1000,100);
		glVertex2f(0,100);
	glEnd();
}

/* TO DRAW SHIP */
void ship()
{
	glScaled(20,20,0);
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(3.5,5.5);
		glVertex2f(3.5,8.5);
		glVertex2f(19.5,8.5);
		glVertex2f(19.5,5.5);
	glEnd();
	glColor3f(0.1,0.1,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(1,5.5);
		glVertex2f(4,1);
		glVertex2f(19,1);
		glVertex2f(21.5,5.5);
	glEnd();
	glColor3f(0.7,0.4,0.2);
	glBegin(GL_POLYGON);
		glVertex2f(4,5.5);
		glVertex2f(4,8);
		glVertex2f(5,8);
		glVertex2f(5,5.5);
	glEnd();
	glColor3f(0.9,0.9,0.9);
	glBegin(GL_POLYGON);
		glVertex2f(7,7.5);
		glVertex2f(7,8);
		glVertex2f(10,8);
		glVertex2f(10,7.5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(11.5,7.5);
		glVertex2f(11.5,8);
		glVertex2f(15,8);
		glVertex2f(15,7.5);
	glEnd();
	glBegin(GL_POLYGON);
		glVertex2f(16,7.5);
		glVertex2f(16,8);
		glVertex2f(19,8);
		glVertex2f(19,7.5);
	glEnd();
	glColor3f(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex2f(4.5,8.5);
		glVertex2f(4.5,10);
		glVertex2f(18.5,10);
		glVertex2f(18.5,8.5);
	glEnd();
	glColor3f(0.1,0.1,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(5.5,10);
		glVertex2f(5.5,12.9);
		glVertex2f(7,12.9);
		glVertex2f(7,10);
	glEnd();
	glColor3f(0.9,0.5,0.2);
	glBegin(GL_POLYGON);
		glVertex2f(5.5,12.9);
		glVertex2f(5.5,13.5);
		glVertex2f(7,13.5);
		glVertex2f(7,12.9);
	glEnd();
	glColor3f(0.1,0.1,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(8.5,10);
		glVertex2f(8.5,12.9);
		glVertex2f(10,12.9);
		glVertex2f(10,10);
	glEnd();
	glColor3f(0.9,0.5,0.2);
	glBegin(GL_POLYGON);
		glVertex2f(8.5,12.9);
		glVertex2f(8.5,13.5);
		glVertex2f(10,13.5);
		glVertex2f(10,12.9);
	glEnd();
	glColor3f(0.1,0.1,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(11.5,10);
		glVertex2f(11.5,12.9);
		glVertex2f(13,12.9);
		glVertex2f(13,10);
	glEnd();
	glColor3f(0.9,0.5,0.2);
	glBegin(GL_POLYGON);
		glVertex2f(11.5,12.9);
		glVertex2f(11.5,13.5);
		glVertex2f(13,13.5);
		glVertex2f(13,12.9);
	glEnd();
	glColor3f(0.1,0.1,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(14.5,10);
		glVertex2f(14.5,12.9);
		glVertex2f(16,12.9);
		glVertex2f(16,10);
	glEnd();
	glColor3f(0.9,0.5,0.2);
	glBegin(GL_POLYGON);
		glVertex2f(14.5,12.9);
		glVertex2f(14.5,13.5);
		glVertex2f(16,13.5);
		glVertex2f(16,12.9);
	glEnd();
	glColor3f(0.1,0.1,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.5,5.5);
		glVertex2f(1.5,6.5);
		glVertex2f(2,6.2);
		glVertex2f(3,6.2);
		glVertex2f(3.5,6.5);
		glVertex2f(3.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(3.5,5.5);
		glVertex2f(3.5,6.5);
		glVertex2f(4,6.2);
		glVertex2f(5,6.2);
		glVertex2f(5.5,6.5);
		glVertex2f(5.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(5.5,5.5);
		glVertex2f(5.5,6.5);
		glVertex2f(6,6.2);
		glVertex2f(7,6.2);
		glVertex2f(7.5,6.5);
		glVertex2f(7.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(7.5,5.5);
		glVertex2f(7.5,6.5);
		glVertex2f(8,6.2);
		glVertex2f(9,6.2);
		glVertex2f(9.5,6.5);
		glVertex2f(9.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(9.5,5.5);
		glVertex2f(9.5,6.5);
		glVertex2f(10,6.2);
		glVertex2f(11,6.2);
		glVertex2f(11.5,6.5);
		glVertex2f(11.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(11.5,5.5);
		glVertex2f(11.5,6.5);
		glVertex2f(12,6.2);
		glVertex2f(13,6.2);
		glVertex2f(13.5,6.5);
		glVertex2f(13.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
	glVertex2f(13.5,5.5);
		glVertex2f(13.5,6.5);
		glVertex2f(14,6.2);
		glVertex2f(15,6.2);
		glVertex2f(15.5,6.5);
		glVertex2f(15.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(15.5,5.5);
		glVertex2f(15.5,6.5);
		glVertex2f(16,6.2);
		glVertex2f(17,6.2);
		glVertex2f(17.5,6.5);
		glVertex2f(17.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(17.5,5.5);
		glVertex2f(17.5,6.5);
		glVertex2f(18,6.2);
		glVertex2f(19,6.2);
		glVertex2f(19.5,6.5);
		glVertex2f(19.5,5.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(19.5,5.5);
		glVertex2f(19.5,6.5);
		glVertex2f(20,6.2);
		glVertex2f(20.5,6.2);
		glVertex2f(21,6.5);
		glVertex2f(21,5.5);
	glEnd();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(4.5,3.5);
		glVertex2f(4.5,4.5);
		glVertex2f(5.5,4.5);
		glVertex2f(5.5,3.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(7,3.5);
		glVertex2f(7,4.5);
		glVertex2f(8,4.5);
		glVertex2f(8,3.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(9.5,3.5);
		glVertex2f(9.5,4.5);
		glVertex2f(10.5,4.5);
		glVertex2f(10.5,3.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(12,3.5);
		glVertex2f(12,4.5);
		glVertex2f(13,4.5);
		glVertex2f(13,3.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(14.5,3.5);
		glVertex2f(14.5,4.5);
		glVertex2f(15.5,4.5);
		glVertex2f(15.5,3.5);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(17,3.5);
		glVertex2f(17,4.5);
		glVertex2f(18,4.5);
		glVertex2f(18,3.5);
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(5,10);
		glVertex2f(5,11);
		glVertex2f(5.5,10.8);
		glVertex2f(6.5,10.8);
		glVertex2f(7,11);
		glVertex2f(7,10);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(7,10);
		glVertex2f(7,11);
		glVertex2f(7.5,10.8);
		glVertex2f(8.5,10.8);
		glVertex2f(9,11);
		glVertex2f(9,10);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(9,10);
		glVertex2f(9,11);
		glVertex2f(9.5,10.8);
		glVertex2f(10.5,10.8);
		glVertex2f(11,11);
		glVertex2f(11,10);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(11,10);
		glVertex2f(11,11);
		glVertex2f(11.5,10.8);
		glVertex2f(12.5,10.8);
		glVertex2f(13,11);
		glVertex2f(13,10);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(13,10);
		glVertex2f(13,11);
		glVertex2f(13.5,10.8);
		glVertex2f(14.5,10.8);
		glVertex2f(15,11);
		glVertex2f(15,10);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(15,10);
		glVertex2f(15,11);
		glVertex2f(15.5,10.8);
		glVertex2f(16.5,10.8);
		glVertex2f(17,11);
		glVertex2f(17,10);
	glEnd();
}

/* TO DRAW ICEBERG */
void ice()
{
	glPushMatrix();
	glTranslated(450,50,0.0);
	glScaled(10,10,0);
	glColor3f(0.8, 0.8, 0.8);	// lightgrey color code
	if(c>0)
	{glPushMatrix();
	glTranslated(0,x,0);
	glPushMatrix();
	glTranslated(7,2,0.0);
			glRotated(-x,0,0,1);
			glTranslated(-7,-2,0.0);
		glBegin(GL_POLYGON);
		glVertex2f(7,2);
		glVertex2f(8,3);
		glVertex2f(11,18);
		glVertex2f(12,19);
		glVertex2f(12,3);
		glEnd();
		glPopMatrix();
		glPushMatrix();

		glTranslated(12,3,0.0);
					glRotated(x,0,0,1);
					glTranslated(-12,-3,0.0);
		glBegin(GL_POLYGON);
		glVertex2f(12,3);
		glVertex2f(12,19);
		glVertex2f(17,18);
		glVertex2f(18,3);
		glVertex2f(19,3);
		glEnd();
		glPopMatrix();
		glPopMatrix();
	}
	else
	{
		glBegin(GL_POLYGON);
			glVertex2f(7,2);
			glVertex2f(8,3);
			glVertex2f(11,18);
			glVertex2f(12,19);
			glVertex2f(12,3);
			glEnd();
			glBegin(GL_POLYGON);
			glVertex2f(12,3);
			glVertex2f(12,19);
			glVertex2f(17,18);
			glVertex2f(18,3);
			glVertex2f(19,3);
			glEnd();
	}


	glPopMatrix();

}

void myinit()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
	glColor3f(1.0,0.0,0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();			// Used to set back to default (origin)
	gluOrtho2D(0.0,999.0,0.0,799.0);	// Sets up 2D Orthographic viewing region
}

int main(int argc, char* argv[])
{	
	int c_menu;
	int key=0;
	printf("Project by Shiva Reddy and Dhruv Shetty\n");
	printf("Press 1 to Start\n");
 	printf("Press 'd' or 'D' to make it day. \n");
	printf("Press 'n' or 'N' to make it night. \n");
	scanf("%d",&key);
	if(key==0) return 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024.0,768.0);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Shipping!");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardFunc);
	myinit();
	c_menu=glutCreateMenu(main_menu);	// Creating a Menu
	glutAddMenuEntry("Aeroplane",1);	// Index=1 for Aeroplane
	glutAddMenuEntry("Comet",2);		// Index=2 for Comet
	glutAttachMenu(GLUT_RIGHT_BUTTON);	// Menu pops on clicking Mouse's right button
	glutTimerFunc(100,update,0);		// Ship's initial movement after 100ms
	glutMainLoop();
	return 0;
}
