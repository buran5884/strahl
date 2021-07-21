#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "strahl.hpp"

using namespace std;

#define WIDTH 640
#define HEIGHT 480

int main() {
    Object3D monkey;
    monkey.ImportOBJ("3dObjects/scene.obj");

    Scene scene;
    scene.AddObject(monkey, "monkey01");
    // scene.SetObjectRotation("monkey01", vector3d(0, 0, 90));
    // scene.SetObjectLocation("monkey01", vector3d(0, 0, -3.0));

    CameraPers cam(60.0, WIDTH, HEIGHT);
    cam.Render(scene, "result.ppm");
    cam.GetZBuffer(scene, "zbuffer.ppm");

    return 0;
}