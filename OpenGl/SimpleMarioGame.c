#include<stdlib.h> 
#include<windows.h> 
#include<MMSystem.h> 
#include<math.h> 
#include<iostream> 
#include<glut.h> 

#define SPEED 40.0 
using namespace std; 

const int font=(int)GLUT_BITMAP_TIMES_ROMAN_24; 
char s[30];  
double t; 
float angle=30.0f,rot=0.5,mov=0.0,mb=0.0,rot1=0.0,bxt=0.0; 
float camera_angle=0.0f,c=0.0,m=0.0,n=0.0,o=0.0,ptx=0.0,pty=0.0; 
float mx=0.0,my=0.0;//mario 
int level=0; 
int text=0,mnt=0,value=0,fr=0.5,i=0,time; 

void draw_pixel(GLint cx, GLint cy) 
{ 
  glBegin(GL_POINTS); 
  glVertex2i(cx,cy); 
  glEnd(); 
} 

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

void draw_circle(GLint h, GLint k, GLint r) 
{ 
  GLint d=1-r, x=0, y=r; 
  while(y>x)   
  { 
  plotpixels(h,k,x,y); 
  if(d<0) 
    d+=2*x+3; 
  else 
  { 
    d+=2*(x-y)+5; 
    --y; 
  } 
  ++x; 
} 
plotpixels(h,k,x,y); 
} 

void Objects1() 
{ 
  int l; 
  glBegin(GL_POLYGON); 
  glColor3f(1.0,0.0,0.0); 
  glVertex2f(925+n,625+o); 
  glColor3f(0.0,1.0,0.0); 
  glVertex2f(950+n,640+o); 
  glColor3f(1.0,1.0,1.0); 
  glVertex2f(1015+n,640+o); 
  glColor3f(0.0,1.0,1.0); 
  glVertex2f(1030+n,650+o); 
  glColor3f(1.0,1.0,0.0); 
  glVertex2f(1050+n,650+o); 
  glColor3f(0.0,0.0,1.0); 
  glVertex2f(1010+n,625+o); 
  glEnd(); 

  //for cloud1 
  for(l=0;l<=20;l++) 
  { 
  glColor3f(1.0,1.0,1.0); 
  draw_circle(160+m,625,l); 
  } 

  for(l=0;l<=35;l++) 
  { 
  glColor3f(1.0,1.0,1.0); 
  draw_circle(200+m,625,l); 
  draw_circle(225+m,625,l); 
  } 

  for(l=0;l<=20;l++) 
  { 
  glColor3f(1.0,1.0,1.0); 
  draw_circle(265+m,625,l); 
  } 

  //cloud2 
  for(l=0;l<=20;l++) 
  { 
    glColor3f(1.0,1.0,1.0); 
    draw_circle(370+m,615,l); 
  } 

  for(l=0;l<=35;l++) 
  { 
    glColor3f(1.0,1.0,1.0); 
    draw_circle(410+m,615,l); 
    draw_circle(435+m,615,l); 
    draw_circle(470+m,615,l); 
  } 

  for(l=0;l<=20;l++) 
  { 
    glColor3f(1.0,1.0,1.0); 
    draw_circle(500+m,615,l); 
  } 
} 

void stars() 
{ 

glColor3f(1.0,1.0,1.0); 

glBegin(GL_TRIANGLES); 

glVertex2f(875,543); 

glVertex2f(870,535); 

glVertex2f(880,535); 

glVertex2f(875,532); 

glVertex2f(870,540); 

glVertex2f(880,540); 

glEnd(); 

int j=-1; 

for(int i=0;i<=5;i++) 

{ 

if(j>1) 

j=0; 

glPushMatrix(); 

glTranslatef(150*i,50*j,0.0); 

glBegin(GL_TRIANGLES); 

glVertex2f(200,628); 

glVertex2f(195,620); 

glVertex2f(205,620); 

glVertex2f(200,618); 

glVertex2f(195,625); 

glVertex2f(205,625); 

glEnd(); 

glPopMatrix(); 

j++; 

} 

} 

void grass() 

