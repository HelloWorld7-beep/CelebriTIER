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
#include <algorithm>
#include <utility>
using namespace std;

class actors {
private:
    unordered_map<string,string> actorMovies;
    unordered_map<string, vector<pair<string, string>>> adjacencyList;
public:
    void InputReader(const string n);
    void PrintActor();
    bool ShareMovies(const string& name1, const string& name2);
    void PrintAdjList();
    string CreateAdjList(string v, string s, string to);
    vector<string> BFS(const string& start, const string& end);


};



#endif //CELEBRTIER1_0_ACTORS_H
