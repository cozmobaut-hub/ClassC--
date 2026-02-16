#include "coordinate_conversion.h"
#include <cmath>

using namespace std;

// (r, theta) -> (x, y)
void polar_to_cartesian(const double radius,
                        const double angle,
                        double* pX,
                        double* pY)
{
    *pX = radius * cos(angle);
    *pY = radius * sin(angle);
}

// (x, y) -> (r, theta)
void cartesian_to_polar(const double x,
                        const double y,
                        double* pRadius,
                        double* pAngle)
{
    *pRadius = sqrt(x * x + y * y);
    *pAngle  = atan2(y, x);
}
