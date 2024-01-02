//
//  training.hpp
//  net_matrix
//
//  Created by 康捷 on 2019/12/17.
//  Copyright © 2019 康捷. All rights reserved.
//

#ifndef training_h
#define training_h

#include <stdio.h>

#endif /* training_hpp */
//cout << "weight" << endl;
//for(int i=0; i<N.layers_.size();i++)
//{
//    for(int j=0; j<N.layers_[i].weight_.size();j++)
//    {
//        cout << "[";
//        for(int k=0; k< N.layers_[i].weight_[0].size();k++)
//        {
//            cout << N.layers_[i].weight_[j][k] << ",";
//        }
//        cout <<"],\n";
//    }
//    cout << endl;
//}
//
//cout << "bias" << endl;
//for(int i=0; i<N.layers_.size();i++)
//{
//    for(int j=0; j<N.layers_[i].bias_.size();j++)
//    {
//        cout << N.layers_[i].bias_[j] << ",";
//    }
//    cout << endl;
//}
//
//cout << "x_act_" << endl;
//for(int i=0; i<N.layers_.size();i++)
//{
//    for(int j=0; j<N.layers_[i].x_act_.size();j++)
//    {
//        cout << "[";
//        for(int k=0; k< N.layers_[i].x_act_[0].size();k++)
//        {
//            cout << N.layers_[i].x_act_[j][k] << ",";
//        }
//        cout <<"],\n";
//    }
//    cout << endl;
//}
//cout << "dweight_" << endl;
//for(int i=0; i<N.grads_weight.size();i++)
//{
//    for(int j=0; j<N.grads_weight[i].size();j++)
//    {
//        cout << "[";
//        for(int k=0; k< N.grads_weight[i][j].size();k++)
//        {
//            cout << N.grads_weight[i][j][k] << ",";
//        }
//        cout <<"],\n";
//    }
//    cout << endl;
//}
//cout << "dbias" << endl;
//for(int i=0; i<N.grads_bias.size();i++)
//{
//    cout << "[";
//    for(int j=0; j<N.grads_bias[i].size();j++)
//    {
//
//        cout << N.grads_bias[i][j] << ",";
//    }
//    cout <<"],\n";
//
//}
//
//        cout << "input" << endl;
//        for(int i=0; i<input.size();i++)
//            {
//                for(int j=0; j<input[0].size();j++)
//                {
//                    cout << input[i][j] << ",";
//                }
//                cout << endl;
//            }
//        cout << "target" << endl;
//        for(int i=0; i<target.size();i++)
//        {
//            for(int j=0; j<target[0].size();j++)
//            {
//                cout << target[i][j] << ",";
//            }
//            cout << endl;
////        }
//srand((int)time(0));
//    vector<int> hidden = {128, 64};
//    vector<double> bias = {3, -10, 2, -5};
//    vector<vector<double> > input = {{1, 0, 0, 0},
//                         {0.3, 0.4, 0.1, 0.2}};
//    vector<vector<double> > target = {{1, 0, 0},
//                                      {0, 1, 0}};
//    int iSecret;
//
//    /* initialize random seed: */
//    srand (time(NULL));
//
//    /* generate secret number between 1 and 10: */
//    iSecret = rand() % 2;
    
//        cout << "input" << endl;
//                for(int i=0; i<input.size();i++)
//                    {
//                        for(int j=0; j<input[0].size();j++)
//                        {
//                            cout << input[i][j] << ",";
//                        }
//                        cout << endl;
//                    }
//                cout << "target" << endl;
//                for(int i=0; i<target.size();i++)
//                {
//                    for(int j=0; j<target[0].size();j++)
//                    {
//                        cout << target[i][j] << ",";
//                    }
//                    cout << endl;
//                }


