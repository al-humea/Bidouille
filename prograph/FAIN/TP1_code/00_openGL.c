
/*===============================================================*\

    Jeudi 23 septembre 2014
	Arash Habibi
	00_openGL.c

	Un programme qui dessine un triangle rouge sur fond noir
	avec openGL.

\*===============================================================*/

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>

void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);
	// Efface toute la fenetre

    glBegin(GL_POLYGON);
    glColor3ub(255,255,0);
    glVertex2i(150,40);
    glVertex2i(20,100);
    glColor3ub(0,0,255);
    glVertex2i(360,360);
    glEnd();

    
    glBegin(GL_POLYGON);
    glColor3ub(255,0,0);
    glVertex2i(150,100);
    glColor3ub(0, 0,255);
    glVertex2i(200,150);
    glColor3ub(0,255,0);
    glVertex2i(150,200);
    glColor3ub(255,255,255);
    glVertex2i(100, 150);
    glEnd();

    glColor3ub(0,255,255);

    glBegin(GL_LINE_STRIP); // On commence le tracer d'une ligne brisée ouverte
    glVertex2i(0,0);
    glVertex2i(360,200);
    glVertex2i(200,360);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    int largeur = 400, hauteur = 400;
    int windowPosX = 100, windowPosY = 100;

	// Definition de la taille de la fenetre pour glut
    glutInitWindowSize(largeur,hauteur);

	// Definition de la position de la fenetre
    glutInitWindowPosition(windowPosX,windowPosY);

	// Allocation des buffers images (et autres eventuellement)
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );

	// Initialisation de glut
    glutInit(&argc, argv);

	// Donner un nom à la fenetre
    glutCreateWindow(argv[0]);

	// Definition de la taille de la fenêtre pour OpenGL
    glViewport(0, 0, largeur, hauteur);

	// Initialisation des matrices de modelisation et de projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// On n'a pas de projection perspective mais orthogonal
    glOrtho(0,largeur,hauteur,0,-1,1);

	// Definition de display_CB comme fonction à appeler pour l'affichage
    glutDisplayFunc(display_CB);

	// Démarrage de la boucle d'attente des événements
    glutMainLoop();

    return 0;
}
