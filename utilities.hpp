#pragma once

#include <string>
#include <vector>
#include <new>
#include <cmath>
#include <iostream>

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
    edge edges[3];
    face(edge e1, edge e2, edge e3) {
        edges[0] = e1;
        edges[1] = e2;
        edges[3] = e3;
    }
};