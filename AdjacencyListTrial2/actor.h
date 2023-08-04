//
// Created by nfran on 8/4/2023.
//

#ifndef CELEBTIER_ACTOR_H
#define CELEBTIER_ACTOR_H
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;


class actor {
public:
    string name;
    vector<string> topMovies;

    actor(const string& n, const vector<string>& movies) : name(n), topMovies(movies) {}
};


class MovieGraph {
private:
    unordered_map<string, vector<string>> movieActors;

public:
    void addMovie(const string &movie, const vector<string> &actors) {
        movieActors[movie] = actors;
    }

    vector<string> getCommonMovies(const actor &actor1, const actor &actor2) {
        unordered_set<string> movies1(actor1.topMovies.begin(), actor1.topMovies.end());
        unordered_set<string> movies2(actor2.topMovies.begin(), actor2.topMovies.end());
        vector<string> commonMovies;

        for (const string &movie: actor1.topMovies) {
            if (movies2.count(movie)) {
                commonMovies.push_back(movie);
            }
        }

        return commonMovies;
    }


};

#endif //CELEBTIER_ACTOR_H
