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

void actors::dijkstras(const string& start, const string& end) {
    // Priority queue manages nodes based on their distance
     priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    // Map that stores distance from start node to each node
     unordered_map<string, int> dist;
    // Map that stores previous node and shared movie in shortest path
    unordered_map<string, string> prev;

    // Initialize dists and add starting actor to the priority queue
    for (const auto &entry: adjList) {
        const string &actor = entry.first;
        dist[actor] = numeric_limits<int>::max();
    }

    // Start node's dist set as 0 and pushed into priority queue
    dist[start] = 0;
    pq.push({0, start});

    // Go through nodes in the priority queue
    while (!pq.empty()) {
        // Get the current node, its dist, and remove it from the priority queue
        string curr = pq.top().second;
        int num = pq.top().first;
        pq.pop();

        // If calculated dist is greater than stored dist then skip it
        if (num > dist[curr]) {
            continue;
        }

        // Explore current node's neighbors
        for (const auto &neighbor: adjList[curr]) {
            // Get the current node, the weight of the edge, and calculate new dist to the neighbor
            const string &movie = neighbor.first;
            const string &nextActor = neighbor.second;
            int weight = ShareMovies(curr, nextActor) ? 1
                                                              : numeric_limits<int>::max(); // Weight is 1 if they share a movie, infinite otherwise
            // If new dist is smaller, then update the dist and the previous node with actor-movie pair
            if (num + weight < dist[nextActor]) {
                dist[nextActor] = num + weight;
                prev[nextActor] = curr;

                // Push the updated dist to the priority queue
                pq.push({dist[nextActor], nextActor});
            }
        }
    }

    // Print shortest path and shared movies
    vector<string> path;
    string actor = end;
    while (!actor.empty()) {
        path.push_back(actor);
        actor = prev[actor];
    }
    reverse(path.begin(), path.end());

    // Reconstruct and print the shortest path
    cout << "(Dijkstra) Shortest path between " << start << " and " << end << ":\n";
    for (int i = 0; i < path.size(); ++i) {
        if (i > 0) {
            cout << " -> ";
        }
        cout << path[i];

        if (i < path.size() - 1 && !ShareMovies(path[i], path[i + 1])) {
            cout << " (" << ShareMovies(path[i], path[i + 1]) << ")";
        }
    }
    cout << endl;
}
