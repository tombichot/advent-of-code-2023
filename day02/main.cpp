#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <array>
#include <vector>
#include <sstream>

using namespace std;

/*
* Split a string into several parts according to a delimiter
*/
vector<string> splitString(const string& input, char delimiter) {
    vector<string> tokens;
    stringstream ss(input);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

/*
* Parse the string of a game to get the highest number of revealed cubes for each color (red, green, blue)
*/
array<int, 3> parseGame(const string& str) {
    array<string, 3> colors = {"red", "green", "blue"};

    array<int, 3> game = { 0, 0, 0 };

    vector<string> gameInfos = splitString(str, ':');

    string listOfSubsets = gameInfos[1];
    vector<string> subsets = splitString(listOfSubsets, ';');

    for (const string& subset : subsets) {
        vector<string> cubes = splitString(subset, ',');

        for (const string& cube : cubes) {
            string cube_tmp = cube.substr(1);
            vector<string> cubeInfos = splitString(cube_tmp, ' ');

            for (int i = 0; i < 3; ++i) {
                if (cubeInfos[1] == colors[i]) {
                    int value = stoi(cubeInfos[0]);
                    if (game[i] < value) {
                        game[i] = value;
                        break;
                    }
                }
            }
        }
    }

    return game;
}

/*
* Checks whether or not a game is possible for a given bag of cubes
*/
bool checkGame(const array<int, 3>& game) {
    const int bag[3] = { 12, 13, 14 }; //RGB

    if (game[0] <= bag[0] && game[1] <= bag[1] && game[2] <= bag[2]) {
        return true;
    }

    return false;
}

int main() {
    fstream newfile;

    newfile.open("day02/input.txt", ios::in); 
    if (newfile.is_open()) { 

        string line;

        vector<array<int, 3>> games;
        
        while (getline(newfile, line)) { 
             games.push_back(parseGame(line)); //Get all games
        }

        newfile.close(); 

        cout << "Advent of Code 2023" << '\n';
        cout << "Day 2: Cube Conundrum" << "\n\n";
        
        //Processing
        int totalPuzzle1 = 0;
        int totalPuzzle2 = 0;
        for (int i = 0; i < games.size(); ++i) {
            if(checkGame(games[i])) totalPuzzle1 += i + 1; //Puzzle 1
            totalPuzzle2 += games[i][0] * games[i][1] * games[i][2]; //Puzzle 2
        }

        cout << "Answer puzzle 1 : " << totalPuzzle1 << '\n';
        cout << "Answer puzzle 2 : " << totalPuzzle2 << '\n';
    }
}