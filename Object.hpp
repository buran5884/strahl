#pragma once

#include "utilities.hpp"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Object3D {
    vector<vector3d> originalVertex;
    vector<vector3d> vertices;
    vector<vector3d> normals;
    vector<vector2d> textures;
    vector<int> faces;

    int LoadOBJ(string filename);
    void SetVertex(size_t index, vector3d location);

public:
    vector3d GetVertex(size_t index);
    vector3d GetOriginalVertex(size_t index);
    vector3d GetNormal(size_t index);

    vector3d GetFaceVertex(size_t index, int elem);
    vector3d GetFaceNormal(size_t index, int elem);

    size_t GetVertexSize(void);
    size_t GetFaceSize(void);

    void Translation(vector3d location);
    void Rotation(int axis, double angle);

    Object3D(string filename) {
        LoadOBJ(filename);
    }
};

void Object3D::Translation(vector3d location) {
    for (int i = 0; i < GetVertexSize(); i++) {
        double x = GetVertex(i).x + location.x;
        double y = GetVertex(i).y + location.y;
        double z = GetVertex(i).z + location.z;
        SetVertex(i, vector3d(x, y, z));
    }
}

void Object3D::Rotation(int axis, double degree) {
    double theta = degree * M_PI / 180.0;
    double x, y, z;
    for (int i = 0; i < GetVertexSize(); i++) {
        switch (axis) {
        case X_AXIS:
            x = GetOriginalVertex(i).x;
            y = GetOriginalVertex(i).y * cos(theta) - GetOriginalVertex(i).z * sin(theta);
            z = GetOriginalVertex(i).y * sin(theta) + GetOriginalVertex(i).z * cos(theta);
            break;

        case Y_AXIS:
            x = GetOriginalVertex(i).x * cos(theta) + GetOriginalVertex(i).z * sin(theta);
            y = GetOriginalVertex(i).y;
            z = -GetOriginalVertex(i).x * sin(theta) + GetOriginalVertex(i).z * cos(theta);
            break;

        case Z_AXIS:
            x = GetOriginalVertex(i).x * cos(theta) - GetOriginalVertex(i).y * sin(theta);
            y = GetOriginalVertex(i).x * sin(theta) + GetOriginalVertex(i).y * cos(theta);
            z = GetOriginalVertex(i).z;
            break;

        default:
            break;
        }
        SetVertex(i, vector3d(x, y, z));
    }
    x = 0.0, y = 0.0, z = 0.0;
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
    puts("hoge");

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