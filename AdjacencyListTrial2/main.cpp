#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;

void addEdges(std::unordered_map<std::string, std::vector<std::string>>& actorToMovies, unordered_map<string, vector<string>>& mtA, unordered_map<string,vector< pair<string, string>>>& adjList) {
    for (const auto &it: actorToMovies) { //iterates through actors and their movie id vectors
        string name = it.first; //saves it
        vector<string> movieIdVector = it.second; //saves it
        for (const auto &movieID: movieIdVector) { // iterates through the movie id vectors
            for (const auto &movieID2: mtA) { // iterates through movies map with actors vector
                if (movieID == movieID2.first) { // if a movie id matches on on the mta(movies to actor map)
                    for (auto getname: mtA.at(movieID2.first)) { //it will iterate through the mta map
                        if(getname != name) { //cause it to get the name that equals that movie and making sure it
                            adjList[name].emplace_back(movieID, getname); // is not the same name and put it into
                            //the adjacency list
                        }
                    }
                }
            }
        }
    }
}

int main() {
    ifstream file(R"(C:\Users\nfran\CLionProjects\AdjacencyListTrial2\cmake-build-debug\Test1.csv)"); // replace with DIRECT csv path, use the test1.csv
    unordered_map<std::string, std::vector<string>> actorsToMovies; //this is technically actors and their movie keys
    unordered_map<string, vector<string>> moviesToActors; //movies and a vector of their actor key
    unordered_map<string, vector<pair<string, string>>> adjList; //adjacency list this connects edges

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string name, movieId;
            vector<string> movieIds;

            if (getline(iss, name, ',')) { // Use '\t' for tab separation, or ',' for comma
                while (getline(iss, movieId, ',')) {
                    movieIds.push_back(movieId);
                    moviesToActors[movieId].push_back(name);// this is reading in
                }

                actorsToMovies[name] = movieIds;


            }
        }

            addEdges(actorsToMovies, moviesToActors, adjList);

        //printing out adjacency list
            for (const auto& entry : adjList) {
                const std::string& node = entry.first;
                const std::vector<std::pair<std::string, std::string>>& connections = entry.second;

                std::cout << node << ": ";
                for (const auto& connection : connections) {
                    std::cout << "(" << connection.first << ", " << connection.second << ") ";
                }
                std::cout << std::endl;
            }

    }
    else {
            std::cerr << "Failed to open the file.\n";
        }

    return 0;
}




