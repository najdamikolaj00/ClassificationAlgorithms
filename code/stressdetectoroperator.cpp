#include "stressdetector.h"

StressDetector::StressDetector() // default constructor
{
    
}
StressDetector::StressDetector(const char *name) // constructor 2
{
    
    data_file_.open(name, std::ios_base::app);
    if (!data_file_.is_open()) // if file somehow doesn't open properly then exit
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        int count{0};
        std::string emg_values;
        std::string eda_values;

      while(getline(data_file_, eda_values, ',') && getline(data_file_, emg_values, '\n'))
        {
            if (count != 0)
            {
                eda_values_normalized_.push_back(stof(eda_values));
                emg_values_normalized_.push_back(stof(emg_values));
            }
            count++;
        }    
    }
    data_file_.close();
    trough_to_peak();
}
StressDetector::~StressDetector() // destructor
{
    
}
void StressDetector::trough_to_peak()
{
    std::vector<float> frame_1;
    std::vector<float> frame_2;

    std:: vector<float>::iterator max_value_frame_1;
    std:: vector<float>::iterator max_value_frame_2;

    float tmp{0};

    for (int j = 0; j < eda_values_normalized_.size(); j+=10)
    {
        for (int i = 0; i < 20; i++) 
        {
            if ((j + 40) < eda_values_normalized_.size())
            {
                frame_1.push_back(eda_values_normalized_[j + i]);
                frame_2.push_back(eda_values_normalized_[j + i + 20]);
            }
        }
        if (j % 10 == 0)
        {
            max_value_frame_1 = std::max_element(frame_1.begin(),frame_1.end());
            max_value_frame_2 = std::max_element(frame_2.begin(),frame_2.end());
            diff_frame_.push_back(max_value_frame_2[0] - max_value_frame_1[0]);
            frame_1.clear();
            frame_2.clear();
        }
    }
    for (int i = 0; i < diff_frame_.size(); i++)
    {
        if (diff_frame_[i] > 0.2) 
        {
            trough_to_peak_values_.push_back(diff_frame_[i]);
            trough_to_peak_indices_.push_back(i * 10);
        }
    }
}
void StressDetector::save_to_csv()
{
    std:: ofstream outFile;
    outFile.open("samples_after_stress_detection.csv", std::ios_base::app);
    int j{0};
    int x{0};
    while (j < trough_to_peak_values_.size())
    {
        for (int i = x; i < eda_values_normalized_.size(); i++)
        {
            if (i >= trough_to_peak_indices_[j] && i < trough_to_peak_indices_[j + 1] + 20)
            {
                outFile << eda_values_normalized_[i] << "stress" << std::endl;
                x++;
            }
            else if (i == trough_to_peak_indices_[j + 1] + 20)
            {
                outFile << eda_values_normalized_[i] << "calm" << std::endl;
                j++;
                x++;
                break;
            }
            else
            {
                outFile << eda_values_normalized_[i] << "calm" << std::endl;
                x++;
            } 
        
        }
    }
    outFile.close();

}
