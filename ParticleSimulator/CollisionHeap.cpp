#include <iostream>
#include <vector>
#include <math.h>
#include "Particle.h"
#include "Collision.h"
#include "CollisionHeap.h"
#pragma once



CollisionHeap::CollisionHeap() {
	heap = {Collision()};
};

void CollisionHeap::sink(int pos) {
	int N = heap.size() - 1;
	while (2 * pos <= N) {
		int j = 2 * pos;
		if (j < N && heap[j] > heap[j + 1]) { j++; }
		if (heap[pos] <= heap[j]) { break; }
		exch(pos, j);
		pos = j;
	}
};

void CollisionHeap::swim(int pos) {

	if (pos > 1 && heap[pos] < heap[pos / 2]) {

		exch(pos, pos / 2);
		swim(pos / 2);
	}
	else { return; }

};

void CollisionHeap::exch(int x, int y) {
	Collision tmp = heap[x];
	heap[x] = heap[y];
	heap[y] = tmp;
};

Collision CollisionHeap::pop_min() {
	Collision max = heap[1];
	exch(1, heap.size() - 1);
	heap.pop_back();
	sink(1);
	return max;
};


Collision CollisionHeap::show_min() {
	Collision max = heap[1];
	return max;
};

void CollisionHeap::insert(Collision x, int currTime) {
	if (x.getTime() == INT_MAX || x.getTime() <= currTime) { return; }
	heap.push_back(x);
	swim(heap.size() - 1);
};



void CollisionHeap::showHeap() {
	for (auto i : this->heap) {
		std::cout << i.getTime() << " ";
	}
	std::cout << std::endl;

}

bool CollisionHeap::isEmpty() {
	return this->heap.size() == 1;
}