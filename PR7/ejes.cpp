#include <cmath>
#include <cstdlib>
#include <GL/glut.h>

/* Coordenadas */
float x;
float y;
float z;
float tamanyo_circulo;
float max_x;
float min_x;
float velocidad;
float ortho_min_x;
float ortho_max_x;
float ortho_min_y;
float ortho_max_y;
/**
 * Metodo que va a mover el objeto
 */
void moveObject(void){
	if(z>=0){
		if(x<max_x){
			x=x+velocidad;
			y=pow(x,z);
		   }
		else{
			x=min_x;
			y=pow(x,z);
			}	
	}	
	else{
		if((x+velocidad)==0){
			x=x+velocidad*2;
			y=pow(x,z);
		}
		else{
			if(x<max_x){
			x=x+velocidad;
			y=pow(x,z);
		   }
		else{
			x=min_x;
			y=pow(x,z);
			}	
		}
	}
	glutPostRedisplay();
};

void display(void){
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //Permitimos movimiento
    glMatrixMode(GL_MODELVIEW);
	glPointSize(tamanyo_circulo);
    glLoadIdentity();

	//Pintamos los ejes
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	//Eje x
	glVertex3f(ortho_min_x, 0, 0);
	glVertex3f(ortho_max_x, 0, 0);
	//Eje y
	glVertex3f(0, ortho_min_y, 0);
	glVertex3f(0, ortho_max_y, 0);
	glEnd();

    int r = 140;
    int g = 170;
    int b = 200;

    //Pintamos nuestro punto
	glColor3ub(r, g, b);
	glBegin(GL_POINTS);
	glVertex3f(x,y,0);
	glEnd();


	//Swap buffers
	glutSwapBuffers();
}

static void reshape(int w, int h){
	glViewport(0, 0, w, h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

    glOrtho(ortho_min_x, ortho_max_x, ortho_min_y, ortho_max_y, -10.0, 10.0);

    glFlush();
}


int main(int argc, char **argv){
    //Inicializamos valores

	min_x=-10;
	z= 1;
	max_x=10;
	tamanyo_circulo=10;
	velocidad=0.1;
	ortho_min_x=-10.0;
	ortho_max_x=10.0;
	ortho_min_y=-10.0;
	ortho_max_y=10.0;

	x = min_x;
	y = pow(x,z);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("Practica 7: Movimiento de un circulo a traves de unos ejes siguiendo una funcion");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(moveObject);

    glutMainLoop();
}
