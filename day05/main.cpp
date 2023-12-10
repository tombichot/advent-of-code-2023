#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cstdlib>
#include <list>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;
mutex mtx;

/*
* Split a string into several parts and convert to int
*/
vector<long long int> split(const string& input) {
    vector<long long int> tokens;
    stringstream ss(input);
    string token;

    while (getline(ss, token, ' ')) {
        tokens.push_back(stoll(token));
    }

    return tokens;
}

/*
* Find a location starting from a seed with a map
*/
long long int getLocation(const list<list<vector<long long int>>>& maps, long long int seed) {
    long long int location = seed; //Start
    for (const auto& map : maps) {
        bool stop = false;
        for (const auto& m : map) {
            long long int SRS = m[1];
            long long int DRS = m[0];
            long long int range = m[2] - 1;

            if (!stop && location >= SRS && location <= SRS + range) {
                stop = true;
                //cout << DRS << " | " << SRS << " | " << range << '\n';
                if (SRS > DRS) location += DRS - SRS;
                else if (SRS < DRS) location += DRS - SRS;
            }
        }
    }
    return location;
}

/*
* Find the shortest location from a range of seeds
*/
void processSeedsRange(const long long int& start, const long long int& end, const list<list<vector<long long int>>>& maps, long long int& locationPart2) {
 
    long long int location = -1; 
    for (long long int j = start; j < start + end; j++) {
        long long int tmp = getLocation(maps, j);
        if (location > tmp || location == -1) location = tmp;
    }

    mtx.lock();
    if (locationPart2 > location || locationPart2 == -1) locationPart2 = location;
    mtx.unlock();
}

int main() {
    cout << "Advent of Code 2023" << '\n';
    cout << "Day 5: If You Give A Seed A Fertilizer" << "\n\n";

    fstream newfile;

    newfile.open("./input.txt", ios::in);
    if (newfile.is_open()) { 

        string line;

        vector<string> almanac = { "seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light", "light-to-temperature", "temperature-to-humidity", "humidity-to-location" };
        vector<long long int> seeds;

        int i = 0;
        list<list<vector<long long int>>> maps;
        list<vector<long long int>> map;

        //Get Data
        while (getline(newfile, line)) {
            if (seeds.size() == 0) {
                seeds = split(line.erase(0, 7));
            }
            else if (line.empty() && map.size() > 0) {
                maps.push_back(map);
                map.clear();
                i++;
            }
            else if (!line.empty() && line.find(almanac[i]) == string::npos) {
                map.push_back(split(line));
            }
        }

        maps.push_back(map);

        newfile.close();

        //Processing
        //Part 1
        long long int puzzleAnswer1 = -1;

        for (int i = 0; i < seeds.size(); i++) {
            long long int tmp = getLocation(maps, seeds[i]);
            if (puzzleAnswer1 > tmp || puzzleAnswer1 == -1) puzzleAnswer1 = tmp;
        }

        //Part 2
        long long int puzzleAnswer2 = -1;

        vector<thread> threads;

        for (int t = 0; t < seeds.size(); t += 2) {
            threads.emplace_back(processSeedsRange, std::ref(seeds[t]), std::ref(seeds[t+1]), std::ref(maps), std::ref(puzzleAnswer2));
        }

        for (auto& th : threads) {
            th.join();
        }    

        //Answers
        cout << "Puzzle answer 1 : " << puzzleAnswer1 << '\n';
        cout << "Puzzle answer 2 : " << puzzleAnswer2 << '\n';
    }
}