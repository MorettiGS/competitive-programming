template<typename T>
struct Point3D { T x, y, z; };

template<typename T>
struct Sphere {
    Point3D<T> C;
    T r;

    double area() const
    {
        return 4.0*PI*r*r;
    }

    double volume() const
    {
        return 4.0*PI*r*r*r/3.0;
    }
};

template<typename T>
struct Cylinder {
    T r, h;

    double area() const
    {
        return 2*PI*r*(r + h);
    }

    double volume() const
    {
        return PI*r*r*h;
    }
};

template<typename T>
struct Cube {
    T L;

    double face_diagonal() const
    {
        return L*sqrt(2.0);
    }

    double space_diagonal() const
    {
        return L*sqrt(3.0);
    }

    double area() const
    {
        return 6.0*L*L;
    }

    double volume() const
    {
        return L*L*L;
    }
};

template<typename T>
struct Cone {
    T r, H;

    double volume() const
    {
        return PI*r*r*H/3.0;
    }

    double area() const
    {
        return PI*r*r + PI*r*sqrt(r*r + H*H);
    }

    // Volume do tronco do cone
    double frustum(double rm, double h) const
    {
        return PI*h*(r*r + r*rm + rm*rm)/3.0;
    }
};

template<typename T>
struct Parallelepiped {
    Vector3D<T> u, v, w;

    double volume() const
    {
        return fabs(u.x*v.y*w.z + u.y*v.z*w.x + u.z*v.x*w.y 
                - (u.x*v.z*.wy + u.y*v.x*w.z + u.z*v.y*w.x);
    }

    double volume2() const
    {
        double a = u.lenght();
        double b = v.length();
        double c = w.length();

        double m = angle(u, v);
        double n = angle(u, w);
        double p = angle(v, w);

        return a*b*c*sqrt(1 + 2*cos(m)*cos(n)*cos(p)
            - cos(m)*cos(m) - cos(n)*cos(n) - cos(p)*cos(p));
    }
    
    double volume3() const
    {
        return fabs(dot_product(u, cross_product(v, w)));
    }

    double area() const
    {
        double uv = cross_product(u, v).length();
        double uw = cross_product(u, w).length();
        double vw = cross_product(v, w).length();

        return 2*(uv + uw + vw);
    }
};
