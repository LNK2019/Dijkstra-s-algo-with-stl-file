#pragma once
#include <set>
#include <memory>
#include <iostream>
#include <cmath>


namespace stl {
	using distance = float;  

	template<typename T>		
	struct compareVert {		// functor instead of the default comparator in the set, compares the coordinates of vertices
		bool operator() (const T & lval, const T & rval) const {
			if (lval->x_ != rval->x_)
				return lval->x_ < rval->x_;
			if (lval->y_ != rval->y_)
				return lval->y_ < rval->y_;
			if (lval->z_ != rval->z_)
				return lval->z_ < rval->z_;
			return false;
		}
	};


	struct Vertex {		
		using adjVerticesSet = std::set<Vertex *,compareVert<Vertex *>>;

		float x_, y_, z_;
		adjVerticesSet adjacentVertices;		// set with adjacent(for *this one) vertices
		bool isAlreadyProcessed;			// parameter indicating whether the vertex is processed (used in the algorithm)
		distance closestDistance;			//closest distance to the starting point (used in the algorithm)
	public:
		Vertex(distance x, distance y,distance z) : x_(x), y_(y), z_(z),
			isAlreadyProcessed(0), closestDistance(INFINITY) {}			//by default the closest distance is infinity
		Vertex() : isAlreadyProcessed(0), closestDistance(INFINITY) {};
		void addAdjacentVrt(Vertex *vx);
		void addAdjacentVrt(Vertex *vx1, Vertex * vx2);
		static bool equal(const Vertex * lval, const Vertex * rval);		//returns true or false if coordinates are equivalent
		bool equal(const Vertex * rval);
		static distance getDistance(const Vertex & lval, const Vertex & rval);		//returns the distance between vertices
		distance getDistance(const Vertex & rval);

	};
}