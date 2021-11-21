#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include "solution.h"
using namespace std;

#define tops 10
#define areas 10
#define scouts 5
#define workers 15


struct graphSolver
{
    vector<vector<int>> graph;
    vector <solution> startPaths;
    int from;
    int to;
    void generateGraph() {
        vector<int> temp(tops, 0);
        for (int i = 0; i < tops; i++) {
            graph.push_back(temp);
        }
        ifstream inFile("test2.txt");
        string temp2;
        for (int i = 0; i < tops; i++) {
            for (int j = 0; j < tops; j++) {
                inFile >> temp2;
                graph[i][j] = stoi(temp2);
            }
        }
        inFile.close();
         /*for (int i = 0; i < tops; i++) {
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
         }*/
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
        int counterOfToopiks = 0;
        for (int k = 0; k < areas; k++) {
            vector<int> tempStartPath = generatePath();
            if (tempStartPath[tempStartPath.size()-1] != -1) {
                startPaths.push_back(solution(tempStartPath,graph));
            }
            else {
                k--;
                counterOfToopiks++;
            }
            if (counterOfToopiks >= 10) {
                counterOfToopiks = 0;
                cout << "There is no path between this tops" << endl;
                exit(0);
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
    solution sendWorkers(int workersNum, solution to) {
        vector<solution> nearby;
        nearby.push_back(to);
        for (int i = 0; i < workersNum; i++) {
            vector<int> near = findNear(to.vec);
            if (near[near.size() - 1] == -1) {
                i--;
                cout << "---------TOOPIK WHILE SEND WORKERS----------" << endl;
            }
            else {
                nearby.push_back(solution(near, graph));
            }
        }
        int min = INT_MAX;
        int index = 0;
        for (int i = 0; i < nearby.size(); i++) {
            if (nearby[i].nectar < min) {
                min = nearby[i].nectar;
                index = i;
            }
        }
        cout << "BEST FROM NEARBY" << endl;
        for (int i = 0; i < nearby[index].vec.size(); i++) {
            cout << nearby[index].vec[i] << " ";
        }
        cout << endl << nearby[index].nectar << endl;
        return nearby[index];
    }
    void sortByNectar() {
        for (int i = 0; i < startPaths.size() - 1; ++i)
        {
            for (int j = 0; j < startPaths.size() - i - 1; ++j)
            {
                if (startPaths[j].nectar > startPaths[j + 1].nectar) {
                    solution temp = startPaths[j];
                    startPaths[j] = startPaths[j + 1];
                    startPaths[j + 1] = temp;
                }
            }
        }
    }
    void beesOptimization() {
        int workersForArea = workers / scouts;
        cout << "Start generation: " << endl;
        for (int i = 0; i < startPaths.size(); i++) {
            for (int j = 0; j < startPaths[i].vec.size(); j++) {
                cout << startPaths[i].vec[j] << " ";
            }
            cout << "\nNectar: " << startPaths[i].nectar << endl;
        }
        for (int iterations = 0; iterations < 10; iterations++) {
            vector<solution> selectedByScouts;
            for (int i = 0; i < scouts; i++) {
                selectedByScouts.push_back(solution(startPaths[rand() % startPaths.size()].vec,graph));
            }
            for (int i = 0; i < selectedByScouts.size(); i++) {
                startPaths.push_back(sendWorkers(workersForArea, selectedByScouts[i]));
                sortByNectar();
                startPaths.pop_back();
            }
        }
        cout << "RESULT: " << endl;
        for (int i = 0; i < startPaths.size(); i++) {
            cout << startPaths[i].nectar << endl;
        }
    }
};



