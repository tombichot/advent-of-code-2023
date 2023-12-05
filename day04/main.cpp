#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>

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
* Replace all occurrences of a substring in a string with a new one
*/
string replaceAllSubstring(string str, string oldString, string newString) {
    size_t pos = str.find(oldString);

    while (pos != string::npos) {
        str.replace(pos, 2, newString);
        pos = str.find(oldString, pos + 1);
    }
    
    return str;
}

/*
* Convert a string to a vector of int
*/
vector<int> convertString(string str) {
    vector<int> numbers;

    vector<string> tmp = splitString(str, ' ');
    for (const string& str : tmp) {
        int convertedInt = stoi(str);
        numbers.push_back(convertedInt);
    }

    return numbers;
}

/*
* Extract the winning numbers and my numbers from a string and return them as vector of int
*/
vector<vector<int>> parse(string str) {
    vector<vector<int>> card;
    
    //Remove Card #:
    vector<string> cardInfos = splitString(str, ':'); 
    
    //Split winning numbers from my numbers
    vector<string> numbersString = splitString(cardInfos[1], '|'); 

    //Delete space for number with one digit
    numbersString[0] = replaceAllSubstring(numbersString[0], "  ", " ");
    numbersString[1] = replaceAllSubstring(numbersString[1], "  ", " ");

    //Delete first character (space)
    numbersString[0] = numbersString[0].substr(1);
    numbersString[1] = numbersString[1].substr(1);

    //Convert string to vector<int>
    card.push_back(convertString(numbersString[0]));
    card.push_back(convertString(numbersString[1]));

    return card;
}

/*
* Calculate point with maching numbers in a card
*/
int getPoints(vector<int> winningNumbers, vector<int> myNumbers) {
    int sum = 0;

    for (int winningNumber : winningNumbers) {
        for (int myNumber : myNumbers) {
            if (winningNumber == myNumber) {
                if (sum == 0) sum += 1;
                else sum *= 2;
                break;
            }
        }
    }
    return sum;
}

/*
* Count maching numbers in a card
*/
int countMachingNumbers(vector<int> winningNumbers, vector<int> myNumbers) {
    int sum = 0;

    for (int winningNumber : winningNumbers) {
        for (int myNumber : myNumbers) {
            if (winningNumber == myNumber) {
                sum += 1;
                break;
            }
        }
    }
    return sum;
}

int main() {
    fstream newfile;

    newfile.open("day04/input.txt", ios::in); 
    if (newfile.is_open()) { 

        string line;
        
        int totalPuzzle1 = 0;
        int totalPuzzle2 = 0;

        vector<vector<int>> winningCards; 
        vector<vector<int>> myCards;

        while (getline(newfile, line)) {
           
            vector<vector<int>> card = parse(line);
            
            winningCards.push_back(card[0]);
            myCards.push_back(card[1]);
        }

        //Processing
        int size = winningCards.size();
        vector<int> cards(size);
        for (int i = 0; i < size; i++) {
            totalPuzzle1 += getPoints(winningCards[i], myCards[i]);

            cards[i] = cards[i] + 1;

            int count = countMachingNumbers(winningCards[i], myCards[i]);

            for (int j = i + 1; j < i + 1 + count; j++) {
                if(j < size) cards[j] = cards[j] + cards[i];
            }

            totalPuzzle2 += cards[i];
        }

        newfile.close(); 

        cout << "Advent of Code 2023" << '\n';
        cout << "Day 4: Scratchcards" << "\n\n";
        
        cout << "Answer puzzle 1 : " << totalPuzzle1 << '\n';
        cout << "Answer puzzle 2 : " << totalPuzzle2 << '\n';
    }
}