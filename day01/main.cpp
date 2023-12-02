#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>

using namespace std;

string replaceLitteralNumbers(string str)
{
    char const* digits = "0123456789";
    cout << str << '\n';
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

    cout << str << '\n';

    return str;
}

int extractValue(string str, bool replace)
{
    char const* digits = "0123456789";

    if (replace) str = replaceLitteralNumbers(str);

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
            totalPuzzle1 += extractValue(line, false);
            totalPuzzle2 += extractValue(line, true);
        }
        newfile.close(); 

        cout << "Total puzzle 1 : " << totalPuzzle1 << '\n';
        cout << "Total puzzle 2 : " << totalPuzzle2 << '\n';
    }
}