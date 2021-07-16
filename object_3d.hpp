#pragma once

#include "utilities.hpp"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Object3D {
    int id;

    vector3d location;
    vector3d rotation;
    vector3d scale;

    vector<vector3d> originalVertex;
    vector<vector3d> vertices;
    vector<vector3d> normals;
    vector<vector2d> textures;
    vector<int> faces;

    int LoadOBJ(string filename);
    void SetVertex(size_t index, vector3d location);

public:
    Object3D(string filename) {
        id = -1;
        LoadOBJ(filename);
    }

    int GetID();
    vector3d GetVertex(size_t index);
    vector3d GetOriginalVertex(size_t index);
    vector3d GetNormal(size_t index);

    vector3d GetFaceVertex(size_t index, int elem);
    vector3d GetFaceNormal(size_t index, int elem);

    size_t GetVertexSize(void);
    size_t GetFaceSize(void);

    void SetID(int _id);
    void SetPosition(vector3d _position);
    void SetRotation(vector3d _rotation);
    void SetScale(vector3d _scale);
};

int Object3D::GetID() {
    return id;
}

void Object3D::SetID(int _id){
    id = _id;
}

void Object3D::SetPosition(vector3d _position) {
    location = _position;
    for (int i = 0; i < GetVertexSize(); i++) {
        double x = GetVertex(i).x + location.x;
        double y = GetVertex(i).y + location.y;
        double z = GetVertex(i).z + location.z;
        SetVertex(i, vector3d(x, y, z));
    }
}

void Object3D::SetRotation(vector3d _rotation) {
    rotation = _rotation;
    double a = rotation.x * M_PI / 180.0;
    double b = rotation.y * M_PI / 180.0;
    double c = rotation.z * M_PI / 180.0;

    double x0, y0, z0;
    double x, y, z;
    double rotMatrix[9];
    rotMatrix[0] = cos(c) * cos(b);
    rotMatrix[1] = cos(c) * sin(b) * sin(a) - sin(c) * cos(a);
    rotMatrix[2] = cos(c) * sin(b) * cos(a) + sin(c) * sin(a);
    rotMatrix[3] = sin(c) * cos(b);
    rotMatrix[4] = sin(c) * sin(b) * sin(a) + cos(c) * cos(a);
    rotMatrix[5] = sin(c) * sin(b) * cos(a) - cos(c) * sin(a);
    rotMatrix[6] = -sin(b);
    rotMatrix[7] = cos(b) * sin(a);
    rotMatrix[8] = cos(b) * cos(a);

    for (int i = 0; i < GetVertexSize(); i++) {
        x0 = GetOriginalVertex(i).x;
        y0 = GetOriginalVertex(i).y;
        z0 = GetOriginalVertex(i).z;
        x = x0 * rotMatrix[0] + y0 * rotMatrix[1] + z0 * rotMatrix[2];
        y = x0 * rotMatrix[3] + y0 * rotMatrix[4] + z0 * rotMatrix[5];
        z = x0 * rotMatrix[6] + y0 * rotMatrix[7] + z0 * rotMatrix[8];
        SetVertex(i, vector3d(x, y, z));
    }
}

void Object3D::SetScale(vector3d _scale) {
    scale = _scale;
    for (int i = 0; i < GetVertexSize(); i++) {
        double x = GetVertex(i).x * scale.x;
        double y = GetVertex(i).y * scale.y;
        double z = GetVertex(i).z * scale.z;
        SetVertex(i, vector3d(x, y, z));
    }
}

void Object3D::SetVertex(size_t index, vector3d location) {
    vertices[index] = location;
}

vector3d Object3D::GetVertex(size_t index) {
    return vertices[index];
}

vector3d Object3D::GetOriginalVertex(size_t index) {
    return originalVertex[index];
}

vector3d Object3D::GetNormal(size_t index) {
    return normals[index];
}

vector3d Object3D::GetFaceVertex(size_t index, int elem) {
    return vertices[faces[index * 10 + elem * 3] - 1];
}

vector3d Object3D::GetFaceNormal(size_t index, int elem) {
    return normals[faces[index * 10 + elem * 2] - 1];
}

size_t Object3D::GetVertexSize() {
    return vertices.size();
}

size_t Object3D::GetFaceSize() {
    return faces.size() / 10;
}

int Object3D::LoadOBJ(string filename) {
    FILE* fp;
    if ((fp = fopen((char*)filename.c_str(), "r")) == NULL) {
        return 1;
    }

    vector3d v, n;
    vector2d t;
    int f[10] = {};

    int mtl_number = -1;
    char line[128], mtl[56];

    while (fgets(line, sizeof(line), fp) != NULL) {
        switch (line[0]) {
        case 'v':
            switch (line[1]) {
            case ' ':
                sscanf(line, "v %lf %lf %lf", &v.x, &v.y, &v.z);
                Object3D::vertices.push_back(v);
                break;

            case 't':
                //OBJ::defUV = true;
                sscanf(line, "vt %lf %lf", &t.x, &t.y);
                Object3D::textures.push_back(t);
                break;

            case 'n':
                //OBJ::defNormal = true;
                sscanf(line, "vn %lf %lf %lf", &n.x, &n.y, &n.z);
                Object3D::normals.push_back(n);
                break;

            default:
                break;
            }
            break;

        case 'u':
            break;

        case 'f':
            if (sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7], &f[8]) == 9) {
                // v/t/n
            } else if (sscanf(line, "f %d//%d %d//%d %d//%d", &f[0], &f[2], &f[3], &f[5], &f[6], &f[8]) == 6) {
                // v//n
            } else if (sscanf(line, "f %d/%d %d/%d %d/%d", &f[0], &f[1], &f[3], &f[4], &f[6], &f[7]) == 6) {
                // v/t
            } else if (sscanf(line, "f %d %d %d", &f[0], &f[3], &f[6]) == 3) {
                // v
            }
            Object3D::faces.insert(faces.end(), f, f + 10);
            break;

        default:
            break;
        }
    }
    copy(vertices.begin(), vertices.end(), back_inserter(originalVertex));

    return 0;
}