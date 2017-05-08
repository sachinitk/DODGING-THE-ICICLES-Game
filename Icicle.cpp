#include<utility>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include "Constants.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class Icicle {

	public:

	std::pair<float,float> position;
    std::pair<float,float> velocity;
    int segment;
    float angle;

    Icicle(float x,float y) {
        position.first = x;
        position.second = y;
        segment = 1000;
        velocity = std::make_pair(0.0f,0.0f);
    }

void intit(std::pair<float,float> pos){
        time_t t;
        srand(time(&t));
        position.first = pos.first;
        position.second = pos.second;
        velocity = std::make_pair(0.0f,0.0f);
    }

	void update() {
        velocity.second += Constants::ICICLES_ACCELERATION * 0.166;
        position.second += velocity.second * 0.166;
    }

    void render() {

        glColor3f(static_cast <float> (rand()) / static_cast <float> (RAND_MAX),static_cast <float> (rand()) / static_cast <float> (RAND_MAX)
                  ,static_cast <float> (rand()) / static_cast <float> (RAND_MAX));

            glBegin(GL_POLYGON);
            glVertex2f(position.first, position.second);
            glVertex2f(position.first - Constants::ICICLES_WIDTH / 2, position.second + Constants::ICICLES_HEIGHT);
            glVertex2f(position.first + Constants::ICICLES_WIDTH / 2, position.second + Constants::ICICLES_HEIGHT);
        glEnd();

    }
};


Icicles.cpp:-

#include<vector>
#include "Icicle.cpp"
#include<cstdlib>
#include<ctime>
#include<random>
#include<stdio.h>


class Icicles {


	public:
    int iciclesDodged;
    std::vector<Icicle> icicleList;
    char str[100];
        Icicles() {
        iciclesDodged = 0;
    }

    void init(int newGame){
        if(newGame == 0){
            iciclesDodged = 0;
        }

        icicleList.clear();
    }

    void update() {

        if(icicleList.size() < Constants::ARRAY_CAPACITY ){

            icicleList.push_back(Icicle(rand()%Constants::WORLD_WIDTH,Constants::WORLD_HEIGHT));
}

        for (int i = 0; i < int(icicleList.size()); i++) {
            icicleList[i].update();
        }

        for (int i = 0; i < int(icicleList.size()); i++) {
            if (icicleList[i].position.second < -1*Constants::ICICLES_HEIGHT) {
                iciclesDodged += 1;
                icicleList.erase(icicleList.begin()+i);
            }
        }

    }

    void drawText(int score){
        char str[20];

        glColor3f(1,1,0);
        glPushMatrix();
        sprintf(str,"S c o r e : %d",score);
        glTranslatef(40,Constants::WORLD_HEIGHT-40,0);
        glScalef(.1,.2,.1);
        for(int i=0;str[i]!='\0';i++)
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN,str[i]);
        glPopMatrix();

    }

	void render() {


        for (Icicle icicle : icicleList) {
            icicle.render();

 }
        drawText(iciclesDodged);
  }
};
