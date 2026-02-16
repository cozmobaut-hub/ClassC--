#ifndef COORDINATE_CONVERSION_H
#define COORDINATE_CONVERSION_H

void polar_to_cartesian(const double radius,
                        const double angle,
                        double* pX,
                        double* pY);

void cartesian_to_polar(const double x,
                        const double y,
                        double* pRadius,
                        double* pAngle);

#endif
