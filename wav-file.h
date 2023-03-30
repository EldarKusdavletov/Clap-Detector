#ifndef WAV_FILE_HH
#define WAV_FILE_HH

#include <string>

using namespace std;

// returns the number of samples in the given .wav file
size_t wav_file_length(std::string filename);

// returns the number of samples per second in the given .wav file
unsigned long wav_file_sampling_rate(std::string filename);

// fills up the given array with sample data from the given .wav file
void wav_file_data(string filename, short*, size_t offset, size_t len);

#endif
