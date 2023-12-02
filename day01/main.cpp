#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

using namespace std;

/*
* Replace each word with its first letter + the corresponding number and its last letter.
*/
string replaceNumberWrittenInLetter(string str)
{
    char const* digits = "0123456789";

    std::map<std::string, std::string> litteralNumber = {
        {"1", "one"},
        {"2", "two"},
        {"3", "three"},
        {"4", "four"},
        {"5", "five"},
        {"6", "six"},
        {"7", "seven"},
        {"8", "eight"},
        {"9", "nine"}
    };

    for (const auto& pair : litteralNumber) {
        str = std::regex_replace(str, std::regex(pair.second), pair.second[0] + pair.first + pair.second[pair.second.length() - 1]);
    }

    return str;
}

/*
* Extract a number composed of the first and last digits appearing in a string
*/
int extractTwoDigitNumber(string str, bool replace)
{
    char const* digits = "0123456789";

    if (replace) str = replaceNumberWrittenInLetter(str);

    size_t firstDigit = str.find_first_of(digits);
    size_t lastDigit = str.find_last_of(digits);

    string number = "";
    number += str[firstDigit];
    number += str[lastDigit];

    return std::stoi(number);
}

int main() {
    fstream newfile;

    newfile.open("day01/input.txt", ios::in); 
    if (newfile.is_open()) { 

        string line;

        int totalPuzzle1 = 0;
        int totalPuzzle2 = 0;

        while (getline(newfile, line)) { 
            totalPuzzle1 += extractTwoDigitNumber(line, false);
            totalPuzzle2 += extractTwoDigitNumber(line, true);
        }

        newfile.close(); 
        cout << "Advent of Code 2023" << '\n';
        cout << "Day 1: Trebuchet?!" << "\n\n";

        cout << "Answer puzzle 1 : " << totalPuzzle1 << '\n';
        cout << "Answer puzzle 2 : " << totalPuzzle2 << '\n';
    }
}