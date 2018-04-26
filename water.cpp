#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>


#define BOUNDS    1



#define WATERSIZE 200
#define DAMP 20

float water[2][WATERSIZE][WATERSIZE];

int spin_x, spin_y, spin_z; /* x-y rotation and zoom */
int h, w;                    /* height, width  of window */
int old_x, old_y, move_z;
int depth = 3;
int i = 0, counter = 0;

int t = 0, f = 1;

void calcwater() {
	int x, y;
	float n;
	for(y = 1; y < WATERSIZE-1; y++) {
		for(x = 1; x < WATERSIZE-1; x++) {
			n = ( water[t][x-1][y] +
				  water[t][x+1][y] + 
				  water[t][x][y-1] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / DAMP);
			water[f][x][y] = n;
		}
	}

	y = 0;
	for(x = 1; x < WATERSIZE-1; x++) {
			n = ( water[t][x-1][y] +
				  water[t][x+1][y] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / DAMP);
			water[f][x][y] = n;
	}
	
	
	x = 0;
	for(y = 1; y < WATERSIZE-1; y++) {
			n = ( water[t][x+1][y] + 
				  water[t][x][y-1] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / DAMP);
			water[f][x][y] = n;
	}

	x = WATERSIZE-1;
	for(y = 1; y < WATERSIZE-1; y++) {
			n = ( water[t][x-1][y] +
				  water[t][x][y-1] + 
				  water[t][x][y+1]
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / DAMP);
			water[f][x][y] = n;
	}
	y = WATERSIZE-1;
	for(x = 1; x < WATERSIZE-1; x++) {
			n = ( water[t][x-1][y] +
				  water[t][x+1][y] + 
				  water[t][x][y-1] 
				  ) /2;
			n -= water[f][x][y];
      		n = n - (n / DAMP);
			water[f][x][y] = n;
	}

}

void init();

void reshape(int width, int height) {
    w = width;
    h = height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

void display(void) {
    int i, j, tmp;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glPushMatrix();
    glTranslatef(0, 0, spin_z-220);
    glRotatef(spin_x, 0, 1, 0);
    glRotatef(spin_y, 1, 0, 0);

    
	calcwater();
	glBegin(GL_POINTS);
	for(i = 0; i < WATERSIZE; i++) {
		for(j = 0; j < WATERSIZE; j++) {
				glColor3f(0,0,1);
    			glVertex3f(j-WATERSIZE/2, i-WATERSIZE/2, water[t][j][i]);
		}
	}
	glEnd();

	tmp = t; t = f; f = tmp;


    glPopMatrix();

    
    glutSwapBuffers();
}

int num  = 0;
int delay = 70;
void idle(void)
{
	
	// if(!(++num %delay))
	// {
	// 	water[f][rand()%WATERSIZE][rand()%WATERSIZE] = -rand()%200;
	// 	delay = rand()%100 + 50;
	// }
    glutPostRedisplay();
}

// void
// mouse(int button, int state, int x, int y)
// {

//     switch(button) {
//         case 0:
//             old_x = x - spin_x;
//             old_y = y - spin_y;
//             break;
//         case 2:
//             old_y = y - spin_z;
//             move_z = (move_z ? 0 : 1);
//     }
            

//     glutPostRedisplay();

// }

// void 
// motion(int x, int y) {

//     // if(!move_z) {
//     //     spin_x = x - old_x;
//     //     spin_y = y - old_y;
//     // } else {
//         spin_y = 60;
//         spin_z = -100;
//     // }

//     glutPostRedisplay();
// }


void
keyboard(unsigned char key, int x, int y)
{
    static int old_x = 50;
    static int old_y = 50;
    static int old_width = 512;
    static int old_height = 512;

    switch (key) {
        case 'x':
                exit(0);
            break;
        case 'm':
                glutPositionWindow(old_x, old_y);
                glutReshapeWindow(old_width, old_height);
            break;
        // case 'f':
        //     if (glutGet(GLUT_WINDOW_WIDTH) < glutGet(GLUT_SCREEN_WIDTH)) {
        //         old_x = glutGet(GLUT_WINDOW_X);
        //         old_y = glutGet(GLUT_WINDOW_Y);
        //         old_width = glutGet(GLUT_WINDOW_WIDTH);
        //         old_height = glutGet(GLUT_WINDOW_HEIGHT);
        //         glutFullScreen();
        //     }
        //     break;
		case ' ':
			water[f][counter++][counter++] = -1000;
			break;

    }
}


void init(void) {
	int i, j;

    w = 450;
    // w = glutGet(GLUT_WINDOW_WIDTH);
    // h = glutGet(GLUT_WINDOW_HEIGHT);
    h = 450;

   // glEnable(GL_LIGHTING);
  //  glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

	for( i = 0; i < WATERSIZE; i++) 
		for( j = 0; j < WATERSIZE; j++) {
			water[0][j][i] = 0;
			water[1][j][i] = 0;
		}
}

int
main(int argc, char** argv)
{
    

   // srand(time(NULL));

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(512, 512);
    glutInit(&argc, argv);

    glutCreateWindow("Simulating Water");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);
    // glutMouseFunc(mouse);
    // glutMotionFunc(motion);

    glEnable (GL_DEPTH_TEST);

    if(argc == 2) {
        if (strcmp(argv[1], "-h") == 0) {
            fprintf(stderr, "%s [depth]\n", argv[0]);
            exit(0);
        }
        sscanf(argv[1], "%d", &depth);
    }

	printf("Water Simulation \n");
    init();

    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


