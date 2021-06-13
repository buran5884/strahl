#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "strahl.hpp"

using namespace std;

#define HEIGHT 10
#define WIDTH 10
#define CHANNEL_NUM 3

int main() {
    RenderedImg img(WIDTH, HEIGHT, MODE_RGBA);
    img.FillColor({ 128, 128, 128, 0 });
    img.SetPixelColor(9, 9, { 0, 255, 255, 255 });
    img.SaveImg("result.png");

    return 0;
}