#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#pragma once

class Particle {

	private:
		double x, y;
		double x_vel, y_vel;
		int radius;
		int mass;
		int id;
		cv::Scalar colour;

	public:

		Particle(int id, int window_size);

		void update(int WINDOW_SIZE);

		int timeToHit(Particle* that, int currTime);

		int timeToHitVerticalWall(int windowSize, int currTime);

		int timeToHitHorizontalWall(int windowSize, int currTime);

		void bounceOff(Particle* that);
#

		void bounceOfVerticalWall();

		void bounceOfHorizontalWall();

		void draw(cv::Mat image);

		int getX();
		int getY();
};