//            cout << "weight" << endl;
//            for(int i=0; i<N.layers_.size();i++)
//            {
//                for(int j=0; j<N.layers_[i].weight_.size();j++)
//                {
//                    cout << "[";
//                    for(int k=0; k< N.layers_[i].weight_[0].size();k++)
//                    {
//                        cout << N.layers_[i].weight_[j][k] << ",";
//                    }
//                    cout <<"],\n";
//                }
//                cout << endl;
//            }
//        cout << "x_act_" << endl;
//        for(int i=0; i<N.layers_.size();i++)
//        {
//            for(int j=0; j<N.layers_[i].x_act_.size();j++)
//            {
//                cout << "[";
//                for(int k=0; k< N.layers_[i].x_act_[0].size();k++)
//                {
//                    cout << N.layers_[i].x_act_[j][k] << ",";
//                }
//                cout <<"],\n";
//            }
//            cout << endl;
//        }
//        
//    }
//    cout << "weight" << endl;
//    for(int i=0; i<N.layers_.size();i++)
//    {
//        for(int j=0; j<N.layers_[i].weight_.size();j++)
//        {
//            cout << "[";
//            for(int k=0; k< N.layers_[i].weight_[0].size();k++)
//            {
//                cout << N.layers_[i].weight_[j][k] << ",";
//            }
//            cout <<"],\n";
//        }
//        cout << endl;
//    }
//
//    cout << "bias" << endl;
//    for(int i=0; i<N.layers_.size();i++)
//    {
//        for(int j=0; j<N.layers_[i].bias_.size();j++)
//        {
//            cout << N.layers_[i].bias_[j] << ",";
//        }
//        cout << endl;
//    }
//
//    cout << "x_act_" << endl;
//    for(int i=0; i<N.layers_.size();i++)
//    {
//        for(int j=0; j<N.layers_[i].x_act_.size();j++)
//        {
//            cout << "[";
//            for(int k=0; k< N.layers_[i].x_act_[0].size();k++)
//            {
//                cout << N.layers_[i].x_act_[j][k] << ",";
//            }
//            cout <<"],\n";
//        }
//        cout << endl;
//    }
//    cout << "diff" << endl;
//    for(int i=0; i<N.layers_.back().loss_.size();i++)
//    {
//        cout << N.layers_.back().loss_[i] << ",";
//        cout << endl;
//    }
//    cout << "dweight_" << endl;
//    for(int i=0; i<N.grads_weight.size();i++)
//    {
//        for(int j=0; j<N.grads_weight[i].size();j++)
//        {
//            cout << "[";
//            for(int k=0; k< N.grads_weight[i][j].size();k++)
//            {
//                cout << N.grads_weight[i][j][k] << ",";
//            }
//            cout <<"],\n";
//        }
//        cout << endl;
//    }
//    cout << "dbias" << endl;
//    for(int i=0; i<N.grads_bias.size();i++)
//    {
//        cout << "[";
//        for(int j=0; j<N.grads_bias[i].size();j++)
//        {
//
//            cout << N.grads_bias[i][j] << ",";
//        }
//        cout <<"],\n";
//
//    }
//
//
//vector<vector<double> > Layer::softmax(vector<vector<double> > x)
//{
////    cout << "softmax" << x << endl;
//    vector<vector<double> > temp(x.size(), vector<double>(x[0].size(), 0));
//
//    for(int i=0; i<x.size();i++)
//    {
//        double sum = 0.0;
//        for(int j=0; j<x[0].size();j++)
//        {
//            temp[i][j] = exp(x[i][j]);
//            sum += exp(x[i][j]);
//        }
//        for(int k=0; k<x[0].size();k++)
//        {
//            temp[i][k] /= sum;
//        }
//    }
//
//    return temp;
//}
//for(int i=0; i < 1000; i++)
//{
//    vector<vector<double> > input(100, vector<double>(2, 0));
//    vector<vector<double> > target(100, vector<double>(2, 0));
//    input = rand(input);
//    for(int i=0; i<100;i++)
//        {
//
//            if(input[i][0] != input[i][1])
//            {
//                target[i][0] = 1;
//
//            }
//            else{
//                target[i][1] = 1;
//            }
//
//        }
// vector<int> hidden = {3, 4};
//    cout << "Training the model ...\n";
//    Net N(2, hidden, 2, "lrelu", false);
//    for(int i=0; i < 1000; i++)
//    {
//        vector<vector<double> > input(100, vector<double>(2, 0));
//        vector<vector<double> > target(100, vector<double>(2, 0));
//        input = rand(input);
//        for(int i=0; i<100;i++)
//            {
//
//                if(input[i][0] != input[i][1])
//                {
//                    target[i][0] = 1;
//
//                }
//                else{
//                    target[i][1] = 1;
//                }
//
//            }
////        cout << "input" << endl;
////        for(int i=0; i<input.size();i++)
////            {
////            for(int j=0; j<input[0].size();j++)
////                {
////                cout << input[i][j] << ",";
////                }
////                    cout << endl;
////                        }
////                    cout << "target" << endl;
////                    for(int i=0; i<target.size();i++)
////                    {
////                        for(int j=0; j<target[0].size();j++)
////                        {
////                            cout << target[i][j] << ",";
////                        }
////                        cout << endl;
////                    }
//        N.gradient(input, target);
//        N.weight_update();
//        N.bias_update();
////        N.show();
//        cout << "diff= " << N.net_loss_<< endl;
//    }
