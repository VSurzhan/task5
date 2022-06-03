#include "Figure.hpp"


Vec3d Figure::colour() const {
    return _colour;
};
void Figure::UpdateColour(const Vec3d& colour) {
    _colour = colour*(1/255.0);
};


double Sphere::ray_intersect(const Vec3d& orig, const Vec3d& dir) const {
    Vec3d L = orig - _center;

    double a = 1.0; // (dir; dir) = 1
    double b = 2*(dir*L);
    double c = (L*L) - _R*_R;
        
    double det = b*b-4*a*c;

    if(det > 0) {
        double t1 = (-b + sqrt(det)) / 2;
        double t2 = (-b - sqrt(det)) / 2;
        if(t1 > 0 && t2 > 0) {
            return std::min(t1, t2);
        }
    }
        
    return -1;
}
Vec3d Sphere::center() const {
    return _center;
}


double Tetrahedron::ray_intersect(const Vec3d& orig, const Vec3d& dir) const {
        double t1 = triangle_intersection(orig, dir, _A, _B, _C);
        double t2 = triangle_intersection(orig, dir, _A, _B, _D);
        double t3 = triangle_intersection(orig, dir, _D, _B, _C);
        double t4 = triangle_intersection(orig, dir, _A, _D, _C);

        double t_leave = std::max(t1, std::max(t2, std::max(t3, t4)));

        if(t_leave <= 0.0) return -1;

        double t_enter = -1.0;

        if(t1 != 0.0) t_enter = t1;
        if(t2 != 0.0) t_enter = std::min(t_enter, t2);
        if(t3 != 0.0) t_enter = std::min(t_enter, t3);
        if(t4 != 0.0) t_enter = std::min(t_enter, t4);

        return t_enter;
}
Vec3d Tetrahedron::center() const {
    double sumi[3] = {0.0, 0.0, 0.0};
    for(size_t i = 0; i < 3; ++i) {
        sumi[i] += (_A[i]+_B[i]+_C[i]+_D[i]);
    }
    return Vec3d(sumi[0]/4, sumi[1]/4, sumi[2]/4);
}
