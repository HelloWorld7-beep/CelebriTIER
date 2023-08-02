//
// Created by nfran on 8/1/2023.
//

#include "actors.h"
void actors::InputReader(const string n) {
    ifstream file(n);
    string line;

    //  temp = m.FilterActorsHelper();

    while(getline(file, line)) {
        istringstream iss(line);
        string key,key2 = "";
        string value, value2 = "";
        string temp1, temp2;

        if (getline(iss, key, ',') && getline(iss, value, ',')) {
            // Get actor2 and movie2
            actorMovies[key] = value; //keeps track of all actors and their movies
            string to = "";
            to = CreateAdjList(value, key, to); // sets up string value for a "to actor" address
            adjacencyList[key].emplace_back(to, value);
        }

        /*while (getline(iss, value, ',')) {
            actorMovies[key] = value;
            cout << "This is first value " << key << endl;

        }

        getline(iss, key, ',');

        while (getline(iss, value, ',')) {
            actorMovies[key] = value;
            cout << "this is second value " << key << endl;
        }

        /*adjacencyList[key].push_back(make_pair(key2, ""));
        if (adjacencyList.find(key2)==adjacencyList.end())
            adjacencyList[key2].push_back(make_pair(key, ""));
*/

    }

    file.close();
}

bool actors::ShareMovies(const string& name1, const string& name2) {
//boolean to see if two actors share a movie this might come in handy for the actual building of algorithms
    if(actorMovies.at(name1) == actorMovies.at(name2)) {
        return true;
    }
    return false;
}


void actors::PrintActor() { // prints out vector of actors and movies this was for me to check it was correct
    for(auto it : actorMovies) {
        cout << it.first << ": " << it.second << endl;
        cout << endl;
    }

}

void actors::PrintAdjList() { // don't use this unless you want to wait forever
    for (auto it : adjacencyList) {
        cout << it.first << " ";
        for(auto it2 : it.second) {
            cout << it2.first << " " << it2.second << endl;
        }
    }

}


string actors::CreateAdjList(string v, string s, string to) {
    //takes in all components of what would go in the list
    //v is the value(movie) s is the original addresss it is coming from, to is where it will go
    for(auto it :actorMovies) { //iterates through the dictionary of actors and movies
        if(it.second == v && it.first != s) { // if the movie equals the value we are putting into the graph
            return it.first;                //AND it isn't the same origin from actor we return the actor of where it has
        }                                   //the same movie
    }
    return ""; //else returns nothing
}


void actors::dijkstras(const string& start, const string& end) {
    //map that stores previous node in shortest path
    unordered_map<string, string> prev;

    //map that stores distance from start node to each node
    unordered_map<string, int> dist;

    //priority queue manages nodes based on their distance
    priority_queue<pair<int, string>, vector<pair<int, string> >, greater<pair<int, string> > > pq;

    //start node's distance set as 0 and pushed into priority queue
    dist[start] = 0;
    pq.push(make_pair(0, start));

    //initializing other nodes' distance to infinity and pushing them into priority queue
    for (const auto& actor : actorMovies) {
        pq.push(make_pair(numeric_limits<int>::max(), actor.first));
        dist[actor.first] = numeric_limits<int>::max();
    }
    
    //go through nodes in the priority queue
    while (!pq.empty()) {

        //get the current node, its distance, and remove it from the priority queue
        string curr = pq.top().second;
        int num = pq.top().first;
        pq.pop();

        //if calculated disntance is greater than stored distance then skip it
        if (num > dist[curr]) {
            continue;
        }

        //explore current node's neighbors
        for (const auto& neighbor : adjacencyList[curr]) {

            //get the current node, the weight of the edge, and calculate new distance to the neighbor
            string nextActor = neighbor.first;
            int weight = 1;
            int newNum = num + weight;

            //if new disntance smaller then update the disntance and the previous node 
            if (newNum < dist[nextActor]) {
                dist[nextActor] = newNum;
                prev[nextActor] = curr;

                //push the updated disntance to the priority queue
                pq.push(make_pair(newNum, nextActor));
            }
        }
    }

    //reconstruct and print the shortest path
    vector<string> path;
    string curr = end;

    while (!prev[curr].empty()) {
        path.insert(path.begin(), start);

        cout << "(Dijkstra) Shortest path between " << start << " and " << end << ":" << endl;
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

void actors::BFS(const string& start, const string& end) 
{

    //Adjacency list is map with key = actor, value = vector of pairs, element 1 = destination actor, element 2 = movie they share

    //If the two actors are the same
    if (start == end)
    {
        //Print message
        cout << "Please pick two different actors" << endl;
        //Return
        return;
    }

    //BFS traversal queue
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

        //Last element of current path
        string currActor = path.back();

        //Find neighbors of current vector from the adjacencyList
        vector<pair<string, string>> neighbors = adjacencyList[currActor];

        for (auto neighbor : neighbors)
        {
            //Find the next actor
            string nextActor = neighbor.first;
            //Find movie that connects current actor to next
            string nextMovie = neighbor.second;

            //Checking if next actor has been visited yet
            if (visitedActors.find(nextActor) == visitedActors.end())
            {
                //Inserting next actor into visited, since we're visiting it
                visitedActors.insert(nextActor);

                //Create new path
                vector<string> currPath = path;

                //Add to path
                currPath.push_back(nextActor);
                currPath.push_back(nextMovie);

                //If the actor is reached
                if (nextActor == end)
                {
                    //Print the movies, every other element is a movie
                    for (int i = 1;  i < currPath.size(); i+=2)
                    {
                        cout << currPath[i] << " -> " << endl;
                    }

                    //Return, ending the method
                    return;
                }

                //If not reached the end yet, push the current path onto the queue
                queue.push(currPath);

            }
        }

    }

}











