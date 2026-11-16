#pragma once

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
};