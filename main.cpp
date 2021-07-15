#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "img_handler.hpp"
#include "iostream"
#include "strahl.hpp"

using namespace std;

#define HEIGHT 1440
#define WIDTH 2560
#define CHANNEL_NUM 3

int main() {
    Object3D monkey("monkey.obj");
    RenderedImg img(WIDTH, HEIGHT, MODE_RGBA);
    Scene scene;

    img.FillColor(RGBA(WHITE));
    scene.DrawModel(img, monkey, WIREFRAME, RGBA(BLACK));
    img.SaveImg("result.png");

    return 0;
}
