#include "readeroperator.cpp"
#include "stressdetectoroperator.cpp"

int main() {

    Reader object_1("eda_samples.csv", "emg_samples.csv");
    object_1.save_to_csv("samplename.csv");

    StressDetector object_2("samplename.csv");
    object_2.save_to_csv();

    return 0;
}