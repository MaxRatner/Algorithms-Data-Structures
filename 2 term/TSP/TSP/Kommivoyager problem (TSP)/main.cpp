//
//  main.cpp
//  Kommivoyager problem (TSP)
//
//  Created by Maxim Fominykh on 29.04.2018.
//  Copyright © 2018 Maxim Fominykh. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "MinOst.h"

using namespace std;

int main() {
    // Количество точек в координатах
    int n, m;
    cin >> n >> m;

    double average = 0;
    vector<Graph> TSM(m);
    for( int i = 0; i < m; i++ ) {
        TSM[i].Coordinates(n);
        TSM[i].Prim();
    
        double answer1 = TSM[i].FindRound();
        double answer2 = TSM[i].Sort();
    
    double deviation = answer1 / answer2;
    average += deviation;
    }
    
    average /= m;
    cout << "Среднее отклонение: " << average << endl;
    
    
    return 0;
}
