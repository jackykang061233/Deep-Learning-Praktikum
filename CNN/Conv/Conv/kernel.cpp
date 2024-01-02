//
//  kernel.cpp
//  Conv
//
//  Created by 康捷 on 2020/1/15.
//  Copyright © 2020 康捷. All rights reserved.
//

#include "kernel.h"

Kernel::Kernel(int FH, int FW, int FT, int C)
{
    FH = FH ;
    FW = FW;
    FT = FT;
    Channel = C;
    
    vector<vector<vector<vector<double> > > > temp(C, vector<vector<vector<double> > >(FT, vector<vector<double> >(FH, vector<double>(FW, 0))));
    kernel_matrix = temp;
    for(unsigned int i=0; i < C; i++) //initialize
    {
        for(unsigned int j=0; j < FT; j++)
        {
            for(unsigned int k=0; k < FH; k++)
            {
                for(unsigned int m=0; m < FW; m++)
                {
                     kernel_matrix[i][j][k][m] = random_num();
                }
            }
        }
    }
    
    for(unsigned int i=0; i < C; i++) //initialize bias
    {
        bias.push_back(random_num());
    }
}

double Kernel::random_num()
{
    unsigned seed = unsigned(chrono::steady_clock::now().time_since_epoch().count());  // Seed based on current time.
    std::mt19937 mt(seed);  // Initialize random number generator "Mersenne twister" with seed of current time.
    std::uniform_real_distribution<double> dist(-1,1);  // Filter random numbers by applying distribution.
//    cout << dist(mt) << endl;
    return dist(mt);
}

void Kernel::show()
{
    for(unsigned int i=0; i < Channel; i++)
    {
        for(unsigned int j=0; j < FT; j++)
        {
            for(unsigned int k=0; k < FH; k++)
            {
                for(unsigned int m=0; m < FW; m++)
                {
                    cout << kernel_matrix[i][j][k][m] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

void Kernel::reset()
{
    for(unsigned int i=0; i < Channel; i++)
    {
        for(unsigned int j=0; j < FT; j++)
        {
            for(unsigned int k=0; k < FH; k++)
            {
                for(unsigned int m=0; m < FW; m++)
                {
                     kernel_matrix[i][j][k][m] = random_num();
                }
            }
        }
    }
}
