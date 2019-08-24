/*
 * Library for...
 */
#include <bits/stdc++.h>
#include "bp-monitor.h"

using namespace std;

/**
 * Return measure result from waveform vector at user selected point
 *
 * @param vector containing entire waveform
 * @param size of the buffer
 * @param point index selected by user
 * @return BP struct result of measure
 */
BP BP_MONITOR::measure(int buffer[], int size, int index){
    
	BP result;

	// Prevent out of range
	if (index > size + 1 || index <= 0 )
		throw std::runtime_error("Invalid index");
	// Vector is empty ?
	if ( size == 0 )
		throw std::runtime_error("Invalid vector size");
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
	if ( result.DBP > result.SBP)
		throw std::runtime_error("Error on measure");
	// Return measure value 
    return result;
}