{ 

int l; 

for(l=0;l<=30;l++) 

{ 

glColor3f(0.0,0.5,0.0); 

draw_circle(340,400,l); 

draw_circle(380,400,l); 

} 

 

for(l=0;l<=25;l++) 

{ 

glColor3f(0.0,0.5,0.0); 

draw_circle(350,440,l); 

draw_circle(370,440,l); 

} 

 

for(l=0;l<=20;l++) 

{ 

glColor3f(0.0,0.5,0.0); 

draw_circle(360,465,l); 

} 

} 

void setorthographic() 

{ 

glMatrixMode(GL_PROJECTION); 

glLoadIdentity(); 

glOrtho(0,1024,0,768,-50,50); 

glMatrixMode(GL_MODELVIEW); 

glLoadIdentity(); 

} 

void comet() 

{ 

int l; 

for(l=0;l<=7;l++) 

{ 

glColor3f(1.0,1.0,1.0); 

draw_circle(300+c,675,l); 

} 

glColor3f(1.0,1.0,1.0); 

glBegin(GL_TRIANGLES); 

glVertex2f(200+c,675); 

glVertex2f(300+c,682); 

glVertex2f(300+c,668); 

glEnd(); 

} 

void brick() 

{ 

if(level==1) 

{ 

//glColor3f(0.5,0.0,0.0); 

glColor3f(1.0,0.0,0.0); 

glutSolidCube(1.0); 

glLineWidth(8); 

//glColor3f(1.0,0.0,0.0); 

glColor3f(0.5,0.0,0.0); 

glutWireCube(1.0); 

} 

else if(level==2) 

{ 

glColor3f(0.5,0.0,0.0); 

glutSolidCube(1.0); 

glLineWidth(8); 

glColor3f(1.0,0.0,0.0); 

glutWireCube(1.0); 

} 

} 

void wall() 

{ 

glColor3f(0.5,0.0,0.0); 

glRotatef(45.0,0.0,1.0,0.0); 

glTranslatef(-5.0,-7.5,0.0); 

for(int j=0;j<=4;j++) 

{ 

glPushMatrix(); 

glTranslatef(j*1,0.0,0.0); 

for(int i=0;i<=j;i++) 

{ 

glPushMatrix(); 

glTranslatef(0.0,i*1,0.0); 

brick(); 

glPopMatrix(); 

} 

glPopMatrix(); 

} 

} 

void renderBitmapString(float x, float y, void *font,const char *string) 

{ 

    const char *c; 

    glRasterPos2f(x, y); 

    for (c=string; *c != '\0'; c++) 

{ 

        glutBitmapCharacter(font, *c); 

    } 

}  

void drawStrokeText(char*string,int x,int y,int z) 

{ 

  char *c; 

  glPushMatrix(); 

  glTranslatef(x, y+8,z); 

glScalef(0.5f,0.5f,z); 

 for (c=string; *c != '\0'; c++) 

  { 

  glLineWidth(50.0f); 

    glutStrokeCharacter(GLUT_STROKE_ROMAN , *c); 

  } 

  glPopMatrix(); 

} 

//enemies 

void BlackGhost() 

{ 

glPushMatrix(); 

glTranslatef(900.0,170.0,0.0); 

glColor3f(1.0,0.0,0.0); 

glutSolidSphere(50,100,100);//body 

glColor3f(1.0,1.0,1.0); 

glTranslatef(10.0,20.0,0.0); 

glutSolidSphere(12,100,100);//eye 

glTranslatef(1.0,0.0,0.0); 

glColor3f(0.0,0.0,0.0); 

glutSolidSphere(6,100,100);//eyeball 

glPopMatrix(); 

glPushMatrix(); 

if(mnt==0) 

glTranslatef(870,155,0.0); 

else if(mnt==1) 

glTranslatef(870,150,0.0); 

for(int j=0;j<4;j++) 

{ 

glPushMatrix(); 

glTranslatef(15*j,1.5*j,0.0); 

glColor3f(0.9,0.7,0.5); 

glutSolidSphere(15,100,100); 

glPopMatrix(); 

} 

glPopMatrix(); 

glColor3f(1.0,1.0,1.0); 

if(mnt==0) 

{ 

for(int i=0;i<=3;i++) 

{ 

glPushMatrix(); 

glTranslatef((20)*i,(-2)*i,0); 

glTranslatef(0.0,15,0.0); 

glBegin(GL_TRIANGLES); 

glVertex2f(850,165); 

glVertex2f(870,165); 

glVertex2f(860,135+(2*i)); 

glEnd(); 

glPopMatrix(); 

} 

  

} 

else if(mnt==1) 

{ 

for(int i=0;i<=3;i++) 

{ 

glPushMatrix(); 

glTranslatef((20)*i,0.0,0); 

glBegin(GL_TRIANGLES); 

glVertex2f(850,165); 

glVertex2f(870,165); 

glVertex2f(860,135+(2*i)); 

glEnd(); 

glPopMatrix(); 

} 

} 

} 

