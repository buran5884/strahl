#include <new>
#include <string>
#include <vector>

#include "stb_image_write.h"
#include "strahl.hpp"

#define MODE_RGB 3
#define MODE_RGBA 4

using namespace std;

class RenderedImg {
private:
    uint8_t* pixels;
    int width;
    int height;
    int mode;

public:
    RenderedImg(int _width, int _height, int _mode) {
        width = _width;
        height = _height;
        mode = _mode;
        pixels = new uint8_t[width * height * mode];
    }
    void DrawPixel(vector2d point, RGBA rgba);
    void SaveImg(string filename);
    void FillColor(RGBA rgba);
    void DrawLine(vector2d point1, vector2d point2, RGBA rgba);
};

void RenderedImg::DrawPixel(vector2d point, RGBA rgba) {
    int cols = point.u;
    int rows = point.v;
    pixels[((cols + rows * width) * mode) + 0] = rgba.r;
    pixels[((cols + rows * width) * mode) + 1] = rgba.g;
    pixels[((cols + rows * width) * mode) + 2] = rgba.b;
    if (mode == MODE_RGBA)
        pixels[((cols + rows * width) * mode) + 3] = rgba.a;
}

void RenderedImg::SaveImg(string filename) {
    stbi_write_png(filename.c_str(), width, height, mode, pixels, 0);
}

void RenderedImg::FillColor(RGBA rgba) {
    for (int i = 0; i < width * height; i++) {
        pixels[i * mode + 0] = rgba.r;
        pixels[i * mode + 1] = rgba.g;
        pixels[i * mode + 2] = rgba.b;
        if (mode == MODE_RGBA)
            pixels[i * mode + 3] = rgba.a;
    }
}

void RenderedImg::DrawLine(vector2d point1, vector2d point2, RGBA rgba) {
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
    DrawPixel(vector2d(uNext, vNext), rgba);
    if (uDelta > vDelta) {
        frac = vDelta * 2 - uDelta;
        while (uNext != uEnd) {
            if (frac >= 0) {
                vNext = vNext + vStep;
                frac = frac - uDelta;
            }
            uNext = uNext + uStep;
            frac = frac + vDelta;
            DrawPixel(vector2d(uNext, vNext), rgba);
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
            DrawPixel(vector2d(uNext, vNext), rgba);
        }
    }
}