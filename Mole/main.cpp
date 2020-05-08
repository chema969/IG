#include <cmath>
#include <cstdlib>
#include <GL/glut.h>
#include <string>
#include <vector>

#define SCREEN_H 300
#define SCREEN_W 400

std::string puntaje="Score=";
int score;
std::vector <std::vector <int> > puntosCirc={{50,125},
    {150,125},
    {250,125},
    {350,125},
    {100,200},
    {200,200},
    {300,200},
    {100,50},
    {200,50},
    {300,50}};

void drawCircle(float x, float y,float rad){
   glBegin(GL_POLYGON);
	for(int i=0;i<360;i=i+6){
          float theta=(i*3.14)/180;
	  glVertex2f(x+rad*cos(theta),y+rad*sin(theta));
	}
   glEnd();
}

void displayMole(std::vector <int> v){
    glColor3ub(244,164,96);
    int x=v[0];
    int y=v[1];
    drawCircle(x,y,20);

    glColor3ub(0,0,0);
  
    drawCircle(x-6,y+6,3);
    drawCircle(x+6,y+6,3);

    glBegin(GL_LINES);
    glVertex3f(x-6,y-2,0);
    glVertex3f(x-2,y-4,0);

    glVertex3f(x-2,y-4,0);
    glVertex3f(x+2,y-4,0);

    glVertex3f(x+2,y-4,0);
    glVertex3f(x+6,y-2,0);
    glEnd();
}

void displayFail(float x, float y){
    glColor3ub(255,0,0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(x-12,y-12);
    glVertex2f(x+12,y+12);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(x-12,y+12);
    glVertex2f(x+12,y-12);
    glEnd();
    glLineWidth(1);
}

void display(void){
    glClearColor(0.1, 0.7, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //Permitimos movimiento
    glMatrixMode(GL_MODELVIEW);
	glPointSize(50);
    glLoadIdentity();

    int r = 139;
    int g = 69;
    int b = 19;
    glEnable(GL_POINT_SMOOTH);
    //Pintamos nuestro punto
    glColor3ub(r, g, b);
    //Dibujamos los circulos
    for(int i=0;i<puntosCirc.size();i++)
        drawCircle(puntosCirc[i][0],puntosCirc[i][1],25);
    

    //Dibujamos el cuadrado donde pondremos la puntuación
    glColor3ub(255,255,255);
    glBegin(GL_QUADS);//Vertices del cuadrilatero para el score
    glVertex2f(25, 250);
    glVertex2f(25, 285);
    glVertex2f(250, 285);
    glVertex2f(250, 250);
    glEnd();

    glBegin(GL_QUADS);//Vertices del cuadrilatero para los fallos
    glVertex2f(275, 250);
    glVertex2f(275, 285);
    glVertex2f(375, 285);
    glVertex2f(375, 250);
    glEnd();


    glColor3ub(0,0,0);
    glRasterPos2d(100, 260);
    std::string str=puntaje+std::to_string(score);
    for (int i=0; i<str.size(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }

    displayMole(puntosCirc[3]);
    displayMole(puntosCirc[8]);
    displayFail(295,267.5);
    //Swap buffers
    glutSwapBuffers();
}

static void reshape(int w, int h){
	glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(0, SCREEN_W, 0, SCREEN_H, -1.0, 1.0);
    glFlush();


}

int main(int argc, char **argv){
    //Inicializamos valores

	
    glutInit(&argc, argv);
    glutInitWindowSize(SCREEN_W,SCREEN_H);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Practica 8: Whac-a-Mole, interfaz");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    //glutIdleFunc(moveObject);

    glutMainLoop();
}
