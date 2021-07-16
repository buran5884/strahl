#pragma once

#include "Object.hpp"
#include "img_handler.hpp"
#include "Utilities.hpp"
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
    RGBA backgroundColor;
    vector<Object3D> objects;

public:
    Scene(RGBA rgba) {
        backgroundColor = rgba;
    }
    Scene() {
        backgroundColor = RGBA(255, 255, 255);
    }
    void DrawModel(Image& img, Object3D& model, int mode, RGBA rgba);
    void DrawModelPers(Image& img, RGBA rgba);

    RGBA GetBackgroundColor();
    size_t GetObjectsSize();
    Object3D GetObject(int n);

    void AddObject(Object3D object);
    void SetObjectPosition(uint id, vector3d position);
    void SetObjectRotation(uint id, vector3d rotation);
    void SetObjectScale(uint id, vector3d scale);
};

void Scene::AddObject(Object3D object) {
    int id = objects.size();
    objects.push_back(object);
    objects.back().SetID(id);
}

void Scene::SetObjectPosition(uint id, vector3d position) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].GetID() == id) {
            objects[i].SetPosition(position);
        }
    }
}

void Scene::SetObjectRotation(uint id, vector3d rotation) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].GetID() == id) {
            objects[i].SetRotation(rotation);
        }
    }
}

void Scene::SetObjectScale(uint id, vector3d scale) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].GetID() == id) {
            objects[i].SetScale(scale);
        }
    }
}

size_t Scene::GetObjectsSize() {
    return objects.size();
}

Object3D Scene::GetObject(int n) {
    return objects[n];
}

void Scene::DrawModel(Image& img, Object3D& model, int mode, RGBA rgba) {
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

void Scene::DrawModelPers(Image& img, RGBA rgba) {
    int width = (double)img.GetWidth();
    int height = (double)img.GetHeight();

    Object3D model = objects[0];
    double fovx = 60.0;
    double aspect = (double)width / (double)height;
    double fovy = fovx / aspect;
    double f = 1.0 / (tan((fovy * M_PI / 180.0) / 2.0));

    double x, y;
    for (int i = 0; i < model.GetFaceSize(); i++) {
        vector3d vertices[3];
        vector2i screenPoints[3];
        for (int j = 0; j < 3; j++) {
            vertices[j] = model.GetFaceVertex(i, j);
            x = (vertices[j].x * f) / (aspect * -vertices[j].z);
            y = (vertices[j].y * f) / -vertices[j].z;
            screenPoints[j] = vector2i(x * width / 2.0 + width / 2.0, -y * height / 2.0 + height / 2.0);
        }
        img.DrawLine(screenPoints[0], screenPoints[1], rgba);
        img.DrawLine(screenPoints[1], screenPoints[2], rgba);
        img.DrawLine(screenPoints[2], screenPoints[0], rgba);
    }
}

RGBA Scene::GetBackgroundColor() {
    return backgroundColor;
}

class CameraPers {
private:
    double width;
    double height;
    double aspect;
    double fovX;
    double fovY;
    double zNear;
    double zFar;

    vector3d position;
    vector3d rotation;

    void DrawObject(Image& img, Object3D& object, RGBA rgba);

public:
    CameraPers(double _fovX, int _width, int _height) {
        width = _width;
        height = _height;
        aspect = (double)width / (double)height;
        fovX = _fovX;
        fovY = fovX / aspect;
        position = vector3d(0.0, 0.0, 0.0);
        rotation = vector3d(0.0, 0.0, 0.0);
    }
    void SetFovX(double _fovX);
    void SetFovY(double _fovY);
    void SetPosition(vector3d _position);
    void SetRotation(vector3d _rotation);
    void Render(Scene scene, int mode, string filename);
};

void CameraPers::SetFovX(double _fovX) {
    fovX = _fovX;
    fovY = fovX / aspect;
}

void CameraPers::SetFovY(double _fovY) {
    fovY = _fovY;
    fovX = fovY * aspect;
}

void CameraPers::SetPosition(vector3d _position) {
    position = _position;
}

void CameraPers::SetRotation(vector3d _rotation) {
    rotation = _rotation;
}

void CameraPers::DrawObject(Image& image, Object3D& object, RGBA rgba) {
    int width = (double)image.GetWidth();
    int height = (double)image.GetHeight();
    double f = 1.0 / (tan((fovX * M_PI / 180.0) / 2.0));
    double x, y;
    double a = 1.0 / aspect;
    for (int i = 0; i < object.GetFaceSize(); i++) {
        vector3d vertices[3];
        vector2i screenPoints[3];
        for (int j = 0; j < 3; j++) {
            vertices[j] = object.GetFaceVertex(i, j);
            x = (vertices[j].x * f) / -vertices[j].z;
            y = (vertices[j].y * f) / (a * -vertices[j].z);
            screenPoints[j] = vector2i(x * width / 2.0 + width / 2.0, -y * height / 2.0 + height / 2.0);
        }
        image.DrawLine(screenPoints[0], screenPoints[1], rgba);
        image.DrawLine(screenPoints[1], screenPoints[2], rgba);
        image.DrawLine(screenPoints[2], screenPoints[0], rgba);
    }
}

void CameraPers::Render(Scene scene, int mode, string filename) {
    Image img(width, height, mode);
    img.FillColor(scene.GetBackgroundColor());
    for (int i = 0; i < scene.GetObjectsSize(); i++) {
        Object3D object = scene.GetObject(i);
        DrawObject(img, object, RGBA(BLACK));
    }
    // image.SavePngImg(filename);
    img.SavePpmImg(filename);
}

class CameraOrtho {
private:
    double left;
    double right;
    double bottom;
    double top;
    double zNear;
    double zFar;

public:
    void setParam(double _left, double _right, double _bottom, double _top, double _zNear, double _zFar);
    void Render(Scene scene, string filename);
};