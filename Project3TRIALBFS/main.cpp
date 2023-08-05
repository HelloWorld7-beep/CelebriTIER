#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <map>
#include "MAM.h"
using namespace std;

int main() {
    string example, example2;
    string filename = "Test1.csv"; //replace with final csv
    MAM m;
    m.InputReader(filename);
    //m.PrintAdjList();

    int choice;
    string startActor;
    string endActor;

    while (true)
    {

        cout << "Menu:" << endl;
        cout << "1. BFS" << endl;
        cout << "2. Dijkstra's" << endl;
        cout << "3. Redo" << endl;
        cout << "4. Check if two actors share a movie" << endl;
        cout << "5. Exit" << endl;

        cout << "Enter 1, 2, 3, or 4 to proceed" << endl;
        cin >> choice;

        cin.ignore();
        cout << "o - - - - - - - - - - - - - - - - - - - o " << endl;
        cout << "| ------------------------------------- |" << endl;
        cout << "|  Menu:                                |" << endl;
        cout << "|                                       |" << endl;
        cout << "|  1. BFS                               |" << endl;
        cout << "|  2. Dijkstra's                        |" << endl;
        cout << "|  3. Redo                              |" << endl;
        cout << "|  4. Check if two actors share a movie"|" << endl;
        cout << "|  5. Exit                              |" << endl;
        cout << "| ------------------------------------- |" << endl;
        cout << "o - - - - - - - - - - - - - - - - - - - o" << endl;

        cout << endl;

        cout << "Please enter 1, 2, 3, 4, or 5 to proceed: ";
        cin >> choice;

        cin.ignore();

        cout << endl;

        if (choice == 1)
        {
            //User input first/second actor
            cout << "Starting actor: ";
            getline(cin, startActor);
            cout << "Ending actor: ";
            getline(cin, endActor);

            cout << endl;

            //Call BFS method
            m.BFS(startActor, endActor);
        }
        else if (choice == 2)
        {
            //User input first/second actor
            cout << "Starting actor: ";
            getline(cin, startActor);
            cout << "Ending actor: ";
            getline(cin, endActor);

            cout << endl;

            //Call dijkstras? Not sure what to call this
            m.dijkstras(startActor, endActor);
        }
        else if (choice == 3)
        {
            //Redo the loop, continue
            continue;
        }

        else if(choice == 4) {
            cout << "Check if actors share a movie" << endl;
            getline(cin, startActor);
            getline(cin, endActor);
            bool check;
            check = m.ShareMovies(startActor, endActor);
            if(check)
               cout << "They do share a movie" << endl;
            else if(!check) {
                cout << "They do not share a movie" << endl;
            }
        }
        else if (choice == 5)
        {
            //Exit the program
            return 0;
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }
}
