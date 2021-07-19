#pragma once

#include <cmath>
#include <iostream>
#include <new>
#include <string>
#include <vector>

#define ZERO 1e-10

#define BLACK 100
#define WHITE 101
#define RED 102
#define GREEN 103
#define BLUE 104

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

struct RGB {
    int r;
    int g;
    int b;
    RGB() { }
    RGB(int _r, int _g, int _b) {
        r = _r;
        g = _g;
        b = _b;
    }
    RGB(int color) {
        switch (color) {
        case BLACK:
            r = 0, g = 0, b = 0;
            break;
        case WHITE:
            r = 255, g = 255, b = 255;
            break;
        case RED:
            r = 255, g = 0, b = 0;
            break;
        case GREEN:
            r = 0, g = 255, b = 0;
            break;
        case BLUE:
            r = 0, g = 0, b = 255;
            break;
        default:
            break;
        }
    }
};

struct vector3d {
    double x;
    double y;
    double z;

    vector3d() { }
    vector3d(double _x, double _y, double _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    double length() {
        return sqrt(x * x + y * y + z * z);
    }

    void print() {
        printf("%lf %lf %lf\n", x, y, z);
    }
    vector3d operator+(vector3d rhs) {
        vector3d add;
        add.x = x + rhs.x;
        add.y = y + rhs.y;
        add.z = z + rhs.z;
        return add;
    }
    vector3d operator-(vector3d rhs) {
        vector3d dif;
        dif.x = x - rhs.x;
        dif.y = y - rhs.y;
        dif.z = z - rhs.z;
        return dif;
    }
    vector3d operator-() {
        return vector3d(-x, -y, -z);
    }
    vector3d operator*(double a) {
        return vector3d(a * x, a * y, a * z);
    }
    vector3d operator=(vector3d rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return vector3d(x, y, z);
    }
    bool operator==(vector3d rhs) {
        return (x == rhs.x && y == rhs.y && z == rhs.z);
    }
};

struct vector4d {
    double x;
    double y;
    double z;
    double w;

    vector4d() { }
    vector4d(double _x, double _y, double _z, double _w) {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }
    vector4d(vector3d _vector3d) {
        x = _vector3d.x;
        y = _vector3d.y;
        z = _vector3d.z;
        w = 1.0;
    }
};

struct vector2d {
    double x;
    double y;

    vector2d() { }
    vector2d(double _x, double _y) {
        x = _x;
        y = _y;
    }
};

struct vector2i {
    int u;
    int v;

    vector2i() { }
    vector2i(int _u, int _v) {
        u = _u;
        v = _v;
    }
};

struct edge {
    uint v[2];
    edge(uint v1, uint v2) {
        if (v1 < v2) {
            v[0] = v1;
            v[1] = v2;
        } else {
            v[0] = v2;
            v[1] = v1;
        }
    }
    edge() { }
    void setEdge(uint v1, uint v2) {
        if (v1 < v2) {
            v[0] = v1;
            v[1] = v2;
        } else {
            v[0] = v2;
            v[1] = v1;
        }
    }
    void print() {
        printf("%d %d\n", v[0], v[1]);
    }
    bool operator==(const edge& e) const {
        return (v[0] == e.v[0] && v[1] == e.v[1]);
    }
};

struct face {
    size_t vertices[3];
    edge edges[3];
    face(size_t v1, size_t v2, size_t v3, edge e1, edge e2, edge e3) {
        vertices[0] = v1;
        vertices[1] = v2;
        vertices[2] = v3;
        edges[0] = e1;
        edges[1] = e2;
        edges[3] = e3;
    }
};

double det(vector3d a, vector3d b, vector3d c) {
    return a.x * b.y * c.z + a.z * b.x * c.y + a.y * b.z * c.x - a.z * b.y * c.x - a.y * b.x * c.z - a.x * b.z * c.y;
}

vector3d hitTriangle(vector3d origin, vector3d ray, vector3d v1, vector3d v2, vector3d v3) {
    vector3d e1 = v2 - v1;
    vector3d e2 = v3 - v1;
    double denominator = det(e1, e2, -ray);

    if (denominator != 0.0) {
        double u = det(origin - v1, e2, -ray) / denominator;
        if (u >= 0.0 && u <= 1.0) {
            double v = det(e1, origin - v1, -ray) / denominator;
            if (v >= 0.0 && (u + v) <= 1.0) {
                double t = det(e1, e2, origin - v1) / denominator;
                return origin + ray * t;
            }
        }
    }
    return origin;
}