#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>


using namespace std;

vector<int> getNumbers(string str) {
    vector<int> numbers;

    regex pattern("\\d+");

    smatch matches;
    while (regex_search(str, matches, pattern)) {
        for (auto match : matches) {
            numbers.push_back(std::stoi(match.str()));
        }
        str = matches.suffix().str();
    }

    return numbers;
}

int main() {
    fstream newfile;

    newfile.open("day06/input.txt", ios::in); 
    if (newfile.is_open()) { 

        string line;

        vector<string> lines;
            
        //Get data
        while (getline(newfile, line)) {
            lines.push_back(line);
        }

        vector<int> times = getNumbers(lines[0]);
        vector<int> distances = getNumbers(lines[1]);

        newfile.close();

        //Processing
        //Part 1
        int puzzlePart1 = 1;
        int speed = 1;

        for (int i = 0; i < times.size(); i++) {
            int count = 0;
            for (int j = 0; j <= times[i]; j++) {
                int d = (j * speed) * (times[i] - j);
                if (d > distances[i]) count++;
            }
            puzzlePart1 *= count;
        }

        //Part 2
        int puzzlePart2 = 0;

        ostringstream ossTime;
        ostringstream ossDistance;

        for (int i = 0; i < times.size(); i++) {
            ossTime << times[i];
            ossDistance << distances[i];
        }

        long long int time = stoll(ossTime.str());
        long long int distance = stoll(ossDistance.str());

        for (long long int j = 0; j <= time; j++) {
            long long int d = (j * speed) * (time - j);
            if (d > distance) puzzlePart2++;
        }

        //Display
        cout << "Advent of Code 2023" << '\n';
        cout << "Day 6: Wait For It" << "\n\n";

        cout << "Answer puzzle 1 : " << puzzlePart1 << '\n';
        cout << "Answer puzzle 1 : " << puzzlePart2 << '\n';
    }
}