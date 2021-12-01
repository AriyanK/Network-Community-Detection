#include <boost/config.hpp>
#include <iostream>
#include <fstream>
#include "Girvan-Newman.h"

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphml.hpp>
#include <chrono>


using namespace std;
using namespace boost;

int main(int argc, char **argv) {
    chrono::time_point<chrono::high_resolution_clock> start, end;
    chrono::duration<double> time_in_seconds;

    ifstream fin(argv[1]);

    Girvan path;
    path.read(fin);
    //path.betweenNessCalculation();
    start = chrono::high_resolution_clock::now();
    path.findCommunity();
    end = chrono::high_resolution_clock::now();
    time_in_seconds = end - start;
    cout << "Time: " << fixed << to_string(time_in_seconds.count());

    path.printGraph();

    return 0;
}