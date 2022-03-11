#include "Collision.h"
#include "Ball.h"


Collision::Collision(int time, Ball* ball1, Ball* ball2) : time(time), ball1(ball1), ball2(ball2) {}



int Collision::getTime() { return time; }

Ball* Collision::getBall1() { return ball1; }
Ball* Collision::getBall2() { return ball2; }

