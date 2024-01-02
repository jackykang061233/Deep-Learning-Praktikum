//
//  Convolution.cpp
//  Conv
//
//  Created by 康捷 on 2020/1/15.
//  Copyright © 2020 康捷. All rights reserved.
//

#include "Layer.h"

Layer::Layer(int H, int W, int T, int C, int FH, int FW, int FT, int FC, int OH, int OW, int OT, int OC)
{
    Channel Ch(H, W, T, C); //intialize input
    input = Ch.list_input;
    input_height = H;
    input_weight = W;
    input_thickness = T;
    channel = C;
    
    Kernel K(FH, FW, FT, FC); // initialize kernel
    filter = K.kernel_matrix;
    filter_height = FH;
    filter_weight = FW;
    filter_thickness = FT;
    filter_channel = FC;
    bias = K.bias;
    
    //out_height
    output_height = OH;
    //out_weight
    output_weight = OW;
    //out_thickness
    output_thickness = OT;
    //out_channel
    output_channel = OC;
    
    padding = (stride*(input_height - 1) + filter_height - input_height) / 2; // initialize padding
}

void Layer::zero_padding()
{
    vector<vector<vector<double> > > temp(input_thickness+2*padding, vector<vector<double>>(input_height+2*padding, vector<double>(input_weight+2*padding, 0)));
    for(unsigned int m=0; m < channel; m++)
    {
        for(unsigned int i=padding; i < input_thickness+padding; i++)
        {
            for(unsigned int j=padding; j < input_height+padding; j++)
            {
                for(unsigned int k=padding; k < input_weight+padding; k++)
                {
                    temp[i][j][k] = input[m][i-padding][j-padding][k-padding];
                }
            }
        }
        input_ap.push_back(temp);
    }
}

void Layer::show()
{
    cout << "INPUT" << endl;
    for(unsigned int m=0; m < channel; m++)
    {
    for(unsigned int i=0; i < input_thickness; i++)
        {
        for(unsigned int j=0; j < input_height; j++)
        {
            for(unsigned int k=0; k < input_weight; k++)
            {
            cout << input[m][i][j][k] << " ";
            }
            cout << "\n";
        }
        
        }
        cout << "\n";
    }
    cout << endl << endl;
    cout << "FILTER" << endl;
    for(unsigned int i=0; i < filter_channel; i++)
    {
        for(unsigned int j=0; j < filter_thickness; j++)
        {
            for(unsigned int k=0; k < filter_height; k++)
            {
                for(unsigned int m=0; m < filter_weight; m++)
                {
                    cout << filter[i][j][k][m] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
    cout << endl << endl;
    cout << "OUTPUT" << endl;
    for(unsigned int m=0; m < output_channel; m++)
    {
        for(unsigned int i=0; i < output[0].size(); i++)
        {
            for(unsigned int j=0; j < output[0][0].size(); j++)
            {
                 for(unsigned int k=0; k < output[0][0][0].size(); k++)
                {
                     cout << output[m][i][j][k] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    cout << output_channel << " " << output[0].size() << " " << output[0][0].size() << " " << output[0][0][0].size();
    cout << endl << endl;
    cout << "OUTPUT_MAX" << endl;
    for(unsigned int m=0; m < output_max.size(); m++)
    {
        for(unsigned int i=0; i < output_max[0].size(); i++)
        {
            for(unsigned int j=0; j < output_max[0][0].size(); j++)
            {
                 for(unsigned int k=0; k < output_max[0][0][0].size(); k++)
                {
                     cout << output_max[m][i][j][k] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
        cout << "\n";
    }
    cout << output_max.size() << " " << output_max[0].size() << " " << output_max[0][0].size() << " " << output_max[0][0][0].size();
}

void Layer::conv()
{
    zero_padding();
    vector<vector<vector<double> > > temp(input_thickness, vector<vector<double>>(input_height, vector<double>(input_weight, 0)));
    
    for(unsigned int m=0; m < output_channel; m++)
    {
        for(unsigned int n=0; n < input_thickness; n++)
        {
            for(unsigned int i=0; i < input_height; i++)
            {
                for(unsigned int j=0; j < input_weight; j++)
                {
                    vector<vector<vector<double> > > temp_1(filter_thickness, vector<vector<double>>(filter_height, vector<double>(filter_weight, 0)));
                    
                    for(unsigned int z=0; z < channel; z++)
                    {
                        for(unsigned int k=0; k < filter_thickness; k++)
                        {
                            for(unsigned int p=0; p < filter_height; p++)
                            {
                                for(unsigned int q=0; q < filter_weight; q++)
                                {
                                    temp_1[k][p][q] = input_ap[z][n+k][i+p][j+q];
                                }
                            }
                        }
                        temp[n][i][j] += matrix_mul(temp_1, filter[m]);
                    }
                    temp[n][i][j] += bias[m];
                }
            }
        }
        output.push_back(temp);
    }
    LReLU();
}

double Layer::matrix_mul(vector<vector<vector<double> > > x, vector<vector<vector<double> > > y)
{
    double num = 0.0;
    for (unsigned int i = 0; i < x.size(); ++i)
    {
        for (unsigned int j = 0; j < x[0].size(); ++j)
        {
            for (unsigned int k = 0; k < x[0][0].size(); ++k)
            {
                num += (x[i][j][k] * y[i][j][k]);
            }
        }
    }
    return num;
}

void Layer::LReLU()
{
    for(unsigned int i=0; i < output_channel; i++)
    {
        for(unsigned int j=0; j < output_thickness; j++)
        {
            for(unsigned int k=0; k < output_height; k++)
            {
                for(unsigned int m=0; m < output_weight; m++)
                {
                    if(output[i][j][k][m] < 0)
                    {
                        output[i][j][k][m] *= 0.01;
                    }
                }
            }
        }
    }
}

void Layer::MaxPool()
{
    vector<vector<vector<vector<double> > > > temp(output_channel, vector<vector<vector<double> > > (output_thickness, vector<vector<double>>(output_height, vector<double>(output_weight, 0))));
    for(unsigned int m=0; m < output_channel; m++)
    {
        for(unsigned int n=0; n < input_thickness; n+=max_filter)
        {
            for(unsigned int i=0; i < input_height; i+=max_filter)
            {
                for(unsigned int j=0; j < input_weight; j+=max_filter)
                {
                    double max_num = output[m][n][i][j];
                        for(unsigned int k=0; k < max_filter; k++)
                        {
                            for(unsigned int p=0; p < max_filter; p++)
                            {
                                for(unsigned int q=0; q < max_filter; q++)
                                {
                                    if (max_num < output[m][n+k][i+p][j+q])
                                    {
                                        max_num = output[m][n+k][i+p][j+q];
                                    }
                                }
                            }
                        }
                    temp[m][n/max_filter][i/max_filter][j/max_filter] = max_num;
                }
            }
        }
    }
    output_max = temp;
}
//
//vector<vector<vector<double> > > Layer::clear(vector<vector<vector<double> > > x)
//{
//    for (unsigned int i = 0; i < x.size(); ++i)
//    {
//        for (unsigned int j = 0; j < x[0].size(); ++j)
//        {
//            for (unsigned int k = 0; k < x[0][0].size(); ++k)
//            {
//                x[i][j][k] = 0;
//            }
//        }
//    }
//    return x;
//}
