# Filter Cascade Library

This library provides an implementation for digital filter cascades, supporting high-pass, low-pass, band-pass, and band-stop filters. It allows initializing, updating, and managing filter cascades for signal processing applications.

## Features

- **Filter Types**: High-pass, Low-pass, Band-pass, and Band-stop.
- **Filter Order**: Configurable up to a maximum order of 6.
- **Reset and Update**: Easily reset and update filter states for real-time processing.
- **Configurable Parameters**: Set filter type, order, center frequency, bandwidth, and sampling frequency.

## File Structure

- **`CascadeFilters.h`**: Contains the declarations of the filter cascade structures and functions.
- **`CascadeFilters.c`**: Contains the implementation of the filter cascade functions.

## Installation

Simply include the `CascadeFilters.h` and `CascadeFilters.c` files in your project and ensure they are part of your build system.

## Usage

### Initialization

To initialize a filter cascade, use `filterCascadeInitialise`:

```c
FilterCascade cascade;
filterCascadeInitialise(
    &cascade,
    FILTER_TYPE_BANDPASS,  // Filter type
    3,                    // Number of filters
    1000.0,               // Center frequency (Hz)
    200.0,                // Bandwidth (Hz)
    44100.0               // Sampling frequency (Hz)
);
```

### Updating the Filter

To process an input signal through the filter cascade:

```c
double output = filterCascadeUpdate(&cascade, input);
```

### Resetting the Filter

To reset the filter's internal states:

```c
filterCascadeReset(&cascade);
```

## API Reference

### Functions

### `void filterCascadeInitialise(FilterCascade* cascade, FilterType type, int numberOfFilters, double centerFrequency, double bandwidth, double sampleFrequency)`

Initializes a filter cascade.

- **Parameters**:
  - `cascade`: Pointer to a `FilterCascade` structure.
  - `type`: Type of the filter (e.g., `FILTER_TYPE_HIGHPASS`).
  - `numberOfFilters`: Number of cascaded filters.
  - `centerFrequency`: Center frequency in Hz.
  - `bandwidth`: Bandwidth in Hz.
  - `sampleFrequency`: Sampling frequency in Hz.

#### `double filterCascadeUpdate(FilterCascade* cascade, double input)`

Processes an input signal through the filter cascade and returns the filtered output.

- **Parameters**:
  - `cascade`: Pointer to the initialized `FilterCascade`.
  - `input`: Input signal value.

#### `void filterCascadeReset(FilterCascade* cascade)`

Resets the filter's internal states.

- **Parameters**:
  - `cascade`: Pointer to the `FilterCascade`.

## Constants

- `FILTER_ORDER_MAX`: Maximum supported filter order (6).


