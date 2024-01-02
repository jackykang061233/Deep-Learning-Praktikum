//
//  main.cpp
//  net_matrix
//
//  Created by 康捷 on 2019/12/11.
//  Copyright © 2019 康捷. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <sstream>
#include <random>
#include <string>
#include <typeinfo>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>
#include "Net.h"
using namespace std;

typedef std::vector<std::string> stringvec;
void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}
void create_library(stringvec dataFolder)
{
    vector<stringvec> fileNames_;
    int totalSamples_ = 0;
    // Calculating number of samples available
    stringvec dataFolder_ = dataFolder;
    int numClasses_ = dataFolder_.size();
    cout << numClasses_<<endl;
    for(unsigned i=0; i < numClasses_; i++){
        stringvec temp;
        read_directory(dataFolder_.at(i), temp);  // Get all file/sample names in folder i and save them in temp
        fileNames_.push_back(temp);  // Add vector of file names (stringVec) to vector of stringVecs
        totalSamples_ += fileNames_.back().size();
    }
    cout << totalSamples_<<endl;

    double maxTrainingSize_ = unsigned(ceil(float(totalSamples_ * 0.6)));  // Maximum training size is 60% of all samples available (40% remain for validation and testing)
    cout << maxTrainingSize_<<endl;
    // Minimum training size is equal to number of folders specified (determines the number of possible outputs)
    double maxValidateSize_ = unsigned(floor(totalSamples_*0.2));  // Number of validation samples will be max 20 % of total samples (ceil removed)

}
vector<vector<double> > rand(vector<vector<double> > x)
{
    // INITIALIZES VECTOR OF DOUBLE VECTOR WITH RANDOM NUMBERS
    unsigned seed = unsigned(chrono::steady_clock::now().time_since_epoch().count());  // Seed based on current time.
    std::mt19937 mt(seed);  // Initialize random number generator "Mersenne twister" with seed of current time.
    std::uniform_int_distribution<double> dist(0,1);  // Filter random numbers by applying distribution.
    for(unsigned int i=0; i<x.size();i++)
    {
        for(unsigned int j=0; j<x[0].size();j++)
        {
//            double num =dist(mt);
            x[i][j] = dist(mt);
        }
    }
    return x;
}
int rand_1()
{
    int randindx = rand() % (3000);
    return randindx;
}

vector<vector<vector<double> > > create_data(double training_ratio)
{
    stringvec nqgp;
    read_directory("/Users/kangchieh/Desktop/dataset_half/nqgp", nqgp);
    stringvec qgp;
    read_directory("/Users/kangchieh/Desktop/dataset_half/qgp", qgp);
    string line;
    vector<string> line_v;

        cout << "Loading data ...\n";
        vector<double> X_train;
        vector<double> y_train;
        vector<vector<double> > X_train_1;
        vector<vector<double> > y_train_1;

        for(int i=0; i<300; i++) //60 procent
        {
            int v1 = rand() % 2;
            int v2 = rand() % 2498 +2;
            if (v1 ==0)
            {
                string a = "/Users/kangchieh/Desktop/dataset_half/nqgp/" + nqgp[v2];
                ifstream myfile (a);
                if (myfile.is_open())
                    {
                        while (getline (myfile,line))
                        {
                            for (unsigned i = 0; i < line.size(); i+=2) {
                                double d = (double)line[i] -48;
                                
                                X_train.push_back(d);
                            }
                        }
                        y_train.push_back(1); //target
                        y_train.push_back(0);
                        X_train_1.push_back(X_train);
                        y_train_1.push_back(y_train);
                        
                        myfile.close();
                    }
                else {cout << "Unable to open file" << '\n';}

            }
            else{
                string b = "/Users/kangchieh/Desktop/dataset_half/nqgp/" + qgp[v2];
                ifstream myfile (b);
                if (myfile.is_open())
                    {
                        while ( getline (myfile,line) )
                        {
                            for (unsigned i = 0; i < line.size(); i+=2) {
                                double d = (double)line[i] -48;
                                
                                X_train.push_back(d);
                            }
                        }
                        y_train.push_back(0); //target
                        y_train.push_back(1);
                        X_train_1.push_back(X_train);
                        y_train_1.push_back(y_train);

                        myfile.close();
                    }
                else {cout << "Unable to open file" << '\n';}

            }

            X_train.clear();
            y_train.clear();

    }
    
}
int main() {
    
//    Random initialization of the weights
    bool enter = true;
    int batch_size;
    int epoch;
    vector<unsigned int> hidden;
    while(enter)
    {
        int neuron;
        cout << "Please enter the number of neurons if each hidden layer: ";
        cin >>neuron;
        if(neuron == -1)
        {
            break;
        }
        hidden.push_back(neuron);
    }
    cout << "Please enter the batch size: ";
    cin >> batch_size;
    cout << "Please enter the epoch size: ";
    cin >> epoch;
   Net N(224000, hidden, 2, "lrelu", false);

    for (unsigned i = 0; i < epoch; ++i) {
        vector<vector<double> > b_X;
        vector<vector<double> > b_y;
        // Building batches of input variables (X) and labels (y)

        for (unsigned j = 0; j < batch_size; ++j){

            int a = rand_1();
            b_X.push_back(X_train_1[a]);
            b_y.push_back(y_train_1[a]);

        }
        N.gradient(b_X, b_y);
//        N.show();
        N.weight_update();
        N.bias_update();
//        cout <<i+1<< ", diff= " << N.net_loss_<< endl;
        cout << "acc = " << N.accuracy()<< endl;
    }
    cout << "Validation" << endl;
    //create data to verify our net
    vector<vector<double> > v_X;
    vector<vector<double> > v_y;
    
    for (unsigned j = 0; j < batch_size; ++j){
        int a = rand_1();
        v_X.push_back(X_train_1[a]);
        v_y.push_back(y_train_1[a]);

        }
    N.loss(v_X, v_y);
    cout << "diff = " << N.net_loss_<< endl;
    cout << "acc = " << N.accuracy()<< endl;
    return 0;
}
//       cout << "input" << endl;
//                for(int i=0; i<b_X.size();i++)
//                    {
//                        for(int j=0; j<b_X[0].size();j++)
//                        {
//                            cout << b_X[i][j] << ",";
//                        }
//                        cout << endl;
//                    }
//        cout << "x_act_" << endl;
//        for(int i=0; i<layers_.size();i++)
//        {
//            for(int j=0; j<layers_[i].x_act_.size();j++)
//            {
//                cout << "[";
//                for(int k=0; k< layers_[i].x_act_[0].size();k++)
//                {
//                    cout << layers_[i].x_act_[j][k] << ",";
//                }
//                cout <<"],\n";
//            }
//            cout << endl;
//        }
//                cout << "target" << endl;
//                for(int i=0; i<b_y.size();i++)
//                {
//                    for(int j=0; j<b_y[0].size();j++)
//                    {
//                        cout <<"ex"<<N.layers_.back().y_[i][j]<<",";
//                        cout <<"target"<< b_y[i][j] << ",";
//                    }
//                    cout << endl;
//               }
//        if((i+1)%100 ==0)
//        {
//            N.show();
//            cout << "diff= " << N.net_loss_<< endl;
//        }
//    }
