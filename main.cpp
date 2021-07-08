#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "img_handler.hpp"

using namespace std;

#define HEIGHT 300
#define WIDTH 300
#define CHANNEL_NUM 3

int main() {
    RenderedImg img(WIDTH, HEIGHT, MODE_RGB);
    RGBA fillcolor(0, 0, 0);
    img.FillColor(fillcolor);
    vector2d sPoint(0, 0);
    vector2d ePoint(30, 99);
    // img.DrawLine(sPoint, ePoint, RGBA(0, 255, 255));
    img.DrawLine(sPoint, ePoint, RGBA(255, 255, 255));

    RGBA pixelcolor(255, 255, 255);
    img.DrawPixel(sPoint, pixelcolor);
    img.DrawPixel(ePoint, pixelcolor);

    img.SaveImg("result.png");

    return 0;
}
