//
//  layer.cpp
//  net_matrix
//
//  Created by 康捷 on 2019/12/11.
//  Copyright © 2019 康捷. All rights reserved.
//

#include "layer.h"
#include <math.h>

//Layer::Layer(vector<vector<double> > weight, vector<double> bias, string mode)
//{
//    weight_ = weight;
//    bias_ = bias;
//    mode_ = mode;
//}

Layer::Layer(string mode)
{
    mode_ = mode; //activation function
}

vector<vector<double> > Layer::hidden_layer_forward(vector<vector<double> > previous_layer)
{

    x_ = previous_layer;
    output_ = matrix_mul(x_, weight_);//matrix multiplication
    for(unsigned int i=0; i<output_.size();i++) //+bias
    {
        for(unsigned int j=0; j<output_[0].size();j++)
        {
            output_[i][j] += bias_[j];
        }
    }
    // ACTIVATE NEURONS
    x_act_ = activation(output_, mode_); //activation

    return x_act_;
}

vector<vector<double> > Layer::hidden_layer_backward(vector<vector<double> > dout)
{
    // BACKPROPAGATION FROM HIDDENLAYER (chainrule)
    dx_act_ = activation(dout, mode_+"_de");
    dx_ = matrix_mul(dx_act_, matrix_transpose(weight_));
    dweight_ = matrix_mul(matrix_transpose(x_), dx_act_);
    dbias_ = sum(dx_act_);
    return dx_;
}

double Layer::output_layer_forward(vector<vector<double> > x, vector<vector<double> > target)
{
    // FEED OUTPUTLAYER
    x_ = x;
    output_ = matrix_mul(x, weight_);//matrix multiplication
    for(unsigned int i=0; i<output_.size();i++) //+bias
    {
        for(unsigned int j=0; j<output_[0].size();j++)
        {
            output_[i][j] += bias_[j];
        }
    }
    // ACTIVATE
    t_ = target;
    y_ = softmax(output_); //softmax
    // CALCULATE LOSS
    x_act_ = y_;
    loss_ = cross_entropy(y_, target); //cross entropy

    return loss_;
}

vector<vector<double> > Layer::output_layer_backward()
{
    // BACKPROPAGATE FROM OUTPUTLAYER (chainrule)
    long batch_size = long(t_.size());
    vector<vector<double> > temp(y_.size(), vector<double>(y_[0].size(), 0));
    for(unsigned int i=0; i<y_.size();i++) // backpropagation for softmax
    {
        for(unsigned int j=0; j<y_[0].size();j++)
        {
            temp[i][j] = (y_[i][j] - t_[i][j]) / batch_size;
            if(output_[i][j]>0)
            {
                temp[i][j] = temp[i][j] * (1 / output_[i][j]);
            }
            else if (output_[i][j]<0)
            {
                temp[i][j] = temp[i][j] * (-1)*(1 / output_[i][j]);
            }

        }
    }
    dx_a = temp;
    //backprogation after softmax
    dx_ = matrix_mul(dx_a, matrix_transpose(weight_));
    dweight_ = matrix_mul(matrix_transpose(x_), dx_a);  // weight gradient
    dbias_ = sum(dx_a);   // bias gradient
    return dx_;
}

double Layer::cross_entropy(vector<vector<double> > y, vector<vector<double> > target)
{
    long batch_size = long(y.size());
    double sum = 0.0;
    for(unsigned int i=0; i<y.size();i++)
    {
        for(unsigned int j=0; j<y[0].size();j++)
        {
            sum += target[i][j] * log(y[i][j] + 1e-7);

        }
    }

    return -sum / batch_size;  // CROSS ENTROPY
}

double Layer::loss_error(vector<vector<double> > y, vector<vector<double> > target) //after loss calculator
{
    long batch_size = long(y.size());
    double sum = 0.0;
    for(unsigned int i=0; i<y.size();i++)
    {
        for(unsigned int j=0; j<y[0].size();j++)
        {
            sum += (y[i][j]-target[i][j])*(y[i][j]-target[i][j]);
        }
    }

    return sum / batch_size;  // MEAN SQUARE ERROR
}

vector<vector<double> > Layer::matrix_mul(vector<vector<double> > x, vector<vector<double> > y)
{
    vector<vector<double> > next(x.size(), vector<double>(y[0].size(), 0));

    for (unsigned int j = 0; j < y[0].size(); ++j)
    {
        for (unsigned int k = 0; k < x[0].size(); ++k)
        {
            for (unsigned int i = 0; i < x.size(); ++i)
            {
                next[i][j] += x[i][k] * y[k][j];
            }
        }
    }
    return next;

}

