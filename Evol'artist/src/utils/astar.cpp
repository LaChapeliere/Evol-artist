//
//  astar.cpp
//  Evol'artist
//
//  Created by Emma Barme on 29/09/2017.
//  Adapted from Mehul Nirala's answer on >https://stackoverflow.com/questions/19193413/pathfinding-in-a-grid-system>
//  Copyright Copyright GNU General Public License v3.0
//

// A* path-finding implementation

#include <stdio.h>
#include <utility>
#include <vector>
#include <stack>
#include <set>
#include "math.h"
#include "float.h"

// Creating a shortcut for int, int pair type
typedef std::pair<int, int> Pair;

// Creating a shortcut for pair<int, pair<int, int>> type
typedef std::pair<double, std::pair<int, int> > pPair;

// A structure to hold the neccesary parameters
struct cell
{
    // Row and Column index of its parent
    // Note that 0 <= x <= worldSize-1 & 0 <= y <= worldSize-1
    int parent_x, parent_y;
    // f = g + h
    double f, g, h;
};

/**
 * A Utility Function to check whether destination cell has been reached or not
 * @param x The horizontal coordinate
 * @param y The vertical coordinate
 * @param dest The coordinates of the target
 * @return True is the specified coordinates correspond to the target
 */
bool isDestination(int x, int y, Pair dest)
{
    if (x == dest.first && y == dest.second)
        return (true);
    else
        return (false);
}

/**
 * A Utility Function to calculate the 'h' heuristics
 * @param grid Reference to a flattened grid matrix with the scores
 * @param x The horizontal coordinate
 * @param y The vertical coordinate
 * @param dest The coordinates of the target
 * @param maxScore The maximum score for a Spot in the grid
 * @return The heuristic value
 */
int calculateHValue(std::vector<int>& grid, int x, int y, Pair dest, const int maxScore)
{
    // Manhattan distance
    const int dist = sqrt(pow((x - dest.first), 2)) + sqrt(pow((y - dest.second), 2));
    const int worldSize = sqrt((double)grid.size());
    return dist + maxScore - grid[y * worldSize + x];
}

/**
 * A Utility Function to trace the path from the source to the destination and determine the stopping point after moveCap moves
 * @param cellDetails The matrix to hold the details of each cell
 * @param dest The coordinates of the target
 * @param moveCap The maximum number of moves
 * @return The heuristic value
 */
Pair tracePath(std::vector<std::vector<cell>> cellDetails, Pair dest, const int moveCap)
{
    int x = dest.first;
    int y = dest.second;
    
    std::stack<Pair> Path;
    
    //Reconstruct path
    while (!(cellDetails[y][x].parent_x == x
             && cellDetails[y][x].parent_y == y))
    {
        Path.push (std::make_pair (x, y));
        int temp_x = cellDetails[y][x].parent_x;
        int temp_y = cellDetails[y][x].parent_y;
        x = temp_x;
        y = temp_y;
    }
    
    Path.push (std::make_pair (x, y));
    
    //Find the stop point
    int move = 0;
    while (!Path.empty() && move < moveCap)
    {
        Path.pop();
        move++;
    }
    
    return Path.top();
}

/**
 * A Function to find the shortest path between a given source cell to a destination cell according to A* Search Algorithm
 * @param grid Reference to a flattened grid matrix with the scores
 * @param src The coordinates of the source in the grid
 * @param dest The coordinates of the target in the grid
 * @param moveCap The maximum number of moves
 * @param maxScore The maximum score for a Spot in the grid
 * @return The coordinates of the Spot reached after moveCap moves on the shortest path to the target
 */
