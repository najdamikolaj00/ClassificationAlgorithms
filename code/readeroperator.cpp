#include "reader.h"


Reader::Reader() // default constructor
{
    
}
Reader::Reader(const char *eda_name, const char *emg_name) // constructor 2
{
    const char *file_names[2] = {eda_name, emg_name};

    for (int i = 0; i < 2; i++)
    {

        data_file_.open(file_names[i], std::ios_base::app);
        if (!data_file_.is_open()) // if file somehow doesn't open properly then exit
        {
            exit(EXIT_FAILURE);
        }
        else
        {
            int count{0};
            std::string value;
            std::string time;

        while(getline(data_file_, time, ',') && getline(data_file_, value, '\n'))
            {
                if (count != 0 && i == 0)
                {
                    eda_times_.push_back(stoi(time));
                    eda_values_.push_back(stoi(value));
                }
                else if (count != 0 && i == 1)
                {
                    emg_times_.push_back(stoi(time));
                    emg_values_.push_back(stoi(value));
                }
                count++;
            }    
        }

        data_file_.close();
    }

}
Reader::~Reader() // destructor
{
    
}
void Reader::save_to_csv(const char *name)
{
    std:: ofstream outFile;
    outFile.open(name, std::ios_base::app);
    for (int i = 0; i < eda_values_.size(); i++)
    {
        outFile << eda_values_[i] << "," << emg_values_[i] << std::endl;
    }
    outFile.close();
}