#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

using namespace std;

/*
* Replace each word with its first letter + the corresponding number and its last letter.
*/
string replaceNumberWrittenInLetter(string& str)
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
int extractTwoDigitNumber(string& str, const bool& replace)
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
    cout << "Advent of Code 2023" << '\n';
    cout << "Day 1: Trebuchet?!" << "\n\n";

    fstream newfile;

    newfile.open("./input.txt", ios::in); 
    if (newfile.is_open()) { 

        string line;

        int puzzleAnswer1 = 0;
        int puzzleAnswer2 = 0;

        while (getline(newfile, line)) { 
            puzzleAnswer1 += extractTwoDigitNumber(line, false);
            puzzleAnswer2 += extractTwoDigitNumber(line, true);
        }

        newfile.close(); 

        //Answers
        cout << "Puzzle answer 1 : " << puzzleAnswer1 << '\n';
        cout << "Puzzle answer 2 : " << puzzleAnswer2 << '\n';
    }
}