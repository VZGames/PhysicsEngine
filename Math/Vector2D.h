#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

typedef struct point
{
    float x;
    float y;
} Vec2;

Vec2 plus(Vec2 A, Vec2 B) // add
{
    return (Vec2){ A.x + B.x, A.y + B.y };
}

Vec2 minus(Vec2 A, Vec2 B) // subtract
{
    return (Vec2){ A.x - B.x, A.y - B.y };
}

Vec2 star(Vec2 A, Vec2 B) // multiply
{
    return (Vec2){ A.x * B.x, A.y * B.y };
}

Vec2 slash(Vec2 A, Vec2 B) // divide
{
    return (Vec2){ A.x / B.x, A.y / B.y };
}

void scale(Vec2* vec, float n)
{
    (*vec) = slash((*vec), (Vec2){n, n});
}

float dot_product(Vec2 A, Vec2 B) // scalar
{
    return (A.x * B.x + A.y * B.y);
}

float cross_product(Vec2 A, Vec2 B)
{
    return (A.x * B.y - A.y * B.x);
}

float magnitude(Vec2 vec)
{
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

float distance(Vec2 A, Vec2 B)
{
    float x = (B.x - A.x);
    float y = (B.y - A.y);
    return sqrtf(x * x + y * y);
}

Vec2 normalize(Vec2 vec)
{
    float len = magnitude(vec);
    return (Vec2) { vec.x / len, vec.y / len };
}

#endif // VECTOR2D_H
