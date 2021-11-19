#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

#define tops 10


struct graphSolver
{
	vector<vector<int>> graph;
    vector <vector<int>> startPaths;
    int from;
    int to;
    void generateGraph() {
        vector<int> temp(tops, 0);
        for (int i = 0; i < tops; i++) {
            graph.push_back(temp);
        }
        /*ifstream inFile("test.txt");
        string temp2;
        for (int i = 0; i < tops; i++) {
            for (int j = 0; j < tops; j++) {
                inFile >> temp2;
                graph[i][j] = stoi(temp2);
            }
        }
        inFile.close();*/
        for (int i = 0; i < tops; i++) {
            int step = rand() % 3 + 1;
            cout << step << endl;
            for (int k = 0; k < step; k++) {
                int connectWith = rand() % (tops-i) + i;
                if (connectWith != i) {
                    int weight = rand() % 145 + 5;
                    if (countStep(i) < 3 && countStep(connectWith) < 3) {
                        graph[i][connectWith] = weight;
                        graph[connectWith][i] = weight;
                    }
                }
            }
        }
        for (int i = 0; i < tops; i++) {
            for (int j = 0; j < tops; j++) {
                cout << setw(4) << graph[i][j];
            }
            cout << endl;
        }
    }
    int countStep(int top) {
        int counter = 0;
        for (int i = 0; i < tops;i++) {
            if (graph[top][i] != 0)counter++;
        }
        return counter;
    }
    void countStepAll() {
        int counter = 0;
        for (int j = 0; j < tops; j++) {
            for (int i = 0; i < tops; i++) {
                if (graph[j][i] != 0)counter++;
            }
            cout << "counter: " << counter << endl;
            counter = 0;
        }

    }


    void startFind() {
        cout << "Between what tops you want to find shortest path?" << endl;
        cout << "Input first top: " << endl;
        cin >> from;
        cout << "Input second top: " << endl;
        cin >> to;
        for (int k = 0; k < 3; k++) {
            int current = from;
            vector<int> tempStartPath;
            tempStartPath.push_back(current);
            while (current != to) {
                vector<int> temp;
                for (int i = 0; i < tops; i++) {
                    if (graph[current][i] != 0) {
                        temp.push_back(i);
                    }
                }
                if (temp.size() == 0) {
                    cout << "The first top is an island" << endl;
                }
                current = temp[rand() % temp.size()];
                tempStartPath.push_back(current);
            }
            startPaths.push_back(tempStartPath);
        }
    }
    void outputPaths() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < startPaths[i].size(); j++) {
                cout << startPaths[i][j] << " ";
            }
            cout << endl;
        }
        countPath(startPaths[0]);
        countPath(startPaths[1]);
        countPath(startPaths[2]);
    }
    int countPath(vector<int> solution) {
        int sum = 0;
        for (int i = 0; i < solution.size() - 1; i++) {
            sum += graph[solution[i]][solution[i + 1]];
        }
        cout << "Sum: " << sum << endl;
        return sum;
    }
};


