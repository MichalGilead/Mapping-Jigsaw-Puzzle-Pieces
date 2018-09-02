/*
 * main.cpp
 *
 *  Created on: 30 בינו׳ 2018
 *      Author: michal
 */


#include "ex4headers.h"

int main() {
    auto joker = std::numeric_limits<int>::min();
    vector<Puzzle2dPiece<5>> pieces1 = {{0, 3, 2, -5}, {0, -2, 2, -5}};
    auto groups1 = groupPuzzlePieces(pieces1.begin(), pieces1.end());
    auto some_pieces1 = groups1.get({0, 3, 2, std::numeric_limits<int>::min()});
    for(auto piece_ptr : some_pieces1) {
        std::cout << *piece_ptr << std::endl; // will print the first piece!
    }

    list<Puzzle3dPiece<1>> pieces2 = {{0, 1, 1, 1, -1, -1}, {0, -1, 1, 1, 1, 1}};
    auto groups2 = groupPuzzlePieces(pieces2.begin(), pieces2.end());
    auto some_pieces2 = groups2.get({0, joker, 1, 1, joker, joker});
    for(auto piece_ptr : some_pieces2) {
        std::cout << *piece_ptr << std::endl; // will print two pieces!
    }

    list<Puzzle3dPiece<1>> pieces3 = {{0, 1, 1, 1, -1, -1}, {0, -1, 1, 1, 1, 1}};
    auto groups3 = groupPuzzlePieces(pieces3.begin(), pieces3.end());
    auto some_pieces3 = groups3.get({0, 1, 1, 1, 1, 1});
    for(auto piece_ptr : some_pieces3) {
        std::cout << *piece_ptr << std::endl; // will print nothing!
    }

    list<Puzzle2dPiece<5>> pieces4 = {{0, 3, 2, -5}, {0, -2, 2, -5}};
    auto groups4 = groupPuzzlePieces(pieces4.begin(), pieces4.end());
    auto some_pieces4 = groups4.get({0, std::numeric_limits<int>::min(), 2, -5});
    for(auto piece_ptr : some_pieces4) {
        cout << *piece_ptr << endl; // will print both pieces!
    }

    list<Puzzle2dPiece<8>> pieces5 = {{0, -8, 2, -5}, {0, -2, 2, 3}, {1, -8, 2, 3}};
    auto groups5 = groupPuzzlePieces(pieces5.begin(), pieces5.end());
    auto some_pieces5 = groups5.get({0, joker, 2, joker});
    for(auto piece_ptr : some_pieces5) {
        cout << *piece_ptr << endl; // will print both pieces!
    }
    auto some_pieces6 = groups5.get({joker, -8, 2, joker});
    for(auto piece_ptr : some_pieces6) {
        cout << *piece_ptr << endl; // will print both pieces!
    }

    list<Puzzle3dPiece<2>> pieces7 = {{0, 2, -2, 1, -1, -1}, {0, 1, 1, 1, -1, 2}, {-1, 2, 1, 2, -1, -1}};
    auto groups7 = groupPuzzlePieces(pieces7.begin(), pieces7.end());
    auto some_pieces7 = groups7.get({0, joker, joker, 1, -1, joker});
    for(auto piece_ptr : some_pieces7) {
        cout << *piece_ptr << endl; // will print both pieces!
    }
    auto some_pieces8 = groups7.get({joker, 2, joker, joker, -1, -1});
    for(auto piece_ptr : some_pieces8) {
        cout << *piece_ptr << endl; // will print both pieces!
    }
    auto some_pieces9 = groups7.get({joker, joker, joker, joker, joker, joker});
    for(auto piece_ptr : some_pieces9) {
        cout << *piece_ptr << endl; // will print both pieces!
    }

    return 1;
}
