#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
#include "graph.h"


using namespace std;


int main()
{
    srand(time(0));
    graphSolver g;
    g.generateGraph();
    g.outputGraph();
    g.countStepAll();
    g.startFind();
    g.outputPaths();
    vector<int> test = g.findNear(g.startPaths[0]);
    cout << "CHECK" << endl;
    for (int i = 0; i < test.size(); i++) {
        cout << test[i] << " ";
    }
}
