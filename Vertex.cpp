#include "Vertex.hpp"

void stl::Vertex::addAdjacentVrt( Vertex *vx) {
	this->adjacentVertices.insert(vx);
}

void stl::Vertex::addAdjacentVrt( Vertex *vx1, Vertex * vx2) {
	addAdjacentVrt(vx1);
	addAdjacentVrt(vx2);
}

float stl::Vertex::getDistance(const Vertex & lval, const Vertex & rval) {
	return sqrt(pow((lval.x_ - rval.x_), 2) + pow((lval.y_ - rval.y_), 2) + pow((lval.z_ - rval.z_), 2));
}

float stl::Vertex::getDistance(const Vertex & rval) {
	return sqrt(pow((this->x_ - rval.x_), 2) + pow((this->y_ - rval.y_), 2) + pow((this->z_ - rval.z_), 2));
}

bool stl::Vertex::equal(const Vertex * lval, const Vertex * rval) {
	return  (lval->x_ == rval->x_ && lval->y_ == rval->y_ && lval->z_ == rval->z_);
}

bool stl::Vertex::equal(const Vertex * rval) {
	return  (this->x_ == rval->x_ && this->y_ == rval->y_ && this->z_ == rval->z_);
}