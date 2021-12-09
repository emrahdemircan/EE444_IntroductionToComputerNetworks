//
//  main.cpp
//  project_SlidingWindowSimulation
//
//  Created by Demircan on 7.12.2021.
//

#include <iostream>
#include "Simulation.h"
using std::iostream;

int main(int argc, const char * argv[]) {
    // insert code here...
    int goon;
    Simulation S;
    
    S.RunSimulation();
    cout <<endl;
    cout <<"Write 'C' or 'C++' and then press enter to continue..."<<endl;
    cin >>goon;
    
    return 0;
}