void Beetle() 

{ 

glScalef(0.4,0.4,1.0); 

glPushMatrix(); 

glColor3f(0.0,0.0,0.0); 

glTranslatef(500,310,0.0); 

glScalef(2.0,1.0,1.0); 

glutSolidSphere(25,100,100); 

glTranslatef(50,0.0,0.0); 

glutSolidSphere(25,100,100); 

glPopMatrix(); 

glColor3f(0.55,0.09,0.09); 

glBegin(GL_POLYGON); 

glVertex2f(470,360); 

glVertex2f(630,360); 

glVertex2f(650,390); 

glVertex2f(570,460); 

glVertex2f(530,460); 

glVertex2f(450,390); 

glEnd(); 

glColor3ub(255,203,208); 

glBegin(GL_POLYGON); 

glVertex2f(500,370); 

glVertex2f(600,370); 

glVertex2f(620,340); 

glVertex2f(550,295); 

glVertex2f(480,340); 

glEnd(); 

glPushMatrix(); 

glScalef(1.0,1.3,1.0); 

glTranslatef(525,313,0.0); 

glColor3f(1.0,1.0,1.0); 

glutSolidCube(30.0); 

glTranslatef(50,0.0,0.0); 

glutSolidCube(30.0); 

glPopMatrix(); 

glPushMatrix(); 

glColor3f(0.0,0.0,0.0); 

glTranslatef(525,407,0.0); 

glScalef(0.5,1.2,1.0); 

glutSolidSphere(15.0,100,100); 

glTranslatef(95,0.0,0.0); 

glutSolidSphere(15.0,100,100); 

glPopMatrix(); 

glLineWidth(50.0); 

glBegin(GL_LINES); 

glColor3f(0.0,0.0,0.0); 

glVertex2f(525,417); 

glVertex2f(575,417); 

glVertex2f(575,417); 

glVertex2f(600,435); 

glVertex2f(525,417); 

glVertex2f(500,435); 

glEnd(); 

glPushMatrix(); 

glColor3f(0.55,0.09,0.09); 

glTranslatef(470,382,0.0); 

glutSolidSphere(20,100,100); 

glTranslatef(160,0.0,0.0); 

glutSolidSphere(20,100,100); 

glPopMatrix(); 

} 

//enemies 

//mario 

void mario() 

