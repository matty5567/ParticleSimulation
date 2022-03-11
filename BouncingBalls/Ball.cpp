#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Ball.h"
#include <iostream>
#include <Windows.h>
#include <cMath>



Ball::Ball(int id, int window_size) {
    this->x = rand() % window_size;
    this->y = rand() % window_size;

    this->id = id;
    this->x_vel = rand() % 3 - 5;
    this->y_vel = rand() % 3 - 5;

    this->radius = 5;
    this->mass = 100;


}

void Ball::update(int WINDOW_SIZE) {

    x += x_vel;
    y += y_vel;

};

int Ball::timeToHit(Ball* that, int currTime) {
    if (this == that) { return INT_MAX; }
    double dx = that->x - this->x, dy = that->y - this->y;
    double dvx = that->x_vel - this->x_vel, dvy = that->y_vel - this->y_vel;
    double dvdr = dx * dvx + dy * dvy;
    if (dvdr > 0) { return INT_MAX; }
    double dvdv = dvx * dvx + dvy * dvy;
    double drdr = dx * dx + dy * dy;
    double sigma = this->radius + that->radius;
    double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
    if (d < 0) { return INT_MAX; }

    int timeToNextHit = -(dvdr + sqrt(d)) / dvdv + currTime;
    return timeToNextHit;

}

int Ball::timeToHitVerticalWall(int windowSize, int currTime) {
    int timeToHit;

    if (x_vel == 0) { return INT_MAX; }

    else if (x_vel > 0) {
        timeToHit = max(0, ((windowSize - x + this->radius) / x_vel));
    }

    else {
        timeToHit = max(0, (( - x + this->radius ) / x_vel));
    }

    return timeToHit + currTime;

}


int Ball::timeToHitHorizontalWall(int windowSize, int currTime) {
    int timeToHit;

    if (y_vel == 0) { return INT_MAX; }

    else if (y_vel > 0) {
        timeToHit = max(0, ((windowSize - y + this->radius) / y_vel));
    }

    else {
        timeToHit = max(0, ((- y + this->radius) / y_vel));
    }

    return timeToHit + currTime;

}



void Ball::bounceOfHorizontalWall() { this->y_vel *= -1; }

void Ball::bounceOfVerticalWall() { this->x_vel *= -1; }



void Ball::bounceOff(Ball* that) {
    double d = sqrt(pow(this->x - that->x, 2) + pow(this->y - that->y, 2));
    double nx = (that->x - this->x) / d;
    double ny = (that->y - this->y) / d;
    double p = 2 * (this->x_vel * nx + this->y_vel * ny - that->x_vel * nx - that->y_vel * ny) / (this->mass + that->mass);
    this->x_vel -= p * this->mass * nx;
    this->y_vel -= p * this->mass * ny;
    that->x_vel += p * that->mass * nx;
    that->y_vel += p * that->mass * ny;

}




void Ball::draw(cv::Mat image) {
    cv::Point centerCircle2(x, y);
    circle(
        image,
        centerCircle2,
        radius,
        cv::Scalar(0, 0, 255),
        cv::FILLED,
        cv::LINE_8
    );
};

int Ball::getX() { return this->x; }

int Ball::getY() { return this->y; }
