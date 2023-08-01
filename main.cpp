#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include "actors.h"
using namespace std;

int main() {
    string filename = "ImdbName.csv";
    actors m;
    m.InputReader(filename);
    //m.PrintActor();
    unordered_map<int, vector<string>> temp;

    temp = m.FilterActorsHelper();


    return 0;
}
