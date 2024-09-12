// Ângulo entre os segmentos de reta PQ e RS
template<typename T>
double angle(const Point<T>& P, const Point<T>& Q, const Point<T>& R, const Point<T>& S)
{
    auto ux = P.x - Q.x;
    auto uy = P.y - Q.y;

    auto vx = R.x - S.x;
    auto vy = R.y - S.y;

    auto num = ux * vx + uy * vy;
    auto den = hypot(ux, uy) * hypot(vx, vy);
    // Caso especial: se den == 0, algum dos vetores é degenerado: os dois
    // pontos são iguais. Neste caso, o ângulo não está definido
    return acos(num / den);
}

template<typename T>
Line<T> perpendicular_bisector(const Point<T>& P, const  Point<T>& Q)
{
    auto a = 2*(Q.x - P.x);
    auto b = 2*(Q.y - P.y);
    auto c = (P.x * P.x + P.y * P.y) - (Q.x * Q.x + Q.y * Q.y);
    return { a, b, c };
}

struct Segment {
    Point<T> A, B;
    // Verifica se o ponto P da reta r que contém A e B  pertence ao segmento
    bool contains(const Point<T>& P) const {
        return equals(A.x, B.x) ?  min(A.y, B.y) <= P.y and P.y <= max(A.y, B.y) 
            : min(A.x, B.x) <= P.x and P.x <= max(A.x, B.x);
    }
    // Esta abordagem não exige que P esteja sobre a reta AB
    bool contains2(const Point<T>& P) const {
        double dAB = dist(A, B), dAP = dist(A, P), dPB = dist(P, B);
        return equals(dAP + dPB, dAB);
    }
    // Ponto mais próximo de P no segmento AB
    Point<T> closest(const Point<T>& P) {
        Line<T> r(A, B);
        auto Q = r.closest(P);
        if (this->contains(Q)) return Q;
        auto distA = P.distanceTo(A);
        auto distB = P.distanceTo(B);
        if (distA <= distB) return A;
        else return B;
    }

    bool intersect(const Segment<T>& s) const
    {
        auto d1 = D(A, B, s.A);
        auto d2 = D(A, B, s.B);
        if ((equals(d1, 0) && contains(s.A)) || (equals(d2, 0) && contains(s.B))) return true;
        auto d3 = D(s.A, s.B, A);
        auto d4 = D(s.A, s.B, B);
        if ((equals(d3, 0) && s.contains(A)) || (equals(d4, 0) && s.contains(B))) return true;
        return (d1 * d2 < 0) && (d3 * d4 < 0);
    }
}

// Verifica se o ponto P pertence ao segmento de reta AB
template<typename T>
bool contains(const Point<T>& A, const Point<T>& B, const Point<T>& P)
{
    // Verifica se P está na região retangular
    auto xmin = min(A.x, B.x);
    auto xmax = max(A.x, B.x);
    auto ymin = min(A.y, B.y);
    auto ymax = max(A.y, B.y);
    if (P.x < xmin || P.x > xmax || P.y < ymin || P.y > ymax)
        return false;
    // Verifica relação de semelhança no triângulo
    return equals((P.y - A.y)*(B.x - A.x), (P.x - A.x)*(B.y - A.y));
}

// D = 0: R pertence a reta PQ
// D > 0: R à esquerda da reta PQ
// D < 0: R à direita da reta PQ
template<typename T>
T D(const Point<T>& P, const Point<T>& Q, const Point<T>& R)
{
    return (P.x * Q.y + P.y * R.x + Q.x * R.y) - (R.x * Q.y + R.y * P.x + Q.x * P.y);
}

template<typename T>
std::pair<int, Point<T>> intersections(const Line<T>& r, const Line<T>& s)
{
    auto det = r.a * s.b - r.b * s.a;
    if (equals(det, 0))     // Coincidentes ou paralelas
    { return { (r == s) ? oo : 0, {} };
    }else                    // Concorrentes
    {
        auto x = (-r.c * s.b + s.c * r.b) / det;
        auto y = (-s.c * r.a + r.c * s.a) / det;
        return { 1, { x, y } };
    }
}