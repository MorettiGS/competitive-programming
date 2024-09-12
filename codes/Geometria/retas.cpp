#include <bits/stdc++.h>

template<typename T>
struct Point {
    T x = 0, y = 0;
};

template<typename T>
struct Line {
    T a, b, c;

    Line(const Point<T>& P, const Point<T>& Q)
        : a(P.y - Q.y), b (Q.x - P.x), c(P.x * Q.y - Q.x * P.y)
    {
    }

    bool contains(const Point<T>& P) const
    {
        return equals(a*P.x + b*P.y + c, 0);
    }

    bool operator==(const Line<T>& r) const
    {
        auto k = a ? a : b;
        auto s = r.a ? r.a : r.b;

        return equals(a*s, r.a*k) && equals(b*s, r.b*k) && equals(c*s, r.c*k);
    }

    bool parallel(const Line<T>& r) const
    {
        auto det = a*r.b - b*r.a;

        return det == 0 and !(*this == r);
    }

    double distance(const Point<T>& p) const        // Distância de p à reta
    {
        return fabs(a*p.x + b*p.y + c)/hypot(a, b);
    }

    Point<T> closest(const Point<T>& p) const       // Ponto mais próximo de p
    {
        auto den = (a*a + b*b);

        auto x = (b*(b*p.x - a*p.y) - a*c)/den;
        auto y = (a*(-b*p.x + a*p.y) - b*c)/den;

        return Point<T> { x, y };
    }

    bool orthogonal(const Line& r) const  // Verdadeiro se perpendiculares
    {
        return equals(a * r.a + b * r.b, 0);
    }
};

template<typename T>
T absolute_value(T x)
{
    if constexpr (std::is_floating_point_v<T>)
        return fabs(x);
    else
        return llabs(static_cast<long long>(x));
}

template<typename T>
double dist(const Point<T>& P, const Point<T>& Q) {
    return hypot(static_cast<double>(P.x - Q.x), static_cast<double>(P.y - Q.y));
}

template<typename T>
T dist2(const Point<T>& P, const Point<T>& Q) {
    return (P.x - Q.x)*(P.x - Q.x) + (P.y - Q.y)*(P.y - Q.y);
}

template<typename T>
T taxicab(const Point<T>& P, const Point<T>& Q) {
    return absolute_value(P.x - Q.x) + absolute_value(P.y - Q.y);
}

template<typename T>
T max_norm(const Point<T>& P, const Point<T>& Q) {
    return std::max(absolute_value(P.x - Q.x), absolute_value(P.y - Q.y));
}

int main()
{
    Point<int> P, Q { 2, 3 };

    std::cout << "Euclidiana: " << dist(P, Q) << '\n';
    std::cout << "Quadrado: " << dist2(P, Q) << '\n';
    std::cout << "Motorista de táxi: " << taxicab(P, Q) << '\n';
    std::cout << "Norma do máximo: " << max_norm(P, Q) << '\n';

    return 0;
}
