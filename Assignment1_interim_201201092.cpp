#include <iostream>
#include <cmath>
#include <GL/glut.h>
using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

typedef struct bullet
{
	float xco;
	float yco;
	float flag;
	float xvel;
	float yvel;
	float angle;

}bullet;

typedef struct spiders
{
	float xco;
	float yco;
	float vel;
	float flag;
	float col;
}spiders;

bullet bullet_array[10000];
spiders spider_array[100000];
// Function Declarations
void drawScene();
void drawoutline();
void update(int value);
void drawBox(float len);
void drawBall(float rad);
void drawTriangle();
void initRendering();
void handleResize(int w, int h);
void handleKeypress1(unsigned char key, int x, int y);
void handleKeypress2(int key, int x, int y);
void handleMouseclick(int button, int state, int x, int y);
void drawline();
void drawtri();
void drawcannon();
void generatebullet();
void generatespider();
void drawbullet();
void drawspiders();
void drawspider2();
void drawcylinder(int a,int b);
// Global Variables
float ball_x = 1.0f;
float ball_y = 0.0f;
float ball_velx = 0.01f;
float ball_vely = 0.02f;
float ball_rad = 0.2f;
float box_len = 3.0f;
float tri_x = 0.0f;
float tri_y = 0.0f;
float theta = 0.0f; 
float constant = 1.0*box_len/400;
float line_length=400 * constant;
float line_height=35 * constant;
float line_width =200 * constant;
float cannon_pos=14.4*constant;
float cannon_angle= 0.0f;
float cannon_width=100 * constant;
float cannon_xco=0.0f;
float cannon_xcomin=box_len/2;
float cannon_xcomax=-box_len/2;
int bulletcount=0;
int spidercount=0;
int spiders_in_screen=0;
int spidercounting=0;
int keyr=0;
int keyl=0;
int keym=1;
float cylinder1_xco=-box_len/4;
float cylinder2_xco=box_len/4;
int stop_space=0;
int spaceflag=1;
float cylinder1_xcomin=box_len/2;
float cylinder1_xcomax=-box_len/2;
float cylinder2_xcomin=box_len/2;
float cylinder2_xcomax=-box_len/2;
int keyp=1;
int score=0;
int keyend=1;

int main(int argc, char **argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w ;
	int windowHeight = h ;

	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);

	glutCreateWindow("Assignment1_interim_201201092");  // Setup the window
	initRendering();

	// Register callbacks
	glutDisplayFunc(drawScene);
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress1);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(10, update, 0);

	glutMainLoop();
	return 0;
}

// Function to draw objects on the screen
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	// Draw Box
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	drawBox(box_len);
	drawline();
	if(1)
	{
			glPushMatrix();
		        glTranslatef(0, 0, 0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glRasterPos3f(0 , box_len/2 + 10*constant, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,115);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,99);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,111);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,114);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,101);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,32);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,32);
			int yyy= score;
			if(score < 0)
			{
				yyy=-1*yyy;
			}
			int array[10];
			int cou=0;
			while(yyy>0)
			{
				array[cou]=yyy%10;
				yyy=yyy/10;
				cou++;
			}
				
			if(cou==0)
			{
				array[cou]=0;
				cou++;
			}
			if(score<0)
			{
				array[cou]=-3;
				cou++;

			}
			int hh=cou-1;;
			while(hh>=0)
			{
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,array[hh]+48);
				hh--;
			}

			glPopMatrix();
	}
	if(keyp==0)
	{
			glPushMatrix();
		        glTranslatef(0, 0, 0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glRasterPos3f(0 ,0, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'P');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'a');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'u');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'s');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'e');
			glPopMatrix();

	}
	if(keyend==0)
	{


			glPushMatrix();
		        glTranslatef(0, 0, 0);
			glColor3f(0.0f, 0.0f, 0.0f);
			glRasterPos3f(0 ,0, 0);
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'E');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'N');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'D');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'_');
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'_');
			glPopMatrix();



	}

	glPushMatrix();
	glTranslatef(cannon_xco, -box_len/2 + cannon_pos, 0.0f);
	glRotatef(cannon_angle, 0.0f, 0.0f, 1.0f);
	glScalef(15 * constant, 15 * constant,15 * constant);
	drawcannon();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(cylinder1_xco, -box_len/2 + cannon_pos, 0.0f);
	glScalef(10 * constant, 10*constant ,10 *  constant);
	drawcylinder(0,1);
	if(keyl==1)
	{
		drawoutline();
	}
	glPopMatrix();


	glPushMatrix();
	glTranslatef(cylinder2_xco, -box_len/2 + cannon_pos, 0.0f);
	glScalef(10 *  constant, 10 *  constant, 10* constant);
	drawcylinder(0,-1);
	if(keyr==1)
	{
		drawoutline();
	}
	glPopMatrix();


	drawbullet();
	drawspiders();


	glPopMatrix();
	glutSwapBuffers();
}

