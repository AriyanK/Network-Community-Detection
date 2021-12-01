#include "Girvan-Newman.h"

Girvan::Girvan() {

}

void Girvan::read(ifstream& fin){
    boost::dynamic_properties dp(boost::ignore_other_properties);
    read_graphml(fin, g, dp);
}

void Girvan::betweenNessCalculation() {
    vector<vertex_descriptor> p(num_vertices(g));
    vector<int> d(num_vertices(g));
    vertex_descriptor start;
    graph_traits<Graph>::vertex_iterator vi, vend;
    graph_traits<Graph>::vertex_iterator vIt, vX;
    std::vector<graph_traits<Graph>::vertex_descriptor> path;
    graph_traits<Graph>::vertex_descriptor current;
    vector<graph_traits<Graph>::vertex_descriptor>::iterator it;



    vertex_descriptor source;
    vertex_descriptor target;

    for(tie(vi, vend) = vertices(g); vi != vend; ++vi) {
        start = vertex(*vi, g);
        dijkstra_shortest_paths(g, start, predecessor_map(&p[0]).distance_map(&d[0]));

        for (tie(vIt, vX) = vertices(g); vIt != vX; ++vIt) {

            current = vertex(*vIt, g);

            int z = 0;

            while (current != start) {
                if(z >= 100){
                    path.clear();
                    test = true;
                    return;
                }
                path.push_back(current);
                current = p[current];
                z++;
            }
            if(z >= 100)
                return;
            path.push_back(start);


            bool check;
            for (it = path.begin(); it != path.end(); ++it) {
                auto temp = it;
                //cout << *it << endl;
                temp++;
                check = false;
                for (auto iter = g.m_edges.begin(); iter != g.m_edges.end(); iter++) {
                    if ((iter->m_source == *it && iter->m_target == *temp) ||
                        (iter->m_source == *temp && iter->m_target == *it)) {
                        for (int x = 0; x < betweenNess.size(); x++) {
                            if (betweenNess[x].first == iter) {
                                betweenNess[x].second++;
                                check = true;
                            }
                        }
                        if (!check) {
                            betweenNess.push_back(make_pair(iter, 1));
                        }

                    }
                }
            }
            path.clear();
        }
    }

    getSingle();

    for(int x=0; x < maxIndices.size(); x++){
        source = vertex(betweenNess[maxIndices[x]].first->m_source, g);
        target = vertex(betweenNess[maxIndices[x]].first->m_target, g);
        remove_edge(source, target, g);
    }
    //remove_edge(source, target, g);
    betweenNess.clear();
    maxIndices.clear();

}

void Girvan::findCommunity() {
    int numEdges = num_edges(g);
    int runLength = numEdges;
    /*if(runLength > 160)
        runLength = 160;*/
    for(int x = 0; x < numEdges; x++){               //2474, 460, 462
        if(test)
            break;
        betweenNessCalculation();
        cout << boost::num_edges(g) << endl;
        //numEdges = num_edges(g);
    }
}

void Girvan::printGraph(){
    ofstream out("graphOutput.graphml");
    boost::dynamic_properties dp(boost::ignore_other_properties);
    write_graphml(out, g, dp, true);

}

void Girvan::getMax() {
    int max = 0;
    int maxIndex = 0;
    for (int x = 0; x < betweenNess.size(); x++) {
        if(betweenNess[x].second > max){
            max = betweenNess[x].second;
            maxIndex = x;
        }
    }
    for(int x = 0; x < betweenNess.size(); x++){
        if(betweenNess[x].second == max){
            maxIndices.push_back(x);
        }
    }
}

void Girvan::getHighest() {
    int max = 0;
    int maxIndex = 0;

    for(int y = 0; y < 5; y++){
        for (int x = 0; x < betweenNess.size(); x++) {
            if(betweenNess[x].second > max){
                max = betweenNess[x].second;
                maxIndex = x;
            }
        }

        maxIndices.push_back(maxIndex);
        betweenNess[maxIndex].second = 0;
        max = 0;
        maxIndex = 0;
    }
}

void Girvan::getSingle() {
    int max = 0;
    int maxIndex = 0;
    for (int x = 0; x < betweenNess.size(); x++) {
        if (betweenNess[x].second > max) {
            max = betweenNess[x].second;
            maxIndex = x;
        }
    }
    maxIndices.push_back(maxIndex);
}
