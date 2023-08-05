//
// Created by nfran on 8/4/2023.
//

#ifndef PROJECT3TRIALBFS_MAM_H
#define PROJECT3TRIALBFS_MAM_H
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
#include <queue>
#include <limits>
using namespace std;

class MAM {
private:
    unordered_map<string, unordered_set<string>> actorsToMovies; //this is technically actors and their movie keys
    unordered_map<string, unordered_set<string>> moviesToActors; //movies and a vector of their actor key
    unordered_map<string, vector<pair<string, string>>> adjList;
public:
    void InputReader(const string n);
    void addEdges();
    bool ShareMovies(const string& name1, const string& name2);
    void PrintAdjList();


    void BFS(const string& start, const string& end);
    void dijkstras(const string& start, const string& end);
};


#endif //PROJECT3TRIALBFS_MAM_H
