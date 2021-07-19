#pragma once

#include "image.hpp"
#include "object_3d.hpp"
#include "utilities.hpp"

#define CAMERA_PERS 0
#define CAMERA_ORTHO 1

#define WIREFRAME 0
#define SOLID 1

using namespace std;

class Scene;
class CameraOrtho;
class CameraPers;

class Scene {
private:
    RGB backgroundColor;
    vector<Object3D> objects;

public:
    Scene(RGB rgba) {
        backgroundColor = rgba;
    }
    Scene() {
        backgroundColor = RGB(255, 255, 255);
    }
    void DrawModel(Image& img, Object3D& model, int mode, RGB rgba);
    void DrawModelPers(Image& img, RGB rgba);

    RGB GetBackgroundColor();
    size_t GetObjectsSize();
    Object3D GetObject(int n);

    void AddObject(Object3D object, string name);
    void SetObjectLocation(string name, vector3d location);
    void SetObjectRotation(string name, vector3d rotation);
    void SetObjectScale(string name, vector3d scale);
};

void Scene::AddObject(Object3D object, string name) {
    int id = objects.size();
    objects.push_back(object);
    objects.back().SetObjectName(name);
}

void Scene::SetObjectLocation(string name, vector3d location) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].GetObjectName() == name) {
            objects[i].SetLocation(location);
        }
    }
}

void Scene::SetObjectRotation(string name, vector3d rotation) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].GetObjectName() == name) {
            objects[i].SetRotation(rotation);
        }
    }
}

void Scene::SetObjectScale(string name, vector3d scale) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i].GetObjectName() == name) {
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

RGB Scene::GetBackgroundColor() {
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

    vector3d location;
    vector3d rotation;

    void DrawObject(Image& img, Object3D& object, RGB rgba);

public:
    CameraPers(double _fovX, int _width, int _height) {
        width = _width;
        height = _height;
        aspect = (double)width / (double)height;
        fovX = _fovX;
        fovY = 2.0 * atan(tan(fovX * M_PI / 360.0) / aspect) * 180.0 / M_PI;
        location = vector3d(0.0, 0.0, 0.0);
        rotation = vector3d(0.0, 0.0, 0.0);
        zNear = 2.0;
        zFar = 4.0;
    }
    void SetFovX(double _fovX);
    void SetFovY(double _fovY);
    void SetLocation(vector3d _location);
    void SetRotation(vector3d _rotation);
    void Render(Scene scene, string filename);
    void GetZBuffer(Scene scene, string filename);
};

void CameraPers::SetFovX(double _fovX) {
    fovX = _fovX;
    fovY = 2.0 * atan(tan(fovX * M_PI / 360.0) / aspect) * 180.0 / M_PI;
}

void CameraPers::SetFovY(double _fovY) {
    fovY = _fovY;
    fovY = 2.0 * atan(tan(fovY * M_PI / 360.0) * aspect) * 180.0 / M_PI;
}

void CameraPers::SetLocation(vector3d _location) {
    location = _location;
}

void CameraPers::SetRotation(vector3d _rotation) {
    rotation = _rotation;
}

void CameraPers::DrawObject(Image& image, Object3D& object, RGB rgba) {
    int width = (double)image.GetWidth();
    int height = (double)image.GetHeight();
    double f = 1.0 / (tan((fovX * M_PI / 180.0) / 2.0));
    double x, y;

    for (int i = 0; i < object.GetEdgeSize(); i++) {
        vector3d vertices[2];
        vector2i p[2];
        for (int j = 0; j < 2; j++) {
            vertices[j] = object.GetVertex(object.GetEdge(i).v[j]);
            x = vertices[j].x * f / -vertices[j].z;
            y = vertices[j].y * f * aspect / -vertices[j].z;
            p[j] = vector2i(x * width / 2.0 + width / 2.0, -y * height / 2.0 + height / 2.0);
        }
        image.DrawLine(p[0], p[1], rgba);
    }
}

void CameraPers::Render(Scene scene, string filename) {
    Image img(width, height);
    img.FillColor(scene.GetBackgroundColor());
    for (int i = 0; i < scene.GetObjectsSize(); i++) {
        Object3D object = scene.GetObject(i);
        DrawObject(img, object, RGB(BLACK));
    }
    img.SavePpmImg(filename);
}

void CameraPers::GetZBuffer(Scene scene, string filename) {
    Image img(width, height);
    img.FillColor(RGB(255, 255, 255));
    vector3d origin = vector3d(0, 0, 0);
    vector3d screenPoint;

    vector3d ray;
    double wc = zNear * tan(fovX * M_PI / 360.0);
    double hc = zNear * tan(fovY * M_PI / 360.0);
    screenPoint.z = -zNear;

    for (int cols = 0; cols < width; cols++) {
        for (int rows = 0; rows < height; rows++) {
            screenPoint.x = wc * ((2 * (double)cols / width) - 1.0);
            screenPoint.y = -hc * ((2 * (double)rows / height) - 1.0);
            ray = screenPoint - origin;

            for (int m = 0; m < scene.GetObjectsSize(); m++) {
                Object3D object = scene.GetObject(m);
                for (int k = 0; k < object.GetFaceSize(); k++) {
                    vector3d v[3];
                    for (int l = 0; l < 3; l++)
                        v[l] = object.GetFaceVertex(k, l);
                    vector3d point = hitTriangle(origin, ray, v[0], v[1], v[2]);
                    if (!(point == origin)) {
                        double z = vector3d(point - origin).length();
                        double _z = (zFar + zNear) / (zFar - zNear) + (-2.0 * zFar * zNear) / (z * (zFar - zNear));
                        int color = 255.0 * (_z + 1.0) / 2.0;
                        if (color < img.GetPixel(cols, rows).r)
                            img.SetPixel(vector2i(cols, rows), RGB(color, color, color));
                    }
                }
            }
        }
    }
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
    void Render(Scene scene, string filename);
};