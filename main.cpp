#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "strahl.hpp"

using namespace std;

#define WIDTH 640
#define HEIGHT 480

int main() {
    Object3D scene_obj;
    scene_obj.ImportOBJ("3dObjects/scene.obj");

    Scene scene;
    scene.AddObject(scene_obj, "scene");

    CameraPers camPers(60.0, WIDTH, HEIGHT);
    camPers.Render(scene, "result_pers.ppm");
    // camPers.GetZBuffer(scene, "zbuffer.ppm");

    CameraOrtho camOrtho(-2.0, 2.0, -1.5, 1.5, WIDTH, HEIGHT);
    camOrtho.Render(scene, "result_ortho.ppm");

    return 0;
}