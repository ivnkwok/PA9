#include "difficulty.h"

int Difficulty::getSize() {
    return size;
}
int Difficulty::getBoardSize() {
    return boardSize;
}
int Difficulty::getWindowSize() {
    return windowSize;
}

int Difficulty::setSize(int size) {
    return size;
}
int Difficulty::setBoardSize(int size) {
    return boardSize;
}
int Difficulty::setWindowSize(int size) {
    return windowSize;
}

void Difficulty::init() {
    boardSize = size + 2;
    windowSize = (size + 1) * 32;
}

Easy::Easy() {
    size = 10;
    init();
}

Medium::Medium() {
    size = 15;
    init();
}

Hard::Hard() {
    size = 25;
    init();
}