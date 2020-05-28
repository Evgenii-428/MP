#ifndef VECTOR
#define VECTOR

#include <cmath>
using namespace std;

class Vec3 {
    double X;
    double Y;
    double Z;
public:
    Vec3(double x, double y, double z) : X(x), Y(y), Z(z) {}
    Vec3 operator +(const Vec3& vec) const {
        return Vec3(X + vec.X, Y + vec.Y, Z + vec.Z);
    }
    Vec3 operator -(const Vec3& vec) const {
        return Vec3(X - vec.X, Y - vec.Y, Z - vec.Z);
    }
    Vec3 operator *(double scalar) const {
        return Vec3(scalar * X, scalar * Y, scalar * Z);
    }
    double dot(const Vec3& vec) {
        return X * vec.X + Y * vec.Y + Z * vec.Z;
    }
    double norm() {
        return sqrt(dot(*this));
    }
    Vec3 normalize() {
        return (*this) * (1 / norm());
    }
};
#endif