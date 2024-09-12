template<typename T>
struct Line {
    bool vertical;
    T m, b;

    Line(const Point<T>& P, const Point<T>& Q) : vertical(false)
    {
        if (equals(P.x, Q.x))
        {
            vertical = true;
            b = P.x;
        } else
        {
            m = (Q.y - P.y)/(Q.x - P.x)
            b = P.y - m * P.x
        }
    }

    bool operator==(const Line<T>& r) const    // Verdadeiro se coincidentes
    {
        if (vertical != r.vertical || !equals(m, r.m)) return false;

        return equals(b, r.b);
    }

    bool parallel(const Line<T>& r) const      // Verdadeiro se paralelas
    {
        if (vertical && r.vertical) return b != r.b;
        if (vertical || r.vertical) return false;

        return equals(m, r.m) && !equals(b, r.b);
    }

    bool orthogonal(const Line& r) const // Verdadeiro se perpendiculares
    {
        if (vertical && r.vertical)
            return false;

        if ((vertical && equals(r.m, 0)) || (equals(m, 0) && r.vertical))
            return true;

        if (vertical || r.vertical)
            return false;

        return equals(m * r.m, -1.0);
    }
};

