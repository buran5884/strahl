#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "strahl.hpp"

using namespace std;

#define WIDTH 1600
#define HEIGHT 1200

int main() {
    Object3D monkey;
    monkey.ImportOBJ("3dObjects/monkey.obj");

    Scene scene;
    scene.AddObject(monkey, "monkey01");
    scene.SetObjectLocation("monkey01", vector3d(0, 0, -6.0));

    CameraPers cam(60.0, WIDTH, HEIGHT);
    cam.Render(scene, "result.ppm");

    return 0;
}