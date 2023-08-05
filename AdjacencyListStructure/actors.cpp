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

//BFS method
void actors::BFS(const string& start, const string& end)
{
    //If the two actors are the same
    if (start == end)
    {
        //Print message
        cout << "Please pick two different actors" << endl;
        //Return
        return;
    }

    //BFS traversal path queue
    queue<vector<string>> queue;
    //Set keeping track of actors visited in path, unordered because don't need order
    unordered_set<string> visitedActors;

    //Start finding the path by enqueueing the start actor
    queue.push({start});
    visitedActors.insert(start);

    //Iterate through BFS
    while (!queue.empty())
    {
        //Dequeue first element, and pop
        vector<string> path = queue.front();
        queue.pop();

        //Last element of the current path
        string currActor = path.back();

        cout << "Current actor: " << currActor << endl;

        //Find neighbor of the current vector from the adjacencyList
        vector<pair<string, string>> neighbors = adjList[currActor];

        for (const auto& neighbor : neighbors)
        {
            const string& nextActor = neighbor.second;
            //Checking if next actor has been visited yet
            if (visitedActors.find(nextActor) == visitedActors.end())
            {
                //Inserting next actor into visited since we're visiting it
                visitedActors.insert(nextActor);

                cout << "Visiting neighbor: " << nextActor << endl;

                //Create a new path
                vector<string> currPath = path;

                //Add to path
                currPath.push_back(nextActor);
                currPath.push_back(neighbor.first);

                //If the actor is reached
                if (nextActor == end)
                {
                    cout << "Path found between " << start << " and " << end << ": ";

                    //Print the movies, every other element is a movie
                    for (int i = 1; i < currPath.size(); i += 2)
                    {
                        cout << currPath[i] << " -> ";
                    }
                    cout << endl;
                    //Return
                    return;
                }

                //If not reached the end yet, push the current path onto the queue
                queue.push(currPath);
            }
        }
    }

    //If no path is found, print a message
    cout << "No path found between " << start << " and " << end << endl;
}