{ 

glPushMatrix(); 

glScalef(0.20,0.20,0.20); 

glTranslatef(0.0,480.0,0.0); 

glColor3ub(255,222,173); 

//head 

glPushMatrix(); 

glBegin(GL_POLYGON);//head 

glVertex3f(310,758,40); 

glVertex3f(250,758,40); 

glVertex3f(140,680,40); 

glVertex3f(140,630,40); 

glVertex3f(340,630,40); 

glVertex3f(340,660,40); 

glEnd(); 

glColor3f(1.0,0.0,0.0); 

glBegin(GL_POLYGON);//cap 

glVertex3f(370,758,40); 

glVertex3f(80,758,40); 

glVertex3f(80,778,40); 

glVertex3f(150,780,40); 

glVertex3f(150,800,40); 

glVertex3f(280,800,40); 

glVertex3f(280,780,40); 

glVertex3f(370,778,40); 

glEnd(); 

glColor3f(0.0,0.5,0.0);//hair 

glBegin(GL_POLYGON); 

glVertex3f(250,758,40); 

glVertex3f(100,758,40); 

glVertex3f(100,680,40); 

glVertex3f(180,680,40); 

glEnd(); 

glTranslatef(280,730,40);//eye 

glColor3f(0.0,0.5,0.0); 

glutSolidSphere(25,100,100); 

glPopMatrix(); 

glColor3ub(255,222,173); 

glPushMatrix();//hair cut 

glTranslatef(200,720,40);//chn 

for(int i=-1;i<=1;i++) 

{ 

glPushMatrix(); 

if(i<=0) 

glTranslatef(50*i,70*i,0.0); 

else 

glTranslatef(125*i,-73*i,0.0); 

glutSolidSphere(20,100,100); 

glPopMatrix(); 

} 

glTranslatef(-60,-20.0,0.0); 

glScalef(1.0,2.0,1.0); 

glutSolidCube(20); 

glPopMatrix(); 

 

glColor3f(0.0,0.5,0.0); 

for(int i=0;i<=1;i++) 

{ 

glPushMatrix(); 

glTranslatef(120+200*i,670.0,0.0); 

glScalef(1.4+1.5*i,1.0,1.0); 

glutSolidCube(30); 

glPopMatrix(); 

} 

 

//hand 

glColor3ub(255,222,173); 

for(int i=0;i<=1;i++) 

{ 

glPushMatrix(); 

glTranslatef(335+20*i,700-20*i,40); 

glScalef(2.0,1.0,1.0); 

glutSolidCube(25); 

glPopMatrix(); 

} 

for(int i=0;i<=1;i++) 

{ 

glPushMatrix(); 

glTranslatef(80+300*i,470+20*i,0.0); 

glScalef(1.0,2.0,1.0); 

glutSolidCube(50); 

glPopMatrix(); 

} 

//start legs 

glPushMatrix(); 

glColor3f(0.0,0.5,0.0); 

glBegin(GL_POLYGON);//right leg 

glVertex3f(370,270,40); 

glVertex3f(350,300,40); 

glVertex3f(290,320,40); 

glVertex3f(290,220,40); 

glVertex3f(430,220,40); 

glVertex3f(430,240,40); 

glVertex3f(370,240,40); 

glEnd(); 

glBegin(GL_POLYGON);//left leg 

glVertex3f(80,270,40); 

glVertex3f(100,300,40); 

glVertex3f(170,320,40); 

glVertex3f(170,220,40); 

glVertex3f(20,220,40); 

glVertex3f(20,240,40); 

glVertex3f(120,240,40); 

glEnd(); 

//end legs 

glPopMatrix(); 

glColor3f(1.0,0.0,0.0); 

//body in red 

glPushMatrix(); 

glBegin(GL_POLYGON); 

glVertex3f(180,540,40); 

glVertex3f(100,500,40); 

glVertex3f(100,300,40); 

glVertex3f(190,320,40); 

glVertex3f(200,420,40); 

glVertex3f(250,420,40); 

glVertex3f(250,500,40); 

glEnd(); 

glBegin(GL_POLYGON); 

glVertex3f(260,540,40); 

glVertex3f(250,500,40); 

glVertex3f(250,420,40); 

glVertex3f(270,320,40); 

glVertex3f(350,300,40); 

glVertex3f(350,500,40); 

glEnd(); 

glBegin(GL_TRIANGLES); 

glVertex3f(150,540,40); 

glVertex3f(250,500,40); 

glVertex3f(290,540,40); 

glEnd(); 

glColor3f(0.0,0.5,0.0); 

glBegin(GL_POLYGON); 

glVertex3f(180,540,40); 

glVertex3f(90,470,40); 

glVertex3f(50,520,40); 

glVertex3f(170,630,40); 

glVertex3f(260,630,40); 

glVertex3f(400,550,40); 

glVertex3f(370,490,40); 

glEnd(); 

glPopMatrix(); 

for(int i=0;i<=9;i++) 

{ 

glPushMatrix(); 

glTranslatef(75+10*i,530+8*i,0); 

glutSolidSphere(25,100,100); 

glPopMatrix(); 

} 

for(int i=0;i<=10;i++) 

{ 

glPushMatrix(); 

glTranslatef(275+10*i,605-5*i,0); 

glutSolidSphere(25,100,100); 

glPopMatrix(); 

} 

 

//body in red end 

for(int i=0;i<=1;i++) 

{ 

glPushMatrix(); 

glColor3f(1.0,0.0,0.0); 

glTranslatef(180+80*i,570,0.0); 

glScalef(0.5,2.5,1.0); 

glutSolidCube(50); 

glPopMatrix(); 

} 

for(int i=0;i<=1;i++) 

{ 

glPushMatrix(); 

glTranslatef(170+100*i,500,0.0); 

glColor3f(1.0,1.0,0.0); 

glutSolidSphere(25,100,100); 

glPopMatrix(); 

} 

//thumb 

glColor3ub(255,222,173); 

for(int i=0;i<=1;i++) 

{ 

glPushMatrix(); 

glTranslatef(100+250*i,450+20*i,0.0); 

glScalef(2.0,1.0,1.0); 

glutSolidCube(30); 

glPopMatrix(); 

} 

//nose 

glPushMatrix(); 

glTranslatef(320,695.0,0.0); 

glScalef(1.0,2.0,1.0); 

glColor3f(0.0,0.5,0.0); 

glutSolidCube(20); 

glPopMatrix(); 

glPopMatrix(); 

} 

