#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <tuple>
#include <map>

using namespace std;

int determineHandValue(const string& s, const bool& joker) {
    std::map<char, int> charCount;

    bool hasJ = false;

    for (char c : s) {
        if (c == 'J') hasJ = true;
        charCount[c]++;
    }

    if (charCount.size() == 1) return 6; // Five of a kind
   
    //Part 2 : Joker
    if (joker && hasJ) {
        char max;
        int count = 0;
        for (const auto& pair : charCount) {
            if (pair.first != 'J' && count <= pair.second) {
                max = pair.first;
                count = pair.second;
            }
        }

        charCount[max] += charCount['J'];
        auto it = charCount.find('J');

        if (it != charCount.end()) {
            charCount.erase(it);
        }
    }

    if (charCount.size() == 1) return 6; // Five of a kind
    if (charCount.size() == 2) {
        for (const auto& pair : charCount) {
            if (pair.second == 4) {
                return 5; // Four of a kind
            }
        }
        return 4; //Full house
    }
    else if (charCount.size() == 3) {
        for (const auto& pair : charCount) {
            if (pair.second == 3) {
                return 3; //Three of a kind
            }
        }
        return 2; //Two pair
    }
    else if (charCount.size() == 4) return 1; //One pair
    else return 0; //High card
}

tuple<string, int, int> getHand(const string& s, const bool& joker) {
    istringstream iss(s);

    string hand;
    int bid, value;

    if (iss >> hand >> bid) {
        value = determineHandValue(hand, joker);
        return make_tuple(hand, bid, value);
    }
}

int getCardValue(const char& c, const bool& joker) {
    map<char, int> cardValues;

    cardValues['A'] = 14;
    cardValues['K'] = 13;
    cardValues['Q'] = 12;
    cardValues['J'] = 11;
    cardValues['T'] = 10;
    cardValues['9'] = 9;
    cardValues['8'] = 8;
    cardValues['7'] = 7;
    cardValues['6'] = 6;
    cardValues['5'] = 5;
    cardValues['4'] = 4;
    cardValues['3'] = 3;
    cardValues['2'] = 2;

    if (joker && c == 'J') return 1;
    else return cardValues[c];
}

bool sortHands(const tuple<string, int, int>& a, const tuple<string, int, int>& b) {
    if (get<2>(a) == get<2>(b)) {
        for (int i = 0; i < get<0>(a).length(); i++) {
            if (getCardValue(get<0>(a)[i], false) == getCardValue(get<0>(b)[i], false)) continue;
            else return getCardValue(get<0>(a)[i], false) < getCardValue(get<0>(b)[i], false);
        }
        return false;
    }
    else return get<2>(a) < get<2>(b);
}


bool sortHandsWithJoker(const tuple<string, int, int>& a, const tuple<string, int, int>& b) {
    if (get<2>(a) == get<2>(b)) {
        for (int i = 0; i < get<0>(a).length(); i++) {
            if (getCardValue(get<0>(a)[i], true) == getCardValue(get<0>(b)[i], true)) continue;
            else return getCardValue(get<0>(a)[i], true) < getCardValue(get<0>(b)[i], true);
        }
        return false;
    }
    else return get<2>(a) < get<2>(b);
}

int main() {
    cout << "Advent of Code 2023" << '\n';
    cout << "Day 7: Camel Cards" << "\n\n";

    fstream newfile;

    newfile.open("./input.txt", ios::in); 
    if (newfile.is_open()) { 

        string line;

        vector<tuple<string, int, int>> hands;
        vector<tuple<string, int, int>> hands2;

        //Get data
        while (getline(newfile, line)) {
            hands.push_back(getHand(line, false));
            hands2.push_back(getHand(line, true));
        }

        newfile.close();

        //Processing
        //Part 1
        int puzzleAnswer1 = 0;

        sort(hands.begin(), hands.end(), sortHands);

        for (int i = 0; i < hands.size(); i++) {
            puzzleAnswer1 += (i + 1) * get<1>(hands[i]);
        }

        //Part 2
        int puzzleAnswer2 = 0;

        sort(hands2.begin(), hands2.end(), sortHandsWithJoker);

        for (int i = 0; i < hands2.size(); i++) {
            puzzleAnswer2 += (i + 1) * get<1>(hands2[i]);
        }
       
        //Answers
        cout << "Puzzle answer 1 : " << puzzleAnswer1 << '\n';
        cout << "Puzzle answer 2 : " << puzzleAnswer2 << '\n';
    }
}