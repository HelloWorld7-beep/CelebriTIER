//
// Created by nfran on 8/1/2023.
//

#include "actors.h"
void actors::InputReader(const string n) {
    ifstream file(n);
    string line;
    string hval;
    vector<string> colHeaders;
    map<string, vector<string>> rep;
    int hcount =0;
    string data = "";
    hcount = 0;
    int i = 0;

    while(getline(file, data)) {
        istringstream ss(data);
        string temp;
        while (getline(ss, data, ',') && hcount < 6) {
            colHeaders.push_back(hval);
            hcount++;
        }
        vector<string> details;

        while (getline(ss, temp, ',')) {
            if (temp.find_first_of('\"') != string::npos) {
                temp.erase(temp.find_first_of('\"'), 1);
            }
            details.push_back(temp);
            actorMovies[i] = details;
        }
        i++;

    }
    cout << actorMovies.size() << endl;
    file.close();
}

void actors::PrintActor() {
    for(auto it : actorMovies) {
        cout << it.first << ": ";
        for(int j = 0; j < it.second.size(); j++) {
            cout << it.second[j] << " ";
        }
        cout << endl;
    }

}


void actors::FilterActors() {
    bool check = false;

    for(auto it : actorMovies) {
        for(const auto & i : it.second) {
            if(i == "actor" || i == "actress") {
                check = true;
            }
        }
        if(!check) {
            actorMovies.erase(it.first);
        }
    }
    cout << actorMovies.size();

}

unordered_map<int,vector<string>> actors::FilterActorsHelper() {
    FilterActors();

    return actorMovies;
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