//
Pair aStarSearch(std::vector<int>& grid, Pair src, Pair dest, const int moveCap, const int maxScore)
{
    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest) == true)
    {
        return src;
    }
    
    const int worldSize = sqrt((double)grid.size());
    
    // Create a closed list and initialise it to false which means that no cell has been included yet
    // This closed list is implemented as a boolean 2D array
    bool closedList[worldSize][worldSize];
    memset(closedList, false, sizeof (closedList));
    
    // Declare a matrix to hold the details of that cell
    std::vector<std::vector<cell>> cellDetails;
    cellDetails.resize(worldSize);
    // Initialise the cells of the A* algorithm
    for (int y = 0; y < worldSize; y++)
    {
        cellDetails[y].resize(worldSize);
        for (int x = 0; x < worldSize; x++)
        {
            cellDetails[y][x].f = FLT_MAX;
            cellDetails[y][x].g = FLT_MAX;
            cellDetails[y][x].h = FLT_MAX;
            cellDetails[y][x].parent_x = -1;
            cellDetails[y][x].parent_y = -1;
        }
    }
    
    // Initialising the parameters of the starting node
    int x = src.first;
    int y = src.second;
    cellDetails[y][x].f = 0.0;
    cellDetails[y][x].g = 0.0;
    cellDetails[y][x].h = 0.0;
    cellDetails[y][x].parent_x= x;
    cellDetails[y][x].parent_y = y;
    
    /*
     Create an open list having information as-
     <f, <x, y>>
     where f = g + h,
     and x, y are the colum and row index of that cell
     Note that 0 <= i <= worldSize-1 & 0 <= j <= worldSize-1
     This open list is implenented as a set of pair of pair.*/
    std::set<pPair> openList;
    
    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.insert(make_pair (0.0, std::make_pair (x, y)));
    
    // We set this boolean value as false as initially
    // the destination is not reached.
    bool foundDest = false;
    
    while (!openList.empty())
    {
        pPair p = *openList.begin();
        
        // Remove this vertex from the open list
        openList.erase(openList.begin());
        
        // Add this vertex to the open list
        x = p.second.first;
        y = p.second.second;
        closedList[y][x] = true;
        
        /*
         Generating all the 4 successor of this cell
         
               N
               |
               |
         W----Cell----E
               |
               |
               S
         
         Cell-->Popped Cell (i, j)
         N -->  North       (x, y-1)
         S -->  South       (x, y+1)
         E -->  East        (x+1, y)
         W -->  West        (x-1, y)
         
         Going round the world so no border effect*/
        
        // To store the 'g', 'h' and 'f' of the 4 successors
        double gNew, hNew, fNew;
        
        //----------- 1st Successor (North) ------------
    
        const int up = (y - 1 + worldSize) % worldSize;
        // If the destination cell is the same as the
        // current successor
        if (isDestination(x, up, dest) == true)
        {
            // Set the Parent of the destination cell
            cellDetails[up][x].parent_x = x;
            cellDetails[up][x].parent_y = y;
            Pair stopPoint = tracePath(cellDetails, dest, moveCap);
            foundDest = true;
            return stopPoint;
        }
        // If the successor is already on the closed list ignore it.
        // Else do the following
        else if (closedList[up][x] == false)
        {
            gNew = cellDetails[y][x].g + 1.0;
            hNew = calculateHValue (grid, x, up, dest, maxScore);
            fNew = gNew + hNew;
            
            // If it isn’t on the open list, add it to
            // the open list. Make the current square
            // the parent of this square. Record the
            // f, g, and h costs of the square cell
            //                OR
            // If it is on the open list already, check
            // to see if this path to that square is better,
            // using 'f' cost as the measure.
            if (cellDetails[up][x].f == FLT_MAX ||
                cellDetails[up][x].f > fNew)
            {
                openList.insert( make_pair(fNew,
                                           std::make_pair(x, up)));
                
                // Update the details of this cell
                cellDetails[up][x].f = fNew;
                cellDetails[up][x].g = gNew;
                cellDetails[up][x].h = hNew;
                cellDetails[up][x].parent_x = x;
                cellDetails[up][x].parent_y = y;
            }
        }
        
        //----------- 2nd Successor (South) ------------
        
        const int down = (y + 1 + worldSize) % worldSize;
        // If the destination cell is the same as the
        // current successor
        if (isDestination(x, down, dest) == true)
        {
            // Set the Parent of the destination cell
            cellDetails[down][x].parent_x = x;
            cellDetails[down][x].parent_y = y;
            Pair stopPoint = tracePath(cellDetails, dest, moveCap);
            foundDest = true;
            return stopPoint;
        }
        // If the successor is already on the closed
        // list or if it is blocked, then ignore it.
        // Else do the following
        else if (closedList[down][x] == false)
        {
            gNew = cellDetails[y][x].g + 1.0;
            hNew = calculateHValue(grid, x, down, dest, maxScore);
            fNew = gNew + hNew;
            
            // If it isn’t on the open list, add it to
            // the open list. Make the current square
            // the parent of this square. Record the
            // f, g, and h costs of the square cell
            //                OR
            // If it is on the open list already, check
            // to see if this path to that square is better,
            // using 'f' cost as the measure.
            if (cellDetails[down][x].f == FLT_MAX ||
                cellDetails[down][x].f > fNew)
            {
                openList.insert( make_pair (fNew, std::make_pair (x, down)));
                // Update the details of this cell
                cellDetails[down][x].f = fNew;
                cellDetails[down][x].g = gNew;
                cellDetails[down][x].h = hNew;
                cellDetails[down][x].parent_x = x;
                cellDetails[down][x].parent_y = y;
            }
        }
        
        //----------- 3rd Successor (East) ------------

        const int right = (x + 1 + worldSize) % worldSize;
        // If the destination cell is the same as the
        // current successor
        if (isDestination(right, y, dest) == true)
        {
            // Set the Parent of the destination cell
            cellDetails[y][right].parent_x = x;
            cellDetails[y][right].parent_y = y;
            Pair stopPoint = tracePath(cellDetails, dest, moveCap);
            foundDest = true;
            return stopPoint;
        }
        
        // If the successor is already on the closed
        // list or if it is blocked, then ignore it.
        // Else do the following
        else if (closedList[y][right] == false)
        {
            gNew = cellDetails[y][x].g + 1.0;
            hNew = calculateHValue (grid, right, y, dest, maxScore);
            fNew = gNew + hNew;
            
            // If it isn’t on the open list, add it to
            // the open list. Make the current square
            // the parent of this square. Record the
            // f, g, and h costs of the square cell
            //                OR
            // If it is on the open list already, check
            // to see if this path to that square is better,
            // using 'f' cost as the measure.
            if (cellDetails[y][right].f == FLT_MAX ||
                cellDetails[y][right].f > fNew)
            {
                openList.insert( make_pair(fNew,
                                           std::make_pair (right, y)));
                
                // Update the details of this cell
                cellDetails[y][right].f = fNew;
                cellDetails[y][right].g = gNew;
                cellDetails[y][right].h = hNew;
                cellDetails[y][right].parent_x = x;
                cellDetails[y][right].parent_y = y;
            }
        }
        
        //----------- 4th Successor (West) ------------
        
        const int left = (x - 1 + worldSize) % worldSize;
        // If the destination cell is the same as the
        // current successor
        if (isDestination(left,y, dest) == true)
        {
            // Set the Parent of the destination cell
            cellDetails[y][left].parent_x = x;
            cellDetails[y][left].parent_y = y;
            Pair stopPoint = tracePath(cellDetails, dest, moveCap);
            foundDest = true;
            return stopPoint;
        }
        
        // If the successor is already on the closed
        // list or if it is blocked, then ignore it.
        // Else do the following
        else if (closedList[y][left] == false)
        {
            gNew = cellDetails[y][x].g + 1.0;
            hNew = calculateHValue(grid, left, y, dest, maxScore);
            fNew = gNew + hNew;
            
            // If it isn’t on the open list, add it to
            // the open list. Make the current square
            // the parent of this square. Record the
            // f, g, and h costs of the square cell
            //                OR
            // If it is on the open list already, check
            // to see if this path to that square is better,
            // using 'f' cost as the measure.
            if (cellDetails[y][left].f == FLT_MAX ||
                cellDetails[y][left].f > fNew)
            {
                openList.insert( make_pair (fNew,
                                            std::make_pair (left, y)));
                
                // Update the details of this cell
                cellDetails[y][left].f = fNew;
                cellDetails[y][left].g = gNew;
                cellDetails[y][left].h = hNew;
                cellDetails[y][left].parent_x = x;
                cellDetails[y][left].parent_y = y;
            }
        }
    }
    
    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to blockages)
    return src;
}
