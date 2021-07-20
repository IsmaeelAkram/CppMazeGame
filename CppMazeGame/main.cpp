#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

#define CLEAR() system("clear")
#define GRID_WIDTH 40
#define GRID_HEIGHT 10
#define GRID_PLAYER 'X'
#define GRID_OBSTACLE '#'
#define GRID_EMPTY '.'
#define UP "w"
#define LEFT "a"
#define DOWN "s"
#define RIGHT "d"

class Point {
public:
    int x;
    int y;
    Point(){
        x = 0;
        y = 0;
    }
    Point(int x, int y){
        this->x = x;
        this-> y = y;
    }
};

typedef vector<Point> Points;

class Player {
public:
    Point pos;
    void Move(int x, int y, Points obstacles){
        bool obstacleFound = false;
        for(Point obstacle : obstacles){
            if(pos.x + x == obstacle.x && pos.y + y == obstacle.y){
                obstacleFound = true;
            }
        }
        
        if(!obstacleFound){
            pos.x += x;
            pos.y += y;
        }
    }
};

void loop(Player* player, Points obstacles);
void getObstacles(Points* obstacles);
vector<string> splitString(string s, string substring);
string grid(int width, int height, Point currentPos, Points obstascles);
string getNextMove();

int main() {
    CLEAR();

    Points obstacles;
    getObstacles(&obstacles);
    
    Player player;
    while(true){
        loop(&player, obstacles);
    }
}

void loop(Player* p, Points obstacles){
    ostringstream posString;
    posString << "(" << p->pos.x << "," << p->pos.y << ")\n\n";
    cout << posString.str();
    cout << grid(GRID_WIDTH, GRID_HEIGHT, p->pos, obstacles);
    
    string move = getNextMove();
    
    if(move == "q"){
        exit(EXIT_SUCCESS);
    } else if (move == UP){
        p->Move(0,-1, obstacles);
    } else if (move == DOWN){
        p->Move(0,1, obstacles);
    } else if (move == LEFT){
        p->Move(-1, 0, obstacles);
    } else if (move == RIGHT){
        p->Move(1,0, obstacles);
    }
    
    CLEAR();
}

vector<string> splitString(string s, char substring){
    vector<string> parts;
    string temp = "";
    for(char c : s){
        if(c == substring){
            parts.push_back(temp);
            temp = "";
        } else {
            temp += c;
        }
    }
    parts.push_back(temp);
    return parts;
}

void getObstacles(Points* obstacles){
    ifstream db("obstacles.txt");

    string line;
    if(db.is_open()){
        while(getline(db, line)) {
            vector<string> coords = splitString(line, ',');
            obstacles->push_back(Point(stoi(coords[0]), stoi(coords[1])));
        }
    } else {
        cerr << "Could not open obstacles.txt" << endl;
        exit(EXIT_FAILURE);
    }
}

string grid(int width, int height, Point pos, Points obstacles){
    string newGrid = "";

    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++) {
            bool obstacleFound = false;
            for(Point obstacle : obstacles){
                if(w == obstacle.x && h == obstacle.y){
                    newGrid += GRID_OBSTACLE;
                    obstacleFound = true;
                }
            }
            
            if(w == pos.x && h == pos.y){
                newGrid += GRID_PLAYER;
            } else {
                if (!obstacleFound) newGrid += GRID_EMPTY;
            }
        }
        newGrid += "\n";
    }
    
    return newGrid;
}

string getNextMove(){
    string move;
    cin >> move;
    return move;
}