vector<vector<double> > Layer::matrix_transpose(vector<vector<double> > mat)
{
    vector<vector<double> > mat_1(mat[0].size(), vector<double>(mat.size(), 0));
    for(unsigned int i = 0; i < mat[0].size(); ++i)
    {
        for(unsigned int j = 0; j < mat.size(); ++j)
        {
             mat_1[i][j] = mat[j][i];
        }
    }
    return mat_1;
}

vector<double> Layer::sum(vector<vector<double> > dout)
{
    vector<double> temp;

    for(unsigned int i=0;i<dout[0].size();i++)
    {
        double s = 0.0;
        for(unsigned int j=0; j<dout.size();j++)
        {
            s += dout[j][i];
        }
        temp.push_back(s);
    }
    return temp;
}
vector<vector<double> > Layer::softmax(vector<vector<double> > x)
{
//    cout << "softmax" << x << endl;
    vector<vector<double> > temp(x.size(), vector<double>(x[0].size(), 0));

    for(unsigned int i=0; i<x.size();i++)
    {
        double sum = 0.0;
        for(unsigned int j=0; j<x[0].size();j++)
        {
            if(x[i][j]>0)
            {
                temp[i][j] = exp(log(x[i][j]));  // normalization for positive values
            }
            else if (x[i][j]<0)
            {
                temp[i][j] = exp(-log(-x[i][j]));  // normalization for negative values
            }
            else{
                temp[i][j] = exp(0);
            }
            sum += temp[i][j];

        }
        for(unsigned int k=0; k<x[0].size();k++)
        {
            temp[i][k] /= sum;  // SOFTMAX ACTIVATION for each neuron in outputlayer
        }
    }

    return temp;
}


vector<vector<double> > Layer::relu(vector<vector<double> > x)
{
    vector<vector<double> > temp(x.size(), vector<double>(x[0].size(), 0));

    for(unsigned int i=0; i<x.size();i++)
    {
        for(unsigned int j=0; j<x[0].size();j++)
        {
            if (x[i][j] > 0)
            {
                temp[i][j] = x[i][j];
            }
        }
    }

    return temp;
}

vector<vector<double> > Layer::relu_de(vector<vector<double> > x)
{
    vector<vector<double> > temp(x.size(), vector<double>(x[0].size(), 0));

    for(unsigned int i=0; i<x.size();i++)
    {
        for(unsigned int j=0; j<x[0].size();j++)
        {
            if(output_[i][j] > 0)
            {
                temp[i][j] = x[i][j];
            }
        }
    }

    return temp;
}

vector<vector<double> > Layer::lrelu(vector<vector<double> > x)
{
    vector<vector<double> > temp(x.size(), vector<double>(x[0].size(), 0));

    for(unsigned int i=0; i<x.size();i++)
    {
        for(unsigned int j=0; j<x[0].size();j++)
        {
            if (x[i][j] > 0)
            {
                temp[i][j] = x[i][j];
            }
            else{
                temp[i][j] = alpha*x[i][j];
            }
        }
    }

    return temp;
}

vector<vector<double> > Layer::lrelu_de(vector<vector<double> > x)
{
    vector<vector<double> > temp(x.size(), vector<double>(x[0].size(), 0));

    for(unsigned int i=0; i<x.size();i++)
    {
        for(unsigned int j=0; j<x[0].size();j++)
        {
            if(output_[i][j] > 0)
            {
                temp[i][j] = x[i][j];
            }
            else{
                temp[i][j] = alpha * x[i][j];
            }
        }
    }

    return temp;
}
vector<vector<double> > Layer::activation(vector<vector<double> > x, string mode)
{
    vector<vector<double> > temp(x.size(), vector<double>(x[0].size(), 0));
    if(mode == "softmax"){
        return softmax(x);
//    } else if(mode == "softmax_de"){
//        softmax_de(x);
//    } else if(mode == "sigmoid"){
//        sigmoid(x);
//    } else if(mode == "sigmoid_de"){
//        sigmoid_de(x);
    } else if(mode == "relu"){
        return relu(x);
    } else if(mode == "relu_de"){
        return relu_de(x);
    } else if(mode == "lrelu"){
        return lrelu(x);
    } else if(mode == "lrelu_de"){
        return lrelu_de(x);
    }
//    } else if(mode == "tanh"){
//        tan(x);
//    } else if(mode == "tanh_de"){
//        tan_de(x);

    return temp;
}

