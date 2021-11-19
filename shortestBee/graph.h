#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

#define tops 300
#define areas 10


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
     /*   ifstream inFile("test.txt");
        string temp2;
        for (int i = 0; i < tops; i++) {
            for (int j = 0; j < tops; j++) {
                inFile >> temp2;
                graph[i][j] = stoi(temp2);
            }
        }
         inFile.close();*/
         for (int i = 0; i < tops; i++) {
             int step = rand() % 10 + 1;
             cout << step << endl;
             for (int k = 0; k < step; k++) {
                 int connectWith = rand() % (tops-i) + i;
                 if (connectWith != i) {
                     int weight = rand() % 145 + 5;
                     if (countStep(i) < 10 && countStep(connectWith) < 10) {
                         graph[i][connectWith] = weight;
                         graph[connectWith][i] = weight;
                     }
                 }
             }
         }
         cout << "accept" << endl;
         for (int i = 0; i < tops; i++) {
             if (countStep(i) == 0) {
                 bool flag = false;
                 int weight = rand() % 145 + 5;
                 while (!flag) {
                     cout << "this" << endl;
                     int connectWith = rand() % tops;
                     cout << "this2 " << connectWith <<  endl;
                     if (countStep(connectWith) < 10 && connectWith != i) {
                         graph[i][connectWith] = weight;
                         graph[connectWith][i] = weight;
                         flag = true;
                         cout << "Check bro: " << i << " " << connectWith << endl;
                     }
                 }
             }
         }
    }
    void outputGraph() {
        for (int i = 0; i < tops; i++) {
            for (int j = 0; j < tops; j++) {
                cout << setw(4) << graph[i][j];
            }
            cout << endl;
        }
    }
    int countStep(int top) {
        int counter = 0;
        for (int i = 0; i < tops; i++) {
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
    bool vectorContains(int value, vector<int> vec) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] == value)return true;
        }
        return false;
    }

    void startFind() {
        cout << "Between what tops you want to find shortest path?" << endl;
        cout << "Input first top: " << endl;
        cin >> from;
        cout << "Input second top: " << endl;
        cin >> to;
        for (int k = 0; k < areas; k++) {
            vector<int> tempStartPath = generatePath();
            if (tempStartPath[tempStartPath.size()-1] != -1) {
                startPaths.push_back(tempStartPath);
            }
            else {
                k--;
            }
        }
    }
    vector<int> generatePath() {
        int current = from;
        vector<int> tempStartPath;
        tempStartPath.push_back(current);
        while (current != to) {
            vector<int> temp;
            for (int i = 0; i < tops; i++) {
                if (graph[current][i] != 0 && !vectorContains(i, tempStartPath)) {
                    temp.push_back(i);
                }
            }
            if (temp.size() == 0) {
                for (int i = 0; i < tempStartPath.size(); i++) {
                    cout << tempStartPath[i] << " ";
                }
                cout << "------------Toopik------------" << endl;
                tempStartPath.push_back(-1);
                return tempStartPath;
            }
            current = temp[rand() % temp.size()];
            tempStartPath.push_back(current);
        }
        return tempStartPath;
    }
    void outputPaths() {
        for (int i = 0; i < areas; i++) {
            for (int j = 0; j < startPaths[i].size(); j++) {
                cout << startPaths[i][j] << " ";
            }
            cout << endl;
            countPath(startPaths[i]);
        }
    }
    int countPath(vector<int> solution) {
        int sum = 0;
        for (int i = 0; i < solution.size() - 1; i++) {
            sum += graph[solution[i]][solution[i + 1]];
        }
        cout << "Sum: " << sum << endl;
        return sum;
    }
    vector<int> findNear(vector<int> vec) {
        vector<int> res;
        if (vec.size() < 4) {
            res = generatePath();
            cout << "check generate " << endl;
            return res;
        }
        else {
            int posFrom = rand() % (vec.size() - 3);
            int localFrom = vec[posFrom];
            int localTo = vec[posFrom + 3];
            int current = localFrom;
            cout << "From " << posFrom << endl;
            cout << "To " << posFrom + 3 << endl;
            vector<int> res;
            for (int i = 0; i < posFrom; i++) {
                res.push_back(vec[i]);
            }
            res.push_back(current);
            while (current != localTo) {
                vector<int> temp;
                for (int i = 0; i < tops; i++) {
                    if (graph[current][i] != 0 && !vectorContains(i, res)) {
                        temp.push_back(i);
                    }
                }
                if (temp.size() == 0) {
                    for (int i = 0; i < res.size(); i++) {
                        cout << res[i] << " ";
                    }
                    cout << "------------Toopik Near------------" << endl;
                    res.push_back(-1);
                    return res;
                }
                current = temp[rand() % temp.size()];
                res.push_back(current);
            }
            res.pop_back();
            for (int i = posFrom + 3; i < vec.size(); i++) {
                res.push_back(vec[i]);
            }
            cout << res.size() << endl;
            return res;
        }
    }
};


