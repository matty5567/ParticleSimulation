#pragma once
#include "Ball.h"

class Collision
{
	int time;
	Ball* ball1;
	Ball* ball2;

	public:

		Collision() {};
		Collision(int time, Ball* ball1, Ball* ball2);

		int getTime();

		Ball* getBall1();
		Ball* getBall2();


		friend bool operator < (const Collision& coll1, const Collision& coll2) {
			return coll1.time < coll2.time;
		}

		friend bool operator <= (const Collision& coll1, const Collision& coll2) {
			return coll1.time <= coll2.time;
		}

		friend bool operator > (const Collision& coll1, const Collision& coll2) {
			return coll1.time > coll2.time;
		}

		friend bool operator != (const Collision& coll1, const Collision& coll2) {
			return ((coll1.ball1 != coll2.ball1) && (coll1.ball2 != coll2.ball2));
		}



};

