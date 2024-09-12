#define PI 2*acos(0.0)

// A unidade de medida do angulo é radianos
template<typename T>
struct Circle {
    Point<T> C;
    T r;

    enum { IN, ON, OUT } PointPosition;

    double perimeter() const {
        return 2.0 * PI * r;
    }

    double area() const {
        return PI * r * r;
    }

    double arc(double theta) const {
        return theta * r;
    }

    double sector(double theta) const {
        return (theta * r * r)/2;
    }

    double chord(double theta) const {
        return 2 * r * sin(theta/2);
    }

    double segment(double a) const {
        return ((a - sin(a))*r*r)/2.0;
    }

    PointPosition position(const Point& P) const
    {
        auto d = dist(P, C);

        return equals(d, r) ? ON : (d < r ? IN : OUT);
    }


    // O código abaixo foi adaptado do livro Competitive Programming 3.  A função retorna um dos
    // círculos: o outro pode ser encontrado invertendo os parâmetros P e Q na chamada da função

    static std::optional<Circle>
    from_2_points_and_r(const Point<T>& P, const Point<T>& Q, T r)
    {
        double d2 = (P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y);
        double det = r * r / d2 - 0.25;
        if (det < 0.0)
            return { };
        double h = sqrt(det);
        auto x = (P.x + Q.x) * 0.5 + (P.y - Q.y) * h;
        auto y = (P.y + Q.y) * 0.5 + (Q.x - P.x) * h;
        return Circle<T>{ Point<T>(x, y), r };
    }

    static std::experimental::optional<Circle>
    from_3_points(const Point<T>& P, const Point<T>& Q, const Point<T>& R)
    {
        auto a = 2*(Q.x - P.x);
        auto b = 2*(Q.y - P.y);
        auto c = 2*(R.x - P.x);
        auto d = 2*(R.y - P.y);
        auto det = a*d - b*c;
        // Pontos colineares
        if (equals(det, 0))
            return { };
        auto k1 = (Q.x*Q.x + Q.y*Q.y) - (P.x*P.x + P.y*P.y);
        auto k2 = (R.x*R.x + R.y*R.y) - (P.x*P.x + P.y*P.y);
        // Solução do sistema por Regra de Cramer
        auto cx = (k1*d - k2*b)/det;
        auto cy = (a*k2 - c*k1)/det;
        Point<T> C { cx, cy };
        auto r = distance(P, C);
        return Circle<T>(C, r);
    }
};

template<typename T> std::variant<int, std::vector<Point<T>>>
intersection(const Circle<T>& c1, const Circle<T>& c2)
{
    double d = distance(c1.C, c2.C);
    if (d > c1.r + c2.r or d < fabs(c1.r - c2.r)) return 0;
    if (equals(d, 0.0) and equals(c1.r, c2.r)) return oo;
    auto a = (c1.r * c1.r - c2.r * c2.r + d * d)/(2 * d);
    auto h = sqrt(c1.r * c1.r - a * a);
    auto x = c1.C.x + (a/d)*(c2.C.x - c1.C.x);
    auto y = c1.C.y + (a/d)*(c2.C.y - c1.C.y);
    auto P = Point<T> { x, y };
    x = P.x + (h/d)*(c2.C.y - c1.C.y);
    y = P.y - (h/d)*(c2.C.x - c1.C.x);
    auto P1 = Point<T> { x, y };
    x = P.x - (h/d)*(c2.C.y - c1.C.y);
    y = P.y + (h/d)*(c2.C.x - c1.C.x);
    auto P2 = Point<T> { x, y };
    return P1 == P2 ? std::vector<Point<T>> { P1 } : std::vector<Point<T>> { P1, P2 };
}

// Interseção entre o círculo c e a reta que passa por P e Q
template<typename T> std::vector<Point<T>>
intersection(const Circle<T>& c, const Point<T>& P, const Point<T>& Q)
{
    auto a = pow(Q.x - P.x, 2.0) + pow(Q.y - P.y, 2.0);
    auto b = 2*((Q.x - P.x) * (P.x - c.C.x) + (Q.y - P.y) * (P.y - c.C.y));
    auto d = pow(c.C.x, 2.0) + pow(c.C.y, 2.0) + pow(P.x, 2.0) 
        + pow(P.y, 2.0) + 2*(c.C.x * P.x + c.C.y * P.y);
    auto D = b * b - 4 * a * d;
    if (D < 0)
        return { };
    else if (equals(D, 0))
    {
        auto u = -b/(2*a);
        auto x = P.x + u*(Q.x - P.x);
        auto y = P.y + u*(Q.y - P.y);
        return { Point { x, y } };
    }
    auto u = (-b + sqrt(D))/(2*a);
    auto x = P.x + u*(Q.x - P.x);
    auto y = P.y + u*(Q.y - P.y);
    auto P1 = Point { x, y };
    u = (-b - sqrt(D))/(2*a);
    x = P.x + u*(Q.x - P.x);
    y = P.y + u*(Q.y - P.y);
    auto P2 = Point { x, y };
    return { P1, P2 };
}