// Function to handle all calculations in the scene
// updated evry 10 milliseconds
void update(int value) {
	if(keyp==1 && keyend==1)
	{
	if(spaceflag==0)
	{
		stop_space++;
	}
	if(stop_space>=100)
	{
		spaceflag=1;
		stop_space=0;
	}
	// Handle ball collisions with box
	if(ball_x + ball_rad > box_len/2 || ball_x - ball_rad < -box_len/2)
		ball_velx *= -1;
	if(ball_y + ball_rad > box_len/2 || ball_y - ball_rad < -box_len/2)
		ball_vely *= -1;

	// Update position of ball
	ball_x += ball_velx;
	ball_y += ball_vely;


	int i=1;
	while(i<=bulletcount)
	{


		if(bullet_array[i].xco  >= box_len/2 || bullet_array[i].xco <= -box_len/2)
		{
			bullet_array[i].xvel*=-1;
			bullet_array[i].angle*=-1;
		//	cout<<bullet_array[i].xco<<" "<<"Printed out variable x"<<endl;

		}
		if(bullet_array[i].yco   > box_len/2 || bullet_array[i].yco  < -box_len/2)
		{
			bullet_array[i].flag=0.0;
		}	
		i++;

	}

	i=1;
	while(i<=bulletcount)
	{
		if(bullet_array[i].flag==1.0)
		{
			bullet_array[i].xco+=bullet_array[i].xvel;	
			bullet_array[i].yco+=bullet_array[i].yvel;
		}
		i++;
	}



	i=1;
	int jj=1;
	
	while(i<=bulletcount)
	{
		if(bullet_array[i].flag==1.0)
		{
			jj=1;
			while(jj<=spidercount)
			{
				if(spider_array[jj].flag==1.0)
				{					
					float xx= bullet_array[i].xco - spider_array[jj].xco;
					float yy= bullet_array[i].yco - spider_array[jj].yco;
					if( (xx*xx + yy*yy) <= 4 * constant )   // need
					{
						spider_array[jj].flag=2.0;
						if(spider_array[jj].col==2)
						{
							score++;
							//cout << "more" <<endl;
						}
						else
						{
							score--;
						//	cout << "less" <<endl;
						}
						spiders_in_screen--;
					}
				}
				jj++;
			}
		}
		i++;
	}



	i=1;
	while(i<=spidercount)
	{
		if(spider_array[i].flag==1.0)
		{
			spider_array[i].yco-=spider_array[i].vel;	
		}
		if(spider_array[i].yco < -box_len/2 + line_height  && spider_array[i].flag==1.0 )
		{
			spider_array[i].flag=0;
			spiders_in_screen--;
			if(spider_array[i].xco < cylinder1_xco + 20 * constant && spider_array[i].xco > cylinder1_xco - 20 * constant ) // need
			{
				if(spider_array[i].col==1)
				{
					score++;
				}
					
				spider_array[i].flag=2;
			}
		else if(spider_array[i].xco < cylinder2_xco + 20 * constant && spider_array[i].xco > cylinder2_xco -20*constant )//need
				{
					if(spider_array[i].col==0)
					{
						score++;
					}
					spider_array[i].flag=2;
				}



		if(spider_array[i].xco < cylinder1_xco + 20 * constant && spider_array[i].xco > cylinder1_xco - 20 * constant ) // need
			{
				if(spider_array[i].col==0 || spider_array[i].col==2)
				{
					score--;
				}
					
				spider_array[i].flag=2;

			}




		if(spider_array[i].xco < cylinder2_xco + 20 * constant && spider_array[i].xco > cylinder2_xco - 20 * constant ) // need
			{
				if(spider_array[i].col==1 || spider_array[i].col==2)
				{
					score--;
				}
					
				spider_array[i].flag=2;
			}
			if(spider_array[i].flag==0)
			{
				score=score-5;
				//cout << "end score" << endl;

			}	//

			if(spider_array[i].xco < cannon_xcomin && spider_array[i].xco > cannon_xcomax)
			{
				if(spider_array[i].xco < cylinder1_xco +20 * constant && spider_array[i].xco > cylinder1_xco -20 * constant )
				{
					spider_array[i].flag=2;
				}
				else if(spider_array[i].xco < cylinder2_xco +20*constant && spider_array[i].xco > cylinder2_xco -20*constant)
				{
					spider_array[i].flag=2;
				}
				else
				{
				   if(spider_array[i].xco < cannon_xco+ 20 * constant && spider_array[i].xco > cannon_xco - 20 * constant)
				   {
					   keyend=0;

				   }
					else if(spider_array[i].xco < cannon_xco - 20 * constant)
					{
						cannon_xcomax=spider_array[i].xco ;
					}
					else if(spider_array[i].xco > cannon_xco + 20 * constant)
					{
						cannon_xcomin=spider_array[i].xco ;	
					}
				}
			}
			if(spider_array[i].xco < cylinder1_xcomin && spider_array[i].xco > cylinder1_xcomax)
			{
				if(spider_array[i].xco < cylinder1_xco +20 * constant && spider_array[i].xco > cylinder1_xco -20*constant  )
				{
					spider_array[i].flag=2;
				}
				else if(spider_array[i].xco < cylinder2_xco +20*constant && spider_array[i].xco > cylinder2_xco -20*constant )
				{
					spider_array[i].flag=2;
				}
				else
				{	
					if(spider_array[i].xco < cylinder1_xco )
					{
						//cout << "fsfsdfds" ;
						cylinder1_xcomax=spider_array[i].xco+10*constant;
					}
					else if(spider_array[i].xco > cylinder1_xco )
					{
						cylinder1_xcomin=spider_array[i].xco-10*constant;	
					}
				}
			}
			//
			if(spider_array[i].xco < cylinder2_xcomin && spider_array[i].xco > cylinder2_xcomax )
			{



				if(spider_array[i].xco < cylinder1_xco +20 * constant && spider_array[i].xco > cylinder1_xco -20*constant )
				{
					spider_array[i].flag=2;
				}


				else if(spider_array[i].xco < cylinder2_xco +20*constant && spider_array[i].xco > cylinder2_xco -20*constant )
				{
					spider_array[i].flag=2;
				}
				else
				{


					if(spider_array[i].xco < cylinder2_xco)
					{
						cylinder2_xcomax=spider_array[i].xco+10*constant;
					}
					else if(spider_array[i].xco > cylinder2_xco)
					{
						cylinder2_xcomin=spider_array[i].xco-10*constant;	
					}
				}
			}	
		}
		i++;

	}
	i=1;
	
	spidercounting ++;
	if(spidercounting==100)
	{
		spidercounting=0;
		//cout << spiders_in_screen << endl;
		if(spiders_in_screen<=2)
		{
			generatespider();
			spiders_in_screen++;
		}
	}
	}


	glutTimerFunc(10, update, 0);
}

