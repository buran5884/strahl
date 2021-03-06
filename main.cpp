#include "strahl.hpp"

using namespace std;

#define WIDTH 640
#define HEIGHT 480

int main() {
    Object3D scene_obj;
    scene_obj.ImportOBJ("3dObjects/scene.obj");

    Scene scene;
    scene.AddObject(scene_obj, "scene");

    CameraOrtho camOrtho(-2.0, 2.0, -1.5, 1.5, WIDTH, HEIGHT);
    camOrtho.Render(scene, "ortho.ppm");

    CameraPers camPers(60.0, WIDTH, HEIGHT);
    camPers.Render(scene, "pers.ppm");
    // camPers.GetZBuffer(scene, "zbuffer.ppm");

    return 0;
}