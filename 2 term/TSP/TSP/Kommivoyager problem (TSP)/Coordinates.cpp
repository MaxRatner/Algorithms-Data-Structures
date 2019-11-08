#include "MinOst.h"

void Graph::Coordinates(int n_dots) {
    n = n_dots;
    vector<pair<int, int> > dots;
    
    
    for (int i = 0; i < n; i++) {
        // Box-muller
        double u = rand() % 2001 / 1000.0 - 1.0;
        double v = sqrt(1 - u * u) * (rand() % 2001 / 1000.0 - 1.0);
        double s = u * u + v * v;
        double p = sqrt(-2 * log(s) / s);
        
        if (fabs(s - 1) < 0.00001){
            p = 0;
        }
        
        double x = 100 * u * p;
        int x_mod_100 = (int)x / 100;
        x -= x_mod_100 * 100;
        
        double y = 100 * u * p;
        int y_mod_100 = (int)y / 100;
        y -= y_mod_100 * 100;
        
        dots.push_back(make_pair(x, y));
    }
    
    // Заполняем привычный граф вершинами и ребрами
    
    g = vector<vector<int> >(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            g[i][j] = sqrt(((dots[i].first - dots[j].first) * (dots[i].first - dots[j].first)) + ((dots[i].second - dots[j].second) * (dots[i].second - dots[j].second)));
            g[j][i] = g[i][j];
        }
    }
}
