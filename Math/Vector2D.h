#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

typedef struct point
{
    float x;
    float y;
} Vec2;

inline Vec2 plus(Vec2 A, Vec2 B){return (Vec2){ A.x + B.x, A.y + B.y };}

inline Vec2 minus(Vec2 A, Vec2 B){return (Vec2){ A.x - B.x, A.y - B.y };}

inline Vec2 star(Vec2 A, Vec2 B){return (Vec2){ A.x * B.x, A.y * B.y };}

inline Vec2 slash(Vec2 A, Vec2 B){return (Vec2){ A.x / B.x, A.y / B.y };}

inline void scale(Vec2* vec, float n){(*vec) = slash((*vec), (Vec2){n, n});}

inline float dot_product(Vec2 A, Vec2 B){return (A.x * B.x + A.y * B.y);}

inline float cross_product(Vec2 A, Vec2 B){return (A.x * B.y - A.y * B.x);}

inline float magnitude(Vec2 vec){return sqrtf(vec.x * vec.x + vec.y * vec.y);}

inline float distance(Vec2 A, Vec2 B){float x = (B.x - A.x);float y = (B.y - A.y);return sqrtf(x * x + y * y);}

inline Vec2 normalize(Vec2 vec){float len = magnitude(vec);return (Vec2) { vec.x / len, vec.y / len };}

inline bool equal(Vec2 A, Vec2 B) { return (A.x == B.x && A.y == B.y); }

#endif // VECTOR2D_H
