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