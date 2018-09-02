/*
 * Puzzle2dPiece.h
 *
 *  Created on: 17 ����� 2018
 *      Author: michal
 */

#ifndef PUZZLE2DPIECE_H_
#define PUZZLE2DPIECE_H_

using namespace std;
#include <iostream>
#include <vector>
#include <list>
#include <limits>

#define NUM_OF_EDGES_2D 4

template<int K> class Puzzle2dPiece{
public:
	static const int value = K;
	Puzzle2dPiece(initializer_list<int> elementEdges){
		for (int i : elementEdges){
			if ((i>K || i<-K) && i!=std::numeric_limits<int>::min())
				throw logic_error("Error: element has out of range edge values");
			edges.push_back(i);
		}
	}
	const vector<int> getElementEdges() const{
		return edges;
	}
	friend ostream& operator<<(ostream& out, const Puzzle2dPiece& p){
		out << "{";
		for (size_t i=0; i<NUM_OF_EDGES_2D; ++i){
			out << p.edges[i];
			if (i<NUM_OF_EDGES_2D-1)
				out << ", ";
		}
		out << "}";
		return out;
	}
private:
	vector<int> edges;
};



#endif /* PUZZLE2DPIECE_H_ */
