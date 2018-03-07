#pragma once
#include "Vertex.hpp"
#include <set>
#include <cstdint>

#define HEADER_SIZE 80
#define POINT_SIZE (sizeof(float)*3)

namespace stl {

	class mainVerticesSet : public std::set<Vertex *, compareVert<Vertex *>> {  // main set with vertices
	public:
		virtual ~mainVerticesSet() {		//overloaded destructor
			for (auto iter : *this) {
				delete iter;
			}
		}
	};

	struct StlData {			//The structure responsible for storing data from a stl file in a form convenient for the algorithm
		char * header_ = new char[HEADER_SIZE];
		uint32_t numOfTriangles_;
		mainVerticesSet vertices_;
	public:
		bool parseData(const char *path);			// parsing function
		distance useDijkstraAlgorithm(Vertex *start, Vertex *end);		// algorithm for finding the distance between vertices (in my case, the Dijkstra’s algorithm)
		~StlData() { delete header_; };
	private:
		void addTriangle(std::ifstream & output); // a function for adding three vertices to the main set of vertices and associating them with each other
	};

}