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











