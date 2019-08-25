/*
 * Library to find the systolic/diastolic pressures on the closest pulse in a 
 * vector based on a point selected by the user.
 * @autor Wariston Pereira <waristonnfernando@gmail.com>
 */
#include "include/bp-monitor.h"
#include <math.h>
#include <vector>
#include <string>

#ifdef _DEBUG
  #include <iostream>
  #define DEBUG_MSG(str) std::cout << str << std::endl
#else
  #define DEBUG_MSG(str)
#endif

/**
 * Detect the trough from waveform array from peak point
 * @param array containing entire waveform
 * @param size of the buffer
 * @param peak point index
 * @return 0 if not found or trough point index
 */
int bPressureMonitor::troughDetector(int* buffer, int size, int index) {
  int last = index;
  for (int i = index; i >= 0; i--) {
    if ( buffer[i] < buffer[last])
      last = i;
    if ( buffer[i] <= buffer[i-1] &&  buffer[i] > buffer[i+1] ) {
      return last;
    }
  }
  return 0;
}

/**
 * Detect the all peaks in the waveform and the calculate the distance
 *
 * @param array containing entire waveform
 * @param size of the buffer
 * @param vector of struct points by ref
 * @return void
 */
void bPressureMonitor::peakDetector(
    int* buffer,
    int size,
    std::vector<point> &peaks) {
  int last = 0;
  bool next = false;
  peaks.clear();
  for (int i = 0; i < size; i++) {
    if (buffer[i] > buffer[last] || next == true) {
      last = i;
      next = false;
    }
    if (buffer[i] >= buffer[i-1] &&  buffer[i] > buffer[i+1]) {
      int v = this->troughDetector(buffer, size, last);
      int distance = last-v;
      if (v != last && distance != 0) {
        point p = {v, last, distance};
        peaks.push_back(p);
        DEBUG_MSG(std::to_string(v) +
            "\t->\t" +
            std::to_string(last) + "\tDistance: \t" +
            std::to_string(distance));
      }
      next = true;
    }
  }
}

/**
 * Return estimated heart rate based on sample rate
 * based on two waves and frequency
 *
 * @param sample rate em HZ
 * @param peak index
 * @param vector of peek points
 * @return BPM estimative
 */
int bPressureMonitor::estimateHr(
    int sampleRate,
    int index,
    std::vector<point> &peaks) {
  return round((sampleRate / (peaks[index+1].peak - peaks[index].peak)) * 60);
}

/**
 * Return measure results from a waveform array 
 * based on user selected point
 * @param array containing entire waveform
 * @param size of the buffer
 * @param point index selected by user
 * @param struct bPressure by ref
 * @return 0 if sucess or error number
 */
int bPressureMonitor::measure(
    int* buffer,
    int size,
    int index,
    bPressure &result) {

  result = {0, 0, 0, 0, 0};
  std::vector <point> peaks;

  // Prevent out of range
  if (index > size || index <= 0 || size == 0 || index == size)
    return (ERR_INVALIDARGS);

  // Find all peaks on buffer and put inside vector
  this->peakDetector(buffer, size, peaks);
  // Search on peak vector the index target
  for (unsigned int i=0; i < peaks.size(); i++) {
    // Check if the index is between range peak-trough and is the highest peak
    if (index-1 >= peaks[i].trough &&
        index-1 <= peaks[i].peak &&
        peaks[i].distance >= peaks[i+1].distance) {
      result.dbpIndex = peaks[i].trough + 1;
      result.dbp = buffer[peaks[i].trough];
      result.sbpIndex = peaks[i].peak + 1;
      result.sbp = buffer[peaks[i].peak];
      if ( i < peaks.size() )
        result.hr = this->estimateHr(125, i, peaks);
      return 0;
    }
  }
  // Error on measure?
  if ( result.dbp > result.sbp || result.dbp == result.sbp)
    return (ERR_INVALIDRESULT);

  // Return with no errors
  return 0;
}
