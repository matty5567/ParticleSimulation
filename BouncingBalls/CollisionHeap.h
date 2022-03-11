#pragma once
#include "Collision.h"

class CollisionHeap {
private:
	std::vector<Collision> heap;


public:
	CollisionHeap();

	void sink(int pos);

	void swim(int pos);

	void exch(int x, int y);

	Collision pop_min();

	Collision show_min();

	void insert(Collision x, int currTime);

	void showHeap();

	bool isEmpty();


};