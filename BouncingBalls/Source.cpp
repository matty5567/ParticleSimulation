#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <Windows.h>
#include <cMath>
#include "ball.h"
#include "CollisionHeap.h"
#include <vector>

int WINDOW_SIZE = 1500;

CollisionHeap initialiseCollisionHeap(std::vector<Ball*> balls) {
    CollisionHeap collisionHeap = CollisionHeap();

    for (Ball* i : balls) {

        collisionHeap.insert(Collision(i->timeToHitVerticalWall(WINDOW_SIZE, 0), NULL, i), 0);
        collisionHeap.insert(Collision(i->timeToHitHorizontalWall(WINDOW_SIZE, 0), i, NULL), 0);

        for (Ball* j : balls) {

            int ballCollisionTime = i->timeToHit(j, 0);

            if (ballCollisionTime < INT_MAX && ballCollisionTime > 0) {
                Collision collision = Collision(ballCollisionTime, i, j);


                collisionHeap.insert(collision, 0);
            }

            
        }
    }

    return collisionHeap;
}

int main(int argc, char** argv)
{
    srand(time(NULL));

    int time = 0;
    

    const int numBalls = 500;

    cv::Mat image, board;
    image = cv::Mat::zeros(WINDOW_SIZE, WINDOW_SIZE, CV_8UC3);

    char ch;

    std::vector<Ball*> balls;

    for (int i = 0; i < numBalls; i++) {
        Ball* ball = new Ball(i, WINDOW_SIZE);
        balls.push_back(ball);
    }


    CollisionHeap collisionHeap = initialiseCollisionHeap(balls);

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);


    Collision nextCollision = collisionHeap.pop_min();
    Collision prevCollision;


    while (true) {


        image.copyTo(board);

        if (time == nextCollision.getTime()) {

            Ball* ball1;
            Ball* ball2;

            while (nextCollision.getTime() == time) {
                ball1 = nextCollision.getBall1();
                ball2 = nextCollision.getBall2();

                if (ball1 == NULL && ball2 != NULL) {
                    // collision with vertical wall
                    if (nextCollision.getBall2()->timeToHitVerticalWall(WINDOW_SIZE, 0) <= 1) {
                        ball2->bounceOfVerticalWall();

                        collisionHeap.insert(Collision(ball2->timeToHitVerticalWall(WINDOW_SIZE, time), NULL, ball2), time);
                        collisionHeap.insert(Collision(ball2->timeToHitHorizontalWall(WINDOW_SIZE, time), ball2, NULL), time);

                        for (Ball* i : balls) {

                            int collisionTimeBall2 = ball2->timeToHit(i, time);

                            Collision collision2 = Collision(collisionTimeBall2, ball2, i);

                            collisionHeap.insert(collision2, time);

                        }
                    }
                    else { collisionHeap.insert(Collision(ball2->timeToHitVerticalWall(WINDOW_SIZE, time), NULL, ball2), time); }
                }

                else if (ball2 == NULL and ball1 != NULL) {
                    // collision with horizontal wall
                    if (nextCollision.getBall1()->timeToHitHorizontalWall(WINDOW_SIZE, 0) <= 1) {
                        ball1->bounceOfHorizontalWall();

                        collisionHeap.insert(Collision(ball1->timeToHitVerticalWall(WINDOW_SIZE, time), NULL, ball1), time);
                        collisionHeap.insert(Collision(ball1->timeToHitHorizontalWall(WINDOW_SIZE, time), ball1, NULL), time);
                        

                        for (Ball* i : balls) {

                            int collisionTimeBall1 = ball1->timeToHit(i, time);

                            Collision collision1 = Collision(collisionTimeBall1, ball1, i);

                            collisionHeap.insert(collision1, time);

                        }
                    }

                    else { collisionHeap.insert(Collision(ball1->timeToHitHorizontalWall(WINDOW_SIZE, time), ball1, NULL), time); }
                }

                else {

                    // Two balls colliding
                     if ((nextCollision.getBall1()->timeToHit(nextCollision.getBall2(), 0) <= 1)) {



                        ball1->bounceOff(ball2);

                        collisionHeap.insert(Collision(ball2->timeToHitVerticalWall(WINDOW_SIZE, time), NULL, ball2), time);
                        collisionHeap.insert(Collision(ball2->timeToHitHorizontalWall(WINDOW_SIZE, time), ball2, NULL), time);


                        collisionHeap.insert(Collision(ball1->timeToHitVerticalWall(WINDOW_SIZE, time), NULL, ball1), time);
                        collisionHeap.insert(Collision(ball1->timeToHitHorizontalWall(WINDOW_SIZE, time), ball1, NULL), time);

                        for (Ball* i : balls) {

                            if ((i != ball1) && (i != ball2)) {

                                int collisionTimeBall1 = ball1->timeToHit(i, time);
                                int collisionTimeBall2 = ball2->timeToHit(i, time);

                                Collision collision1 = Collision(collisionTimeBall1, ball1, i);
                                Collision collision2 = Collision(collisionTimeBall2, ball2, i);

                                collisionHeap.insert(collision1, time);
                                collisionHeap.insert(collision2, time);

                            }
                        }
                    }
                }


                
                prevCollision = nextCollision;
                nextCollision = collisionHeap.pop_min();

                
            }


 

            
        }

        for (auto& x : balls) {

            x->update(WINDOW_SIZE);
            x->draw(board);
        }

        imshow("Display window", board);


        Sleep(1);

        ch = cv::pollKey();

        if (ch != -1) { break; }

        time += 1;

    }

    return 0;
};


