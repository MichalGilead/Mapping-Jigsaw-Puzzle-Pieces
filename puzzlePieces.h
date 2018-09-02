/*
 * puzzlePieces.h
 *
 *  Created on: 14 Dec 2017
 *      Author: Sivan
 */

#ifndef PUZZLEPIECES_H_
#define PUZZLEPIECES_H_

#include "Puzzle2dPiece.h"
#include "Puzzle3dPiece.h"
#include <cmath>
#include <list>
#include <iterator>
#include <typeinfo>


using namespace std;

/**
 * The class represents a structure that manage a jigsaw puzzle elements.
 * The structure is an array in the range of all possible coding (NUM_OF_EDGE_TYPES base) for the elements
 * (that is NUM_OF_EDGE_TYPES^NUM_OF_EDGES), that holds in index i all the elements
 * that has suitable coding i.
 * Each element has 2^NUM_OF_EDGES coding options (the arrangement of the joker (*)).
 * All coding are by this convention: 0 for straight edge, 1 for male edge, 2 for female edge, 3 for joker(*) edge
 *
 *
*/


template<typename T> // T is puzzle piece type (2d/3d)
class puzzlePieces{
private:
	int numOfElements; //number of elements in the puzzle
	int numOfElementEdges;
	int numOfEdgesTypes;
	T*** codedPieces;//holds in index i all elements with (NUM_OF_EDGE_TYPES base)i coding
	vector<int> indices;

	//converts parameter numArray from base parameter-base to 10-base.
	int calc10BaseFromNBasedNum(int* numArray, int length, int base){
		int result=0;
		for (int i=0; i< length; i++)
			result += numArray[i]*pow(base, i);
		return result;
	}

	//converts parameter num from 10-base to base parameter-base
	//stores the result in result
	void calcNBasedNumFrom10Base(int num, int base, int* result, int resultLen){
		int index=0;

		while (num > 0){
			result[index] = num%base;
			num /= base;
			index++;
		}

		for (int i=index; i<resultLen; i++)
			result[i] =0;
	}

	//Calculates pieceCoding according to pieceEdges.
	//Increase each edge value by K.
	void calcElementCoding(T* element, int* pieceCoding){
		vector<int> edges = element->getElementEdges();
		for (int i=0; i<numOfElementEdges; i++){
			pieceCoding[i] = edges[i] + numOfEdgesTypes/2 -1;
		}

	}


public:

	puzzlePieces(int numOfPieces){
		int numOfCodingOptions;
		numOfElementEdges = (typeid(T) == typeid(Puzzle2dPiece<T::value>))? NUM_OF_EDGES_2D : NUM_OF_EDGES_3D;
		numOfEdgesTypes = 2*(T::value)+2;
		numOfCodingOptions = pow(numOfEdgesTypes, numOfElementEdges);

		numOfElements = numOfPieces;

		//creates codedPieces
		codedPieces = new T**[numOfCodingOptions];
		for (int i=0; i<numOfCodingOptions; i++){
			codedPieces[i] = new T*[numOfElements];
			indices.push_back(0);
		}

	}

	//adds an element to codedPieces array.
	void addElement(T& element){
		int* elementCoding; //holds the element original coding-  NUM_OF_EDGE_TYPES-1 base
		int* elementJokerCoding; //holds an element joker coding-  NUM_OF_EDGE_TYPES base
		int* binaryBaseNum;
		int numOfJokerChoices;
		int JokerCodingIndex;

		elementCoding = new int[numOfElementEdges];
		elementJokerCoding = new int[numOfElementEdges];

		//initializes arrays to the original NUM_OF_EDGE_TYPES-1 base coding
		calcElementCoding(&element, elementCoding);
		calcElementCoding(&element, elementJokerCoding);

		binaryBaseNum = new int[numOfElementEdges];
		numOfJokerChoices = pow(2,numOfElementEdges); //calculates number of jokerChoices


		//calculates coding for all joker options
		for (int i=0; i<numOfJokerChoices; i++){
			calcNBasedNumFrom10Base(i, 2, binaryBaseNum, numOfElementEdges); //converts 10-base i to binary-base number

			//for each j that binaryBaseNum[j] == 1, replace the elementJokerCoding[j] to "3" (joker- *)
			for (int j=0; j<numOfElementEdges; j++){
				if (binaryBaseNum[j] == 1)
					elementJokerCoding[j] = numOfEdgesTypes-1;
			}

			//converts element coding number to 10-base number
			JokerCodingIndex = calc10BaseFromNBasedNum(elementJokerCoding, numOfElementEdges, numOfEdgesTypes);

			//adds element to codedPieces according to its JokerCodingIndex

			codedPieces[JokerCodingIndex][indices[JokerCodingIndex]] = &element;
			indices[JokerCodingIndex]++;

			//restores elementJokerCoding the original coding
			for (int j=0; j<numOfElementEdges; j++){
				elementJokerCoding[j] = elementCoding[j];
			}

		}

		delete[] binaryBaseNum;
		delete[] elementCoding;
		delete[] elementJokerCoding;

	}

	//The structure is responsible for returning all pieces possible for a give requrement.
	vector<T*> get(T pieceRequirement){
		int* pieceRequirementCoding;
		int codingIndex;
		vector<T*> result;

		pieceRequirementCoding = new int[numOfElementEdges];

		//initializes array- NUM_OF_EDGE_TYPES-base coding for pieceRequirement
		calcElementCoding(&pieceRequirement, pieceRequirementCoding);

		for (int i=0; i< numOfElementEdges; i++)
			pieceRequirementCoding[i] = (pieceRequirement.getElementEdges()[i] == numeric_limits<int>::min())? numOfEdgesTypes-1 : pieceRequirement.getElementEdges()[i]+numOfEdgesTypes/2 -1;

		//converts pieceRequirementCoding number to 10-base number
		codingIndex = calc10BaseFromNBasedNum(pieceRequirementCoding, numOfElementEdges, numOfEdgesTypes);


		delete[] pieceRequirementCoding;
		for (int i=0; i<indices[codingIndex]; i++)
			result.push_back(codedPieces[codingIndex][i]);

		return result;

	}

	~puzzlePieces(){
		for (int i=0; i<pow(numOfEdgesTypes, numOfElementEdges); i++){
			delete[] codedPieces[i];
		}
		delete[] codedPieces;
	}

};

template <typename T> using deref_iter_t = std::remove_reference_t<decltype(*std::declval<T>())>;

template<class RandomContainer> auto groupPuzzlePieces(RandomContainer beginIt, RandomContainer endIt){
	int numOfPieces = 0;
	for (RandomContainer it=beginIt; it!=endIt; it++){
		numOfPieces++;
	}
	using T = deref_iter_t<RandomContainer>;
    puzzlePieces<T> groups(numOfPieces);
	for (RandomContainer it=beginIt; it!=endIt; it++){
		groups.addElement(*it);
	}
    return groups;
}
#endif /* PUZZLEPIECES_H_ */
