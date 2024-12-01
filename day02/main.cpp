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
vector<string> splitString(const string& input, const char delimiter) {
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
    cout << "Advent of Code 2023" << endl;
    cout << "Day 2: Cube Conundrum" << endl;
    cout << endl;

    fstream newfile;

    newfile.open("./input.txt", ios::in);
    if (newfile.is_open()) { 

        string line;

        vector<array<int, 3>> games;
        
        while (getline(newfile, line)) { 
             games.push_back(parseGame(line)); 
        }

        newfile.close(); 

        //Processing
        int puzzleAnswer1 = 0;
        int puzzleAnswer2 = 0;

        for (int i = 0; i < games.size(); ++i) {
            if(checkGame(games[i])) puzzleAnswer1 += i + 1;
            puzzleAnswer2 += games[i][0] * games[i][1] * games[i][2];
        }

        //Answers
        cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
        cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;
    }
}