#include <new>
#include <string>
#include <vector>

#include "stb_image_write.h"

#define MODE_RGB 3
#define MODE_RGBA 4

using namespace std;

struct RGBA {
    int r;
    int g;
    int b;
    int a;
    RGBA(int _r, int _g, int _b) {
        r = _r;
        g = _g;
        b = _b;
    }
    RGBA(int _r, int _g, int _b, int _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
};

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
    void SetPixelColor(int cols, int rows, RGBA rgba);
    void SaveImg(string filename);
    void FillColor(RGBA rgba);
};

void RenderedImg::SetPixelColor(int cols, int rows, RGBA rgba) {
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
