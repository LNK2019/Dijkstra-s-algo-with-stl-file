#include "StlData.hpp"
#include <fstream>
#include <iostream>

namespace stl {
	/*The concepts that will be used :
	The processed vertex is the vertex in which all adjacent vertices have the closest distances not equal to the inf*/


	distance stl::StlData::useDijkstraAlgorithm(Vertex * start, Vertex * end) 
	{
		struct compareDistantace {			// functor for a multiset with vertices, compares the closest distance
			bool operator() (const Vertex * lVal, const Vertex * rVal) const {
				return lVal->closestDistance < rVal->closestDistance;
			}
		};

		auto iterStart = this->vertices_.find(start);		  // try to find the specified vertices
		auto iterEnd = this->vertices_.find(end);
		if (iterStart == this->vertices_.end() || iterEnd == this->vertices_.end()) {		// if the vertex is absent in the main set
			std::cerr << "ERROR: there is no vertex you enter" << std::endl;			 
			return -1.0;
		}
		std::multiset<Vertex *, compareDistantace> verticesByDistance;		// set of vertices which the elements will be located depending on their distance to the start
		(*iterStart)->closestDistance = 0.0;				// The starting point is the closest distance 0.0
		verticesByDistance.insert(*iterStart);


		Vertex * curSmallestVertex = nullptr;
		while (!(*iterEnd)->isAlreadyProcessed) {
			curSmallestVertex = nullptr;				// unprocessed vertex with the smallest closest distance to the starting vertex(default value is nullptr)
			for (auto iter : verticesByDistance) {		// search for the vertex with the smallest distance to the starting vertex
				if (!iter->isAlreadyProcessed) {
					curSmallestVertex = iter;
					break;
				}
			}
			if (curSmallestVertex == nullptr) {			//if all vertices in the miltiset are already processed
				std::cerr << "ERROR: there is no connection between start and end vercies" << std::endl;
				return -1.0;
			}
			
			for (auto curAdjVertex : curSmallestVertex->adjacentVertices) {  //check all adjacent vertices
																			 
				if (curAdjVertex->isAlreadyProcessed)			// if already processed
					continue;
				if (curAdjVertex->closestDistance == INFINITY) {			//if the closest distance is not set
					curAdjVertex->closestDistance = curSmallestVertex->closestDistance + Vertex::getDistance(*curSmallestVertex, *curAdjVertex);		// set it 
					verticesByDistance.insert(curAdjVertex);																							// and insert
					continue;
				}
				
				if (curSmallestVertex->closestDistance + Vertex::getDistance(*curSmallestVertex, *curAdjVertex) < curAdjVertex->closestDistance)		//if the closest distance is already set but it is bigger than distance from our curSmallestVertex
				{																																		
					auto distanceIters = verticesByDistance.equal_range(curAdjVertex);																	//find it in miltiset
					for (auto curIter = distanceIters.first; curIter != distanceIters.second; ++curIter) {												
						if (Vertex::equal(curAdjVertex, *curIter)) {
							verticesByDistance.erase(curIter);																							//erase it
							curAdjVertex->closestDistance = curSmallestVertex->closestDistance + Vertex::getDistance(*curSmallestVertex, *curAdjVertex);//set new value
							verticesByDistance.insert(curAdjVertex);																					//insert it
							break;
						}
					}
				}


			}
			curSmallestVertex->isAlreadyProcessed = true;		// when we set all closets distance in adjacent value
		}
		distance shortestPath = curSmallestVertex->closestDistance;
		for (auto iter : verticesByDistance) {			// return all parameters by default because you can use the same vertices for other start and end
			iter->isAlreadyProcessed = false;
			iter->closestDistance = INFINITY;
		}
		return shortestPath;
	}

	void stl::StlData::addTriangle(std::ifstream &output)
	{
		Vertex *vx1 = new Vertex;
		Vertex *vx2 = new Vertex;
		Vertex *vx3 = new Vertex;
		output.read(reinterpret_cast<char *>(vx1), POINT_SIZE);
		output.read(reinterpret_cast<char *>(vx2), POINT_SIZE);
		output.read(reinterpret_cast<char *>(vx3), POINT_SIZE);
		auto iter1 = vertices_.insert(vx1);
		auto iter2 = vertices_.insert(vx2);
		auto iter3 = vertices_.insert(vx3);
		(*iter1.first)->addAdjacentVrt(*iter2.first, *iter3.first);
		(*iter2.first)->addAdjacentVrt(*iter1.first, *iter3.first);
		(*iter3.first)->addAdjacentVrt(*iter1.first, *iter2.first);
		if (!iter1.second) delete vx1;
		if (!iter2.second) delete vx2;
		if (!iter3.second) delete vx3;
	}

	bool stl::StlData::parseData(const char * path)
	{
		std::ifstream output(path, std::ios::binary);
		if (!output.is_open()) return false;
		output.read(reinterpret_cast<char *>(header_), HEADER_SIZE);
		output.read(reinterpret_cast<char *>(&numOfTriangles_), sizeof(uint32_t));
		for (size_t i = 0; i < numOfTriangles_; ++i) {
			output.seekg(POINT_SIZE, std::ios_base::cur);
			addTriangle(output);
			output.seekg(sizeof(uint16_t), std::ios_base::cur);
		}
		output.close();
		return true;
	}


}
