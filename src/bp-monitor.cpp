/*
 * Library for...
 * @autor Wariston Pereira <waristonnfernando@gmail.com>
 */
#include <bits/stdc++.h>
#include "bp-monitor.h"

using namespace std;

/**
 * Return measure result from waveform array at user selected point
 *
 * @param array containing entire waveform
 * @param size of the buffer
 * @param point index selected by user
 * @return BP struct result of measure
 */
BP BP_MONITOR::measure(int buffer[], int size, int index){
    
	BP result;

	// Prevent out of range
	if (index > size + 1 || index <= 0 )
		throw std::out_of_range("Invalid index");
	// Vector is empty ?
	if ( size == 0 )
		throw std::out_of_range("Invalid vector size");
	// Find the max value after index point
	for (int i = index - 1; i < size; i++) { 
		if (buffer[i] >= result.SBP){
			result.SBP = buffer[i];
			result.SBPi = i + 1;
		} else {
			break;
		}
	}
	// Start value as selected index
	result.DBP=buffer[index - 1];
	// Find the min value before index point
	for (int i = index - 1; i >= 0; i--) {
		if (buffer[i] <= result.DBP){
			result.DBP = buffer[i];
			result.DBPi = i + 1;
		} else {
			break;
		}
	}
	// Error on measure?
	if ( result.DBP > result.SBP || result.DBP == result.SBP)
		throw std::runtime_error("Error on measure");
	// Return measure value 
    return result;
}