//mario 

void developer() 

{ 

glPushMatrix(); 

setorthographic(); 

glClearColor(0.9f,0.7f,0.5f,1.0f); 

glColor3f(1.0,0.0,0.0); 

renderBitmapString(400,610,(void *)font,"DEVELOPED BY :"); 

renderBitmapString(400,510,(void *)font,"GAJENDRA SINGH NEGI"); 

renderBitmapString(400,410, (void*)font, "GADDAM JAYENDRA"); 

renderBitmapString(400,310, (void*)font, "SHIKHA SRIVASTAV"); 

glPopMatrix(); 

} 

void menu(int x) 

{ 

switch(x) 

{ 

 

case 0:exit(0); 

case 1:text=1; 

level=0; 

break; 

case 2:level=x-1; 

PlaySound(TEXT("world1-1.wav"),NULL,SND_ASYNC); 

break; 

case 3:level=x-1; 

PlaySound(TEXT("NT.wav"),NULL,SND_ASYNC); 

break; 

case 4:level=x;; 

PlaySound(TEXT("London Town.wav"),NULL,SND_ASYNC); 

break; 

default:break; 

} 

glutPostRedisplay(); 

 

} 

void powers() 

{ 

glPushMatrix(); 

setorthographic(); 

glColor3f(0.5,0.7,0.9); 

if(time>=31 && time<=50) 

for(int l=0;l<=8;l++) 

draw_circle(350+ptx,375-pty,l); 

glPopMatrix(); 

} 

void skateboard() 

{ 

glPushMatrix(); 

glTranslatef(45,135,40.0); 

glColor3f(0.0,0.0,1.0); 

glScalef(3.0,0.4,1.0); 

glutSolidCube(35); 

glPopMatrix(); 

for(int i=0;i<=1;i++) 

{ 

glPushMatrix(); 

glTranslatef(10+65*i,125,40); 

glColor3f(0.0,0.0,0.0); 

glutSolidSphere(15,100,100); 

glColor3f(1.0,1.0,1.0); 

glutSolidSphere(10,100,100); 

glColor3f(0.0,0.0,0.0); 

glutSolidSphere(5,100,100); 

glPopMatrix(); 

} 

} 

void mouse(int btn,int state,int x,int y) 

{ 

if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) 

{ 

 

} 

if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) 

{ 

} 

} 

void keyboard(unsigned char key ,int x,int y) 

{ 

switch(key) 

{ 

case 27:exit(0); 

} 

} 

void LTDisp() 

{ 

glColor3f(1.0,0.0,0.0); 

if(level==1) 

{ 

renderBitmapString(50,710,(void *)font,"LEVEL 1"); 

renderBitmapString(415,710,(void *)font,"WORLD 1-1"); 

} 

else if(level=2) 

{ 

renderBitmapString(50,710,(void *)font,"LEVEL 2"); 

renderBitmapString(415,710,(void *)font,"WORLD 1-2"); 

} 

renderBitmapString(800,710, (void*)font, s); 

} 

void Tdisp() 

{ 

glClearColor(0.0,0.0,1.0,1.0); 

glColor3f(1.0f,0.75f,0.35f); 

drawStrokeText("  SUPER-MARIO  ",180,700,0); 

drawStrokeText("   BROS  ",270,600,0); 

drawStrokeText("   START  ",240,400,0); 

drawStrokeText("SETTING",370,300,0); 

drawStrokeText("   EXIT  ",280,200,0); 

} 

void plaza() 

