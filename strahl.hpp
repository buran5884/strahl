#pragma once

#include "Object.hpp"
#include "utilities.hpp"
#include <vector>

#define CAMERA_PERS 0
#define CAMERA_ORTHO 1

#define WIREFRAME 0
#define SOLID 1

using namespace std;

class Scene;
class Camera;
class CameraOrtho;
class CameraPers;

class Scene {
private:
    vector<CameraPers> camerapersList;
    vector<CameraOrtho> cameraorthoList;
    vector<Object3D> meshmodelList;
    RGBA backgroundColor;

public:
    void DrawModel(RenderedImg& img, Object3D& model, int mode, RGBA rgba);
    void DrawModelPers(RenderedImg& img, Object3D& model, int mode, RGBA rgba);
    void SetBackgroundColor(RenderedImg& img, RGBA rgba);
};

void Scene::DrawModel(RenderedImg& img, Object3D& model, int mode, RGBA rgba) {
    vector2d scale(img.GetWidth() / 6.4, img.GetHeight() / 3.6);
    for (int i = 0; i < model.GetFaceSize(); i++) {
        vector3d vertices[3];
        vector2i screenPoints[3];
        for (int j = 0; j < 3; j++) {
            vertices[j] = model.GetFaceVertex(i, j);
            screenPoints[j] = vector2i(scale.x * (vertices[j].x + 3.2), scale.y * (-vertices[j].y + 1.8));
        }
        img.DrawLine(screenPoints[0], screenPoints[1], rgba);
        img.DrawLine(screenPoints[1], screenPoints[2], rgba);
        img.DrawLine(screenPoints[2], screenPoints[0], rgba);
    }
}

void Scene::DrawModelPers(RenderedImg& img, Object3D& model, int mode, RGBA rgba) {
    double fovy = 30.0;
    double fovx = 60.0;
    double f = 1.0 / (tan((fovx * M_PI / 180.0) / 2.0));
    // double f = 1.0 / (tan((fovy * M_PI / 180.0) / 2.0));
    double aspect = 9.0 / 16.0;
    // double aspect = 16.0 / 9.0;

    double x, y;
    for (int i = 0; i < model.GetFaceSize(); i++) {
        vector3d vertices[3];
        vector2i screenPoints[3];
        for (int j = 0; j < 3; j++) {
            vertices[j] = model.GetFaceVertex(i, j);
            x = (vertices[j].x * f) / -vertices[j].z;
            y = (vertices[j].y * f) / (aspect * -vertices[j].z);
            // x = (vertices[j].x * f) / (aspect * -vertices[j].z);
            // y = (vertices[j].y * f) / -vertices[j].z;
            screenPoints[j] = vector2i(x * img.GetWidth() / 2.0 + img.GetWidth() / 2.0, -y * img.GetHeight() / 2.0 + img.GetHeight() / 2.0);
        }
        img.DrawLine(screenPoints[0], screenPoints[1], rgba);
        img.DrawLine(screenPoints[1], screenPoints[2], rgba);
        img.DrawLine(screenPoints[2], screenPoints[0], rgba);
    }
}

void Scene::SetBackgroundColor(RenderedImg& img, RGBA rgba) {
    // test;
}

class Camera {
private:
    vector3d posision;
    vector2i resolution;

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
    void Capture(Scene scene, string filename);
};

void CameraOrtho::Capture(Scene scene, string filename) {
}