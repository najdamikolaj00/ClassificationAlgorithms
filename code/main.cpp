#include "readeroperator.cpp"


int main() {

    Reader object("eda_samples.csv", "emg_samples.csv");
    object.save_to_csv("samplename.csv");

    return 0;
}