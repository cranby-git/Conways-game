#include "Coordinate.h"

using namespace std;

Coordinate::Coordinate() {
    r = 0;
    c = 0;
    surround = 0; 
}

Coordinate::Coordinate(int ROW, int COLUMN) {
    r = ROW;
    c = COLUMN;
    surround = 0;
}

Coordinate::Coordinate(int ROW, int COLUMN, int COUNT) {
    r = ROW;
    c = COLUMN;
    surround = COUNT;
}
