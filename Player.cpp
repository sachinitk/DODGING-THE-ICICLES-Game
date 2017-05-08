#include<utility>
#include <iostream>
#include <cmath>
#include "Icicles.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Player {

    std::pair<float,float> position;
    std::pair<float,float> hand;
    std::pair<float,float> legs;
    int deaths=0;

	public:

    Player() {
        position.first = Constants::PLAYER_HEAD_RADIUS;
        position.second = Constants::PLAYER_HEAD_HEIGHT;
    }

    void update(char key) {
        if (key=='l') {
position.first -= /*delta*/0.166 * Constants::PLAYER_MOVEMENT_SPEED;
        }
        else if (key=='r') {
            position.first += /*delta*/0.166 * Constants::PLAYER_MOVEMENT_SPEED;
        }

        ensureInBounds();
    }


	private:

    void ensureInBounds() {
        if (position.first - Constants::PLAYER_HEAD_RADIUS < 0) {
            position.first = Constants::PLAYER_HEAD_RADIUS;
        }

        if (position.first + Constants::PLAYER_HEAD_RADIUS > Constants::WORLD_WIDTH) {
            position.first = Constants::WORLD_WIDTH - Constants::PLAYER_HEAD_RADIUS;
        }

    }

	float distance(std::pair<float,float>&p1,std::pair<float,float>&p2){
		return sqrt((p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second));
	}


	public:


    bool hitByIcicle(Icicles &icicles) {
        bool isHit = false;

for (Icicle icicle : icicles.icicleList) {
            if (distance(icicle.position,position) < Constants::PLAYER_HEAD_RADIUS) {
                isHit = true;
                break;
            }
        }
        if (isHit) {
            deaths += 1;
        }

        return isHit;
    }

    void render() {

        glColor3f(1,192.0/255,134.0/255);
        glBegin(GL_TRIANGLE_FAN);
        int segment = 1000;
        glVertex2f(position.first,position.second);
        for(int i=0;i<segment;i++){
            float angle = i*2*3.142/segment;
            glVertex2f(position.first+Constants::PLAYER_HEAD_RADIUS*cos(angle),position.second+Constants::PLAYER_HEAD_RADIUS*sin(angle));
        }
        glEnd();


        hand.first = position.first;
        hand.second = position.second - Constants::PLAYER_HEAD_RADIUS;

        legs.first = position.first;
        legs.second = position.second - 3 * Constants::PLAYER_HEAD_RADIUS;

        glBegin(GL_LINES);
        glVertex2f(hand.first,hand.second);
glVertex2f(legs.first,legs.second);
		glEnd();

        glBegin(GL_LINES);
        glVertex2f(hand.first - Constants::PLAYER_HEAD_RADIUS,hand.second);
        glVertex2f(hand.first + Constants::PLAYER_HEAD_RADIUS, hand.second);
		glEnd();

        glBegin(GL_LINES);
        glVertex2f(legs.first, legs.second);
        glVertex2f(legs.first + Constants::PLAYER_HEAD_RADIUS, legs.second - Constants::PLAYER_HEAD_RADIUS);
		glEnd();

        glBegin(GL_LINES);
        glVertex2f(legs.first, legs.second);
        glVertex2f(legs.first - Constants::PLAYER_HEAD_RADIUS, legs.second - Constants::PLAYER_HEAD_RADIUS);
		glEnd();

    }

};