{ 

glPushMatrix(); 

gluLookAt(10.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0); 

glPushMatrix(); 

glRotatef(45,0.0,1.0,0.0); 

glTranslatef(0.0,-4.0,0.0); 

glScalef(6.5,0.5,1.0); 

glColor3ub(150,145,215); 

glutSolidCube(1.5); 

glLineWidth(15); 

glutWireCube(1.5); 

glPopMatrix(); 

glPushMatrix(); 

glTranslatef(0.0,-12.0,0.0); 

glColor3f(0.0,0.0,1.0); 

glRotatef(45,0.0,1.0,0.0); 

glScalef(17.0,2.0,1.0); 

glutSolidCube(1.5); 

glPopMatrix(); 

glPushMatrix(); 

glTranslatef(5.2,0.0,0.0); 

glRotatef(180,0,1,0); 

wall(); 

glPopMatrix(); 

glTranslatef(0.0,0.0,5.2); 

wall(); 

glPopMatrix(); 

} 

void DDM() 

{ 

int sub_menu=glutCreateMenu(menu); 

glutAddMenuEntry("LEVEL1",2); 

glutAddMenuEntry("LEVEL2",3); 

glutCreateMenu(menu); 

glutAddMenuEntry("START",1); 

glutAddSubMenu("LEVEL",sub_menu); 

glutAddMenuEntry("SETTING",9); 

glutAddMenuEntry("DEVELOPER",4); 

glutAddMenuEntry("QUIT",0); 

glutAttachMenu(GLUT_RIGHT_BUTTON); 

} 

void initRendering() 

{ 

glEnable(GL_DEPTH_TEST); 

glEnable(GL_COLOR_MATERIAL); 

} 

void display() 

{ 

glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT ); 

glMatrixMode(GL_MODELVIEW); 

glLoadIdentity(); 

glClearColor(1.0f,1.0f,1.0f,1.0f); 

if(text==1 && level==0) 

Tdisp(); 

if(level==1) 

{ 

setorthographic(); 

LTDisp(); 

for(int j=0;j<2100;j+=20) 

{ 

glLoadIdentity(); 

glTranslatef(-143+j,0.0f,0.0f); 

for(int i=0;i<10;i++) 

{ 

glTranslatef(15.0f,10.0f,0.0f); 

glColor3f(1.0f,0.0f,0.0f); 

glutSolidCube(15.0); 

} 

} 

glLoadIdentity(); 

glColor3f(0.0f,1.0f,0.0f); 

glBegin(GL_QUADS); 

glVertex3f(0.0,110,0.0); 

glVertex3f(1024.0,110,0.0); 

glVertex3f(1024.0,120,0.0); 

glVertex3f(0.0,120,0.0); 

glEnd(); 

int l; 

glClearColor(0.7f,0.9f,1.0f,1.0f); 

for(l=0;l<=35;l++) 

{ 

glColor3f(1.0,0.9,0.0); 

draw_circle(100,625,l); 

} 

Objects1(); 

glTranslatef(-200.0f,-260.0f,0.0f); 

grass(); 

glLoadIdentity(); 

glTranslatef(450.0f,-260.0f,0.0f); 

grass(); 

glLoadIdentity(); 

glTranslatef(400.0f,300.0f,0.0f); 

for(int j=0;j<=5;j++) 

{ 

glPushMatrix(); 

glScalef(35.0,35.0,35.0); 

glTranslatef(j*1,0.0,0.0); 

brick(); 

glPopMatrix(); 

} 

glTranslatef(90.0,150.0,0.0); 

glScalef(35.0,35.0,35.0); 

brick(); 

glLoadIdentity(); 

glDisable(GL_DEPTH_TEST); 

glColor3f(1.0,1.0,0.0); 

glScalef(0.5,0.5,0.0); 

drawStrokeText("?",775,570,0); 

drawStrokeText("?",930,570,0); 

drawStrokeText("?",1060,570,0); 

drawStrokeText("x",965,873,0); 

glLoadIdentity(); 

//multiple copies of beetle 

glLoadIdentity(); 

glTranslatef(700,0.0,0.0); 

glTranslatef(mb--,0.0,0.0); 

for(int k=0;k<=4;k++) 

{ 

glPushMatrix(); 

glTranslatef(150*k,0.0,0.0); 

if(k==1 || k==2) 

glTranslatef(200,0.0,0.0); 

else if(k==3 || k==4) 

glTranslatef(350,0.0,0.0); 

Beetle(); 

glPopMatrix(); 

} 

glLoadIdentity(); 

//movement of mario 

glPushMatrix(); 

glTranslatef(mx,my+20,0); 

glScalef(0.8,0.8,0.8); 

mario(); 

skateboard(); 

glPopMatrix(); 

//movement of mario 

glEnable(GL_DEPTH_TEST); 

} 

