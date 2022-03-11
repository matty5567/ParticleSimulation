#include "Collision.h"
#include "Particle.h"


Collision::Collision(int time, Particle* particle1, Particle* particle2) : time(time), particle1(particle1), particle2(particle2) {}

int Collision::getTime() { return time; }

Particle* Collision::getParticle1() { return particle1; }
Particle* Collision::getParticle2() { return particle2; }

