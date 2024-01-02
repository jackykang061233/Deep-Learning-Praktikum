//
//  channel.hpp
//  Conv
//
//  Created by 康捷 on 2020/1/15.
//  Copyright © 2020 康捷. All rights reserved.
//


#define channel_h

#include <stdio.h>
#include <vector>
#include <random>
#include <iostream>

using namespace std;

class Channel
{
public:
    Channel(int H, int W, int T, int C);
    int channel; //number of channels
    int input_height;
    int input_weight;
    int input_thickness;
    vector<vector<vector<vector<double> > > > list_input;
    double random_num();
    void get(); // get value
    void set();  // set value
    void add(int num); // add a number
    void clear(); // clear the function
    void LReLU(); //LReLU
};

