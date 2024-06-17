#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include "Body2D.h"
#include "DataStructs/Array1D.h"

bool IsCollisionCircle(Body2D *a, Body2D *b, void (*callback)(Body2D *, Body2D *));
void CollisionDetect(Array1D *nodeList, void (*callback)(Body2D *, Body2D *));
#endif // COLLISION_H
