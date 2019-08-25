/*
 * Library to find the systolic/diastolic pressures of the closest pulse in a 
 * vector based on a point selected by the user.
 * @autor Wariston Pereira <waristonnfernando@gmail.com>
 */
#include "include/bp-monitor.h"
#include <vector>

/**
 * Detect the valley from waveform array at user selected point 
 * or peak point
 * @param array containing entire waveform
 * @param size of the buffer
 * @param point index selected by user
 * @return 0 if not found or valley point index
 */
int bPressureMonitor::valleyDetector(int* buffer, int size, int index) {
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
 * Detect the all peaks in waveform and calculation the distance
 *
 * @param array containing entire waveform
 * @param size of the buffer
 * @param point index selected by user
 * @param vector of struct points by ref
 * @return void
 */
void bPressureMonitor::peakDetector(
    int* buffer,
    int size,
    int index,
    std::vector<point> &peaks) {
  int last = index;
  bool next = false;
  for (int i = index; i <= size; i++) {
    if (buffer[i] > buffer[last] || next == true) {
      last = i;
      next = false;
    }
    if (buffer[i] >= buffer[i-1] &&  buffer[i] > buffer[i+1]) {
      int v = this->valleyDetector(buffer, size, last);
      if (v != last) {
        point p = {last, v, last-v};
        peaks.push_back(p);
      }
      next = true;
    }
  }
}

/**
 * Return measure result from waveform array at user selected point
 *
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

  result = {0, 0, 0, 0};
  std::vector <point> peaks;

  // Prevent out of range
  if (index > size || index <= 0 || size == 0 || index == size)
    return (ERR_INVALIDARGS);

  // Find all peaks on buffer and put inside vector
  this->peakDetector(buffer, size, 1, peaks);
  // Search on peak vector the index target
  for (unsigned int i=0; i < peaks.size(); i++) {
    // Check if index is between range peak-valley and is the high peak
    if (index-1 >= peaks[i].valley &&
        index-1 <= peaks[i].peak &&
        peaks[i].distance > peaks[i+1].distance) {
      result.dbpIndex = peaks[i].valley + 1;
      result.dbp = buffer[peaks[i].valley];
      result.sbpIndex = peaks[i].peak + 1;
      result.sbp = buffer[peaks[i].peak];
      return 0;
    }
  }
  // Error on measure?
  if ( result.dbp > result.sbp || result.dbp == result.sbp)
    return (ERR_INVALIDRESULT);

  // Return with no errors
  return 0;
}
