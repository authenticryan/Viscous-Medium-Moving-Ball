#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include "gl_helper.h"
#include <time.h>


#define BOUNDS    1



#define WATERSIZE 450
#define DAMP 20

float water[2][WATERSIZE][WATERSIZE];

int spin_x, spin_y, spin_z; /* x-y rotation and zoom */
int h, w;                    /* height, width  of window */
int old_x, old_y, move_z;
int depth = 3;
int i = 0, counter = 0;

// for the ping pong program  
// starts here -----------------------
const int width = 450 , height = 450 ;
const int RacketWidth = 10 , RacketHeight = 460;
const int BallWidth = 10 , BallHeight = 10;

double time1;

int LeftY=0;
int RightY=0;
int Racketspeed=5;

int ballX,ballY;
int ballVelocityX = 4;
float ballVelocityY =0.0f;
float StoredVelocity = 0.0f;


int LeftScore = 0;
int RightScore = 0;

void Reset();
void Collisions();
bool Between(int target, int min , int max );

// ends here --------------------------------

clock_t this_time = clock();
clock_t last_time = this_time;

const int NUM_SECONDS = .2;
double time_counter = 0;


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

    glViewport(0, 0, 450, 450);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
}

void Collisions(){

	this_time = clock();
	time_counter += (double)(this_time - last_time);
	last_time = this_time;

    if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC) ){

		time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
        // time1 = glfwGetTime()*TimeSpeed;

        ballX += ballVelocityX;

        StoredVelocity += ballVelocityY;

		printf("Value of stored velocity %f\n", StoredVelocity);
        // To ensure that the ball bounces
        if(StoredVelocity > 10.0f){
            ballY+=1;
            StoredVelocity-=10;
        }else if(StoredVelocity < -10.0f){
            ballY-=1;
            StoredVelocity+=10;

        }
    }


    //Ball at Right Edge
    if( ballX > 440 ){
            ballVelocityX= -ballVelocityX;

    //Ball at Left Edge
    }else if( ballX < 10 ){
            ballVelocityX= -ballVelocityX;

    //Ball at bottom Edge
    }else if( ballY <= 0 ){

        ballY = 0;
        ballVelocityY= -ballVelocityY;
        // printf("Ball velocity y: %f", ballVelocityY);

    //Ball at top Edge
    }else if( ballY >= 450 ){

		printf("Ball position in the y axis before: %d\n", ballY);
        ballY = 450;
		printf("Ball position in the y axis: %d\n", ballY);
        printf("Ball velocity y before: %f\n", ballVelocityY);
        
        ballVelocityY = -ballVelocityY;
        printf("Ball velocity y: %f\n", ballVelocityY);

    }

	water[f][ballX%WATERSIZE][ballY%WATERSIZE] = -100;

}

bool Between(int target, int a , int b ){

int max;
int min;

if( a > b){

    max = a;
    min = b;

}else{
    max=b;
    min=a;
}

     if( target < max && target > min)
        return true;

 return false;

}

void display(void) {
    int i, j, tmp;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	// Code from main.cpp
		
		glPushMatrix();

		// glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        glOrtho(0 , 450 , 0 , 450 , 0 , 1);

        glClearColor(0.0f, 0.0f, 0.0f, 0);
        glClear(GL_COLOR_BUFFER_BIT);


		glColor3f(1.0, 1.0, 1.0);
		//Left Racket
        gl_helper::DrawRect( 0 , LeftY, RacketWidth , RacketHeight  );
        //Right Racket
        gl_helper::DrawRect( width - 10 , RightY , RacketWidth , RacketHeight  );
        //Ball
        gl_helper::DrawRect( ballX , ballY , BallWidth , BallHeight  );


        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        

        //Collision Detection
        Collisions();
	
	
		


		glPopMatrix();
	// end of code from main.cpp

	glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glEnable(GL_DEPTH_TEST);

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
// keyboard(unsigned char key, int x, int y)
// {
//     static int old_x = 50;
//     static int old_y = 50;
//     static int old_width = 512;
//     static int old_height = 512;

//     // switch (key) {
//     //     case 'x':
//     //             exit(0);
//     //         break;
//     //     case 'm':
//     //             glutPositionWindow(old_x, old_y);
//     //             glutReshapeWindow(old_width, old_height);
//     //         break;
//     //     // case 'f':
//     //     //     if (glutGet(GLUT_WINDOW_WIDTH) < glutGet(GLUT_SCREEN_WIDTH)) {
//     //     //         old_x = glutGet(GLUT_WINDOW_X);
//     //     //         old_y = glutGet(GLUT_WINDOW_Y);
//     //     //         old_width = glutGet(GLUT_WINDOW_WIDTH);
//     //     //         old_height = glutGet(GLUT_WINDOW_HEIGHT);
//     //     //         glutFullScreen();
//     //     //     }
//     //     //     break;
// 	// 	case ' ':
// 	// 		water[f][ballX][ballY] = -1000;
// 	// 		break;

//     // }
// }


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
    glutInitWindowSize(width, height);
    glutInit(&argc, argv);

	// setting initial parameters from main.cpp
	     //Ball Starting position
     	ballX = width/2 - 5 ;
     	ballY = height/2 - 5;

        // initial ball velocity
     	ballVelocityY= 10;
     


    	LeftY = 0;
    	RightY = 0;

	// end of setting parameters from main.cpp

    glutCreateWindow("Particle in volumic mesh");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // glutKeyboardFunc(keyboard);
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

	// printf("Water Simulation \n");
    init();

    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}


