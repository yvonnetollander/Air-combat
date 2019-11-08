#include <cmath>
#include <stdlib.h>
#include <Graphics.hpp>

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

template <typename T>
T rotate(const T& vec, float rad) {
    float sn = std::sin(rad);
    float cs = std::cos(rad);
    return T(vec.x * cs - vec.y * sn, vec.y * cs + vec.x * sn);
}

// Returns a random floating point number between 0 and 1
float randFloat() {
    float random = ((float) rand()) / (float) RAND_MAX;
}
