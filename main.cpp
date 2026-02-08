//let there be life
#include "Coordinate.h"

#include <fstream>
#include <iostream>
#include <stack>
using namespace std;

#include "SFML/Graphics.hpp"
using namespace sf;

int main(int argc, char* argv[]) {
    int R, C;
    
    string saveFileName = "";
    string fileName;
    if (argc == 1) {
        fileName = argv[1];
    } else if (argc > 1) {
        fileName = argv[1];
        saveFileName = argv[2];
    } else {
        cout << "Insert game file: ";
        cin >> fileName;
    }

    ifstream ifile;
    ifile.open("gameFiles/" + fileName);
    if (!ifile.is_open()) {
        cerr << "Failed to load maze file: '" << fileName << "'" << endl;
        return -1;
    }

    ifile >> R >> C;

    //clockwise from noon
    Coordinate dirCells[8];
    dirCells[0] = Coordinate(-1, 0);
    dirCells[1] = Coordinate(-1, 1);
    dirCells[2] = Coordinate(0, 1);
    dirCells[3] = Coordinate(1, 1);
    dirCells[4] = Coordinate(1, 0);
    dirCells[5] = Coordinate(1, -1);
    dirCells[6] = Coordinate(0, -1);
    dirCells[7] = Coordinate(-1, -1);

    stack<Coordinate> nextGen;
    
    //load all data dynamically because C++ cant handle arrays with varriables as size on the stack
    char** conrray = new char*[R];
    for (int i = 0; i < R; i++) {
        conrray[i] = new char[C];
        for (int j = 0; j < C; j++) {
            ifile >> conrray[i][j];
        }
    }

    //create window
    sf::RenderWindow window(sf::VideoMode(C * 15, R * 15), "Conway's Game of Life");

    Event event;

    RectangleShape tile;
    tile.setSize(Vector2f(15.f, 15.f));

    bool isPlaying = false;

    while (window.isOpen()) {
        window.clear();

        //draw
        for (int j = 0; j < R; j++) {
            for (int k = 0; k < C; k++) {
                switch (conrray[j][k]) {
                    case '#':
                        tile.setFillColor(Color::White);
                        break;
                    case '.':
                        tile.setFillColor(Color::Black);
                        break;
                    default:
                        tile.setFillColor(Color::Red);
                        break;
                }
                tile.setPosition(Vector2f(k * 15, j * 15));
                window.draw(tile);
            }
        }

        if (isPlaying) {
            //run check
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    Coordinate cell(i, j);
                    for (int n = 0; n < 8; n++) {
                        if ((cell + dirCells[n]).r >= 0 &&
                            (cell + dirCells[n]).r < R &&
                            (cell + dirCells[n]).c >= 0 &&
                            (cell + dirCells[n]).c < C)
                            if (conrray[(cell + dirCells[n]).r][(cell + dirCells[n]).c] == '#') {
                                cell.surround++;
                            }
                    }
                    if (conrray[i][j] == '#') {
                        if (cell.surround == 2 || cell.surround == 3) nextGen.push(cell);
                    } else {
                        if (cell.surround == 3) nextGen.push(cell);
                    }
                }
            }

            // print next generation
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    conrray[i][j] = '.';        
                }
            }
            while (nextGen.size() > 0) {
                conrray[nextGen.top().r][nextGen.top().c] = '#';
                nextGen.pop();
            }
        }   

        //close window
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // add/delete cells
            if (event.type == Event::MouseButtonPressed) {
                conrray[Mouse::getPosition(window).y / 15][Mouse::getPosition(window).x / 15] = (conrray[Mouse::getPosition(window).y / 15][Mouse::getPosition(window).x / 15] == '#') ? '.' : '#'; 
            }

            //save
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::S) {
                if (saveFileName != "") cout << "saving to file '" << saveFileName << "'..." << endl;
                while (saveFileName == "") {
                    cout << "Save file name?: ";
                    cin >> saveFileName;
                    cout << endl;
                }
                
                ofstream saveFile("gameFiles/" + saveFileName);
                if (!saveFile.is_open()) cerr << "failed to open save file." << endl;
                else {
                    saveFile << R << " " << C << endl;
                    for (int i = 0; i < R; i++) {
                        for (int j = 0; j < C; j++) {
                            saveFile << conrray[i][j];
                        }
                        saveFile << endl;
                    }
                }
            }

            // pause/play
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space) {
                isPlaying = isPlaying ? 0 : 1;
            }
        }

        
        window.display();

        //delay
        sf::sleep(milliseconds(50));
    }
    
    return 0;
}