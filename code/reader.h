#ifndef READER_H_
#define READER_H_
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <conio.h>
#include <vector>
#include<cmath>
#include<algorithm>

class Reader
{
    private:
        std:: string eda_file_name_;
	    std:: string emg_file_name_;

        std:: vector<float> eda_values_;
        std:: vector<int> eda_times_;
        std:: vector<float> emg_values_;
        std:: vector<int> emg_times_;

        std:: ifstream data_file_;
    public:
        Reader();
        explicit Reader(const char *eda_name, const char *emg_name);
        ~Reader();
        void save_to_csv(const char *name);
};
#endif