void drawBox(float len) {

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.5f, 0.25f);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);
	glEnd();
	glLineWidth(line_width);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2)	;
	glEnd();
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void drawcylinder(int len,int col)
{
	glBegin(GL_QUADS);
	if(col==1)
	{

		glColor3f(1.0f, 0.0f, 0.0f);

	}
	else
	{

		glColor3f(0.0f, 1.0f, 0.0f);
	}

	glVertex2f(2, 2);
	glVertex2f(-2, 2);
	glVertex2f(-2,-2);
	glVertex2f(2, -2);
	glEnd();

}


void drawoutline()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(2, 2);
	glVertex2f(-2, 2);
	glVertex2f(-2,-2);
	glVertex2f(2, -2);
	glEnd();

}


void drawline()
{
	glLineWidth(line_width);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-line_length/2, (-box_len / 2) + line_height, 0.0);
	glVertex3f(line_length/2, (-box_len / 2 ) + line_height , 0.0);
	glEnd();

}


void drawspiders()
{

	int i=1;
	while(i<=spidercount)
	{

		if(spider_array[i].flag==1.0 || spider_array[i].flag==0.0)
		{
			glPushMatrix();
			if(spider_array[i].col==1.0)
			{
				glColor3f(1.0, 0.0, 0.0);
			}
			else if(spider_array[i].col==0.0)
			{
				glColor3f(0.0, 1.0, 0.0);
			}
			else
			{
				glColor3f(0.0, 0.0, 1.0);

			}
			glTranslatef(spider_array[i].xco, spider_array[i].yco, 0.0f);
			glScalef(10*constant, 10*constant,10*constant);
			drawspider2();
			glPopMatrix();
		}
		i++;

	}
}
void drawspider2()
{

	glPushMatrix();
	glTranslatef(0,1, 0.0f);
	// glScalef(0.1f, 0.1f,0.1f);
	drawBall(1);
	glPopMatrix();	
	glPushMatrix();
	glTranslatef(0,-0.5, 0.0f);
	// glScalef(0.1f, 0.1f,0.1f);
	drawBall(0.5);
	glPopMatrix();
	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(-1,0, 0.0);
	glVertex3f(1,0, 0.0);
	glEnd();


	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(-1,-1, 0.0);
	glVertex3f(2,2, 0.0);
	glEnd();


	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(1,-1, 0.0);
	glVertex3f(-2,2, 0.0);
	glEnd();



	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(-1,0, 0.0);
	glVertex3f(-2,-0.5, 0.0);
	glEnd();


	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(1,0, 0.0);
	glVertex3f(2,-0.5, 0.0);
	glEnd();



	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(-0.5,-1.5, 0.0);
	glVertex3f(-1,-1, 0.0);
	glEnd();

	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(0.5,-1.5, 0.0);
	glVertex3f(1,-1, 0.0);
	glEnd();

	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(-3,1, 0.0);
	glVertex3f(-2,2, 0.0);
	glEnd();

	glLineWidth(line_width);
	glBegin(GL_LINES);
	glVertex3f(3,1, 0.0);
	glVertex3f(2,2, 0.0);
	glEnd();


}



































