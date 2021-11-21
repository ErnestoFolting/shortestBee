#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
struct solution
{
	vector<int> vec;
	int nectar;
    solution(vector<int> temp,vector<vector<int>> graph) {
        vec = temp;
        int sum = 0;
        for (int i = 0; i < temp.size() - 1; i++) {
            sum += graph[temp[i]][temp[i + 1]];
        }
        nectar = sum;
    }
};

