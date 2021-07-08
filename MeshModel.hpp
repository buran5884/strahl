#pragma once

#include "utilities.hpp"
#include <iostream>
#include <vector>

using namespace std;

class MeshModel {
    vector<vector3d> vertices;
    vector<vector3d> normals;
    vector<vector2d> textures;
    vector<int> faces;

    int loadOBJ(string filename);

public:
    vector3d vertex(size_t index);
    vector3d normal(size_t index);

    vector3d faceVertex(size_t index, int elem);
    vector3d faceNormal(size_t index, int elem);

    size_t vertexSize(void);
    size_t faceSize(void);

    MeshModel(string filename) {
        loadOBJ(filename);
    }
};

vector3d MeshModel::vertex(size_t index) {
    return vertices[index];
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

    return 0;
}