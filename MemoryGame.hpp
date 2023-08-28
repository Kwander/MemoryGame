#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

#include <string>
#include <vector>

class MemoryGame {
public:
    MemoryGame();
    MemoryGame(int n);
    MemoryGame(int n, int m);
    MemoryGame(std::string *words, int size);
    ~MemoryGame();

    void play();
    void display(bool *bShown);

private:
    int numPairs;
    int numSlots;
    std::string *values;

    int* randomize(int numSlots);
    void swap(int *arr, int i, int j);
    void displaySeparateLine(int numSlots);
};

#endif