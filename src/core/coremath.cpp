#include "coremath.h"

Vector2 Vector2Backward(Vector2 vector)
{
    return Vector2Rotate(vector, 180 * DEG2RAD);
}

Vector2 RotateAroundPoint(Vector2 point, Vector2 pivot, float rotation)
{
    float radians = rotation * DEG2RAD; // Convert degrees to radians
    float cosAngle = cos(radians);
    float sinAngle = sin(radians);

    // Translate point to origin
    float translatedX = point.x - pivot.x;
    float translatedY = point.y - pivot.y;

    // Apply rotation
    float rotatedX = translatedX * cosAngle - translatedY * sinAngle;
    float rotatedY = translatedX * sinAngle + translatedY * cosAngle;

    // Translate point back
    Vector2 result;
    result.x = rotatedX + pivot.x;
    result.y = rotatedY + pivot.y;

    return result;
}