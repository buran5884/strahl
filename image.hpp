#pragma once
#include "utilities.hpp"

using namespace std;

class Image {
private:
    uint8_t* pixels;
    int width;
    int height;

public:
    Image(int _width, int _height) {
        width = _width;
        height = _height;
        pixels = new uint8_t[width * height * 3];
    }

    void SetResolution(int _width, int _height);
    void SetPixel(vector2i point, RGB rgba);
    void DrawLine(vector2i point1, vector2i point2, RGB rgba);
    void SavePngImg(string filename);
    void SavePpmImg(string filename);
    void FillColor(RGB rgba);
    int GetWidth();
    int GetHeight();
    RGB GetPixel(int width, int height);
};

RGB Image::GetPixel(int cols, int rows) {
    int r = pixels[((cols + rows * width) * 3) + 0];
    int g = pixels[((cols + rows * width) * 3) + 1];
    int b = pixels[((cols + rows * width) * 3) + 2];
    return RGB(r,g,b);
}

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

void Image::SetPixel(vector2i point, RGB rgba) {
    int cols = point.u;
    int rows = point.v;
    if (0 <= cols && cols < width && 0 <= rows && rows < height) {
        pixels[((cols + rows * width) * 3) + 0] = rgba.r;
        pixels[((cols + rows * width) * 3) + 1] = rgba.g;
        pixels[((cols + rows * width) * 3) + 2] = rgba.b;
    }
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

void Image::FillColor(RGB rgba) {
    for (int i = 0; i < width * height; i++) {
        pixels[i * 3 + 0] = rgba.r;
        pixels[i * 3 + 1] = rgba.g;
        pixels[i * 3 + 2] = rgba.b;
    }
}

void Image::DrawLine(vector2i point1, vector2i point2, RGB rgba) {
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
    SetPixel(vector2i(uNext, vNext), rgba);
    if (uDelta > vDelta) {
        frac = vDelta * 2 - uDelta;
        while (uNext != uEnd) {
            if (frac >= 0) {
                vNext = vNext + vStep;
                frac = frac - uDelta;
            }
            uNext = uNext + uStep;
            frac = frac + vDelta;
            SetPixel(vector2i(uNext, vNext), rgba);
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
            SetPixel(vector2i(uNext, vNext), rgba);
        }
    }
}