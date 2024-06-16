#include "geometry.h"
#include "wrapper/checkError.h"

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
    geometry->mIndicesCount = 36;

    float halfSize = size / 2.0f;

    float positions[] = {
        // 前面
        -halfSize, -halfSize,  halfSize,  // 左下
        halfSize, -halfSize,  halfSize,  // 右下
        halfSize,  halfSize,  halfSize,  // 右上
        -halfSize,  halfSize,  halfSize,  // 左上

        // 后面
        -halfSize, -halfSize, -halfSize,  // 左下
        halfSize, -halfSize, -halfSize,  // 右下
        halfSize,  halfSize, -halfSize,  // 右上
        -halfSize,  halfSize, -halfSize,  // 左上

        // 左面
        -halfSize, -halfSize, -halfSize,  // 后下
        -halfSize,  halfSize, -halfSize,  // 后上
        -halfSize,  halfSize,  halfSize,  // 前上
        -halfSize, -halfSize,  halfSize,  // 前下

        // 右面
        halfSize, -halfSize, -halfSize,  // 后下
        halfSize,  halfSize, -halfSize,  // 后上
        halfSize,  halfSize,  halfSize,  // 前上
        halfSize, -halfSize,  halfSize,  // 前下

        // 上面
        -halfSize,  halfSize, -halfSize,  // 左后
        halfSize,  halfSize, -halfSize,  // 右后
        halfSize,  halfSize,  halfSize,  // 右前
        -halfSize,  halfSize,  halfSize,  // 左前

        // 下面
        -halfSize, -halfSize, -halfSize,  // 左后
        halfSize, -halfSize, -halfSize,  // 右后
        halfSize, -halfSize,  halfSize,  // 右前
        -halfSize, -halfSize,  halfSize,  // 左前
    };

    float uvs[] = {
        // 前面
        0.0f, 0.0f,  // 左下
        1.0f, 0.0f,  // 右下
        1.0f, 1.0f,  // 右上
        0.0f, 1.0f,  // 左上

        // 后面
        0.0f, 0.0f,  // 左下
        1.0f, 0.0f,  // 右下
        1.0f, 1.0f,  // 右上
        0.0f, 1.0f,  // 左上

        // 左面
        0.0f, 0.0f,  // 后下
        1.0f, 1.0f,  // 后上
        1.0f, 1.0f,  // 前上
        0.0f, 0.0f,  // 前下

        // 右面
        0.0f, 0.0f,  // 后下
        1.0f, 1.0f,  // 后上
        1.0f, 1.0f,  // 前上
        0.0f, 0.0f,  // 前下

        // 上面
        0.0f, 1.0f,  // 左后
        1.0f, 1.0f,  // 右后
        1.0f, 0.0f,  // 右前
        0.0f, 0.0f,  // 左前

        // 下面
        0.0f, 0.0f,  // 左后
        1.0f, 0.0f,  // 右后
        1.0f, 1.0f,  // 右前
        0.0f, 1.0f,  // 左前
    };

    unsigned int indices[] = {
        // 前面
        0, 1, 2,
        2, 3, 0,

        // 后面
        4, 5, 6,
        6, 7, 4,

        // 左面
        8, 9, 10,
        10, 11, 8,

        // 右面
        12, 13, 14,
        14, 15, 12,

        // 上面
        16, 17, 18,
        18, 19, 16,

        // 下面
        20, 21, 22,
        22, 23, 20,
    };

    // Position VBO
    GL_CALL(glGenBuffers(1, &geometry->mPosVbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    // UV VBO
    glGenBuffers(1, &geometry->mUvVbo);
    glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    // EBO
    GL_CALL(glGenBuffers(1, &geometry->mEbo));
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo));
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

    // VAO
    GL_CALL(glGenVertexArrays(1, &geometry->mVao));
    GL_CALL(glBindVertexArray(geometry->mVao));

    // VAO bidings
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo));
    GL_CALL(glEnableVertexAttribArray(1));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0));

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo));

    // unbind vao
    GL_CALL(glBindVertexArray(0));

    return geometry;
}

Geometry* Geometry::createSphere(float size) {
    Geometry* geometry = new Geometry();
    return geometry;
}
