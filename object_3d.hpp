#pragma once
#include "utilities.hpp"

using namespace std;

class Object3D {
    vector3d location;
    vector3d rotation;
    vector3d scale;
    string objectName;

    vector<vector3d> originalVertex;
    vector<vector3d> vertices;
    vector<vector3d> normals;
    vector<vector2d> textures;
    vector<int> faces;
    vector<edge> edges;
    vector<face> faces_test;

    void SetVertex(size_t index, vector3d location);

public:
    Object3D() { }

    int ImportOBJ(string filename);

    vector3d GetVertex(size_t index);
    edge GetEdge(size_t index);
    vector3d GetOriginalVertex(size_t index);
    vector3d GetNormal(size_t index);

    vector3d GetFaceVertex(size_t index, int elem);
    vector3d GetFaceNormal(size_t index, int elem);

    size_t GetVertexSize(void);
    size_t GetEdgeSize(void);
    size_t GetFaceSize(void);
    string GetObjectName(void);

    void SetObjectName(string name);
    void SetLocation(vector3d _location);
    void SetRotation(vector3d _rotation);
    void SetScale(vector3d _scale);
};

string Object3D::GetObjectName(void) {
    return objectName;
}

void Object3D::SetObjectName(string name) {
    objectName = name;
}

void Object3D::SetLocation(vector3d _location) {
    location = _location;
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
    // return vertices[faces[index * 10 + elem * 3] - 1];
    return vertices[faces_test[index].vertices[elem]];
}

vector3d Object3D::GetFaceNormal(size_t index, int elem) {
    return normals[faces[index * 10 + elem * 2] - 1];
}

size_t Object3D::GetVertexSize() {
    return vertices.size();
}

size_t Object3D::GetEdgeSize() {
    return edges.size();
}

edge Object3D::GetEdge(size_t index) {
    return edges[index];
}

size_t Object3D::GetFaceSize() {
    return faces.size() / 10;
}

int Object3D::ImportOBJ(string filename) {
    FILE* fp;
    if ((fp = fopen((char*)filename.c_str(), "r")) == NULL) {
        cout << filename << "does not exist." << endl;
        return 1;
    }

    vector3d v, n;
    vector2d t;
    int f[10] = {};
    edge temp_edge[3];
    size_t e1, e2, e3;

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

            temp_edge[0].setEdge(f[0] - 1, f[3] - 1);
            temp_edge[1].setEdge(f[3] - 1, f[6] - 1);
            temp_edge[2].setEdge(f[6] - 1, f[0] - 1);

            if (edges.size() != 0) {
                size_t size = edges.size();
                e1 = -1;
                e2 = -1;
                e3 = -1;
                for (size_t i = 0; i < size; i++) {
                    if (temp_edge[0] == edges[i]) {
                        e1 = i;
                    }
                    if (temp_edge[1] == edges[i]) {
                        e2 = i;
                    }
                    if (temp_edge[2] == edges[i]) {
                        e3 = i;
                    }
                }
                if (e1 == -1) {
                    edges.push_back(temp_edge[0]);
                    e1 = edges.size() - 1;
                }
                if (e2 == -1) {
                    edges.push_back(temp_edge[1]);
                    e2 = edges.size() - 1;
                }
                if (e3 == -1) {
                    edges.push_back(temp_edge[2]);
                    e3 = edges.size() - 1;
                }
            } else {
                for (int i = 0; i < 3; i++)
                    edges.push_back(temp_edge[i]);
                e1 = 0;
                e2 = 1;
                e3 = 2;
            }
            faces_test.push_back(face(f[0] - 1, f[3] - 1, f[6] - 1, edges[e1], edges[e2], edges[e3]));
            break;

        default:
            break;
        }
    }
    copy(vertices.begin(), vertices.end(), back_inserter(originalVertex));

    return 0;
}