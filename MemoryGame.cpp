#include "MemoryGame.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

MemoryGame::MemoryGame()
{
    srand(static_cast<unsigned>(time(nullptr)));
    numPairs = 3;
    numSlots = 2 * numPairs + 2;

    int *data = new int[numPairs];
    for (int i = 0; i < numPairs; i++)
    {
        data[i] = rand() % 1000;
    }

    values = new std::string[numSlots];
    int *arr = randomize(numSlots);
    for (int i = 0; i < numSlots; i++)
    {
        if (i < numPairs * 2)
        {
            values[arr[i]] = std::to_string(data[i / 2]);
        }
        else
        {
            values[arr[i]] = "";
        }
    }

    delete[] arr;
    delete[] data;
}

MemoryGame::~MemoryGame()
{
    delete[] values;
}

int *MemoryGame::randomize(int size)
{
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }

    int num = 0;
    while (size > 0)
    {
        num = rand() % size;
        swap(arr, num, size - 1);
        size = size - 1;
    }

    return arr;
}

void MemoryGame::swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void MemoryGame::displaySeparateLine(int numSlots)
{
    for (int i = 0; i < numSlots; i++)
    {
        if (i == 0)
        {
            std::cout << "+";
        }
        std::cout << "-----+";
    }
    std::cout << std::endl;
}

void MemoryGame::display(bool *bShown)
{
    std::cout << " ";
    for (int i = 0; i < numSlots; i++)
    {
        std::cout << std::setw(3) << i;
        std::cout << std::setw(3) << " ";
    }
    std::cout << std::endl;

    displaySeparateLine(numSlots);
    std::cout << "|";
    for (int i = 0; i < numSlots; i++)
    {
        if (bShown[i])
        {
            std::cout << std::setw(5) << values[i];
        }
        else
        {
            std::cout << std::setw(5) << "";
        }
        std::cout << "|";
    }
    std::cout << "\n";
    displaySeparateLine(numSlots);
}

void MemoryGame::play()
{
    bool *bShown = new bool[numSlots];
    for (int i = 0; i < numSlots; i++)
    {
        bShown[i] = false;
    }

    display(bShown);
    int index, starting, flipping = 0, progress = 0;

    while (progress < numPairs)
    {
        std::cout << "Pick a cell to flip: ";
        std::cin >> index;

        while (index < 0 || index >= numSlots || bShown[index])
        {
            if (index < 0 || index >= numSlots)
            {
                std::cout << "Index needs to be in the range [0, " << numSlots << "]." << std::endl;
            }
            else
            {
                std::cout << "The cell indexed at " << index << " is shown." << std::endl;
            }

            std::cout << "Re-enter an index: ";
            std::cin >> index;
        }

        if (flipping % 2 == 0)
        {
            bShown[index] = true;
            starting = index;
        }
        else
        {
            if (values[starting] == values[index] && !values[starting].empty())
            {
                bShown[index] = true;
                progress++;
            }
            else
            {
                bShown[starting] = false;
            }
        }

        display(bShown);
        flipping += 1;
    }

    std::cout << "Congratulations! Take " << flipping << " steps to find all matched pairs." << std::endl;
    delete[] bShown;
}
