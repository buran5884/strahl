#include "MeshModel.hpp"
#include "utilities.hpp"
#include <vector>

#define CAMERA_PERS 0
#define CAMERA_ORTHO 1

#define WIREFRAME 0
#define SOLID 1

using namespace std;

class Camera {
private:
    vector3d posision;

public:
    void setPosition(vector3d);
};

class CameraPers : Camera {
private:
    double fovX;
    double fovY;
    double zNear;
    double zFar;

public:
    void setParam(double _fovX, double _fovY, double _zNear, double zFar);
};

class CameraOrtho : Camera {
private:
    double left;
    double right;
    double bottom;
    double top;
    double zNear;
    double zFar;

public:
    void setParam(double _left, double _right, double _bottom, double _top, double _zNear, double _zFar);
};

class Scene {
private:
    vector<CameraPers> camerapersList;
    vector<CameraOrtho> cameraorthoList;
    vector<MeshModel> meshmodelList;

public:
    void DrawModel(RenderedImg& img, MeshModel& model, int mode, RGBA rgba);
    void SetBackgroundColor(RenderedImg& img, RGBA rgba);
};

void Scene::DrawModel(RenderedImg& img, MeshModel& model, int mode, RGBA rgba) {
    vector2d scale(img.GetWidth() / 6.4, img.GetHeight() / 3.6);
    for (int i = 0; i < model.faceSize(); i++) {
        vector3d vertices[3];
        vector2i screenPoints[3];
        for (int j = 0; j < 3; j++) {
            vertices[j] = model.faceVertex(i, j);
            screenPoints[j] = vector2i(scale.x * (vertices[j].x + 3.2), scale.y * (-vertices[j].y + 1.8));
        }
        img.DrawLine(screenPoints[0], screenPoints[1], rgba);
        img.DrawLine(screenPoints[1], screenPoints[2], rgba);
        img.DrawLine(screenPoints[2], screenPoints[0], rgba);
    }
}

void Scene::SetBackgroundColor(RenderedImg& img, RGBA rgba) {
    // test;
}