//
// Created by nfran on 8/5/2023.
//

#include "ActorMovie.h"
void ActorMovie::InputReader(const string n) {
    ifstream file(n); // Replace with your CSV file path
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

    }
    //file.close();
}

bool ActorMovie::ShareMovies(const string &name1, const string &name2) {
//boolean to see if two actors that share a movie
    if(actorsToMovies.count(name1) && actorsToMovies.count(name2)) {
        unordered_set<string>& movieList1 = actorsToMovies[name1];
        unordered_set<string>& movieList2 = actorsToMovies[name2];
        for(const auto& it : movieList1) {
            if(movieList2.find(it) != movieList2.end()) {
                return true;
            }
        }
    }
    return false;
}

//extra printing function for adjacency list
void ActorMovie::PrintAdjList() {
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

//edges are added by string to save time and space
void ActorMovie::addEdges(const string& a) {
    const string &name = a;
    const unordered_set<string> &movieIdSet = actorsToMovies[a]; //access the id set that is attatched to this actor
    for (const string &movieID: movieIdSet) { //circulate through the set for each movie ID
        const auto &aInMovie = moviesToActors[movieID]; // Directly access the set that has the actors in that movie id
        for (const auto &getname: aInMovie) { //get the name for the actor in that movie id
            if (getname != name) { //as long as the getname does not equal the original name 
                adjList[name].emplace_back(movieID, getname); //add in undirected paths between the two actors that share the same movie
                adjList[getname].emplace_back(movieID, name);
            }
        }
    }
}

void ActorMovie::BFS(const string& start, const string& end)
{
    if (start == end) {
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
    queue.push({start}); // Store the starting actor in the queue
    visitedActors.insert(start);

    //Iterate through BFS
    while (!queue.empty()) {
        //Dequeue first element, and pop
        vector<string> path = queue.front();
        queue.pop();

        //Last element of the current path
        string currActor = path.back();
        addEdges(currActor);

        //Find neighbor of the current vector from the adjacencyList
        vector<pair<string, string>> neighbors = adjList[currActor];

        for (const auto& neighbor : neighbors) {
            const string& nextActor = neighbor.second;


            //Checking if next actor has been visited yet
            if (visitedActors.find(nextActor) == visitedActors.end()) {
                //Inserting next actor into visited since we're visiting it
                visitedActors.insert(nextActor);

                //Create a new path1
                vector<string> currPath = path;
                //Add to path
                currPath.push_back(neighbor.first); // Add the movie to the path
                currPath.push_back(nextActor);

                //If the actor is reached
                if (nextActor == end) {
                    cout << "Path found between " << start << " and " << end << ": ";

                    //Print the list of movies and actors
                    for (int i = 0; i < currPath.size(); ++i) {
                        if (i % 2 == 0) {
                            //Print the actor
                            cout << currPath[i];
                        }
                        else {
                            //Print the movie
                            cout << " (" << currPath[i] << ") -> ";
                        }
                    }

                    cout << endl;
                    return;
                }

                queue.push(currPath);
            }
        }
    }

    //If no path found, this is printed
    cout << "No path found between " << start << " and " << end << endl;
}

void ActorMovie::dijkstras(const string &start, const string &end) {
    if (start == end) {
        //Print message
        cout << "Please pick two different actors" << endl;
        //Return
        return;
    }
    addEdges(start);
    addEdges(end);
    // Priority queue manages nodes based on their distance
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    // Map that stores distance from start node to each node
    unordered_map<string, int> dist;
    // Map that stores previous node and shared movie in the shortest path
    unordered_map<string, pair<string, string>> prev; // <Node, <Previous Node, Movie>>

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
                prev[nextActor] = make_pair(curr, movie);

                // Push the updated dist to the priority queue
                pq.push({dist[nextActor], nextActor});
            }
        }
    }

    // Reconstruct and print the shortest path with movies
    if (dist[end] != numeric_limits<int>::max()) {
        cout << "(Dijkstra) Shortest path between " << start << " and " << end << ":\n";

        // Reconstruct the path
        string actor = end;
        vector<pair<string, string>> path;
        while (actor != start) {
            auto prevNode = prev[actor];
            path.push_back(prevNode);
            actor = prevNode.first;
        }

        // Print the path
        for (int i = path.size() - 1; i >= 0; --i) {
            if (i < path.size() - 1) {
                cout << " -> ";
            }
            cout << path[i].first << " (" << path[i].second << ")";
        }
        cout << " -> " << end << endl;
    } else {
        cout << "No path found between " << start << " and " << end << endl;
    }
}

//print for chechking the two maps besides the adjacency list
void ActorMovie::printOtherMaps() {
    for(const auto& it: actorsToMovies) {
        cout << it.first << " ";

        for(const auto& it2 : it.second)  {
            cout << "Value: "<< it2 << " ";
        }
        cout << endl;
    }
}