else if(level==4) 

{ 

developer(); 

} 

else if(level==2) 

{ 

glPushMatrix(); 

setorthographic(); 

glClearColor(0.0f,0.0f,0.0f,1.0f); 

for(int l=0;l<=35;l++) 

{ 

glColor3f(1.0,1.0,1.0); 

draw_circle(100,625,l); 

} 

stars(); 

LTDisp(); 

comet(); 

glDisable(GL_DEPTH_TEST); 

glTranslatef(-220-bxt,165,0); 

if(time<=30) 

glRotatef(180,0,0,0); 

BlackGhost(); 

glLoadIdentity(); 

glScalef(0.6,0.6,0.6); 

glTranslatef(510,270,0); 

glScalef(1.5,1.5,1.5); 

mario(); 

glLoadIdentity(); 

powers(); 

glEnable(GL_DEPTH_TEST); 

glPopMatrix(); 

glClearColor(0.0f,0.0f,0.0f,1.0f); 

glMatrixMode(GL_PROJECTION); 

glLoadIdentity();; 

gluPerspective(85.0,1024/768,1.0,100.0); 

glMatrixMode(GL_MODELVIEW); 

glLoadIdentity(); 

plaza(); 

} 

glutSwapBuffers(); 

} 

void idle() 

{ 

if(level==1) 

{ 

if(mx<=200 || mx>=600)//250 

mx+=0.5; 

if(mx>=200 && mx<=600 && my!=210)//250,190 

{ 

mx++; 

my+=2; 

} 

if(my==210 && mx<=600)//190 

mx+=0.5; 

if(mx>=600 && my!=0) 

{ 

my--; 

} 

} 

else 

{ 

mx=0.0; 

my=0.0; 

} 

if(level==2) 

{ 

if(time<=50) 

{ 

ptx+=2; 

pty+=0.5; 

if(400-pty==300 || 650-bxt<=350+ptx) 

{ 

pty=0.0; 

ptx=0.0; 

} 

} 

} 

 

m+=2; 

n-=2; 

o+=0.2; 

c+=2.5; 

if(c==700) 

c=0; 

if(m>800) 

m=0.0; 

if(n==-1024) 

n=0; 

if(o+625>768) 

 { 

o=0; 

n=0; 

 } 

if(level==2 && time<=50) 

bxt+=0.2; 

else 

bxt=0.0; 

angle+=2.0f; 

if(angle>360) 

angle-=360; 

if(level==1) 

{ 

mov-=0.5; 

mb-=0.01; 

} 

else 

{ 

mov=0.0; 

mb=0.0; 

} 

glutPostRedisplay(); 

} 

 

void reshape(int w , int h) 

{ 

glViewport(0,0,w,h); 

glMatrixMode(GL_PROJECTION); 

glLoadIdentity(); 

glOrtho(0,1024,0,768,-50,50); 

} 

void update(int value) 

{ 

    t =201-glutGet(GLUT_ELAPSED_TIME) / 1000.0; 

    time = (int)t; 

if(time==0) 

exit(0); 

if(time==195) 

menu(1); 

if(time==180) 

menu(2); 

if(time==90) 

menu(3); 

if(time==20) 

menu(4); 

    sprintf(s, "TIME : %2d Sec", time); 

if(time%2!=0) 

mnt=1; 

else 

mnt=0; 

    glutTimerFunc(1000, update, 0); 

    glutPostRedisplay(); 

}  

 

int main(int argc,char** argv) 

{ 

glutInit(&argc,argv); 

glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); 

glutInitWindowSize(1024,768); 

glutInitWindowPosition(0,0); 

glutCreateWindow("sampleProgram"); 

initRendering(); 

glutReshapeFunc(reshape); 

//DDM();//drop down menu 

glutDisplayFunc(display); 

glutKeyboardFunc(keyboard); 

glutIdleFunc(idle); 

glutMouseFunc(mouse); 

glutTimerFunc(1000,update,0); 

glutMainLoop(); 

return 0; 

} 

 

 