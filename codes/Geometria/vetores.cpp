template<typename T>
struct Vector
{
    T x = 0, y = 0;

    Vector(const Point<T>& A, const Point<T>& B) 
        : x(B.x - A.x), y(B.y - A.y) {}
};

template<typename T>
Vector<T> normalize(const Vector<T>& v)
{
    auto len = v.length();
    return { v.x / len, v.y / len };
}

template<typename T>
Point<T> rotate(const Point<T>& P, T angle)
{
    auto x = cos(angle) * P.x - sin(angle) * P.y;
    auto y = sin(angle) * P.x + cos(angle) * P.y;

    return { x, y };
}

template<typename T>
Point<T> rotate2(const Point<T>& P, T angle, const Point<T>& C)
{
    auto Q = translate(P, -C.x, -C.y);
    Q = rotate(Q, angle);
    Q = translate(Q, C.x, C.y);

    return Q;
}

template<typename T>
Vector<T> scale(const Vector<T>& v, T sx, T sy)
{
    return { sx * v.x, sy * v.y };
}

template<typename T>
Point<T> translate(const Point<T>& P, T dx, T dy)
{
    return { P.x + dx, P.y + dy };
}

template<typename T>
Vector<T> cross_product(const Vector<T>& u, const Vector<T>& v)
{
    auto x = u.y*v.z - v.y*u.z;
    auto y = u.z*v.x - u.x*v.z;
    auto z = u.x*v.y - u.y*v.x;

    return { x, y, z };
}

template<typename T>
T dot_product(const Vector<T>& u, const Vector<T>& v)
{
    return u.x * v.x + u.y * v.y;
}

// O retorno está no intervalo [0, pi]
template<typename T>
double angle(const Vector<T>& u, const Vector<T>& v)
{
    auto lu = u.length();
    auto lv = v.length();
    auto prod = dot_product(u, v);

    return acos(prod/(lu * lv));
}
