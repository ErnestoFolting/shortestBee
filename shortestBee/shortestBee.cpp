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
    g.beesOptimization();
}
