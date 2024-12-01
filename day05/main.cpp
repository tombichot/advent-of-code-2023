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
#include <iterator>

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
long long int getLocation(const list<list<vector<long long int>>>& maps, const long long int& seed) {
    long long int location = seed;
    
    //cout << "Seed : " << seed << endl;

        //cout << "----" << endl;
    for (const auto& map : maps) {
        for (const auto& m : map) {

            //cout << m[0] << " " << m[1] << " " << m[2] << endl;

            long long int SRS = m[1]; // Source range start
            long long int range = m[2];
            
            if (location >= SRS && location < SRS + range) {
                long long int DRS = m[0];; // Destination range start
                location += DRS - SRS;
                break;
            }
        }

        //cout << "Location : " << location << endl;
    }

    //cout << "--------------" << endl;

    return location;
}

long long int getSeed(const list<list<vector<long long int>>>& maps, const long long int& location, const vector<string>& almanac) {
    long long int seed = location;
    for (auto it = maps.rbegin(); it != maps.rend(); ++it) {
        for (const auto& m : *it) {
 
            long long int DRS = m[0]; // Destination range start
            long long int range = m[2];
            if(seed < DRS) {
                break;
            }
            else if (seed >= DRS && seed < DRS + range) {
                long long int SRS = m[1]; // Source range start
                seed -= DRS - SRS;
                break;
            }
        }
    }
    
    return seed;
}


list<vector<long long int>> getElementAtIndex(const list<list<vector<long long int>>>& maps, int index) {
    auto it = maps.begin();
    advance(it, index);
    return *it;
}

bool isSeed(const vector<long long int>& seeds, const long long int& value){
    for (const long long int& seed : seeds) {
        if (seed == value) {
            return true;
        }
    }
    return false;
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

bool compareSourceRangeStart(const vector<long long int> &a, const vector<long long int> &b) {
    return a[0] < b[0];
}

list<vector<long long int>> addMissingRules(list<vector<long long int>> map){
    list<vector<long long int>> newMap;
    for (const auto& m : map) {
        if (newMap.empty()) {
            if(m[1] != 0) newMap.push_back({0, 0, m[1]});
        }
        else {
            vector<long long int> last = newMap.back();
            if(last[1] + last[2] < m[1]) newMap.push_back({last[2], last[2], m[1] - last[2]});
        }
        newMap.push_back(m);
    }

    return newMap;
}

int main() {
    cout << "Advent of Code 2023" << endl;
    cout << "Day 5: If You Give A Seed A Fertilizer" << endl;
    cout << endl;

    fstream newfile;

    newfile.open("./input.txt", ios::in);
    if (newfile.is_open()) { 

        string line;

        vector<string> almanac = { "seed-to-soil", "soil-to-fertilizer", "fertilizer-to-water", "water-to-light", "light-to-temperature", "temperature-to-humidity", "humidity-to-location" };
        vector<long long int> seeds;

        int count = 0;
        list<list<vector<long long int>>> maps;
        list<vector<long long int>> map;

        //Get Data
        while (getline(newfile, line)) {
            if (seeds.size() == 0) {
                seeds = split(line.erase(0, 7));
            }
            else if (line.empty() && map.size() > 0) {
                map.sort(compareSourceRangeStart);
                //map = addMissingRules(map);
                maps.push_back(map);
                map.clear();
                count++;
            }
            else if (!line.empty() && line.find(almanac[count]) == string::npos) {
                map.push_back(split(line));
            }
        }
        map.sort(compareSourceRangeStart);
        maps.push_back(map);

        newfile.close();

/*
        //Debug maps
        count = 0;
        for (const auto& map : maps) {
            cout << almanac[count] << endl;
            for (const auto& m : map) {
                 cout << m[0] << " " << m[1] << " " << m[2] << endl;
            }
            count++;
        }
        cout << endl;
*/

        //Processing
        //Part 1
        long long int puzzleAnswer1 = -1;

        for (int i = 0; i < seeds.size(); i++) {
            long long int location = getLocation(maps, seeds[i]);
            if (puzzleAnswer1 > location || puzzleAnswer1 == -1) puzzleAnswer1 = location;
            if(puzzleAnswer1 == 424490994){
                cout << seeds[i] << endl;
                break;
            }
        }

        long long int location = -1;
        long long int seed = -1;
        bool stop = false;
        while(!stop){
            location++;
            long long int seed = getSeed(maps, location, almanac);
            stop = isSeed(seeds, seed);
        }
        long long int puzzleAnswer2 = location;
/*
        auto start = chrono::high_resolution_clock::now();

        for(int t = 0; t < seeds.size(); t+=2) {
            for (long long int seed = seeds[t]; seed < seeds[t] + seeds[t+1]; seed++) {
                long long int location = getLocation(maps, seed);
                if (puzzleAnswer2 > location || puzzleAnswer2 == -1) puzzleAnswer2 = location;  
            }
        }

        auto end = chrono::high_resolution_clock::now();

        chrono::duration<double, milli> duration = end - start;

        cout << "Temps d'execution : " << duration.count() << " ms" << endl;
        cout << endl;
*/
/*
        vector<thread> threads;

        for (int t = 0; t < seeds.size(); t += 2) {
            threads.emplace_back(processSeedsRange, ref(seeds[t]), ref(seeds[t+1]), ref(maps), ref(puzzleAnswer2));
        }

        for (auto& th : threads) {
            th.join();
        }
*/

        //Answers
        cout << "Puzzle answer 1 : " << puzzleAnswer1 << endl;
        cout << "Puzzle answer 2 : " << puzzleAnswer2 << endl;
    }
    else {
        std::cerr << "File not found" << std::endl;
        return 1;
    }
}