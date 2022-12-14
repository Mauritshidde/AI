#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <time.h>

class MazeCell
{
public:
    int coordX = 0;
    int coordY = 0;
    bool partOfPath = false;
    std::vector<int> walls{0, 1, 2, 3};
    bool visit = false;
};

class Maze
{
public:
    void createMazeGrid(int rows, int columns, int randomSeed);
    std::vector<MazeCell> visitedCells;
    int amountOfVisitedCells = 0;
    std::vector<std::vector<MazeCell>> createMaze(std::vector<std::vector<MazeCell>> mazeGrid, int coordX, int coordY, std::vector<MazeCell> visitedCells, int amountOfVisitedCells);
    void printMaze(std::vector<std::vector<MazeCell>> mazeGrid);
};

void Maze::createMazeGrid(int rows, int columns, int randomSeed)
{
    if (randomSeed != 0)
        srand(randomSeed);

    std::string partOfPath = " ";
    MazeCell singleCell;
    std::vector<std::vector<MazeCell>> mazeGrid;
    for (int i = 0; i < rows; i++)
    {
        std::vector<MazeCell> mazeColumn;
        for (int j = 0; j < columns; j++)
        {
            mazeColumn.push_back(singleCell);
        }
        mazeGrid.push_back(mazeColumn);
    }
    Maze newMaze;
    MazeCell startingMazeCell;
    startingMazeCell.visit = true;
    newMaze.visitedCells.push_back(startingMazeCell);
    mazeGrid = newMaze.createMaze(mazeGrid, startingMazeCell.coordX, startingMazeCell.coordY, newMaze.visitedCells, newMaze.amountOfVisitedCells);
    newMaze.printMaze(mazeGrid);
}

int removePossibleWall(std::vector<std::vector<MazeCell>> mazeGrid, std::vector<int> possibleWalls, int coordX, int coordY)
{
    if (possibleWalls.size() > 0)
    {

        int removedWallIndex = rand() % possibleWalls.size();
        int removedWall = possibleWalls.at(removedWallIndex);
        switch (removedWall)
        {
        case 0: // wall 0 is the left wall
            if (mazeGrid.at(coordX - 1).at(coordY).visit == true)
            {
                possibleWalls.erase(possibleWalls.begin() + removedWallIndex);
                return removePossibleWall(mazeGrid, possibleWalls, coordX, coordY);
            }
            else
            {
                return removedWall;
            }
            break;
        case 1: // wall 1 is the back wall
            if (mazeGrid.at(coordX).at(coordY - 1).visit == true)
            {
                possibleWalls.erase(possibleWalls.begin() + removedWallIndex);
                return removePossibleWall(mazeGrid, possibleWalls, coordX, coordY);
            }
            else
            {
                return removedWall;
            }
            break;
        case 2: // wall 2 is the right wall
            if (mazeGrid.at(coordX + 1).at(coordY).visit == true)
            {
                possibleWalls.erase(possibleWalls.begin() + removedWallIndex);
                return removePossibleWall(mazeGrid, possibleWalls, coordX, coordY);
            }
            else
            {
                return removedWall;
            }
            break;
        case 3: // wall 3 is the bottom wall
            if (mazeGrid.at(coordX).at(coordY + 1).visit == true)
            {
                possibleWalls.erase(possibleWalls.begin() + removedWallIndex);
                return removePossibleWall(mazeGrid, possibleWalls, coordX, coordY);
            }
            else
            {
                return removedWall;
            }
            break;
        }
    }
    return -1; //if no walls (adjacent tiles) are available, return -1 to let the createMaze function know
}

