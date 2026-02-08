#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

struct Coordinate {
    /**
     * @brief Construct a new Coordinate object at (0, 0)
     * 
     */
    Coordinate();
    /**
     * @brief Construct a new Coordinate object
     * 
     * @param ROW row to set to
     * @param COLUMN column to set to
     */
    Coordinate(int ROW, int COLUMN);
    /**
     * @brief Construct a new Coordinate object with set coordinates
     * 
     * @param ROW row to be intialized to
     * @param COLUMN column to be set to
     * @param HISTORY vector of coords visted
     */
    Coordinate(int ROW, int COLUMN, int COUNT);
    // row number
    int r;
    // column number
    int c;
    // cell that surround
    int surround;

    /**
     * @brief overload addition operator between coordiantes. keeps the history of the original coordinate
     * 
     * @param COORDINATE coordinate being added
     * @return Coordinate with r's and c's added 
     */
    Coordinate operator+(Coordinate const& COORDINATE) {
        return Coordinate(r + COORDINATE.r, c + COORDINATE.c, surround);
    }
};

#endif//COORDINATE_H