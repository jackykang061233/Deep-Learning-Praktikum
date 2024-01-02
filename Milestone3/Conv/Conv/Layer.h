//
//  Convolution.hpp
//  Conv
//
//  Created by 康捷 on 2020/1/15.
//  Copyright © 2020 康捷. All rights reserved.
//




#include <stdio.h>
#include <vector>
#include "kernel.h"
#include "channel.h"
#include <algorithm> 

using namespace std;
class Layer
{
public:
    Layer(int H, int W, int T, int C, int FH, int FW, int FT, int FC, int OH, int OW, int OT, int OC);
    vector<vector<vector<vector<double> > > > input;
    int input_height;
    int input_weight;
    int input_thickness;
    int channel;
    vector<vector<vector<vector<double> > > > input_ap; // input after padding
    
    vector<vector<vector<vector<double> > > > filter;
    int filter_height;
    int filter_weight;
    int filter_thickness;
    int filter_channel;
    
    vector<vector<vector<vector<double> > > > output;
    int output_thickness;
    int output_height;
    int output_weight;
    int output_channel;
    
    int stride=1;
    int padding;
    void zero_padding();
    
    vector<double> bias;
    vector<vector<vector<vector<double> > > > output_max; //output after maxpooling
    int max_filter=2; //the size of max filter
    
    void conv();
    void MaxPool();
    
    void show();
    
    double matrix_mul(vector<vector<vector<double> > > x, vector<vector<vector<double> > > y); //help function
    void LReLU();
    vector<vector<vector<double> > > clear(vector<vector<vector<double> > > x);
};

