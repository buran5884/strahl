#include <vector>

#define CAMERA_PERS 0
#define CAMERA_ORTHO 1

using namespace std;

struct RGBA {
    int r;
    int g;
    int b;
    int a;
    RGBA(int _r, int _g, int _b) {
        r = _r;
        g = _g;
        b = _b;
    }
    RGBA(int _r, int _g, int _b, int _a) {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
};

struct vector3d {
    double x;
    double y;
    double z;
};

struct vector2d{
    double u;
    double v;

    vector2d(){}
    vector2d(int _u,int _v){
        u = _u;
        v = _v;
    }
};

class CameraPers {
private:
    int type;
    vector3d pos;
    double fovX;
    double fovY;
    double zNear;
    double zFar;

public:
    void setPosition(vector3d);
};

class CameraOrtho {
private:
    vector3d pos;
    double left;
    double right;
    double bottom;
    double top;
    double zNear;
    double zFar;

public:
    void setPosition(vector3d);
};

class MeshModel {
private:
    bool visibility;
    vector<vector3d> vertices;
    // vector<mesh> meshseIndices;

public:
    void setVisibility(bool visibility);
    void setTranslation();
    void setRotation();
    void setScale();
};

class Scene {
private:
    vector<CameraPers> camerapersList;
    vector<CameraOrtho> cameraorthoList;
    vector<MeshModel> meshmodelList;
};
