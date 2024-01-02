//
//  Net.cpp
//  net_matrix
//
//  Created by 康捷 on 2019/12/12.
//  Copyright © 2019 康捷. All rights reserved.
//

#include "Net.h"
Net::Net(unsigned int input_size, vector<unsigned int> hidden_size_list, unsigned int output_size, string mode, bool dropout_train)
{
    dropout = dropout_train;
    // CREATE LAYERS ACCORDING TO PROVIDED TOPOLOGY AND APPEND TO layers_ vector
    Layer layer(mode);
    layer.weight_ = random_weight(input_size, hidden_size_list[0]); //weight between input and first hidden layer
    layer.bias_ = random_bias(hidden_size_list[0]); //weight from first hidden layer
    layers_.push_back(layer);
    for(unsigned int i=0; i<hidden_size_list.size()-1; i++)
    {
        Layer layer(mode);
        layer.weight_ = random_weight(hidden_size_list[i], hidden_size_list[i+1]);
        layer.bias_ = random_bias(hidden_size_list[i+1]);
        layers_.push_back(layer); //hidden layer
    }
     Layer layer_1("softmax"); //output layer
     layer_1.weight_ = random_weight(hidden_size_list.back(), output_size);
     layer_1.bias_ = random_bias(output_size);
     layers_.push_back(layer_1);

}

void Net::predict(vector<vector<double> > input, bool train, vector<vector<double> > target)
{
    // FEED AND ACTIVATE FIRST HIDDENLAYER LAYER
    input = drop_out_forward(input, dropout, dropout_ratio_i); //dropout
    layers_[0].hidden_layer_forward(input);
    for(unsigned int i=0; i<layers_.size()-1; i++)
    {
        if(i == layers_.size()-2) //reach output layer
        {
            layers_.back().output_layer_forward(layers_[layers_.size()-2].x_act_, target);  // FEED AND ACTIVATE OUTPUT LAYER
        }
        else
        {
        Layer &last_layer = layers_[i];
        Layer &current_layer= layers_[i+1];

        last_layer.x_act_drop_ = drop_out_forward(last_layer.x_act_, dropout, dropout_ratio_h); //dropout
        current_layer.hidden_layer_forward(last_layer.x_act_drop_);   // FEED AND ACTIVATE HIDDENLAYER LAYER

        }
    }

}

void Net::loss(vector<vector<double> > input, vector<vector<double> > target)
{
    predict(input, dropout, target);   // feed and activate all layers
    net_loss_ = layers_.back().loss_;   // get net loss
}


void Net::gradient(vector<vector<double> > input, vector<vector<double> > target)
{
    //forward
    loss(input, target);

    //backward

    layers_.back().output_layer_backward();
    grads_weight.push_back(layers_.back().dweight_);
    grads_bias.push_back(layers_.back().dbias_);
    layers_.back().dx_drop_=layers_.back().dx_;
    for(int i=int(layers_.size())-2;i>-1;i--)
    {
        layers_[unsigned(i)].hidden_layer_backward(layers_[unsigned(i)+1].dx_drop_);
        grads_weight.push_back(layers_[unsigned(i)].dweight_);
        grads_bias.push_back(layers_[unsigned(i)].dbias_);
        layers_[unsigned(i)].dx_drop_ = drop_out_backward(layers_[unsigned(i)].x_act_drop_, dropout, layers_[unsigned(i)].dx_);
    }

}

vector<vector<double> > Net::random_weight(unsigned int currentlayer_size, unsigned int nextlayer_size)
{
    vector<vector<double> > temp(currentlayer_size, vector<double>(nextlayer_size, 0));
    unsigned seed = unsigned(chrono::steady_clock::now().time_since_epoch().count());  // Seed based on current time.
    std::mt19937 mt(seed);  // Initialize random number generator "Mersenne twister" with seed of current time.
    std::uniform_real_distribution<double> dist(0,1);  // Filter random numbers by applying distribution.
    for(unsigned int i=0; i<currentlayer_size;i++)
    {
        for(unsigned int j=0; j<nextlayer_size;j++)
        {
            temp[i][j] = dist(mt);
        }
    }
    return temp;
}

vector<double> Net::random_bias(unsigned int currentlayer_size)
{
    vector<double> temp(currentlayer_size, 0);
    unsigned seed = unsigned(chrono::steady_clock::now().time_since_epoch().count());  // Seed based on current time.
    std::mt19937 mt(seed);  // Initialize random number generator "Mersenne twister" with seed of current time.
    std::uniform_real_distribution<double> dist(0,1);  // Filter random numbers by applying distribution.
    for(unsigned int i=0; i<currentlayer_size;i++)
    {
        temp[i] = dist(mt);
    }
    return temp;
}

void Net::weight_update()
{
    for(unsigned int i=0; i<layers_.size();i++)
    {
        for(unsigned int j=0; j<layers_[i].weight_.size();j++)
        {
            for(unsigned int k=0; k<layers_[i].weight_[0].size();k++)
            {
                layers_[i].weight_[j][k] -= learning_rate * grads_weight[layers_.size()-i -1][j][k];
            }
        }
    }
    grads_weight.clear();
}

