/*===============================================================*\

  Jeudi 23 septembre 2014

  Arash Habibi

  01_evenements.c

  Un programme test qui utilise un grand nombre des primitives
  de glut.

\*===============================================================*/

#include <stdio.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdlib.h>
#include <time.h>

float r;
int la, lb;

//------------------------------------------------------------------
//	C'est le display callback. A chaque fois qu'il faut
//	redessiner l'image, c'est cette fonction qui est
//	appelee. Tous les dessins doivent etre faits a partir
//	de cette fonction.
//------------------------------------------------------------------
void display_CB()
{
    glClear(GL_COLOR_BUFFER_BIT);

	// Dessin d'un triangle rouge avec un dégradé noir sur un sommet

    glColor3ub(r,0,0);

    glBegin(GL_POLYGON);
    glVertex2i(200,40);
    glVertex2i(40,200);
    glColor3ub(0,0,0);
    glVertex2i(360,360);
    glEnd();

	// Dessin d'une ligne brisée blanche

    glColor3ub(255,255,255);

    glBegin(GL_LINE_STRIP);
    glVertex2i(la,lb);
    glVertex2i(360,200);
    glVertex2i(200,360);
    glEnd();

    glutSwapBuffers();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir en fonction de la position de
// la souris (x,y), en fonction du bouton de la souris qui a été
// pressé ou relaché.
//------------------------------------------------------------------

void mouse_CB(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN){
			fprintf(stderr,"Presser ");
			r = ((float)x/y) * 255;
			la = x;
			lb = y;
	}
	else if(state==GLUT_UP)
			fprintf(stderr,"Relacher ");

	if(button==GLUT_LEFT_BUTTON)
		fprintf(stderr,"Bouton gauche souris en (%d,%d).\n",x,y);

	else if((button==GLUT_MIDDLE_BUTTON)||(button==5))
		fprintf(stderr,"Bouton du milieu souris en (%d,%d).\n",x,y);

	else if(button==GLUT_RIGHT_BUTTON)
		fprintf(stderr,"Bouton droit souris en (%d,%d).\n",x,y);

	else
		fprintf(stderr,"Autre : %d (%d %d %d).\n",button,GLUT_LEFT_BUTTON,GLUT_MIDDLE_BUTTON,GLUT_RIGHT_BUTTON);

	glutPostRedisplay(); 
}

//------------------------------------------------------------------
// Cette fonction permet de réagir aux mouvements de la souris
// quand l'un des boutons de la souris est pressé.
//------------------------------------------------------------------

void mouse_move_CB(int x, int y)
{
	fprintf(stderr,"Position de la souris : (%d,%d)\n",x,y);
	glutPostRedisplay();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir au fait que l'utilisateur
// presse une touche (non-spéciale) du clavier.
//------------------------------------------------------------------

void keyboard_CB(unsigned char key, int x, int y)
{
	printf("key = %c = %d\n", key, key);
	if(key==113) exit(0); // Touche Escape : quitter le programme
	glutPostRedisplay();
}

//------------------------------------------------------------------
// Cette fonction permet de réagir au fait que l'utilisateur
// presse une touche spéciale (F1, F2 ... F12, home, end, insert,
// haut, bas, droite, gauche etc).
//------------------------------------------------------------------

void special_CB(int key, int x, int y)
{
	int mod;

	switch(key)
	{
 	case GLUT_KEY_F1  : printf("touche F1"); break;
 	case GLUT_KEY_F2  : printf("touche F2"); break;
 	case GLUT_KEY_F3  : printf("touche F3"); break;
 	case GLUT_KEY_F4  : printf("touche F4"); break;
 	case GLUT_KEY_F5  : printf("touche F5"); break;
 	case GLUT_KEY_F6  : printf("touche F6"); break;
 	case GLUT_KEY_F7  : printf("touche F7"); break;
 	case GLUT_KEY_F8  : printf("touche F8"); break;
 	case GLUT_KEY_F9  : printf("touche F9"); break;
 	case GLUT_KEY_F10 : printf("touche F10"); break;
 	case GLUT_KEY_F11 : printf("touche F11"); break;
 	case GLUT_KEY_F12 : printf("touche F12"); break;

 	case GLUT_KEY_LEFT : printf("touche gauche"); break;
 	case GLUT_KEY_UP   : printf("touche haut"); break;
	case GLUT_KEY_RIGHT: printf("touche droite"); break;
 	case GLUT_KEY_DOWN : printf("touche bas"); break;

 	case GLUT_KEY_PAGE_UP   : printf("touche page suiv"); break;
 	case GLUT_KEY_PAGE_DOWN : printf("touche page prec"); break;

 	case GLUT_KEY_HOME   : printf("touche HOME"); break;
 	case GLUT_KEY_END    : printf("touche END"); break;
 	case GLUT_KEY_INSERT : printf("touche INSERT"); break;
	default : fprintf(stderr,"touche inconnue.");
	}

	mod = glutGetModifiers();

	switch(mod)
	{
 	case GLUT_ACTIVE_SHIFT : printf("\t SHIFT\n"); break;
	case GLUT_ACTIVE_CTRL  : printf("\t CTRL\n");  break;
	case GLUT_ACTIVE_ALT   : printf("\t ALT\n");   break;
	case 0                 : printf("\t\n"); break ;
	default : fprintf(stderr,"Modifier unknown.\n");
	}
	glutPostRedisplay(); 
}

//------------------------------------------------------------------------

int main(int argc, char **argv)
{
    int largeur = 400, hauteur = 400;
    int windowPosX = 100, windowPosY = 100;
	r = 255;
	la = 0;
	lb = 0;

    glutInitWindowSize(largeur,hauteur);
    glutInitWindowPosition(windowPosX,windowPosY);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE );
    glutInit(&argc, argv);
    glutCreateWindow(argv[0]);

    glViewport(0, 0, largeur, hauteur);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(0,largeur,hauteur,0,-1,1);

    glutDisplayFunc(display_CB);
	glutKeyboardFunc(keyboard_CB);
	glutSpecialFunc(special_CB);
	glutMouseFunc(mouse_CB);
	glutMotionFunc(mouse_move_CB);

    glutMainLoop();

    return 0;
}
