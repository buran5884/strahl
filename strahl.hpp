#include <vector>

#define CAMERA_PERS 0
#define CAMERA_ORTHO 1

using namespace std;

struct vector3d {
    double x;
    double y;
    double z;
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
