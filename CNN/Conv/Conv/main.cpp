//
//  main.cpp
//  Conv
//
//  Created by 康捷 on 2020/1/15.
//  Copyright © 2020 康捷. All rights reserved.
//

#include <iostream>
#include "Layer.h"
int main(int argc, const char * argv[])
{
    Layer L(20, 20, 20, 28, 3 ,3 ,3, 32, 10, 10 , 10, 32);
//    vector<vector<vector<vector<double> > > > temp(2, vector<vector<vector<double> > > (2, vector<vector<double>>(2, vector<double>(2, 0))));
//    L.input = temp;
//    cout << L.input.size() << L.input[0].size() << L.input[0][0].size() << L.input[0][0][0].size() << endl;
//    Layer L(3, 3, 3, 1, 3, 3, 3, 1, 3, 3, 3, 1);
    L.conv();
    L.MaxPool();
    L.show();
    
    
    
//    Layer L_1(10, 10, 10, 32, 3 ,3 ,3, 64, 5, 5, 5, 64);
//    L_1.input = L.output_max;
//    L_1.conv();
//    L_1.MaxPool();
//    L_1.show();
    return 0;
}