void drawcannon()
{

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1,-1,0);
	glVertex3f(1,-1,0);
	glVertex3f(1,1,0);
	glVertex3f(-1,1,0);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1,-1,0);
	glVertex3f(1,-1,0);
	glVertex3f(1,1,0);
	glVertex3f(-1,1,0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1,1.28,0);
	glVertex3f(1,1,0);
	glVertex3f(0,1,0);
	glVertex3f(0,1.28,0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1,1.28,0);
	glVertex3f(-1,1,0);
	glVertex3f(0,1,0);
	glVertex3f(0,1.28,0);
	glEnd();

	glPushMatrix();
	glTranslatef(1, 1, 0.0f);
	drawBall(0.28);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 1, 0.0f);
	drawBall(0.28);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1,1,0);
	glVertex3f(1.28,1,0);
	glVertex3f(1.28,0,0);
	glVertex3f(0,0,0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0,0,0);
	glVertex3f(1.28,0,0);
	glVertex3f(1.28,-1,0);
	glVertex3f(0,-1,0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1,1,0);
	glVertex3f(-1.28,1,0);
	glVertex3f(-1.28,0,0);
	glVertex3f(0,0,0);
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0,0,0);
	glVertex3f(-1.28,0,0);
	glVertex3f(-1.28,-1,0);
	glVertex3f(0,-1,0);
	glEnd();
	glPushMatrix();
	glTranslatef(-1, -1, 0.0f);
	drawBall(0.28);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1, -1, 0.0f);
	drawBall(0.28);
	glPopMatrix();	

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.78,1.28,0);
	glVertex3f(2.28,1.28,0);
	glVertex3f(2.28,-1.28,0);
	glVertex3f(1.78,-1.28,0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1.78,1.28,0);
	glVertex3f(-2.28,1.28,0);
	glVertex3f(-2.28,-1.28,0);
	glVertex3f(-1.78,-1.28,0);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0,0.25,0);
	glVertex3f(2.21,0.25,0);
	glVertex3f(2.21,-0.25,0);
	glVertex3f(0.0,-0.25,0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0,0.25,0);
	glVertex3f(-2.21,0.25,0);
	glVertex3f(-2.21,-0.25,0);
	glVertex3f(0.0,-0.25,0);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.25,0,0);
	glVertex3f(-0.25,0.0,0);
	glVertex3f(-0.25,3.0,0);
	glVertex3f(0.25,3.0,0);
	glEnd();

	glPushMatrix();
	glTranslatef(0.25, 3.0, 0.0f);
	drawBall(0.15);
	glPopMatrix();	

	glPushMatrix();
	glTranslatef(-0.25, 3.0, 0.0f);
	drawBall(0.15);
	glPopMatrix();	

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.25,0,0);
	glVertex3f(-0.25,0.0,0);
	glVertex3f(-0.25,3.15,0);
	glVertex3f(0.25,3.15,0);
	glEnd();

}


