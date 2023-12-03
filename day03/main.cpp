#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
* Check whether a character is a symbol or not
*/
bool isSymbol(char c) {
    if (!isdigit(c) && c != '.') {
        return true;
    }
    return false;
}

/*
* Get the sum of all number (part numbers) adjacent to a symbol in the engine
*/
int getSumOfAllPartNumbers(vector<string> engine) {
    int sum = 0;
    
    int lineLength = engine[0].length();
    int engineSize = engine.size();

    for (int i = 0; i < engineSize; i++) {
        string number = "";
        for (int j = 0; j < lineLength; j++) {
            if (isdigit(engine[i][j])) {
               
                //Get the whole number
                int k = j;
                while (k < lineLength && isdigit(engine[i][k]))
                {
                    number += engine[i][k];
                    k++;
                }

                int numberLength = number.length();
                //Check character around this number
                char symbol = '\0';
                int a = (i - 1);
                while (a < i + 2 && symbol == '\0') {
                    int b = j - 1;
                    while (b < j + 1 + numberLength && symbol == '\0') {
                        if (a >= 0 && a < engineSize && b >= 0 && b < lineLength) {
                            if (isSymbol(engine[a][b])) {
                                sum += stoi(number);
                                symbol = engine[a][b];
                            }
                        }
                       
                        b++;
                    }
                    a++;
                }

                number = "";
                j = k;
            }
        }
    }

    return sum;
}

/*
* Get the sum of all gear ratios (multiple of two number adjacent to *) in the engine
*/
int getSumOfAllGearRatios(vector<string> engine) {
    int sum = 0;

    int lineLength = engine[0].length();
    int engineSize = engine.size();

    for (int i = 0; i < engineSize; i++) {
        string number = "";
        for (int j = 0; j < lineLength; j++) {

            vector<int> partNumbers;

            if (engine[i][j] == '*') {

                //Check around the symbol to find a number
                for (int a = i - 1; a < i + 2; a++) {
                    for (int b = j - 1; b < j + 2; b++) {

                        if (isdigit(engine[a][b])) {
                            string number = "";
                            number += engine[a][b];

                            //Get the whole number
                            int k = 1;
                            while (b - k >= 0 && b - k < lineLength && isdigit(engine[a][b - k]))
                            {
                                number = engine[a][b - k] + number;
                                k++;
                            }

                            k = 1;
                            while (b + k >= 0 && b + k < lineLength && isdigit(engine[a][b + k]))
                            {
                                number = number + engine[a][b + k];
                                k++;
                            }

                            partNumbers.push_back(stoi(number));
                            b += k;
                        }
                    }
                }

                if (partNumbers.size() == 2) sum += partNumbers[0] * partNumbers[1];
            }
        }
    }
    return sum;
}

int main() {
    fstream newfile;

    newfile.open("day03/input.txt", ios::in); 
    if (newfile.is_open()) { 

        string line;

        vector<string> engine;
        
        while (getline(newfile, line)) { 
            engine.push_back(line); //Get engine
        }

        newfile.close(); 

        cout << "Advent of Code 2023" << '\n';
        cout << "Day 3: Gear Ratios" << "\n\n";
        
        //Processing
        int totalPuzzle1 = getSumOfAllPartNumbers(engine);
        int totalPuzzle2 = getSumOfAllGearRatios(engine);


        cout << "Answer puzzle 1 : " << totalPuzzle1 << '\n';
        cout << "Answer puzzle 2 : " << totalPuzzle2 << '\n';
    }
}