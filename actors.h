//
// Created by nfran on 8/1/2023.
//

#ifndef CELEBRTIER1_0_ACTORS_H
#define CELEBRTIER1_0_ACTORS_H


#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

class actors {
private:
    unordered_map<int,vector<string>> actorMovies;
public:

    void InputReader(const string n);
    void FilterActors();
    unordered_map<int,vector<string>> FilterActorsHelper();
    void PrintActor();
};



#endif //CELEBRTIER1_0_ACTORS_H
