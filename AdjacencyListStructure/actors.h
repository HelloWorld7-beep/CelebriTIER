//
// Created by nfran on 8/4/2023.
//

#ifndef ADJACENCYLISTSTRUCTURE_ACTORS_H
#define ADJACENCYLISTSTRUCTURE_ACTORS_H

#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <algorithm>
#include <utility>
#include <unordered_set>
using namespace std;

class actors {
private:
    unordered_map<string, unordered_set<string>> actorsToMovies; //this is technically actors and their movie keys
    unordered_map<string, unordered_set<string>> moviesToActors; //movies and a vector of their actor key
    unordered_map<string, vector<pair<string, string>>> adjList;
public:
    void InputReader(const string n);
    void addEdges(unordered_map<string, unordered_set<string>>& actorToMovies,
                  unordered_map<string, unordered_set<string>>& mtA,
                  unordered_map<string, vector<pair<string, string>>>& adjList);
    bool ShareMovies(const string& name1, const string& name2);
    void PrintAdjList();

    void BFS(const string& start, const string& end);
};



#endif //ADJACENCYLISTSTRUCTURE_ACTORS_H
