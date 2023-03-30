#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdint>

#include "wav-file.h"

using namespace std;

static void wav_file_header(string filename, unsigned char *header) {
    ifstream wav_file(filename, std::ios::binary);
    wav_file.read(reinterpret_cast<char *>(header), 44);
    if (wav_file.fail()) {
        cerr << "Couldn't read WAV file " << filename << endl;
        exit(1);
    }
}

static unsigned long ulong_from_little_endian(unsigned char const *x) {
    return x[0] | (x[1] << 8) | (x[2] << 16) | (x[3] << 24);
}
static signed short short_from_little_endian(unsigned char const *x) {
    if (x[1] & 0x80)    return -(x[0] | (~(x[1] + 1) << 8));
    else                return x[0] | (x[1] << 8);
}

size_t wav_file_length(string filename) {
    unsigned char header[44];
    wav_file_header(filename, header);
    return ulong_from_little_endian(&header[40]) / sizeof (int16_t);
}

unsigned long wav_file_sampling_rate(string filename) {
    unsigned char header[44];
    wav_file_header(filename, header);
    return ulong_from_little_endian(&header[24]);
}

void wav_file_data(string filename, short *data, size_t off, size_t len) {
    ifstream wav_file(filename, std::ios::binary);
    wav_file.ignore(44 + off * sizeof (int16_t));
    for (size_t i = 0; i < len; i++) {
        unsigned char sample[sizeof (int16_t)];
        wav_file.read(reinterpret_cast<char *>(sample), sizeof sample / sizeof *sample);
        data[i] = short_from_little_endian(sample);
    }
    if (wav_file.fail()) {
        cerr << "Error reading WAV data" << endl;
        exit(1);
    }
}
