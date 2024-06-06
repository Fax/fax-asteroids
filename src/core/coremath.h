#pragma once
#include "raylib.h"
#include "raymath.h"

Vector2 Vector2Backward(Vector2 vector){
    return Vector2Rotate(vector, 180 * DEG2RAD);
}