void Net::bias_update()
{
    for(unsigned int i=0; i<layers_.size();i++)
    {
        for(unsigned int j=0; j<layers_[i].bias_.size();j++)
        {
            layers_[i].bias_[j] -= learning_rate * grads_bias[layers_.size()-i -1][j];

        }
    }
    grads_bias.clear();
}

void Net::show()
{
        cout << "weight" << endl;
        for(unsigned int i=0; i<layers_.size();i++)
        {
            for(unsigned int j=0; j<layers_[i].weight_.size();j++)
            {
                cout << "[";
                for(unsigned int k=0; k< layers_[i].weight_[0].size();k++)
                {
                    cout << layers_[i].weight_[j][k] << ",";
                }
                cout <<"],\n";
            }
            cout << endl;
        }

        cout << "bias" << endl;
        for(unsigned int i=0; i<layers_.size();i++)
        {
            for(unsigned int j=0; j<layers_[i].bias_.size();j++)
            {
                cout << layers_[i].bias_[j] << ",";
            }
            cout << endl;
        }

        cout << "result" << endl;
        for(unsigned int i=0; i<layers_.size();i++)
        {
            for(unsigned int j=0; j<layers_[i].x_act_drop_.size();j++)
            {
                cout << "[";
                for(unsigned int k=0; k< layers_[i].x_act_drop_[0].size();k++)
                {
                    cout << layers_[i].x_act_drop_[j][k] << ",";
                }
                cout <<"],\n";
            }
            cout << endl;
        }
        cout << "dweight" << endl;
        for(unsigned int i=0; i<grads_weight.size();i++)
        {
            for(unsigned int j=0; j<grads_weight[i].size();j++)
            {
                cout<< j << endl;
                cout << "[";
                for(unsigned int k=0; k< grads_weight[i][j].size();k++)
                {
                    cout << grads_weight[i][j][k] << ",";
                }
                cout <<"],\n";
            }
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
            cout << endl;
        }

        cout << "dbias" << endl;
        for(unsigned int i=0; i<grads_bias.size();i++)
        {
            cout << "[";
            for(unsigned int j=0; j<grads_bias[i].size();j++)
            {

                cout << grads_bias[i][j] << ",";
            }
            cout <<"],\n";

        }
}

double Net::accuracy()
{
    double batch_size = layers_.back().y_.size();
    double acc = 0.0;
    unsigned int max;
    unsigned int max_1;
    for(unsigned int i=0; i<layers_.back().y_.size();i++)
    {
        for(unsigned int j=0; j<layers_.back().y_[0].size();j++)
        {
            max = 0;
            if(layers_.back().y_[i][j] > layers_.back().y_[i][max])
            {
                max = j;
            }
//            cout << max;
        }
        for(unsigned int k=0; k<layers_.back().t_[0].size();k++)
        {
            max_1 = 0;
            if(layers_.back().t_[i][k] > layers_.back().t_[i][max_1])
            {
                max_1 = k;
            }
//            cout << max_1;
        }
        if(max == max_1)  // comparing prediction and target
        {
            acc += 1;
        }
    }
    return acc / batch_size;
}

vector<vector<double> > Net::drop_out_forward(vector<vector<double> > x, bool train_flag, double dropout_ratio)
{
    vector<vector<double> > temp=x;

    if (train_flag){
        for (unsigned int i=0; i < x.size(); i++){

            for (unsigned int j=0; j < x[0].size(); j++)
            {
                double rand = random_num();
                if (rand < dropout_ratio){
                    temp[i][j] = 0;
                }
        }
        }
        for (unsigned int m=0; m < x.size(); m++){
            for (unsigned int n=0; n < x[0].size(); n++)
            {
                temp[m][n] = temp[m][n] * (1-dropout_ratio);

            }
        }
       }

    return temp;
}
vector<vector<double> > Net::drop_out_backward(vector<vector<double> > x, bool train_flag, vector<vector<double> > dout)
{
    vector<vector<double> > temp=dout;
//    cout << "fef" << temp.size() << "ferer" << x.size()<<endl;

    if (train_flag){
        for (unsigned int i=0; i < x.size(); i++){

            for (unsigned int j=0; j < x[0].size(); j++)
            {
                if (x[i][j] == 0){
                    temp[i][j] = 0;
                }
            }
        }
    }
    return temp;
}
double Net::random_num()
{
    unsigned seed = unsigned(chrono::steady_clock::now().time_since_epoch().count());  // Seed based on current time.
    std::mt19937 mt(seed);  // Initialize random number generator "Mersenne twister" with seed of current time.
    std::uniform_real_distribution<double> dist(0,1);  // Filter random numbers by applying distribution.
//    cout << dist(mt) << endl;
    return dist(mt);

}
