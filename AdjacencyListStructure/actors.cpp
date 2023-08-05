//
// Created by nfran on 8/4/2023.
//

#include "actors.h"
void actors::InputReader(const string n) {
    ifstream file("Test1.csv"); // Replace with your CSV file path
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, movieId;


            if (getline(iss, name, ',')) { // Use '\t' for tab separation, or ',' for comma
                while (getline(iss, movieId, ',')) {
                    actorsToMovies[name].insert(movieId);
                    moviesToActors[movieId].insert(name);// this is reading in
                }


            }
        }

        addEdges(actorsToMovies, moviesToActors, adjList);
    }
}

bool actors::ShareMovies(const string &name1, const string &name2) {
//boolean to see if two actors share a movie this might come in handy for the actual building of algorithms
    if (actorsToMovies.at(name1) == actorsToMovies.at(name2)) {
        return true;
    }
    return false;
}


void actors::PrintAdjList() {
    for (const auto &entry: adjList) {
        const string &node = entry.first;
        const vector<pair<string, string>> &connections = entry.second;

        cout << node << ": ";
        for (const auto &connection: connections) {
            cout << "(" << connection.first << ", " << connection.second << ") ";
        }
        cout << endl;
    }
}


void actors::addEdges(unordered_map<string, unordered_set<string>> &actorToMovies,
                      unordered_map<string, unordered_set<string>> &mtA,
                      unordered_map<string, vector<pair<string, string>>> &adjList) {
    for (const auto &it: actorToMovies) {
        const string &name = it.first;
        const unordered_set<string> &movieIdSet = it.second;
        for (const string &movieID: movieIdSet) {
            const auto &actorsInMovie = mtA[movieID]; // Directly access actors for the current movie
            for (const auto &getname: actorsInMovie) {
                if (getname != name) {
                    adjList[name].emplace_back(movieID, getname);
                }
            }
        }
    }
}