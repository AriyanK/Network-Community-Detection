#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/graphml.hpp>
#include <math.h>
#include <chrono>
#ifndef INC_21F_PA03_KYLE_ARIYAN_PATH_H
#define INC_21F_PA03_KYLE_ARIYAN_PATH_H
using namespace boost;
using namespace std;


class Girvan {
public:
    struct VertexProperty {
        long node_id;
        long value;
        string label;
    };
    struct GraphData {
        string Name;
    };
    typedef adjacency_list<listS, vecS, undirectedS, no_property, property<edge_weight_t, int>, no_property> Graph;
    vector<pair<std::_List_iterator<boost::list_edge<long unsigned int, boost::property<boost::edge_weight_t, int> > >, int>> betweenNess;
    vector<int> maxIndices;
    bool test = false;
    Girvan();

    void read(ifstream& fin);

    void getMax();
    void getHighest();
    void getSingle();



    typedef graph_traits<Graph>::vertex_descriptor vertex_descriptor;
    typedef graph_traits<Graph>::edge_descriptor edge_descriptor;

    Graph g;
    void betweenNessCalculation();
    void findCommunity();
    void printGraph();
};


#endif //INC_21F_PA03_KYLE_ARIYAN_PATH_H