#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <cMath>
#include "Particle.h"
#include "CollisionHeap.h"
#include <vector>

int WINDOW_SIZE = 800;
const int NUM_PARTICLES = 100;

void insertNextWallCollisionsToHeap(Particle* particle, CollisionHeap* collisionHeap, int time) {
    collisionHeap->insert(Collision(particle->timeToHitVerticalWall(WINDOW_SIZE, time), NULL, particle), time);
    collisionHeap->insert(Collision(particle->timeToHitHorizontalWall(WINDOW_SIZE, time), particle, NULL), time);
}

void insertNextParticleCollisionsToHeap(Particle* particle, std::vector<Particle*> particles, CollisionHeap* collisionHeap, int time) {
    for (Particle* j : particles) {

        int ballCollisionTime = particle->timeToHit(j, time);

        if (ballCollisionTime < INT_MAX && ballCollisionTime > time) {
            Collision collision = Collision(ballCollisionTime, particle, j);
            collisionHeap->insert(collision, time);
        }
    }
}

cv::Mat initialiseWindow() {
    srand(time(NULL));
    cv::Mat window, board;
    window = cv::Mat::zeros(WINDOW_SIZE, WINDOW_SIZE, CV_8UC3);
    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    window.setTo(cv::Scalar(0, 0, 0));
    return window;
    }


CollisionHeap initialiseCollisionHeap(std::vector<Particle*> particles) {
    CollisionHeap collisionHeap = CollisionHeap();

    for (Particle* i : particles) {
        insertNextWallCollisionsToHeap(i, &collisionHeap, 0);
        insertNextParticleCollisionsToHeap(i, particles, &collisionHeap, 0);
    }

    return collisionHeap;
}

std::vector<Particle*> initialiseParticles() {
    std::vector<Particle*> particles;
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle* ball = new Particle(i, WINDOW_SIZE);
        particles.push_back(ball);
    }
    return particles;
}

int main(int argc, char** argv)
{
    cv::Mat window = initialiseWindow();
    cv::Mat board;
    int time = 0;
    char ch;

    std::vector<Particle*> particles = initialiseParticles();

    CollisionHeap collisionHeap = initialiseCollisionHeap(particles);

    Collision nextCollision = collisionHeap.pop_min();
    Collision prevCollision;


    while (true) {

        window.copyTo(board);

        if (time == nextCollision.getTime()) {

            Particle* particle1;
            Particle* particle2;

            while (nextCollision.getTime() == time) {
                particle1 = nextCollision.getParticle1();
                particle2 = nextCollision.getParticle2();

                if (particle1 == NULL && particle2 != NULL) {
                    // collision with vertical wall
                    if (nextCollision.getParticle2()->timeToHitVerticalWall(WINDOW_SIZE, 0) <= 1) {
                        particle2->bounceOfVerticalWall();

                        insertNextWallCollisionsToHeap(particle2, &collisionHeap, time);
                        insertNextParticleCollisionsToHeap(particle2, particles, &collisionHeap, time);

                    }
                    else { collisionHeap.insert(Collision(particle2->timeToHitVerticalWall(WINDOW_SIZE, time), NULL, particle2), time); }
                }

                else if (particle2 == NULL and particle1 != NULL) {
                    // collision with horizontal wall
                    if (nextCollision.getParticle1()->timeToHitHorizontalWall(WINDOW_SIZE, 0) <= 1) {
                        particle1->bounceOfHorizontalWall();

                        insertNextWallCollisionsToHeap(particle1, &collisionHeap, time);
                        insertNextParticleCollisionsToHeap(particle1, particles, &collisionHeap, time);
                    }

                    else { collisionHeap.insert(Collision(particle1->timeToHitHorizontalWall(WINDOW_SIZE, time), particle1, NULL), time); }
                }

                else {

                    // Two Particles colliding
                    // Two Particles colliding
                     if ((nextCollision.getParticle1()->timeToHit(nextCollision.getParticle2(), 0) <= 1)) {

                         particle1->bounceOff(particle2);

                        insertNextWallCollisionsToHeap(particle1, &collisionHeap, time);
                        insertNextWallCollisionsToHeap(particle2, &collisionHeap, time);

                        insertNextParticleCollisionsToHeap(particle1, particles, &collisionHeap, time);
                        insertNextParticleCollisionsToHeap(particle2, particles, &collisionHeap, time);
                    }
                }

                
                prevCollision = nextCollision;
                nextCollision = collisionHeap.pop_min();

            }
        }

        for (auto& x : particles) {

            x->update(WINDOW_SIZE);
            x->draw(board);
        }

        imshow("Display window", board);

        ch = cv::pollKey();
        if (ch != -1) { break; }
        time += 1;

    }

    return 0;
};


