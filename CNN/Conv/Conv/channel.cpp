//
//  channel.cpp
//  Conv
//
//  Created by 康捷 on 2020/1/15.
//  Copyright © 2020 康捷. All rights reserved.
//

#include "channel.h"
Channel::Channel(int H, int W, int T, int C)
{
    channel = C;
    input_height = H;
    input_weight = W;
    input_thickness = T;
    
    vector<vector<vector<double> > > temp(T, vector<vector<double>>(H, vector<double>(W, 0)));
    for(unsigned int m=0; m < channel; m++) //initialize
    {
        for(unsigned int i=0; i < T; i++)
        {
        
            for(unsigned int j=0; j < H; j++)
            {
                for(unsigned int k=0; k < W; k++)
                {
                    temp[i][j][k] = random_num();
                }
            }
        }
        list_input.push_back(temp);
    }
    
    
}

double Channel::random_num()
{
    unsigned seed = unsigned(chrono::steady_clock::now().time_since_epoch().count());  // Seed based on current time.
    std::mt19937 mt(seed);  // Initialize random number generator "Mersenne twister" with seed of current time.
    std::uniform_real_distribution<double> dist(-1,1);  // Filter random numbers by applying distribution.
    return dist(mt);
}

void Channel::get() //get the value
{
    for(unsigned int i=0; i < channel; i++)
    {
        for(unsigned int j=0; j < input_thickness; j++)
        {
            for(unsigned int k=0; k < input_height; k++)
            {
                for(unsigned int m=0; m < input_weight; m++)
                {
                    cout << list_input[i][j][k][m] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

//void Channel::set()
//{
//    while (true)
//    {
//        cin >> "Please enter the "
//    }
//}

void Channel::add(int num) // add a specific number
{
    for(unsigned int m=0; m < channel; m++)
    {
        for(unsigned int i=0; i < input_thickness; i++)
        {
        
            for(unsigned int j=0; j < input_height; j++)
            {
                for(unsigned int k=0; k < input_weight; k++)
                {
                    list_input[m][i][j][k] += num;
                }
            }
        }
    }
}


void Channel::clear() //reset
{
    for(unsigned int m=0; m < channel; m++)
    {
        for(unsigned int i=0; i < input_thickness; i++)
        {
        
            for(unsigned int j=0; j < input_height; j++)
            {
                for(unsigned int k=0; k < input_weight; k++)
                {
                    list_input[m][i][j][k] = random_num();
                }
            }
        }
    }
}

void Channel::LReLU()
{
    for(unsigned int i=0; i < channel; i++)
    {
        for(unsigned int j=0; j < input_thickness; j++)
        {
            for(unsigned int k=0; k < input_height; k++)
            {
                for(unsigned int m=0; m < input_weight; m++)
                {
                    if(list_input[i][j][k][m] < 0)
                    {
                        list_input[i][j][k][m] *= 0.01;
                    }
                }
            }
        }
    }
}
