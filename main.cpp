#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "img_handler.hpp"
#include "strahl.hpp"

using namespace std;

#define HEIGHT 10
#define WIDTH 10
#define CHANNEL_NUM 3

int main() {
    RenderedImg img(WIDTH, HEIGHT, MODE_RGB);
    RGBA fillcolor(0, 0, 0);
    RGBA pixelcolor(0, 255, 255);
    img.FillColor(fillcolor);
    img.SetPixelColor(9, 9, pixelcolor);
    img.SaveImg("result.png");

    return 0;
}
