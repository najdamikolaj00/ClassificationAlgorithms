#ifndef STRESSDETECTOR_H_
#define STRESSDETECTOR_H_
#include <fstream>
#include <iostream>
#include <cstring>
#include <conio.h>
#include <vector>
#include<cmath>
#include<algorithm>


class StressDetector
{
    private:
        std:: ifstream data_file_;
        std:: vector<float> eda_values_normalized_;
        std:: vector<float> emg_values_normalized_;

        std:: vector<float> diff_frame_;
        std:: vector<float> trough_to_peak_values_; 
        std:: vector<float> trough_to_peak_indices_;
    public:
        StressDetector();
        explicit StressDetector(const char *sample_name);
        ~StressDetector();
        void trough_to_peak();
        void save_to_csv();
        
};
#endif