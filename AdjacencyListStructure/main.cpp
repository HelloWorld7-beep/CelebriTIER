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
    string filename = "IMBDexample2.csv"; //replace with final csv
    actors m;
    m.InputReader(filename);
    m.PrintAdjList();



    return 0;
}