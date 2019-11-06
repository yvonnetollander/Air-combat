#include <cmath>
#include <stdlib.h>

// Returns the length of a given vector
template <typename T>
float len(const T& vec) {
    return std::sqrt(T.x*T.x + T.y*T.y + T.z*T.z);
}

// Return a normalized version of a given vector
template <typename T>
T normalize(const T& vec) {
    return T / len(T);
}

// Returns a random floating point number between 0 and 1
float randFloat() {
    float random = ((float) rand()) / (float) RAND_MAX;
}

