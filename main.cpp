#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "img_handler.hpp"

using namespace std;

#define HEIGHT 480
#define WIDTH 720
#define CHANNEL_NUM 3

int main() {
    RenderedImg img(WIDTH, HEIGHT, MODE_RGB);
    img.FillColor({ 255, 255, 255 });
    img.SetPixelColor(9, 9, { 0, 255, 255 });
    img.SaveImg("result.png");

    return 0;
}