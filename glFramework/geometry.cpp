#include "geometry.h"

Geometry::Geometry() {

}

Geometry::~Geometry() {
    if (mVao != 0) {
        glDeleteVertexArrays(1, &mVao);
    }
    if (mPosVbo != 0) {
        glDeleteBuffers(1, &mPosVbo);
    }
    if (mUvVbo != 0) {
        glDeleteBuffers(1, &mUvVbo);
    }
    if (mEbo != 0) {
        glDeleteBuffers(1, &mEbo);
    }
}

Geometry* Geometry::createBox(float size) {
    Geometry* geometry = new Geometry();
    return geometry;
}

Geometry* Geometry::createSphere(float size) {
    Geometry* geometry = new Geometry();
    return geometry;
}
