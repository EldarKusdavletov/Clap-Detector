#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include "wav-file.h"
using namespace std;

double peak_amplitude(const short *cur_sample, size_t start, size_t length){
    /*
     *cur_sample     =  Pointer to array storing current second
     size_t start    =  First element of current millisecond
     size_t length   =  Length of current millisecond
    */
    
    double cur_peak = 0;
    
    for (size_t j = start; j < start + length; j ++)
        if (abs(cur_sample[j]) > cur_peak)
            cur_peak = abs(cur_sample[j]);
    // Compares every element of current millisecond with cur_peak, if greater replaces it
    
    cur_peak /= SHRT_MAX;
    // Transforms peak amplitude to the normalized peak amplitude
    
    return cur_peak;
    // Returns normalized peak amplitude in current millisecond (double type)
}

int main() {
    
    string inp_wav = "inp.wav";
    // Your .wav file path
    
    short cur_samples[wav_file_sampling_rate(inp_wav)];
    // Stores all samples for one second
    
    double prev_peak = 0, cur_peak;
    
    for (size_t cur_sec = 0; cur_sec < wav_file_length(inp_wav) / wav_file_sampling_rate(inp_wav); cur_sec ++){
        
        fill_n (cur_samples, wav_file_sampling_rate(inp_wav), 0);
        // Before rewriting cur_sample, we set all its elements to 0, because last 0.01 sec may not be full
        
        wav_file_data(inp_wav, cur_samples, cur_sec * wav_file_sampling_rate(inp_wav), wav_file_sampling_rate(inp_wav));
        // Writing in cur_sample all the values of current second
        
        
        for (size_t milisec = 0; milisec < 100; milisec ++){
            // Dividing 1 second into 100 milliseconds
            
            cur_peak = peak_amplitude(cur_samples, milisec * wav_file_sampling_rate(inp_wav) / 100, wav_file_sampling_rate(inp_wav) / 100);
            // In order not to call the same function several times, we will store its value in "cur_peak"
            
            if (cur_peak >= 0.03 && cur_peak >= prev_peak * 8)
                cout << setw(8) << fixed << setprecision(2) << cur_sec + double(milisec) / 100 << "\n" << flush;
            // Condition for clapping sound
            
            prev_peak = cur_peak;
            // Berore going to next millisecond, we set value of cur_peak to prev_peak
        }
        
    }
    
    return 0;
}
