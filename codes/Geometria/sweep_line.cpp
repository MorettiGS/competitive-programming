vector<int> max_intersection(const vector<pll>& is)
{
    vector<pll> es;

    for (size_t i = 0; i < is.size(); ++i)
    {
        auto [a, b] = is[i];

        es.emplace_back(a, i + 1);      // Evento de início
        es.emplace_back(b, -(i + 1));   // Evento de fim
    }

    sort(es.begin(), es.end());

    set<int> active, max_set;

    for (const auto& [_, i] : es)
    {
        if (i > 0)
            active.emplace(i);
        else
            active.erase(-i);

        if (active.size() >= max_set.size())
            max_set = active;
    }

    return { max_set.begin(), max_set.end() };
}

// bf

template<typename T>
set<Point<T>> intersections(int N, const vector<Segment<T>>& segments)
{
    set<Point<T>> ans;

    for (int i = 0; i < N; ++i)
    {
        auto s = segments[i];

        for (int j = i + 1; j < N; ++j)
        {
            auto r = segments[j];
            auto P = s.intersection(r);

            if (P) ans.insert(P.value());
        }
    }

    return ans;
}

// Closest

pair<Point, Point> closest_pair(int N, vector<Point>& ps)
{
    sort(ps.begin(), ps.end());

    // Este código assume que N > 1
    auto d = dist(ps[0], ps[1]);
    auto closest = make_pair(ps[0], ps[1]);

    set<ii> S;
    S.insert(ii(ps[0].y, ps[0].x));
    S.insert(ii(ps[1].y, ps[1].x));

    for (int i = 2; i < N; ++i)
    {
        auto P = ps[i];
        auto it = S.lower_bound(Point(P.y - d, 0));

        while (it != S.end())
        {
            auto Q = Point(it->second, it->first);

            if (Q.x < P.x - d)
            {
                it = S.erase(it);
                continue;
            }

            if (Q.y > P.y + d)
                break;

            auto t = dist(P, Q);

            if (t < d)
            {
                d = t;
                closest = make_pair(P, Q);
            }

            ++it;
        }

        S.insert(ii(P.y, P.x));
    }

    return closest;
}

// Bentley Ottman

void add_neighbor_intersections(const Segment& s, const set<Segment>& sl, 
    set<Point>& ans, priority_queue<Event>& events)
{
    // TODO: garantir que a busca identifique unicamente o elemento s,
    // através do ajuste fino da variável Segment::sweep_x
    auto it = sl.find(s);

    if (it != sl.begin())
    {
        auto L = *prev(it);
        auto P = s.intersection(L);
        
        if (P and ans.count(P.value()) == 0)
        {
            events.push(Event { P.value(), Event::INTERSECTION, s.idx } );
            ans.insert(P.value());
        }
    } 

    if (next(it) != sl.end())
    {
        auto U = *next(it);
        auto P = s.intersection(U);

        if (P and ans.count(P.value()) == 0)
        {
            events.push(Event { P.value(), Event::INTERSECTION, s.idx } );
            ans.insert(P.value());
        }
    }
} 

set<Point> bentley_ottman(vector<Segment>& segments)
{
    set<Point> ans;
    priority_queue<Event> events;

    for (size_t i = 0; i < segments.size(); ++i)
    {
        events.push(Event { segments[i].A, Event::OPEN, i });
        events.push(Event { segments[i].B, Event::CLOSE, i });
    }

    set<Segment> sl;

    while (not events.empty())
    {
        auto e = events.top();
        events.pop();

        Segment::sweep_x = e.P.x;

        switch (e.type) {
        case Event::OPEN:
        {
            auto s = segments[e.i];
            sl.insert(s);

            add_neighbor_intersections(s, sl, ans, events);
        } 
        break;

        case Event::CLOSE:
        {
            auto s = segments[e.i];
            auto it = sl.find(s);       // TODO: aqui também

            if (it != sl.begin() and it != sl.end())
            {
                auto L = *prev(it);
                auto U = *next(it);
                auto P = L.intersection(U);

                if (P and ans.count(P.value()) == 0)
                    events.push( Event { P.value(), Event::INTERSECTION, L.idx } );
            }

            sl.erase(it);
        }
        break;

        default:
            auto r = segments[e.i];
            auto p = sl.equal_range(r);

            vector<Segment> range(p.first, p.second);

            // Remove os segmentos que se interceptam
            sl.erase(p.first, p.second);

            // Reinsere os segmentos
            Segment::sweep_x += 0.1;

            sl.insert(range.begin(), range.end());

            // Procura interseções com os novos vizinhos
            for (const auto& s : range)
                add_neighbor_intersections(s, sl, ans, events);
        }
    }

    return ans;
}