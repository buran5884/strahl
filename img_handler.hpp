#pragma once

#include <new>
#include <string>
#include <vector>

#include "Object.hpp"
#include "stb_image_write.h"
#include "Utilities.hpp"

#define MODE_RGB 3
#define MODE_RGBA 4

using namespace std;

class Image {
private:
    uint8_t* pixels;
    int width;
    int height;
    int mode;

public:
    Image(int _width, int _height, int _mode) {
        width = _width;
        height = _height;
        mode = _mode;
        pixels = new uint8_t[width * height * mode];
    }

    void SetResolution(int _width, int _height);
    void DrawPixel(vector2i point, RGBA rgba);
    void SavePngImg(string filename);
    void SavePpmImg(string filename);
    void FillColor(RGBA rgba);
    void DrawLine(vector2i point1, vector2i point2, RGBA rgba);
    void DrawWireframe(Object3D model, RGBA rgba);
    int GetWidth();
    int GetHeight();
};

void Image::SetResolution(int _width, int _height) {
    width = _width;
    height = _height;
}

int Image::GetWidth() {
    return width;
}

int Image::GetHeight() {
    return height;
}

void Image::DrawPixel(vector2i point, RGBA rgba) {
    int cols = point.u;
    int rows = point.v;
    if (0 <= cols && cols < width && 0 <= rows && rows < height) {
        pixels[((cols + rows * width) * mode) + 0] = rgba.r;
        pixels[((cols + rows * width) * mode) + 1] = rgba.g;
        pixels[((cols + rows * width) * mode) + 2] = rgba.b;
        if (mode == MODE_RGBA)
            pixels[((cols + rows * width) * mode) + 3] = rgba.a;
    }
}

void Image::SavePngImg(string filename) {
    stbi_write_png(filename.c_str(), width, height, mode, pixels, 0);
}

void Image::SavePpmImg(string filename) {
    FILE* fp;
    fp = fopen((const char*)filename.c_str(), "w");
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "255\n");
    for (int i = 0; i < width * height; i++)
        fprintf(fp, "%d %d %d\n", pixels[i * 3 + 0], pixels[i * 3 + 1], pixels[i * 3 + 2]);
    fclose(fp);
}

void Image::FillColor(RGBA rgba) {
    for (int i = 0; i < width * height; i++) {
        pixels[i * mode + 0] = rgba.r;
        pixels[i * mode + 1] = rgba.g;
        pixels[i * mode + 2] = rgba.b;
        if (mode == MODE_RGBA)
            pixels[i * mode + 3] = rgba.a;
    }
}

void Image::DrawLine(vector2i point1, vector2i point2, RGBA rgba) {
    int frac;
    int uNext, vNext, uStep, vStep, uDelta, vDelta;
    int uself, vself, uEnd, vEnd;
    uself = point1.u;
    vself = point1.v;
    uEnd = point2.u;
    vEnd = point2.v;
    uNext = uself;
    vNext = vself;
    uDelta = uEnd - uself;
    vDelta = vEnd - vself;
    uStep = 1;
    vStep = 1;
    if (uDelta < 0)
        uStep = -1;
    if (vDelta < 0)
        vStep = -1;
    uDelta = uDelta * 2;
    vDelta = vDelta * 2;
    if (uDelta < 0)
        uDelta = -uDelta;
    if (vDelta < 0)
        vDelta = -vDelta;
    DrawPixel(vector2i(uNext, vNext), rgba);
    if (uDelta > vDelta) {
        frac = vDelta * 2 - uDelta;
        while (uNext != uEnd) {
            if (frac >= 0) {
                vNext = vNext + vStep;
                frac = frac - uDelta;
            }
            uNext = uNext + uStep;
            frac = frac + vDelta;
            DrawPixel(vector2i(uNext, vNext), rgba);
        }
    } else {
        frac = uDelta * 2 - vDelta;
        while (vNext != vEnd) {
            if (frac >= 0) {
                uNext = uNext + uStep;
                frac = frac - vDelta;
            }
            vNext = vNext + vStep;
            frac = frac + uDelta;
            DrawPixel(vector2i(uNext, vNext), rgba);
        }
    }
}