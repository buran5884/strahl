#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "img_handler.hpp"
#include "iostream"
#include "strahl.hpp"

using namespace std;

#define HEIGHT 1440
#define WIDTH 2560
#define CHANNEL_NUM 3

int rotate(MeshModel& model) {
    return 0;
}

int main() {
    MeshModel monkey("monkey.obj");
    RenderedImg img(WIDTH, HEIGHT, MODE_RGBA);
    Scene scene1;

    for (int i = 0; i <= 90; i += 10) {
        img.FillColor(RGBA(GREEN));
        monkey.rotation(Z_AXIS, i);
        scene1.DrawModel(img, monkey, WIREFRAME, RGBA(BLACK));
        img.SaveImg("result.png");
    }

    for (int i = 0; i <= 90; i += 10) {
        img.FillColor(RGBA(GREEN));
        monkey.rotation(Y_AXIS, i);
        scene1.DrawModel(img, monkey, WIREFRAME, RGBA(BLACK));
        img.SaveImg("result.png");
    }

    return 0;
}
