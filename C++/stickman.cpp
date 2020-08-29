#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<glut.h>

float player1x, player1y;  //player 1 and 2's x and y axis
float boxx[5], boxheight[5], boxwidth[5];

int player1walkaction, player1walkcounter; //player1walkaction is used to animate player1 //player1walkcounter is used to animate stick man walking
int score, hiscore;
float boxvel;

bool jump, highjump;
float upvelocity;
float gravity = 0.2;
bool keystates[256]; //array stores the keys pressed either true or false
char buffer[100]; //used to display tesxt 
bool pause; //used to display game over

//set the game initialize both players
void initgame()
{
	int i;

	score = 0;

	player1x = 100;
	player1y = 300;
	player1walkaction = 0;

	boxx[0] = 800;
	boxwidth[0] = rand() % 20 + 10;
	boxheight[0] = rand() % 60 + 30;
	boxvel = 3.5;

	for(i = 1; i <= 4; i++)
	{
		boxx[i] = boxx[i - 1] + rand() % 150 + 250;
		boxwidth[i] = rand() % 20 + 10;
		boxheight[i] = rand() % 60 + 30;
	}
}

//this function is called when the keyboard button is released
void KeyUpPress(unsigned char key, int x, int y ){
    switch(key){
	case ' ':
		keystates[' '] = false;
		break;
	
	case 'c':
		break;
	case 27:
		exit(0);
 
	} 
}

//this function is called when the keyboard button is pressed 
void KeyDownPress(unsigned char key, int x, int y ){
    switch(key){
	case ' ':
		keystates[' '] = true;
	break;
 
	case 'y':
		if(pause == true)
		{
			pause = false;
			initgame();
		}
		break;
	
	case 'n':
		if(pause == true)
		exit(0);
		break;
	case 27:
		exit(0);
 
	}
      
}

//This function is used to draw text on the screen
void drawString (void * font, char *s, float x, float y){
     unsigned int i;
     glRasterPos2f(x, y);
     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}

/*
This function is used to draw stick man figures
The first argument is the x position of the stick man, 
the second argument is they position of stick man,
the third argument is the walkaction, there are 2 action in walking it is 0 and 1 
*/
void drawStickMan(int x, int y, int walkaction)
{
	glLoadIdentity();
	glTranslatef(x, y, 0);
	
	glLineWidth(2);
    //head

    glBegin(GL_LINE_LOOP); 
        glColor3f(0, 0, 0);                                          
        glVertex2f(0 - 10, - 10 - 10);
        glVertex2f(0 - 10, - 10 + 10);
        glVertex2f(0 + 10, - 10 + 10);
        glVertex2f(0 + 10, - 10 - 10); 
    glEnd();
    
    //body
    glBegin(GL_LINES);  
        glColor3f(0, 0, 0);                                        
        glVertex2f(0, 0);
        glVertex2f(0,  30);
    glEnd();       
	 
	if(walkaction == 0 || jump == true)
	{
		//feets
        glBegin(GL_LINE_STRIP);  
            glColor3f(0, 0, 0);      
            glVertex2f(0,  30);                                  
            glVertex2f(0,  60);
            glVertex2f(0 + 10,  60);
        glEnd();
        glBegin(GL_LINE_STRIP);  
            glColor3f(0, 0, 0);      
            glVertex2f(0,  30);                                  
            glVertex2f(0 + 15,  45);
            glVertex2f(0 - 3,  48);
            glVertex2f(0 + 2,  57);
        glEnd();

		//hands
		glBegin(GL_LINE_STRIP);  
			glColor3f(0, 0, 0);                                        
			glVertex2f(0,  20);
			glVertex2f(0 - 12,  30);
			glVertex2f(0 - 2,  40);
		glEnd();                                    
		glBegin(GL_LINE_STRIP);  
			glColor3f(0, 0, 0);              
			glVertex2f(0,  20);
			glVertex2f(0 + 15,  27);
			glVertex2f(0 + 20,  12);
		glEnd();	
	}
	//stick man is walking 
	else if (walkaction == 1)
	{
		//feets
        glBegin(GL_LINE_STRIP);  
            glColor3f(0, 0, 0);      
            glVertex2f(0,  30);                                  
            glVertex2f(0 - 12,  55);
            glVertex2f(0 - 3,  60);
        glEnd();
        glBegin(GL_LINE_STRIP);  
            glColor3f(0, 0, 0);      
            glVertex2f(0,  30);                                  
            glVertex2f(0 + 10,  60);
            glVertex2f(0 + 20,  55);
        glEnd();

		//hands
		glBegin(GL_LINE_STRIP);  
			glColor3f(0, 0, 0);                                        
			glVertex2f(0,  20);
			glVertex2f(0 - 5,  35);
			glVertex2f(0 + 15,  28);
		glEnd();                                    
		glBegin(GL_LINE_STRIP);  
			glColor3f(0, 0, 0);              
			glVertex2f(0,  20);
			glVertex2f(0 + 8,  38);
			glVertex2f(0 + 20,  27);
		glEnd();
    }
	
	glLoadIdentity();
}


