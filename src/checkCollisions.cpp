#include <algorithm>
#include <cmath>
#include <vector>

struct Point {
    std::vector<double> pos;
    double r;
    int idx;
};

bool isCollision(const Point &a, const Point &b) {
    double R2 = pow(a.r + b.r, 2);
    double dis2 = 0;
    for (int i = 0; i < (int)a.pos.size(); i++) {
        dis2 += pow(a.pos[i] - b.pos[i], 2);
    }
    return dis2 <= R2;
}

template <typename Iter>  // Iter = std::vector<Point>::iterator
void findCollisions(Iter begin, Iter end, Iter tbegin, Iter tend,
                    std::vector<std::pair<int, int>> &collisions) {
    if (begin == end) return;

    int n = distance(begin, end);
    int D = begin->pos.size();

    if (n < 10) {
        for (Iter i = begin; i != end; ++i) {
            for (Iter j = begin; j != i; ++j) {
                if (isCollision(*i, *j)) {
                    int a = i->idx, b = j->idx;
                    if (a == b) continue;
                    if (a > b) std::swap(a, b);
                    collisions.push_back({a, b});
                }
            }
        }
        return;
    }

    Point pivot = *(begin + rand() % n);
    int k = rand() % D;

    Iter l = begin, m = tbegin, r = tend;
    for (Iter it = begin; it != end; ++it) {
        if (it->pos[k] + it->r < pivot.pos[k]) {
            *(l++) = *it;
        } else if (it->pos[k] - it->r > pivot.pos[k]) {
            *(--r) = *it;
        } else {
            *(m++) = *it;
        }
    }
    copy(r, tend, l);
    copy(tbegin, m, end - (m - tbegin));

    for (Iter i = end - (m - tbegin); i != end; ++i) {
        for (Iter j = begin; j != i; ++j) {
            if (isCollision(*i, *j)) {
                int a = i->idx, b = j->idx;
                if (a == b) continue;
                if (a > b) std::swap(a, b);
                collisions.push_back({a, b});
            }
        }
    }
    findCollisions(begin, l, tbegin, tbegin + (l - begin), collisions);
    findCollisions(l, l + (tend - r), tbegin, tbegin + (tend - r), collisions);
}

std::vector<std::pair<int, int>> checkCollisions(
    std::vector<std::vector<double>> _points) {
    std::vector<Point> points;
    for (int i = 0; i < (int)_points.size(); i++) {
        points.push_back({_points[i], _points[i].back(), i});
        points[i].pos.pop_back();
    }

    std::vector<std::pair<int, int>> collisions;
    std::vector<Point> tmp = points;
    findCollisions(points.begin(), points.end(), tmp.begin(), tmp.end(),
                   collisions);
    return collisions;
}

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
namespace py = pybind11;

PYBIND11_MODULE(checkCollisions, m) {
    m.def("checkCollisions",           // function name
          &checkCollisions,            // function pointer
          "Get collisions of n balls"  // function doc string
    );
}
