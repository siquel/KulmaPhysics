#pragma once

#include "math_types.h"
#include "math_util.h"
namespace kphys {
    
    inline Vec2 vec2(float x, float y) {
        return Vec2{ x, y };
    }

    inline Vec2& operator+=(Vec2& a, const Vec2& b) {
        a.x += b.x;
        a.y += b.y;
        return a;
    }

    inline Vec2& operator-=(Vec2& a, const Vec2& b){
        a.x -= b.x;
        a.y -= b.y;
    }

    inline Vec2& operator*=(Vec2& a, const Vec2& b) {
        a.x *= b.x;
        a.y *= b.y;
        return a;
    }

    inline Vec2& operator*=(Vec2& a, float s) {
        a.x *= s;
        a.y *= s;
        return a;
    }

    inline Vec2 operator+(Vec2 a, const Vec2& b) {
        return a += b;
    }

    inline Vec2 operator-(Vec2 a, const Vec2& b) {
        return a -= b;
    }

    inline Vec2 operator-(const Vec2& a) {
        return Vec2{ -a.x, -a.y };
    }

    inline Vec2 operator*(Vec2 a, const Vec2& b){
        return a *= b;
    }

    inline Vec2 operator*(float s, Vec2 a) {
        return a *= s;
    }

    inline Vec2 operator*(Vec2 a, float s) {
        return a *= s;
    }

    inline bool operator==(const Vec2& a, const Vec2& b) {
        return fequal(a.x, b.x) && fequal(a.y, b.y);
    }

    inline float dot(const Vec2& a, const Vec2& b){
        return a.x * b.x + a.y * b.y;
    }

    inline float lengthSquared(const Vec2& a) {
        return dot(a, a);
    }

    inline float length(const Vec2& a) {
        return sqrtf(lengthSquared(a));
    }
    
    inline Vec2 normalize(Vec2& a) {
        float len = length(a);
        float inv = 1.f / len;
        a.x *= inv;
        a.y *= inv;
        return a;
    }

    inline float distance(const Vec2& a, const Vec2& b) {
        return length(b - a);
    }

    inline float angle(const Vec2& a, const Vec2& b) {
        return acos(dot(a, b) / (length(a) * length(b)));
    }

    inline float* toPointer(Vec2& a) {
        return &a.x;
    }

    inline const float* toPointer(const Vec2& a) {
        return &a.x;
    }

    inline Vec2 cross(const Vec2& v, float a) {
        return Vec2{a *v[1], -a * v[0] };
    }

    inline Vec2 cross(float a, const Vec2& v) {
        return Vec2{ a *v[1], -a * v[0] };
    }

    inline float cross(const Vec2& a, const Vec2& b) {
        return a[0] * b[1] - a[1] * b[0];
    }
}