#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "img_handler.hpp"
#include "iostream"
#include "strahl.hpp"

using namespace std;

#define HEIGHT 720
#define WIDTH 1280
#define CHANNEL_NUM 3

int main() {
    Object3D monkey("monkey.obj");
    monkey.SetRotation(vector3d(0, 45, 0));
    monkey.SetPosition(vector3d(0.0, 0.0, -4.0));
    RenderedImg img(WIDTH, HEIGHT, MODE_RGB);
    Scene scene;
    CameraOrtho camera;

    img.FillColor(RGBA(WHITE));
    scene.DrawModelPers(img, monkey, WIREFRAME, RGBA(BLACK));
    img.SaveImg("result.png");

    return 0;
}