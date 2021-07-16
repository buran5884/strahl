#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.hpp"
#include "iostream"
#include "strahl.hpp"
#include <chrono>

using namespace std;

#define WIDTH 1600
#define HEIGHT 1200

int main() {
    Object3D monkey("3dObjects/monkey.obj");
    Object3D cube("3dObjects/cube.obj");

    Scene scene(RGBA(122, 122, 122));
    scene.AddObject(monkey);
    scene.AddObject(cube);
    scene.SetObjectPosition(0, vector3d(1.6, 0, -6.0));
    scene.SetObjectPosition(1, vector3d(-1.6, 0, -6.0));

    CameraPers cam(60.0, WIDTH, HEIGHT);
    Image img(WIDTH, HEIGHT, MODE_RGB);

    // std::chrono::system_clock::time_point start, end;
    // start = std::chrono::system_clock::now();
    cam.Render(scene, MODE_RGB, "result.ppm");
    // end = std::chrono::system_clock::now();
    // double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    // cout << elapsed << "[ms]" << endl;

    return 0;
}