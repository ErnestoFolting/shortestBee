#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

vector<vector<int>> generateGraph() {
    vector<vector<int>> graph;
    vector<int> temp (10, 0);
    for (int i = 0; i < 10; i++) {
        graph.push_back(temp);
    }
    ifstream inFile("test.txt");
    string temp2;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            inFile >> temp2;
            graph[i][j] = stoi(temp2);
        }
    }
    inFile.close();
    /*for (int i = 0; i < 10; i++) {
        int step = rand() % 10 + 1;
        cout << step << endl;
        for (int k = 0; k < step; k++) {
            int connectWith = rand() % 10;
            if (connectWith != i) {
                int weight = rand() % 145 + 5;
                graph[i][connectWith] = weight;
                graph[connectWith][i] = weight;
            }
        }
    }*/
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cout << setw(4) << graph[i][j];
        }
        cout << endl;
    }
    return graph;
}

int main()
{
    srand(time(0));
    vector<vector<int>> graph = generateGraph();
}
