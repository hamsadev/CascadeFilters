#include "CascadeFilters.h"
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Helper functions to initialize coefficients
static double calculateHighPassCoefficient(int numberOfFilters, double cornerFrequency, double sampleFrequency) {
    cornerFrequency = cornerFrequency * sqrt(pow(2, 1.0 / numberOfFilters) - 1);
    return 1 / ((2 * M_PI * cornerFrequency * (1.0 / sampleFrequency)) + 1);
}

static double calculateLowPassCoefficient(int numberOfFilters, double cornerFrequency, double sampleFrequency) {
    double samplePeriod = 1.0 / sampleFrequency;
    cornerFrequency = cornerFrequency / sqrt(pow(2, 1.0 / numberOfFilters) - 1);
    return samplePeriod / ((1.0 / (2 * M_PI * cornerFrequency)) + samplePeriod);
}

// Initialize filter cascade
void filterCascadeInitialise(FilterCascade* cascade, FilterType type, int numberOfFilters, double centerFrequency, double bandwidth, double sampleFrequency) {
    cascade->type = type;
    cascade->numberOfFilters = numberOfFilters;

    // Calculate coefficients
    if (type == FILTER_TYPE_HIGHPASS) {
        cascade->highPassCoefficient = calculateHighPassCoefficient(numberOfFilters, centerFrequency, sampleFrequency);
    }
    else if (type == FILTER_TYPE_LOWPASS) {
        cascade->lowPassCoefficient = calculateLowPassCoefficient(numberOfFilters, centerFrequency, sampleFrequency);
    }
    else if (type == FILTER_TYPE_BANDPASS || type == FILTER_TYPE_BANDSTOP) {
        double lowCornerFrequency = centerFrequency - (bandwidth / 2.0);
        double highCornerFrequency = centerFrequency + (bandwidth / 2.0);
        cascade->highPassCoefficient = calculateHighPassCoefficient(numberOfFilters, lowCornerFrequency, sampleFrequency);
        cascade->lowPassCoefficient = calculateLowPassCoefficient(numberOfFilters, highCornerFrequency, sampleFrequency);
    }
}

// Update filter cascade
double filterCascadeUpdate(FilterCascade* cascade, double input) {
    double output = input;

    // High-pass filtering stage
    if (cascade->type == FILTER_TYPE_HIGHPASS || cascade->type == FILTER_TYPE_BANDPASS || cascade->type == FILTER_TYPE_BANDSTOP) {
        for (int i = 0; i < cascade->numberOfFilters; i++) {
            if (i > 0) {
                input = cascade->highPassOutputs[i - 1];
            }
            cascade->highPassOutputs[i] = cascade->highPassCoefficient * (cascade->highPassOutputs[i] + input - cascade->highPassInputs[i]);
            cascade->highPassInputs[i] = input;
        }
        output = cascade->highPassOutputs[cascade->numberOfFilters - 1];
        if (cascade->type == FILTER_TYPE_HIGHPASS) {
            return output;
        }
        input = output;
    }

    // Low-pass filtering stage
    if (cascade->type == FILTER_TYPE_LOWPASS || cascade->type == FILTER_TYPE_BANDPASS || cascade->type == FILTER_TYPE_BANDSTOP) {
        for (int i = 0; i < cascade->numberOfFilters; i++) {
            if (i > 0) {
                input = cascade->lowPassOutputs[i - 1];
            }
            cascade->lowPassOutputs[i] = cascade->lowPassOutputs[i] + ((input - cascade->lowPassOutputs[i]) * cascade->lowPassCoefficient);
            cascade->lowPassInputs[i] = input;
        }
        output = cascade->lowPassOutputs[cascade->numberOfFilters - 1];
    }

    return output;
}

// Reset filter cascade
void filterCascadeReset(FilterCascade* cascade) {
    if (cascade == NULL) {
        return;  // If cascade is NULL, do nothing
    }

    // Reset high-pass filter buffers
    if (cascade->highPassInputs != NULL) {
        for (int i = 0; i < cascade->numberOfFilters; i++) {
            cascade->highPassInputs[i] = 0.0;
        }
    }

    if (cascade->highPassOutputs != NULL) {
        for (int i = 0; i < cascade->numberOfFilters; i++) {
            cascade->highPassOutputs[i] = 0.0;
        }
    }

    // Reset low-pass filter buffers
    if (cascade->lowPassInputs != NULL) {
        for (int i = 0; i < cascade->numberOfFilters; i++) {
            cascade->lowPassInputs[i] = 0.0;
        }
    }

    if (cascade->lowPassOutputs != NULL) {
        for (int i = 0; i < cascade->numberOfFilters; i++) {
            cascade->lowPassOutputs[i] = 0.0;
        }
    }
}