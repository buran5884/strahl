#pragma once

#include "utilities.hpp"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class MeshModel {
    vector<vector3d> vertices_origin;
    vector<vector3d> vertices;
    vector<vector3d> normals;
    vector<vector2d> textures;
    vector<int> faces;

    int loadOBJ(string filename);
    void setVertex(size_t index, vector3d location);

public:
    vector3d vertex(size_t index);
    vector3d vertex_origin(size_t index);
    vector3d normal(size_t index);

    vector3d faceVertex(size_t index, int elem);
    vector3d faceNormal(size_t index, int elem);

    size_t vertexSize(void);
    size_t faceSize(void);

    void translation(vector3d location);
    void rotation(int axis, double angle);

    MeshModel(string filename) {
        loadOBJ(filename);
    }
};

void MeshModel::translation(vector3d location) {
    for (int i = 0; i < vertexSize(); i++) {
        double x = vertex(i).x + location.x;
        double y = vertex(i).y + location.y;
        double z = vertex(i).z + location.z;
        setVertex(i, vector3d(x, y, z));
    }
}

void MeshModel::rotation(int axis, double degree) {
    double theta = degree * M_PI / 180.0;
    double x, y, z;
    for (int i = 0; i < vertexSize(); i++) {
        switch (axis) {
        case X_AXIS:
            x = vertex_origin(i).x;
            y = vertex_origin(i).y * cos(theta) - vertex_origin(i).z * sin(theta);
            z = vertex_origin(i).y * sin(theta) + vertex_origin(i).z * cos(theta);
            break;

        case Y_AXIS:
            x = vertex_origin(i).x * cos(theta) + vertex_origin(i).z * sin(theta);
            y = vertex_origin(i).y;
            z = -vertex_origin(i).x * sin(theta) + vertex_origin(i).z * cos(theta);
            break;

        case Z_AXIS:
            x = vertex_origin(i).x * cos(theta) - vertex_origin(i).y * sin(theta);
            y = vertex_origin(i).x * sin(theta) + vertex_origin(i).y * cos(theta);
            z = vertex_origin(i).z;
            break;

        default:
            break;
        }
        setVertex(i, vector3d(x, y, z));
    }
    x = 0.0, y = 0.0, z = 0.0;
}

void MeshModel::setVertex(size_t index, vector3d location) {
    vertices[index] = location;
}

vector3d MeshModel::vertex(size_t index) {
    return vertices[index];
}

vector3d MeshModel::vertex_origin(size_t index) {
    return vertices_origin[index];
}

vector3d MeshModel::normal(size_t index) {
    return normals[index];
}

vector3d MeshModel::faceVertex(size_t index, int elem) {
    return vertices[faces[index * 10 + elem * 3] - 1];
}

vector3d MeshModel::faceNormal(size_t index, int elem) {
    return normals[faces[index * 10 + elem * 2] - 1];
}

size_t MeshModel::vertexSize() {
    return vertices.size();
}

size_t MeshModel::faceSize() {
    return faces.size() / 10;
}

int MeshModel::loadOBJ(string filename) {
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
                MeshModel::vertices.push_back(v);
                break;

            case 't':
                //OBJ::defUV = true;
                sscanf(line, "vt %lf %lf", &t.x, &t.y);
                MeshModel::textures.push_back(t);
                break;

            case 'n':
                //OBJ::defNormal = true;
                sscanf(line, "vn %lf %lf %lf", &n.x, &n.y, &n.z);
                MeshModel::normals.push_back(n);
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
            MeshModel::faces.insert(faces.end(), f, f + 10);
            break;

        default:
            break;
        }
    }
    copy(vertices.begin(), vertices.end(), back_inserter(vertices_origin));

    return 0;
}