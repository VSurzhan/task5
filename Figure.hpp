#ifndef Figure_hpp
#define Figure_hpp

#include <iostream>
#include "Vec3d.hpp"

class Figure {
protected:
    Vec3d _colour;
public:
    Figure(): _colour() {};
    Figure(const Vec3d& color): _colour(color) {};

    virtual double ray_intersect(const Vec3d&, const Vec3d&) const = 0;
    
    virtual Vec3d center() const = 0;

    Vec3d colour() const;
    void UpdateColour(const Vec3d&);

    virtual ~Figure(){};
};

class Sphere : public Figure {
private:
    Vec3d _center = {0.0, 0.0, 0.0};
    double _R = 1.0;
private:
    const double PI = 3.14159265358979323846;
public:
    Sphere() = default;
    Sphere(const Vec3d& c, double R, const Vec3d& colour): Figure(colour), _center(c), _R(R) {};
    Sphere(const Vec3d& c, double R): Figure(), _center(c), _R(R) {};

    double ray_intersect(const Vec3d&, const Vec3d&) const override;

    Vec3d center() const override;
};


class Tetrahedron : public Figure {
private:
    Vec3d _A = {0.0, 0.0, 0.0};
    Vec3d _B = {1.0, 0.0, 0.0};
    Vec3d _C = {0.0, 1.0, 0.0};
    Vec3d _D = {0.0, 0.0, 1.0};
private:
    double triangle_intersection(const Vec3d& orig, const Vec3d& dir, const Vec3d& v0, const Vec3d& v1, const Vec3d& v2) const {
        Vec3d e1 = v1 - v0;
        Vec3d e2 = v2 - v0;
        
        Vec3d pvec = cross(dir, e2);
        double det = e1*pvec;

        if (det < 1e-8 && det > -1e-8) {
            return 0;
        }

        double inv_det = 1 / det;
        Vec3d tvec = orig - v0;
        double u = (tvec*pvec) * inv_det;
        if (u < 0 || u > 1) {
            return 0;
        }

        Vec3d qvec = cross(tvec, e1);
        double v = (dir*qvec) * inv_det;
        if (v < 0 || u + v > 1) {
            return 0;
        }
        return (e2*qvec) * inv_det;
    }
public:
    Tetrahedron() = default;
    Tetrahedron(const Vec3d& A, const Vec3d& B, const Vec3d& C, const Vec3d& D, const Vec3d& colour): Figure(colour), _A(A), _B(B), _C(C), _D(D) {};
    Tetrahedron(const Vec3d& A, const Vec3d& B, const Vec3d& C, const Vec3d& D): Figure(), _A(A), _B(B), _C(C), _D(D) {};
    
    double ray_intersect(const Vec3d&, const Vec3d&) const override;

    Vec3d center() const override;
};

#endif
