double polygonArea(const std::vector<std::pair<double, double>>& vertices) {
    int n = vertices.size();
    double area = 0.0;

    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += vertices[i].first * vertices[j].second;
        area -= vertices[i].second * vertices[j].first;
    }

    return std::fabs(area) / 2.0;
}