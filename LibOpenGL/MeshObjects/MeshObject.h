﻿//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//    .--------------------------------------------------.
//    |  This file is part of NTCodeBase                 |
//    |  Created 2018 by NT (https://ttnghia.github.io)  |
//    '--------------------------------------------------'
//                            \o/
//                             |
//                            / |
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#pragma once

#include <LibCommon/CommonSetup.h>
#include <LibOpenGL/OpenGLMacros.h>
#include <LibOpenGL/OpenGLBuffer.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
namespace NTCodeBase::MeshObjects {
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class MeshObject : public OpenGLCallable {
public:
    MeshObject(GLenum dataTopology = GL_TRIANGLES, bool isMeshVeryLarge = false) : m_DataTopology(dataTopology), m_isMeshVeryLarge(isMeshVeryLarge) {}
    virtual ~MeshObject();

    // for multiple transformation, one may need to have original position of vertices
    void backupVertices() { m_VerticesBackup = m_Vertices; }
    void restoreVertices() { m_Vertices = m_VerticesBackup; }

    void transform(const Vec3f& translation, const Vec3f& scale);
    void transform(const Vec3f& translation, const Vec3f& scale, const Vec3f& rotation);
    void translate(const Vec3f& translation);
    void scale(const Vec3f& scale);
    void rotate(const Vec3f& rotation);

    void setVertices(const StdVT<Vec3f>& vertices);
    void setVertices(const StdVT<GLfloat>& vertices);
    void setVertices(void* vertexData, size_t dataSize);

    void setVertexNormal(const StdVT<Vec3f>& normals);
    void setVertexNormal(const StdVT<GLfloat>& normals);
    void setVertexNormal(void* normalData, size_t dataSize);
    void inverseVertexNormal();
    void clearVertexNormal();

    void setVertexTexCoord(const StdVT<Vec2f>& texcoords);
    void setVertexTexCoord(const StdVT<GLfloat>& texcoords);
    void setVertexTexCoord(void* texData, size_t dataSize);
    void scaleVertexTexCoord(GLfloat scaleX, GLfloat scaleY);
    void clearVertexTexCoord();

    void setVertexColor(const StdVT<Vec3f>& vcolors);
    void setVertexColor(const StdVT<GLfloat>& vcolors);
    void setVertexColor(void* colorData, size_t dataSize);
    void generateRandomVertexColor();
    void clearVertexColor();

    void setElementIndex(const StdVT<GLushort>& indices);
    void clearElementIndex();
    void setElementIndex(const StdVT<GLuint>& indices);
    void clearElementIndexLong();

    ////////////////////////////////////////////////////////////////////////////////
    void setCullFaceMode(GLenum cullFaceMode) { m_CullFaceMode = cullFaceMode; }
    void draw();
    void uploadDataToGPU();

    void clearData();
    bool   isEmpty() const { return !m_isDataReady; }
    size_t getNVertices() const { return m_NVertices; }

    const auto& getIndexList() const { return m_IndexList; }
    const auto& getIndexListLong() const { return m_IndexListLong; }
    const auto& getVertices() const { return m_Vertices; }
    const auto& getVertexNormals() const { return m_VertexNormals; }
    const auto& getVertexTexCoords() const { return m_VertexTexCoords; }
    const auto& getVertexColors() const { return m_VertexColors; }

    const SharedPtr<OpenGLBuffer>& getIndexBuffer() const { return m_IndexBuffer; }
    const SharedPtr<OpenGLBuffer>& getVertexBuffer() const { return m_VertexBuffer; }
    const SharedPtr<OpenGLBuffer>& getNormalBuffer() const { return m_NormalBuffer; }
    const SharedPtr<OpenGLBuffer>& getTexCoordBuffer() const { return m_TexCoordBuffer; }
    const SharedPtr<OpenGLBuffer>& getVertexColorBuffer() const { return m_VertexColorBuffer; }

    bool hasVertexNormal() const { return m_hasVertexNormal; }
    bool hasVertexTexCoord() const { return m_hasVertexTexCoord; }
    bool hasVertexColor() const { return m_hasVertexColor; }
    bool hasIndexBuffer() const { return m_hasIndexBuffer; }

protected:
    void createBuffers();

    ////////////////////////////////////////////////////////////////////////////////
    SharedPtr<OpenGLBuffer> m_VertexBuffer      = nullptr;
    SharedPtr<OpenGLBuffer> m_NormalBuffer      = nullptr;
    SharedPtr<OpenGLBuffer> m_TexCoordBuffer    = nullptr;
    SharedPtr<OpenGLBuffer> m_VertexColorBuffer = nullptr;
    SharedPtr<OpenGLBuffer> m_IndexBuffer       = nullptr;

    StdVT<GLushort> m_IndexList;
    StdVT<GLuint>   m_IndexListLong;
    StdVT<Vec3f>    m_Vertices;
    StdVT<Vec3f>    m_VerticesBackup;
    StdVT<Vec3f>    m_VertexNormals;
    StdVT<Vec2f>    m_VertexTexCoords;
    StdVT<Vec3f>    m_VertexColors;

    size_t m_NVertices    = 0;
    GLenum m_DataTopology = GL_TRIANGLES;
    GLenum m_CullFaceMode = GL_NONE;

    bool m_isMeshVeryLarge = false;
    bool m_isDataReady     = false;
    bool m_isBufferCreated = false;
    bool m_isGLDataReady   = false;
    bool m_bTranslation    = false;
    bool m_bScale          = false;
    bool m_bRotate         = false;

    bool m_hasVertexNormal   = false;
    bool m_hasVertexTexCoord = false;
    bool m_hasVertexColor    = false;
    bool m_hasIndexBuffer    = false;

    Vec3f m_Translation = Vec3f(0);
    Vec3f m_Scale       = Vec3f(1);
    Vec3f m_Rotation    = Vec3f(0);
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
} // end namespace NTCodeBase::MeshObjects
