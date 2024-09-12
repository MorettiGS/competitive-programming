template<typename T>
struct Triangle {
    Point<T> A, B, C;

    enum Angles { RIGHT, ACUTE, OBTUSE };
    enum Sides { EQUILATERAL, ISOSCELES, SCALENE };

    double perimeter() const
    {
        auto a = dist(A, B), b = dist(B, C), c = dist(C, A);

        return a + b + c;
    }

    double area() const
    {
        Line<T> r(A, B);

        auto b = dist(A, B);
        auto h = r.distance(C);
        
        return (b * h)/2;
    }

    double area2() const
    {
        auto a = dist(A, B);
        auto b = dist(B, C);
        auto c = dist(C, A);
        auto s = (a + b + c)/2
        return sqrt(s)*sqrt(s - a)*sqrt(s - b)*sqrt(s - c);
    }

    double area3() const
    {
        double det = (A.x*B.y + A.y*C.x + B.x*C.y) - (C.x*B.y + C.y*A.x + B.x*A.y);

        return 0.5 * fabs(det);
    }

    Point<T> barycenter() const
    {
        auto x = (A.x + B.x + C.x) / 3.0;
        auto y = (A.y + B.y + C.y) / 3.0;

        return Point<T> { x, y };
    }

    double inradius() const
    {
        return (2 * area()) / perimeter();
    }

    Point<double> incenter() const
    {
        auto a = dist(B, C), b = dist(A, C), c = dist(A, B);
        auto P = perimeter();
        auto x = (a*A.x + b*B.x + c*C.x)/P;
        auto y = (a*A.y + b*B.y + c*C.y)/P;

        return { x, y };
    }

    double circumradius() const
    {
        auto a = dist(B, C);
        auto b = dist(A, C);
        auto c = dist(A, B);

        return (a * b * c)/(4 * area());
    }

    Point<T> circumcenter() const
    {
        auto D = 2*(A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y));

        auto A2 = A.x*A.x + A.y*A.y;
        auto B2 = B.x*B.x + B.y*B.y;
        auto C2 = C.x*C.x + C.y*C.y;

        auto x = (A2*(B.y - C.y) + B2*(C.y - A.y) + C2*(A.y - B.y))/D;
        auto y = (A2*(C.x - B.x) + B2*(A.x - C.x) + C2*(B.x - A.x))/D;

        return { x, y };
    }

    Point<T> orthocenter() const
    {
        Line<T> r(A, B), s(A, C);

        Line<T> u { r.b, -r.a, -(C.x*r.b - C.y*r.a) };
        Line<T> v { s.b, -s.a, -(B.x*s.b - B.y*s.a) };

        auto det = u.a * v.b - u.b * v.a;  
        auto x = (-u.c * v.b + v.c * u.b) / det;                                                    
        auto y = (-v.c * u.a + u.c * v.a) / det;  

        return { x, y };
    }

    Angles classification_by_angles() const
    {
        auto a = dist(A, B);
        auto b = dist(B, C);
        auto c = dist(C, A);

        auto alpha = acos((a*a - b*b - c*c)/(-2*b*c));
        auto beta = acos((b*b - a*a - c*c)/(-2*a*c));
        auto gamma = acos((c*c - a*a - b*b)/(-2*a*b));

        auto right = PI / 2.0;

        if (equals(alpha, right) || equals(beta, right) || equals(gamma, right))
            return RIGHT;

        if (alpha > right || beta > right || gamma > right)
            return OBTUSE;

        return ACUTE;
    }

    Sides classification_by_sides() const
    {
        auto a = dist(A, B), b = dist(B, C), c = dist(C, A);

        if (equals(a, b) and equals(b, c))
            return EQUILATERAL;

        if (equals(a, b) or equals(a, c) or equals(b, c))
            return ISOSCELES;

        return SCALENE;
    }
};
