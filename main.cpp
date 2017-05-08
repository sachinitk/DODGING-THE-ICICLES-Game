
#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include "Player.cpp"
#include <stdio.h>

Player player;
Icicles ics;

int overScore;
int start = 1;
int play = 2;
int pause = 3;
int over = 4;
int resume = 5;
int gamestate = start;
int life = 5;
char str[20];
static void reshape(int width, int height)
{

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void timer(int){

    if(gamestate == play){
        ics.update();
        if(player.hitByIcicle(ics)){
            if(life == 1){
                gamestate = over;
                overScore = ics.iciclesDodged;
                ics.init(0);
            }
            ics.init(1);
            life -= 1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);

}



void drawText(char str[],float x,float y){

        glColor3f(1,1,0);
        glPushMatrix();
        glTranslatef(x,y,0);
        glScalef(.1,.2,.1);
        for(int i=0;str[i]!='\0';i++)
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,str[i]);
        glPopMatrix();

    }

void gameoverMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(Constants::WORLD_WIDTH,0);
        glVertex2f(Constants::WORLD_WIDTH,Constants::WORLD_HEIGHT);
        glVertex2f(0,Constants::WORLD_HEIGHT);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,0,0);

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.75);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.75);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.25);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.75);
    glEnd();
glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.75);
    glEnd();


    glPopMatrix();

    sprintf(str,"***** GAME OVER *****");
    drawText(str,Constants::WORLD_WIDTH/2-80,Constants::WORLD_HEIGHT * 0.75-40);

    sprintf(str,"SCORE : %d ",overScore);
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2);

    sprintf(str,"1. Quit");
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2-40);

    sprintf(str,"2. New Game");
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2-80);

}

void startMenu()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,0,0);

    glBegin(GL_QUADS);
        glVertex2f(0,0);

glVertex2f(Constants::WORLD_WIDTH,0);
        glVertex2f(Constants::WORLD_WIDTH,Constants::WORLD_HEIGHT);
        glVertex2f(0,Constants::WORLD_HEIGHT);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,0,0);

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.75);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.75);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.25);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.75);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.75);
    glEnd();

    glPopMatrix();
sprintf(str,"press S for Start Q for Quit");
    drawText(str,Constants::WORLD_WIDTH/2-100,Constants::WORLD_HEIGHT/2+70);

    sprintf(str,"START GAME");
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2);

    sprintf(str,"QUIT");
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2-50);

}

void pauseMenu(){

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,0,0);

    glBegin(GL_QUADS);
        glVertex2f(0,0);
        glVertex2f(Constants::WORLD_WIDTH,0);
        glVertex2f(Constants::WORLD_WIDTH,Constants::WORLD_HEIGHT);
        glVertex2f(0,Constants::WORLD_HEIGHT);
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,0,0);

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.75);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.75);
glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.25);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.75,Constants::WORLD_HEIGHT*0.75);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.25);
        glVertex2f(Constants::WORLD_WIDTH*0.25,Constants::WORLD_HEIGHT*0.75);
    glEnd();


    sprintf(str,"1. RESUME");
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2+50);

    sprintf(str,"2. NEW GAME");
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2);

    sprintf(str,"3. QUIT GAME");
    drawText(str,Constants::WORLD_WIDTH/2-20,Constants::WORLD_HEIGHT/2-50);

}


static void display(void)
{
    if(gamestate == play ){
glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glClearColor(0.24,0.24,0.24,0);

        player.render();
        ics.render();
        sprintf(str,"Life : %d ",life);
        drawText(str,40,Constants::WORLD_HEIGHT-80);

        sprintf(str,"P-Pause");
        drawText(str,40,Constants::WORLD_HEIGHT-120);
    }

    else if(gamestate == start){
        startMenu();

    }

    else if(gamestate == pause){
        pauseMenu();
    }

    else if (gamestate == over){
        gameoverMenu();

    }

    glutSwapBuffers();

}

static void idle(void)
{
    glutPostRedisplay();
}

static void key(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_RIGHT:
            if(gamestate == play) {player.update('r');}
            break;

        case GLUT_KEY_LEFT:
            if(gamestate == play) {player.update('l');}
            break;

    }

    glutPostRedisplay();
}

static void normalKey(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's':
        case 'S':
            if(gamestate == start) {gamestate = play;}
            break;

        case 'p':
        case 'P':
            if(gamestate == play) {gamestate = pause;}
            break;

        case '1':
if(gamestate == pause) {gamestate = play;}
            if(gamestate == over) {exit(0);}
            break;

        case '2':
            if(gamestate == pause || gamestate == over) {
                ics.init(0);
                gamestate = play;
                life = 5;
            }
            break;

        case '3':
            if(gamestate == pause) {exit(0);}

        case 'q':
            if(gamestate == start) {exit(0);}
           break;

    }

    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(Constants::WORLD_WIDTH,Constants::WORLD_HEIGHT);
    glutInitWindowPosition(50,50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Icicle Game");

    glutReshapeFunc(reshape);

    glutDisplayFunc(display);


    glutKeyboardFunc(normalKey);
    glutSpecialFunc(key);

    glutIdleFunc(idle);

    glutTimerFunc(16,timer,1);

    glutMainLoop();

    return EXIT_SUCCESS;
}
