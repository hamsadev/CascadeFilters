#ifndef FILTERS_H
#define FILTERS_H

#include <stdint.h>
#include <stdbool.h>

#define FILTER_ORDER_MAX    6

typedef enum {
    FILTER_TYPE_HIGHPASS,
    FILTER_TYPE_LOWPASS,
    FILTER_TYPE_BANDPASS,
    FILTER_TYPE_BANDSTOP
} FilterType;

typedef struct {
    FilterType type;
    int numberOfFilters;
    double highPassInputs[FILTER_ORDER_MAX];     // Inputs for high-pass filter
    double highPassOutputs[FILTER_ORDER_MAX];   // Outputs for high-pass filter
    double lowPassInputs[FILTER_ORDER_MAX];     // Inputs for low-pass filter
    double lowPassOutputs[FILTER_ORDER_MAX];    // Outputs for low-pass filter
    double highPassCoefficient;
    double lowPassCoefficient;
} FilterCascade;

// Filter functions
void filterCascadeInitialise(
    FilterCascade* cascade,
    FilterType type,
    int numberOfFilters,
    double centerFrequency,
    double bandwidth,
    double sampleFrequency);
double filterCascadeUpdate(FilterCascade* cascade, double input);
void filterCascadeReset(FilterCascade* cascade);

#endif // FILTERS_H
