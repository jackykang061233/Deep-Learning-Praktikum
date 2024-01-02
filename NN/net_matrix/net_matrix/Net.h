//
//  Net.hpp
//  net_matrix
//
//  Created by 康捷 on 2019/12/12.
//  Copyright © 2019 康捷. All rights reserved.
//

#ifndef Net_hpp
#define Net_hpp

#include <chrono>
#include <random>
#include <stdio.h>
#include <string>
#include "layer.h"
#include <vector>

#endif /* Net_hpp */
using namespace std;

class Net
{
    public:
        Net(int input_size, vector<unsigned int> hidden_size_list, int output_size, string mode, bool dropout_train);
        double learning_rate = 0.5;
        int input_size;
        int hidden_size_list; //a list with the number of neurons of each hidden layer
        int output_size;
        double net_loss_;
    
        string mode; //activation
        bool dropout;
    
        vector<Layer> layers_; // vector of hidden layers and output
        void predict(vector<vector<double> > input, bool train, vector<vector<double> > target); //predict result
        void loss(vector<vector<double> > input, vector<vector<double> > target); //calculate loss with predict
        void gradient(vector<vector<double> > input, vector<vector<double> > target); //calculate gradient with predict and loss
     
        vector<vector<double> > random_weight(int currentlayer_size, int nextlayer_size); //randomize weight
        vector<double> random_bias(int currentlayer_size); //randomize bias
    
        vector<vector<vector<double> > > grads_weight; //store the differences of weights of every layer
        vector<vector<double> > grads_bias; //store the differences of bias of every layer

        void weight_update(); //update weight
        void bias_update(); //update bias
        void show(); //show weight, bias, result, dweight, dbias
        double accuracy(); // calculate accuracy of net
    
    
        vector<vector<double> > drop_out_forward(vector<vector<double> > x, bool train_flag, double dropout_ratio);
        vector<vector<double> > drop_out_backward(vector<vector<double> > x, bool train_flag, vector<vector<double> > dout);
    
        double random_num();
        double dropout_ratio_i=0.2;
        double dropout_ratio_h=0.5;
};
