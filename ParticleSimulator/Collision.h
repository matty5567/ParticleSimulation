#pragma once
#include "Particle.h"

class Collision
{
	int time;
	Particle* particle1;
	Particle* particle2;

	public:

		Collision() {};
		Collision(int time, Particle* ball1, Particle* ball2);

		int getTime();

		Particle* getParticle1();
		Particle* getParticle2();


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
			return ((coll1.particle1 != coll2.particle1) && (coll1.particle2 != coll2.particle2));
		}



};

