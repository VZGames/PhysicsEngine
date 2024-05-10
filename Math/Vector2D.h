#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include "Transform2D.h"

typedef struct point
{
    float x;
    float y;
} Vec2;

inline Vec2 zero() { return (Vec2){0.0f, 0.0f}; }

inline Vec2 plus(Vec2 A, Vec2 B){return (Vec2){ A.x + B.x, A.y + B.y };}

inline Vec2 minus(Vec2 A, Vec2 B){return (Vec2){ A.x - B.x, A.y - B.y };}

inline Vec2 star(Vec2 A, Vec2 B){return (Vec2){ A.x * B.x, A.y * B.y };}

inline Vec2 slash(Vec2 A, Vec2 B){return (Vec2){ A.x / B.x, A.y / B.y };}

inline void scale(Vec2* vec, float n){(*vec) = slash((*vec), (Vec2){n, n});}

inline float dot_product(Vec2 A, Vec2 B){return (A.x * B.x + A.y * B.y);}

inline float cross_product(Vec2 A, Vec2 B){return (A.x * B.y - A.y * B.x);}

inline float magnitude(Vec2 vec){return sqrtf(vec.x * vec.x + vec.y * vec.y);}

inline float distance(Vec2 A, Vec2 B){ return sqrtf((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));}

inline Vec2 normalize(Vec2 vec){return (Vec2) { vec.x / magnitude(vec), vec.y / magnitude(vec) };}

inline bool equals(Vec2 A, Vec2 B) { return (A.x == B.x && A.y == B.y); }

inline Vec2 transform(Vec2 vec, Trans2D transform)
{
    /**
     * x2=cosβx1−sinβy1
     * y2=sinβx1+cosβy1
    `*/

    return (Vec2) {
        (transform.cos * vec.x - transform.sin * vec.y) + transform.x,
        (transform.sin * vec.x + transform.cos * vec.y) + transform.y
    };
}

#endif // VECTOR2D_H