void drawBall(float rad) {

	glBegin(GL_TRIANGLE_FAN);
	for(int i=0 ; i<360 ; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}

void drawTriangle() {

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
}




void drawbullet()
{

	int i=1;
	while(i<=bulletcount)
	{

		if(bullet_array[i].flag==1.0)
		{
			float bullen=box_len*10*constant;
		//	cout << (bullet_array[i].xco + bullen * sin(DEG2RAD(-1 * bullet_array[i].angle))) << endl;
			if(bullet_array[i].xco + bullen * sin(DEG2RAD(-1 * bullet_array[i].angle))  < (box_len/2) &&  bullet_array[i].xco + bullen * sin(DEG2RAD(-1 * bullet_array[i].angle)) > -1 * (box_len/2)     )
			{	
				glPushMatrix();
				glTranslatef(bullet_array[i].xco, bullet_array[i].yco, 0.0f);
				glRotatef(bullet_array[i].angle, 0.0f, 0.0f, 1.0f);			
			//	glTranslatef(1.0f, 1.0f, 0.0f);
				glScalef(10*constant, 10*constant,10*constant);
				glLineWidth(200*constant);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(0.0,0.0, 0.0);
				glVertex3f(0.0 ,box_len, 0.0);
				glEnd();
				glPopMatrix();
			}	
			
			if(bullet_array[i].xco + bullen * sin(DEG2RAD(-1 * bullet_array[i].angle))  > (box_len/2) )
			{	
				float ans= tan(DEG2RAD(-1 * bullet_array[i].angle));
				float newyco = bullet_array[i].yco + (((box_len/2)-bullet_array[i].xco)/ans);
				glLineWidth(200*constant);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(bullet_array[i].xco,bullet_array[i].yco, 0.0);
				glVertex3f(box_len/2 ,newyco, 0.0);
				glEnd();
				float aaa = box_len - (bullet_array[i].xco + bullen * sin(DEG2RAD(-1 * bullet_array[i].angle)) );
				float bbb = (bullet_array[i].yco + bullen * cos(DEG2RAD(-1 * bullet_array[i].angle)));
				glLineWidth(200*constant);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(box_len/2 ,newyco, 0.0);
				glVertex3f(aaa,bbb, 0.0);
				glEnd();

			}


			if(bullet_array[i].xco + bullen * sin(DEG2RAD(-1 * bullet_array[i].angle))  <  -1 * (box_len/2) )
			{	
				float ans= tan(DEG2RAD(-1 * bullet_array[i].angle));
				float newyco = bullet_array[i].yco + ((-1 * (box_len/2)-bullet_array[i].xco)/ans);
				glLineWidth(200*constant);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(bullet_array[i].xco,bullet_array[i].yco, 0.0);
				glVertex3f( -1 * box_len/2 ,newyco, 0.0);
				glEnd();
				float aaa = -1 * box_len - (bullet_array[i].xco + bullen * sin(DEG2RAD(-1 * bullet_array[i].angle)) );
				float bbb = (bullet_array [i].yco + bullen * cos(DEG2RAD(-1 * bullet_array[i].angle)));
				glLineWidth(200*constant);
				glColor3f(1.0, 0.0, 0.0);
				glBegin(GL_LINES);
				glVertex3f(-1 * box_len/2 ,newyco, 0.0);
				glVertex3f(aaa,bbb, 0.0);
				glEnd();

			}








			
		}
		i++;

	}


}

// Initializing some openGL 3D rendering options
void initRendering() {

	glEnable(GL_DEPTH_TEST);        // Enable objects to be drawn ahead/behind one another
	glEnable(GL_COLOR_MATERIAL);    // Enable coloring
	glClearColor(0.81f, 0.71f, 0.23f, 1.0f);   // Setting a background color
}

// Function called when the window is resized
void handleResize(int w, int h) {

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)w / (float)h, 0.1f, 200.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress1(unsigned char key, int x, int y) {

	if (key == 27) {
		exit(0);     // escape key is pressed
	}
	if (key == 32 && stop_space==0 && keym==1 && keyp==1 && keyend==1) {
		generatebullet();
		stop_space++;
		spaceflag=0;
		// escape key is pressed
	}

	if (key == 114) {
		keyr=0;// escape key is pressed
		keym=0;// escape key is pressed
		keyl=1;// escape key is pressed
		//cout << "asdas" ;
	}
	if (key == 103) {
		keyr=1;// escape key is pressed
		keym=0;// escape key is pressed
		keyl=0;// escape key is pressed
	}
	if (key == 98) {
		keyr=0;// escape key is pressed
		keym=1;// escape key is pressed
		keyl=0;// escape key is pressed
	}
	if (key == 112) {
		keyp=(keyp+1)%2;// escape key is pressed
	}
	if (key == 82) {
		keyend=1;
		keyp=1;
 ball_x = 1.0f;
 ball_y = 0.0f;
 ball_velx = 0.01f;
 ball_vely = 0.02f;
 ball_rad = 0.2f;
// box_len = 3.0f;
 tri_x = 0.0f;
 tri_y = 0.0f;
 theta = 0.0f; 
 constant = 1.0*box_len/400;
 line_length=400 * constant;
 line_height=35 * constant;
 line_width =200 * constant;
 cannon_pos=14.4*constant;
 cannon_angle= 0.0f;
 cannon_width=100 * constant;
 cannon_xco=0.0f;
 cannon_xcomin=box_len/2;
 cannon_xcomax=-box_len/2;
 bulletcount=0;
 spidercount=0;
 spiders_in_screen=0;
 spidercounting=0;
 keyr=0;
 keyl=0;
keym=1;
 cylinder1_xco=-box_len/4;
 cylinder2_xco=box_len/4;
 stop_space=0;
 spaceflag=1;
 cylinder1_xcomin=box_len/2;
 cylinder1_xcomax=-box_len/2;
 cylinder2_xcomin=box_len/2;
 cylinder2_xcomax=-box_len/2;
 keyp=1;
 score=0;


	}

}

void handleKeypress2(int key, int x, int y) {
//need
	if(keyp==1 && keyend==1)
	{
	if (key == GLUT_KEY_LEFT && (cannon_xco - 20*constant > cannon_xcomax) && keym==1)
		cannon_xco -= 10*constant;
	if (key == GLUT_KEY_RIGHT && cannon_xco + 20*constant < cannon_xcomin && keym==1)
		cannon_xco += 10*constant;

	if (key == GLUT_KEY_LEFT && (cylinder1_xco - 10*constant > cylinder1_xcomax) && keyl==1)
		cylinder1_xco -= 10*constant;
	if (key == GLUT_KEY_RIGHT && cylinder1_xco + 10*constant < cylinder1_xcomin && keyl==1)
		cylinder1_xco += 10*constant;

	if (key == GLUT_KEY_LEFT && (cylinder2_xco - 10*constant > cylinder2_xcomax) && keyr==1)
		cylinder2_xco-= 10*constant;
	if (key == GLUT_KEY_RIGHT && cylinder2_xco + 10*constant < cylinder2_xcomin && keyr==1)
		cylinder2_xco += 10*constant;




	if (key == GLUT_KEY_UP)
	{
		if ( cannon_angle+15 != 90)
			cannon_angle += 15;
	}
	if (key == GLUT_KEY_DOWN)
	{

		if (cannon_angle-15!=-90)
			cannon_angle -= 15;
	}
	}
}


void generatebullet()
{
	bulletcount++;
	bullet_array[bulletcount].angle=cannon_angle;;
	bullet_array[bulletcount].xco=cannon_xco + 40 * sin(DEG2RAD(-1* cannon_angle)) * constant;
	bullet_array[bulletcount].yco=-box_len/2 + cannon_pos + 40 * cos(DEG2RAD(-1* cannon_angle)) * constant;
	bullet_array[bulletcount].xvel=6*constant * sin(DEG2RAD(-1* cannon_angle));
	bullet_array[bulletcount].yvel=6*constant * cos(DEG2RAD(-1 * cannon_angle));
	bullet_array[bulletcount].flag=1.0;
	bullet_array[bulletcount].angle=cannon_angle;;

}



void generatespider()
{
	int pp = (box_len /2 )*100 - (3000 * constant);
	int l=rand()%pp;
	if(l%2==0)
	{
		l=-1*l;
	}
	int k=rand()%3;

	spidercount++;
	spider_array[spidercount].xco=1.0 * l / 100;
	spider_array[spidercount].yco=box_len/2;
	spider_array[spidercount].vel= constant;
	spider_array[spidercount].flag=1.0;

	spider_array[spidercount].col=1.0 * k;

}



void handleMouseclick(int button, int state, int x, int y) {

	if (state == GLUT_DOWN && keyp==1)
	{
		if (button == GLUT_LEFT_BUTTON && cannon_angle+15 != 90)
			cannon_angle += 15;
		else if (button == GLUT_RIGHT_BUTTON && cannon_angle-15!=-90)
			cannon_angle -= 15;
	}
}
