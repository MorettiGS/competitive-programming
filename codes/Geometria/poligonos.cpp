template<typename T>
class Polygon {
    vector<Point<T>> vs;
    int n;

    // O parâmetro deve conter os n vértices do polígono
    Polygon(const vector<Point<T>>& ps) : vs(ps), n(vs.size())
    {
        vs.push_back(vs.front());
    }

    T D(const Point<T>& P, const Point<T>& Q, const Point<T>& R) const
    {
        return (P.x * Q.y + P.y * R.x + Q.x * R.y) - (R.x * Q.y + R.y * P.x + Q.x * P.y);
    }

    bool convex() const {
        // Um polígono deve ter, no minimo, 3 vértices
        if (n < 3) return false;

        int P = 0, N = 0, Z = 0;

        for (int i = 0; i < n; ++i) {
            auto d = D(vs[i], vs[(i + 1) % n], vs[(i + 2) % n]);
            d ? (d > 0 ? ++P : ++N) : ++Z;
        }

        return P == n or N == n;
    } 

    double distance(const Point<T>&P, const Point<T>& Q)
    {
        return hypot(P.x - Q.x, P.y - Q.y);
    }
    
    double perimeter() const
    {
        auto p = 0.0;
        for (int i = 0; i < n; ++i)
            p += distance(vs[i], vs[i + 1]);
        return p;
    }

    double area() const
    {
        auto a = 0.0;
        for (int i = 0; i < n; ++i)
        {
            a += vs[i].x * vs[i + 1].y;
            a -= vs[i + 1].x * vs[i].y;
        }
        return 0.5 * fabs(a);
    }

    // Ângulo APB, em radianos
    double angle(const Point<T>& P, const Point<T>& A, const Point<T>& B)
    {
        auto ux = P.x - A.x;
        auto uy = P.y - A.y;
        auto vx = P.x - B.x;
        auto vy = P.y - B.y;
        auto num = ux * vx + uy * vy;
        auto den = hypot(ux, uy) * hypot(vx, vy);
        // Caso especial: se den == 0, algum dos vetores é degenerado: os 
        // dois pontos são iguais. Neste caso, o ângulo não está definido
        return acos(num / den);
    }

    bool equals(double x, double y) {
        static const double EPS { 1e-6 };
        return fabs(x - y) < EPS;
    }
    
    bool contains(const Point<T>& P) const
    {
        if (n < 3) return false;
        auto sum = 0.0;
        for (int i = 0; i < n - 1; ++i) {
            auto d = D(P, vs[i], vs[i + 1]);
            auto a = angle(P, vs[i], vs[i + 1]);
            sum += d > 0 ? a : (d < 0 ? -a : 0);
        }
        static const double PI = acos(-1.0);
        return equals(fabs(sum), 2*PI);
    }

    // Interseção entre a reta AB e o segmento de reta PQ
    Point<T> intersection(const Point<T>& P, const Point<T>& Q, 
                          const Point<T>& A, const Point<T>& B)
    {
        auto a = B.y - A.y;
        auto b = A.x - B.x;
        auto c = B.x * A.y - A.x * B.y;
        auto u = fabs(a * P.x + b * P.y + c);
        auto v = fabs(a * Q.x + b * Q.y + c);

        // Média ponderada pelas distâncias de P e Q até a reta AB
        return {(P.x * v + Q.x * u)/(u + v), (P.y * v + Q.y * u)/(u + v)};
    }

    // Corta o polígono com a reta r que passa por A e B
    Polygon cut_polygon(const Point<T>& A, const Point<T>& B) const
    {
        vector<Point<T>> points;
        const double EPS { 1e-6 };
        for (int i = 0; i < n; ++i)
        {
            auto d1 = D(A, B, vs[i]);
            auto d2 = D(A, B, vs[i + 1]);

            // Vértice à esquerda da reta
            if (d1 > -EPS)
                points.push_back(vs[i]);

            // A aresta cruza a reta
            if (d1 * d2 < -EPS)
                points.push_back(intersection(vs[i], vs[i + 1], A, B));
        }
        return Polygon(points);
    }

    double circumradius() const
    {
        auto s = distance(vs[0], vs[1]);
        const double PI { acos(-1.0) };
        return (s/2.0)*(1.0/sin(PI/n));
    }

    double apothem() const
    {
        auto s = distance(vs[0], vs[1]);
        const double PI { acos(-1.0) };
        return (s/2.0)*(1.0/tan(PI/n));
    }
};