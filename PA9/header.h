#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iomanip>
#include "difficulty.h"

std::vector<std::vector<int>> fillBoard(Difficulty diff, std::vector<std::vector<int>> grid);
std::vector<std::vector<int>> setDisplayBoard(Difficulty diff, std::vector<std::vector<int>> grid);
void playGame(Difficulty diff);