//
//  not important.h
//  net_modift
//
//  Created by 康捷 on 2019/12/18.
//  Copyright © 2019 康捷. All rights reserved.
//

#ifndef not_important_h
#define not_important_h


#endif /* not_important_h */
//void training::create_library(stringVector dataFolder)
//{
//    totalSamples_ = 0;
//    // Calculating number of samples available
//    dataFolder_ = dataFolder;
//    numClasses_ = dataFolder_.size();
//    cout << numClasses_<<endl;
//    for(unsigned i=0; i < numClasses_; i++){
//        stringVector temp;
//        read_directory(dataFolder_.at(i), temp);  // Get all file/sample names in folder i and save them in temp
//        fileNames_.push_back(temp);  // Add vector of file names (stringVec) to vector of stringVecs
//        totalSamples_ += fileNames_.back().size();
//    }
//    cout << totalSamples_<<endl;
//
//    maxTrainingSize_ = unsigned(ceil(float(totalSamples_ * 0.6)));  // Maximum training size is 60% of all samples available (40% remain for validation and testing)
//    cout << maxTrainingSize_<<endl;
//    // Minimum training size is equal to number of folders specified (determines the number of possible outputs)
//    maxValidateSize_ = unsigned(floor(totalSamples_*0.2));  // Number of validation samples will be max 20 % of total samples (ceil removed)
//
//}
//int main()
//{
//    bool enter = true;
//    int batch_size;
//    vector<unsigned int> hidden;
//    while(enter)
//    {
//        int neuron;
//        cout << "Please enter the number of neurons if each hidden layer: ";
//        cin >>neuron;
//        if(neuron == -1)
//        {
//            break;
//        }
//        hidden.push_back(neuron);
//    }
//    cout << "Please enter the batch size: ";
//    cin >> batch_size;
//
//    Net N(2, hidden, 2, "lrelu", false); //initialize net
//
//    for(int i=0; i < 10000; i++) //run 10000 times
//    {
//        vector<vector<double> > input(batch_size, vector<double>(2, 0)); //input
//        vector<vector<double> > target(batch_size, vector<double>(2, 0)); //target
//        input = rand(input);
//        for(int i=0; i<batch_size;i++)
//            {
//
//                if(input[i][0] != input[i][1])
//                {
//                    target[i][0] = 1;
//
//                }
//                else{
//                        target[i][1] = 1;
//                    }
//
//                }
//
//        N.gradient(input, target);
////        N.show();
//        N.weight_update();
//        N.bias_update();
////        cout << "diff = " << N.net_loss_<< endl;
//        cout << "acc = " << N.accuracy()<< endl;
//    }
//    cout << "Validation" << endl;
//    //create data to verify our net
//    vector<vector<double> > input_1(50, vector<double>(2, 0));
//        vector<vector<double> > target_1(50, vector<double>(2, 0));
//        input_1 = rand(input_1);
//        for(unsigned int i=0; i<50;i++)
//            {
//
//                if(input_1[i][0] != input_1[i][1])
//                {
//                    target_1[i][0] = 1;
//
//                }
//                else{
//                        target_1[i][1] = 1;
//                    }
//
//                }
////    N.loss(input_1, target_1);
////    cout << "diff = " << N.net_loss_<< endl;
//
//    cout << "acc = " << N.accuracy()<< endl;
//    return 0;
//}


