//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
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
#include <LibOpenGL/MeshObjects/MeshObject.h>
#include <array>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
namespace NTCodeBase::MeshObjects {
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class CubeObject : public MeshObject {
public:
    CubeObject() { generateCube(); }

    void generateCube() {
        clearData();

        m_Vertices = {
            // right
            Vec3f(   -1.0f,    -1.0f, 1.0f),
            Vec3f(1.0f,        -1.0f, 1.0f),
            Vec3f(1.0f,     1.0f,     1.0f),
            Vec3f(   -1.0f, 1.0f,     1.0f),
            // top
            Vec3f(   -1.0f, 1.0f,     1.0f),
            Vec3f(1.0f,     1.0f,     1.0f),
            Vec3f(1.0f,     1.0f,        -1.0f),
            Vec3f(   -1.0f, 1.0f,        -1.0f),
            // left
            Vec3f(1.0f,        -1.0f,    -1.0f),
            Vec3f(   -1.0f,    -1.0f,    -1.0f),
            Vec3f(   -1.0f, 1.0f,        -1.0f),
            Vec3f(1.0f,     1.0f,        -1.0f),
            // bottom
            Vec3f(   -1.0f,    -1.0f,    -1.0f),
            Vec3f(1.0f,        -1.0f,    -1.0f),
            Vec3f(1.0f,        -1.0f, 1.0f),
            Vec3f(   -1.0f,    -1.0f, 1.0f),
            // back
            Vec3f(   -1.0f,    -1.0f,    -1.0f),
            Vec3f(   -1.0f,    -1.0f, 1.0f),
            Vec3f(   -1.0f, 1.0f,     1.0f),
            Vec3f(   -1.0f, 1.0f,        -1.0f),
            // front
            Vec3f(1.0f,        -1.0f, 1.0f),
            Vec3f(1.0f,        -1.0f,    -1.0f),
            Vec3f(1.0f,     1.0f,        -1.0f),
            Vec3f(1.0f,     1.0f,     1.0f)
        };

        m_VertexNormals = {
            // right
            Vec3f(0.0f,     0.0f,     1.0f),
            Vec3f(0.0f,     0.0f,     1.0f),
            Vec3f(0.0f,     0.0f,     1.0f),
            Vec3f(0.0f,     0.0f,     1.0f),
            // top
            Vec3f(0.0f,     1.0f,     0.0f),
            Vec3f(0.0f,     1.0f,     0.0f),
            Vec3f(0.0f,     1.0f,     0.0f),
            Vec3f(0.0f,     1.0f,     0.0f),
            // left
            Vec3f(0.0f,     0.0f,        -1.0f),
            Vec3f(0.0f,     0.0f,        -1.0f),
            Vec3f(0.0f,     0.0f,        -1.0f),
            Vec3f(0.0f,     0.0f,        -1.0f),
            // bottom
            Vec3f(0.0f,        -1.0f, 0.0f),
            Vec3f(0.0f,        -1.0f, 0.0f),
            Vec3f(0.0f,        -1.0f, 0.0f),
            Vec3f(0.0f,        -1.0f, 0.0f),
            // back
            Vec3f(   -1.0f, 0.0f,     0.0f),
            Vec3f(   -1.0f, 0.0f,     0.0f),
            Vec3f(   -1.0f, 0.0f,     0.0f),
            Vec3f(   -1.0f, 0.0f,     0.0f),
            //front
            Vec3f(1.0f,     0.0f,     0.0f),
            Vec3f(1.0f,     0.0f,     0.0f),
            Vec3f(1.0f,     0.0f,     0.0f),
            Vec3f(1.0f,     0.0f,     0.0f)
        };

        m_VertexTexCoords = {
            // 0
            Vec2f(0.0f, 0.0f),
            Vec2f(1.0f, 0.0f),
            Vec2f(1.0f, 1.0f),
            Vec2f(0.0f, 1.0f),
            // 1
            Vec2f(0.0f, 0.0f),
            Vec2f(1.0f, 0.0f),
            Vec2f(1.0f, 1.0f),
            Vec2f(0.0f, 1.0f),
            // 2
            Vec2f(0.0f, 0.0f),
            Vec2f(1.0f, 0.0f),
            Vec2f(1.0f, 1.0f),
            Vec2f(0.0f, 1.0f),
            // 3
            Vec2f(0.0f, 0.0f),
            Vec2f(1.0f, 0.0f),
            Vec2f(1.0f, 1.0f),
            Vec2f(0.0f, 1.0f),
            // 4
            Vec2f(0.0f, 0.0f),
            Vec2f(1.0f, 0.0f),
            Vec2f(1.0f, 1.0f),
            Vec2f(0.0f, 1.0f),
            // 5
            Vec2f(0.0f, 0.0f),
            Vec2f(1.0f, 0.0f),
            Vec2f(1.0f, 1.0f),
            Vec2f(0.0f, 1.0f)
        };

        m_IndexList = {
            // right
            0,   1,  2,
            2,   3,  0,
            // top
            4,   5,  6,
            6,   7,  4,
            // left
            8,   9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // back
            16, 17, 18,
            18, 19, 16,
            // front
            20, 21, 22,
            22, 23, 20,
        };

        // generate color based on coordinate
        m_VertexColors.resize(0);

        for(size_t i = 0; i < m_Vertices.size(); ++i) {
            m_VertexColors.push_back(0.5f * (m_Vertices[i] + Vec3f(1.0f)));
        }

        ////////////////////////////////////////////////////////////////////////////////
        m_NVertices         = 24;
        m_isDataReady       = true;
        m_hasVertexNormal   = true;
        m_hasVertexTexCoord = true;
        m_hasVertexColor    = true;
        m_hasIndexBuffer    = true;
    }
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
} // end namespace NTCodeBase::MeshObjects