std::vector<std::vector<MazeCell>> Maze::createMaze(std::vector<std::vector<MazeCell>> mazeGrid, int coordX, int coordY, std::vector<MazeCell> visitedCells, int amountOfVisitedCells)
{
    if (amountOfVisitedCells >= mazeGrid.size() * mazeGrid.at(0).size())
    {
        return mazeGrid;
    }
    Maze newMaze;
    MazeCell currentMazeCell = mazeGrid.at(coordX).at(coordY);
    currentMazeCell.coordX = coordX; // currentMazeCell coordinates are 0, 0, this line changes that
    currentMazeCell.coordY = coordY;
    visitedCells.push_back(currentMazeCell);
    if (currentMazeCell.visit == false)
    {
        if (coordX == mazeGrid.size() - 1 && coordY == mazeGrid.at(0).size() - 1)
        {
            for (int i = 0; i < visitedCells.size(); i++)
            {
                int x = visitedCells.at(i).coordX;
                int y = visitedCells.at(i).coordY;
                mazeGrid.at(x).at(y).partOfPath = true;
            }
            currentMazeCell.partOfPath = true;
        }
        currentMazeCell.visit = true;
        amountOfVisitedCells = amountOfVisitedCells + 1;
    }
    // create a list of possible walls to break
    std::vector<int> possibleWalls;
    if (coordX > 0)
        possibleWalls.push_back(0);
    if (coordX < mazeGrid.size() - 1)
        possibleWalls.push_back(2);
    if (coordY > 0)
        possibleWalls.push_back(1);
    if (coordY < mazeGrid.at(0).size() - 1)
        possibleWalls.push_back(3);
    int removedWall = removePossibleWall(mazeGrid, possibleWalls, coordX, coordY);
    if (removedWall == -1)
    {
        while (visitedCells.back().coordX == currentMazeCell.coordX && visitedCells.back().coordY == currentMazeCell.coordY)
        {
            visitedCells.pop_back();
        }
        mazeGrid.at(coordX).at(coordY) = currentMazeCell;
        return newMaze.createMaze(mazeGrid, visitedCells.back().coordX, visitedCells.back().coordY, visitedCells, amountOfVisitedCells);
    }
    for (int i = 0; i < currentMazeCell.walls.size(); i++)
    {
        if (currentMazeCell.walls.at(i) == removedWall)
        {
            currentMazeCell.walls.erase(currentMazeCell.walls.begin() + i);
            break;
        }
    }
    mazeGrid.at(coordX).at(coordY) = currentMazeCell;
    switch (removedWall)
    {
    case 0:
        return newMaze.createMaze(mazeGrid, coordX - 1, coordY, visitedCells, amountOfVisitedCells);
        coordX = coordX - 1;
    case 1:
        coordY = coordY - 1;
        return newMaze.createMaze(mazeGrid, coordX, coordY, visitedCells, amountOfVisitedCells);
    case 2:
        coordX++;
        return newMaze.createMaze(mazeGrid, coordX, coordY, visitedCells, amountOfVisitedCells);
    case 3:
        coordY++;
        return newMaze.createMaze(mazeGrid, coordX, coordY, visitedCells, amountOfVisitedCells);
    }
    return mazeGrid; // never reached
}

std::string checkForWall(std::vector<std::vector<MazeCell>> mazeGrid, int coordY, int coordX, int oddOrEvenRow)
{
    if (oddOrEvenRow == 1)
    {
        for (int i = 0; i < mazeGrid.at(coordX).at(coordY).walls.size(); i++)
        {
            if (mazeGrid.at(coordX).at(coordY).walls.at(i) == 1)
            {
                try
                {
                    for (int i = 0; i < mazeGrid.at(coordX).at(coordY - 1).walls.size(); i++)
                    {
                        if (mazeGrid.at(coordX).at(coordY - 1).walls.at(i) == 3)
                        {
                            return "+---";
                        }
                    }
                    return "+   ";
                }
                catch (std::out_of_range)
                {
                    return "+---";
                }
            }
        }
        return "+   ";
    }
    else
    {
        for (int i = 0; i < mazeGrid.at(coordX).at(coordY).walls.size(); i++)
        {
            if (mazeGrid.at(coordX).at(coordY).walls.at(i) == 0)
            {
                try
                {
                    for (int i = 0; i < mazeGrid.at(coordX - 1).at(coordY).walls.size(); i++)
                    {
                        if (mazeGrid.at(coordX - 1).at(coordY).walls.at(i) == 2)
                        {
                            if (mazeGrid.at(coordX).at(coordY).partOfPath)
                            {
                                return "| . ";
                            }
                            else
                            {
                                return "|   ";
                            }
                        }
                    }
                }
                catch (std::out_of_range)
                {
                    if (mazeGrid.at(coordX).at(coordY).partOfPath)
                    {
                        return "| . ";
                    }
                    else
                    {
                        return "|   ";
                    }
                }
            }
        }
        if (mazeGrid.at(coordX).at(coordY).partOfPath)
        {
            return "  . ";
        }
        else
        {
            return "    ";
        }
        return ""; //never reached
    }
}

void Maze::printMaze(std::vector<std::vector<MazeCell>> mazeGrid)
{
    int columns = mazeGrid.size();
    int rows = mazeGrid.at(0).size() * 2 + 1;
    for (int i = 0; i < rows - 1; i++)
    {
        if (i % 2)
        { //for the rows that have the horizontal walls |
            for (int j = 0; j < columns; j++)
            {
                std::cout << checkForWall(mazeGrid, (i - 1) / 2, j, 0);
            }
            std::cout << "|\n";
        }
        else //for the rows that have the vertical walls +---
        {
            for (int j = 0; j < columns; j++)
            {
                std::cout << checkForWall(mazeGrid, i / 2, j, 1);
            }
            std::cout << "+\n";
        }
    }
    for (int i = 0; i < columns; i++)
    {
        std::cout << "+---";
    }
    std::cout << "+\n";
}

int main(int argc, char** argv)
{
    Maze newMaze;
    int columns = 0;
    int rows = 0;
    int randomSeed = time(0);
    const clock_t begin_time = clock(); 
    if (argc >= 2) 
    {
        rows = atoi(argv[1]);
    }
    if (argc >= 3) 
    {
        columns = atoi(argv[2]);
    }
    if (argc >= 4) 
    {
        randomSeed = atoi(argv[3]);
    }
    if (columns * rows == 0)
    {
        std::cout << "Error: Not enough arguments provided\n";
        return - 1;
    }
    newMaze.createMazeGrid(columns, rows, randomSeed);
    std::cout << clock () - begin_time << std::endl;
    return 0;
}