#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include "actors.h"
using namespace std;

int main() {
    string example, example2;
    string filename = "IMBDexample2.csv";
    actors m;
    m.InputReader(filename);
   // m.PrintActor();
  //  m.CreateAdjList();
    //m.PrintAdjList();

    /*cout << "Enter" << endl;
    getline(cin, example);
    getline(cin, example2);
    m.ShareMovies(example, example2);*/

 //  unordered_map<string, vector<string>> temp;
  // ifstream file(filename);
  // string line;

  //  temp = m.FilterActorsHelper();

    /*while(getline(file, line)) {
        istringstream iss(line);
        string key = "";
        string value = "";
        string temp2 = "";
        vector<string> colHeaders;

        while (getline(iss, value, ',')) {
            while (getline(iss, key, ',')) {
                temp[key];
                while (getline(iss, value, ',')) {
                    if(value.find('\"') != std::string::npos) {
                        value.erase(value.find('\"'), 1);
                    }
                    temp[key].push_back(value);
                }
            }
        }
    }

    for(auto it : temp) {
        cout << it.first << ": ";
        for(int j = 0; j < it.second.size(); j++) {
            cout << j << ") " << it.second[j] << " ";
        }
        cout << endl;
    }
*/


    return 0;
}
