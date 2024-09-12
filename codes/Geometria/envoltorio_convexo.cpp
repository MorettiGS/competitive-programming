template<typename T>
class GrahamScan {
    static Point<T> pivot(vector<Point<T>>& P)
    {
        size_t idx = 0;
        for (size_t i = 1; i < P.size(); ++i)
            if (P[i].y < P[idx].y or (equals(P[i].y, P[idx].y) and P[i].x > P[idx].x))
                idx = i;
        swap(P[0], P[idx]);
        return P[0];
    }

    static void sort_by_angle(vector<Point<T>>& P)
    {
        auto P0 = pivot(P);
        sort(P.begin() + 1, P.end(), [&](const Point<T>& A, const Point<T>& B) {
            // pontos colineares: escolhe-se o mais próximo do pivô
            if (equals(D(P0, A, B), 0)) return A.distance(P0) < B.distance(P0);
            auto alfa = atan2(A.y - P0.y, A.x - P0.x);
            auto beta = atan2(B.y - P0.y, B.x - P0.x);
            return alfa < beta;
        });
    }

    static vector<Point<T>> convex_hull(const vector<Point<T>>& points)
    {
        vector<Point<T>> P(points);
        auto N = P.size();
        // Corner case: com 3 vértices ou menos, P é o próprio convex hull
        if (N <= 3) return P;
        sort_by_angle(P);
        vector<Point<T>> ch;
        ch.push_back(P[N - 1]);
        ch.push_back(P[0]);
        ch.push_back(P[1]);
        size_t i = 2;
        while (i < N)
        {
            auto j = ch.size() - 1;
            if (D(ch[j - 1], ch[j], P[i]) > 0)
                ch.push_back(P[i++]);
            else
                ch.pop_back();
        }
        // O envoltório é um caminho fechado: o primeiro ponto é igual ao último
        return ch;
    }
};


// Cadeia monótona de Andrew
template<typename T>
vector<Point<T>> make_hull(const vector<Point<T>>& points, vector<Point<T>>& hull)
{
    for (const auto& p : points)
    {
        auto size = hull.size();

        while (size >= 2 and D(hull[size - 2], hull[size - 1], p) <= 0)
        {
            hull.pop_back();
            size = hull.size();
        }

        hull.push_back(p);
    }

    return hull;
}

template<typename T>
vector<Point<T>> monotone_chain(const vector<Point<T>>& points)
{
    vector<Point<T>> P(points);

    sort(P.begin(), P.end());

    vector<Point<T>> lower, upper;
    
    lower = make_hull(P, lower);

    reverse(P.begin(), P.end());
    
    upper = make_hull(P, upper);

    lower.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end()); 

    return lower;
}