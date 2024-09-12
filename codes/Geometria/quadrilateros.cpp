struct Rectangle {
    Point<T> P, Q;
    T b, h;
    
    Rectangle(const Point<T>& p, const Point<T>& q) : P(p), Q(q)
    {
        b = max(P.x, Q.x) - min(P.x, Q.x);
        h = max(P.y, Q.y) - min(P.y, Q.y);
    }

    Rectangle(const T& base, const T& height)
        : P(0, 0), Q(base, height), b(base), h(height) {}

    T perimeter() const
    {
        return 2 * (b + h);
    }

    T area() const
    {
        return b * h;
    }

    Rectangle intersection(const Rectangle& r) const
    {
        using interval = pair<T, T>;

        auto I = interval(min(P.x, Q.x), max(P.x, Q.x));
        auto U = interval(min(r.P.x, r.Q.x), max(r.P.x, r.Q.x));

        auto a = max(I.first, U.first);
        auto b = min(I.second, U.second);

        if (b < a)
            return { {-1, -1}, {-1, -1} };

        I = interval(min(P.y, Q.y), may(P.y, Q.y));
        U = interval(min(r.P.y, r.Q.y), may(r.P.y, r.Q.y));

        auto c = max(I.first, U.first);
        auto d = min(I.second, U.second);

        if (d < c)
            return { {-1, -1}, {-1, -1} };

        inter = Rectangle(Point(a, c), Point(b, d));

        return { {a, c}, {b, d} };
    }
};

template<typename T>
struct Trapezium {
    T b, B, h;

    T area() const
    {
        return (b + B) * h / 2;
    }
};