void drawBoxes()
{
	int i;

	for(i = 0; i <= 4; i++)
	{
		glBegin(GL_QUADS);  
			glColor3f(0.5f, 0.35f, 0.05f);              
			glVertex2f(boxx[i] - boxwidth[i],  360);
			glVertex2f(boxx[i] + boxwidth[i],  360);
			glVertex2f(boxx[i] + boxwidth[i],  360 - boxheight[i]);
			glVertex2f(boxx[i] - boxwidth[i],  360 - boxheight[i]);
		glEnd();

		glBegin(GL_QUADS);  
			glColor3f(0, 0.25, 0);              
			glVertex2f(boxx[i] - boxwidth[i],  360);
			glVertex2f(boxx[i] + boxwidth[i],  360);
			glVertex2f(boxx[i] + boxwidth[i],  360 + boxheight[i] * 0.5);
			glVertex2f(boxx[i] - boxwidth[i],  360 + boxheight[i] * 0.5);
		glEnd();
	
	}
}

//This is where the positions of the players are updated
void updategame(int value)
{
	int i;

	glutTimerFunc(10, updategame, 0);

	if(pause == false)
	{		
		score = score + 1;
		if(score > hiscore)
			hiscore = score;

		if(score % 500 == 0)
			boxvel = boxvel + 0.1;

		if(jump == false && keystates[' '] == true)
		{
			jump = true;
			upvelocity = 6.5;
		}

		if(jump == true)
		{
			player1y = player1y - upvelocity;
			upvelocity = upvelocity - gravity;
			
			if(highjump == false && player1y <= 222 && keystates[' '] == true)
			{
				upvelocity = upvelocity + upvelocity * 0.5;
				highjump = true;
			}
			if(player1y >= 300)
			{
				player1y = 300;
				jump = false;
				highjump = false;
			}
		}
		
		//used to alternate between walking action 0 and 1
		if(player1walkaction == 0 && player1walkcounter == 0)
		{
			player1walkcounter = 20;
			player1walkaction = 1;
		}
		else if(player1walkaction == 1 && player1walkcounter == 0)
		{
			player1walkcounter = 20;
			player1walkaction = 0;
		}
		else
		{
			player1walkcounter = player1walkcounter - 1;
		}

		//move the boxes
		for(i = 0; i <= 4; i++)
		{
			boxx[i] = boxx[i] - boxvel;
			
			if(boxx[i] < -50)
			{
				if(i == 0)
					boxx[i] = boxx[4] + rand() % 300 + 250;
				else
					boxx[i] = boxx[i - 1] + rand() % 300 + 250;
				boxwidth[i] = rand() % 20 + 20;
				boxheight[i] = rand() % 60 + 30;
			}
		}	

		//chech if player hot the box
		for(i = 0; i <= 4; i++)
		{
			if(player1x - 10 < boxx[i] + boxwidth[i] && player1x + 10 > boxx[i] - boxwidth[i] && player1y - 20 < 360 && player1y + 60 > 360 - boxheight[i] + 10)
			{
				pause = true;
			}
		}
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//blue sky
	glClearColor(0.43 , 0.77, 0.86, 1);
		
	//display score	
	glColor3f(1, 1, 1);
	drawString(GLUT_BITMAP_HELVETICA_18, "score:", 460, 30);	
	itoa(score, buffer, 10);
	drawString(GLUT_BITMAP_HELVETICA_18, buffer, 520, 30);

	//display hi score	
	drawString(GLUT_BITMAP_HELVETICA_18, "hi-score:", 60, 30);	
	itoa(hiscore, buffer, 10);
	drawString(GLUT_BITMAP_HELVETICA_18, buffer, 145, 30);

	//draw ground in green
	glBegin(GL_QUADS);
		glColor3f(0, 0.5, 0);
		glVertex2f (0, 360);
		glVertex2f (0, 480);
		glVertex2f (640, 480);
		glVertex2f (640, 360);
	glEnd();

	//draw both stick man
	drawStickMan(player1x, player1y, player1walkaction);
	
	drawBoxes();

	if(pause == true)
	{	
		glColor3f(1, 1, 1);
		
		drawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 270, 280);
		drawString(GLUT_BITMAP_HELVETICA_18, "Do you want to continue(y/n)", 200, 300);		
	}

	glutSwapBuffers();
}

//This function is called when the opengl window is resized
void reshape(int x, int y)
{
	glViewport(0, 0, x, y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


void main(int argc, char **argv)
{
	initgame(); //call init function to initialize the game
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowPosition(300,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("Stick Man Jump");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(KeyDownPress);
	glutKeyboardUpFunc(KeyUpPress);
	glutIdleFunc(display);
	glutTimerFunc(10, updategame, 0);
	glutMainLoop();
}
