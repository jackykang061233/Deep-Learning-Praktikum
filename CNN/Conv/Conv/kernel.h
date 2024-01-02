//
//  kernel.hpp
//  Conv
//
//  Created by 康捷 on 2020/1/15.
//  Copyright © 2020 康捷. All rights reserved.
//


#define kernel_h

#include <stdio.h>
#include <vector>
#include <random>
#include <iostream>
#include <math.h>

using namespace std;
class Kernel
{
public:
    Kernel(int FH, int FW, int FT, int C);
    int FH; //height of the filter
    int FW; //weight of the filter
    int FT; //thickness of the filter
    int Channel; // number of channels
    vector<vector<vector<vector<double> > > > kernel_matrix;
    vector<double> bias; // a vector of bias that corresponds each channel
    double random_num();
    void show();
    void reset();
};
