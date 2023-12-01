#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double eps = 1e-8;

struct p
{
    double x, y; // 二维向量，表示一个点
    p(double _x = 0, double _y = 0) : x(_x), y(_y) {}

    // 向量基本运算的实现+ - · *
    p operator+(const p &a) const { return p{x + a.x, y + a.y}; }
    p operator-(const p &a) const { return p{x - a.x, y - a.y}; }
    p operator-() const { return p{-x, -y}; }

    double operator|(const p &a) const { return x * a.x + y * a.y; } // 点乘
    double operator*(const p &a) const { return x * a.y - y * a.x; } // 叉乘
    p operator*(const ll a) const { return p{x * a, y * a}; }        // 向量数乘
    double pow() const { return x * x + y * y; }                     // 向量取平方

    // 求距离
    // 点到点的距离
    double disPoint(const p &a) const
    {
        return sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
    }

    // 点到直线的距离
    // a,b直线上两点
    double disline(const p &a, const p &b) const
    {
        p ap = (*this) - a, ab = b - a;
        return abs(ap * ab) / abs(ab);
    }

    // 点到线段的距离
    // a,b线段两端点
    double disSeg(const p &a, const p &b) const
    {
        // 判断点和线段的位置关系
        if ((((*this) - a) | (b - a)) <= -eps || (((*this) - b) | (a - b)) <= -eps)
            return min(this->disPoint(a), this->disPoint(b));
        return disline(a, b);
    }
};
double abs(const p &p) { return sqrt(p.pow()); } // 向量取模
double triangle(p &a, p &b, p &c) { return (b - a) * (b - c) / 2.0; } // 求三角形面积


