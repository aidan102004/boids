#pragma once

#include <cmath>

class vec2 {
public:
    float e[2];

    vec2() : e{0,0} {}

    vec2(float e0, float e1) : e{e0, e1} {}

    float x() const {
        return e[0];
    }
    float y() const {
        return e[1];
    }

    vec2& operator*=(float k) {
        e[0] *= k;
        e[1] *= k;
        return *this;
    }

    vec2& operator+=(const vec2& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        return *this;
    }

    vec2& operator/=(float k) {
        return *this *= 1/k;
    }

    float length_squared() const {
        return e[0]*e[0] + e[1]*e[1];
    }

    float len() const {
        return std::sqrt(length_squared());
    }

    vec2& normalise() {
        *this /= this->len();
        return *this;
    }

};

inline vec2 operator-(const vec2& v1, const vec2& v2) {
    return vec2{v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]};
}

inline vec2 operator+(const vec2& v1, const vec2& v2) {
    return vec2({v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]});
}

inline vec2 operator*(float k, const vec2& v1) {
    return vec2{v1.e[0] * k, v1.e[1] * k};
}

inline vec2 operator*(const vec2& v1, float k) {
    return vec2{v1.e[0] * k, v1.e[1] * k};
}


inline vec2 operator/(const vec2& v, float k) {
    return (1/k) * v;
}

inline float distance(const vec2& v1, const vec2& v2) {
    float dx = v1.e[0] - v2.e[0];
    float dy = v1.e[1] - v2.e[1];
    return std::sqrt(dx*dx + dy*dy);
}
