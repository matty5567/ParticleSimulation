#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Particle.h"   
#include <iostream>
#include <Windows.h>
#include <cMath>



Particle::Particle(int id, int window_size){ 
    this->x = rand() % window_size;
    this->y = rand() % window_size;
    this->colour = cv::Scalar(0, 0, 255);
    this->id = id;
    this->x_vel = rand() % 2;
    this->y_vel = rand() % 2  ;

    this->radius = 5;
    this->mass = 100;


}

void Particle::update(int WINDOW_SIZE) {
    x += x_vel;
    y += y_vel;
};

int Particle::timeToHit(Particle* that, int currTime) {
    if (this == that) { return INT_MAX; }
    double dx = that->x - this->x, dy = that->y - this->y;
    double dvx = that->x_vel - this->x_vel, dvy = that->y_vel - this->y_vel;
    double dvdr = dx * dvx + dy * dvy;
    if (dvdr > 0) { return INT_MAX; }
    double dvdv = dvx * dvx + dvy * dvy;
    double drdr = dx * dx + dy * dy;
    double sigma = (double)this->radius + (double)that->radius;
    double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
    if (d < 0) { return INT_MAX; }
    return -(dvdr + sqrt(d)) / dvdv + currTime;

}

int Particle::timeToHitVerticalWall(int windowSize, int currTime) {

    if (x_vel == 0) { return INT_MAX; }
    int w = x_vel > 0 ? windowSize : 0;
    return max(0, ((w -x + this->radius) / x_vel)) + currTime;

}


int Particle::timeToHitHorizontalWall(int windowSize, int currTime) {

    if (y_vel == 0) { return INT_MAX; }
    int w = y_vel > 0 ? windowSize : 0;
    return max(0, ((w - y + this->radius) / y_vel)) + currTime;

}



void Particle::bounceOfHorizontalWall() { this->y_vel *= -1; }

void Particle::bounceOfVerticalWall() { this->x_vel *= -1; }



void Particle::bounceOff(Particle* that) {
    double d = sqrt(pow(this->x - that->x, 2) + pow(this->y - that->y, 2));
    double nx = (that->x - this->x) / d;
    double ny = (that->y - this->y) / d;
    double p = 2 * (this->x_vel * nx + this->y_vel * ny - that->x_vel * nx - that->y_vel * ny) / (this->mass + that->mass);
    this->x_vel -= p * this->mass * nx;
    this->y_vel -= p * this->mass * ny;
    that->x_vel += p * that->mass * nx;
    that->y_vel += p * that->mass * ny;

}


void Particle::draw(cv::Mat image) {
    cv::Point centerCircle2(x, y);
    circle(
        image,
        centerCircle2,
        radius,
        this->colour,
        cv::FILLED,
        cv::LINE_8
    );
};

int Particle::getX() { return this->x; }

int Particle::getY() { return this->y; }
