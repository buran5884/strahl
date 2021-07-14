#pragma once

#define BLACK 100
#define WHITE 101
#define RED 102
#define GREEN 103
#define BLUE 104

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

struct RGBA {
    int r;
    int g;
    int b;
    int a;
    RGBA(int _r, int _g, int _b) {
        r = _r;
        g = _g;
        b = _b;
        a = 255;
    }
    RGBA(int _r, int _g, int _b, int _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
    RGBA(int color) {
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
        a = 255;
    }
    RGBA(int color, int _a) {
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
        a = _a;
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