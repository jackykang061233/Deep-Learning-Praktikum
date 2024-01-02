//
//  layer.hpp
//  net_matrix
//
//  Created by 康捷 on 2019/12/11.
//  Copyright © 2019 康捷. All rights reserved.
//
//#ifndef LAYER_H
//#define LAYER_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Layer
{
public:
    Layer(string mode);
    bool dropout;
    string mode_;  //
    vector<vector<double> > hidden_layer_forward(vector<vector<double> > previous_layer);
    vector<vector<double> > hidden_layer_backward(vector<vector<double> > dout);
    double output_layer_forward(vector<vector<double> > x, vector<vector<double> > target);
    vector<vector<double> > output_layer_backward();
    double cross_entropy(vector<vector<double> > y, vector<vector<double> > target);
    double loss_error(vector<vector<double> > y, vector<vector<double> > target);
    double alpha = 0.2;
    // forward
    // hidden layer
    vector<vector<double> > x_; //the value from last layer
    vector<vector<double> > weight_;
    vector<double> bias_;
    vector<vector<double> > output_; //output before activation
    vector<vector<double> > x_act_; //output before dropout
    vector<vector<double> > x_act_drop_; //output after dropout
    
    
    // output layer
    double loss_; //entropy loss
    vector<vector<double> > y_; //output for output layer
    vector<vector<double> > t_; //target for output layer
    
    // back propagation
    // hidden layer
    vector<vector<double> > dx_act_; // backpropagation after activation
    vector<vector<double> > dx_; // before dropout
    vector<vector<double> > dx_drop_; // after dropout
    vector<vector<double> > dweight_;
    vector<double> dbias_;
    
    // output layer
    vector<vector<double> > dx_a; //backpropagation after softmax
    
    
    //useful function for matrix calculation
    vector<vector<double> > matrix_mul(vector<vector<double> > x, vector<vector<double> > y);
    vector<vector<double> > matrix_transpose(vector<vector<double> > mat);
    vector<double> sum(vector<vector<double> > dout);
    vector<vector<double> > cal_act(vector<vector<double> > x);
    vector<vector<double> > derive(vector<vector<double> > x);
    
    //softmax
    vector<vector<double> > softmax(vector<vector<double> > x);
    
    //relu
    vector<vector<double> > relu(vector<vector<double> > x);
    vector<vector<double> > relu_de(vector<vector<double> > x);
    
    //lrelu
    vector<vector<double> > lrelu(vector<vector<double> > x);
    vector<vector<double> > lrelu_de(vector<vector<double> > x);

    vector<vector<double> > activation(vector<vector<double> > x, string mode);
    
};


