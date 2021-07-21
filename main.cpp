#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "strahl.hpp"

using namespace std;

#define WIDTH 640
#define HEIGHT 480

int main() {
    Object3D scene_object;
    scene_object.ImportOBJ("3dObjects/scene.obj");

    Scene scene;
    scene.AddObject(scene_object, "scene");

    CameraPers cam_pers(60.0, WIDTH, HEIGHT);
    cam_pers.Render(scene, "result_pers.ppm");
    
    CameraOrtho cam_ortho(-1.5, 1.5, -2.0, 2.0, WIDTH, HEIGHT);
    cam_ortho.Render(scene, "result_ortho.ppm");

    return 0;
}