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

#include <cstddef>
#include <LibOpenGL/OpenGLMacros.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class OpenGLBuffer : public OpenGLCallable
{
public:
    OpenGLBuffer() : m_isBufferCreated(false), m_BufferSize(0) {}
    ~OpenGLBuffer() { deleteBuffer(); }

    //-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    void deleteBuffer();
    void createBuffer(GLenum bufferType, size_t bufferSize, const GLvoid* buffData = nullptr, GLenum bufferUsage = GL_STATIC_DRAW);
    void resize(size_t bufferSize);
    void uploadData(const GLvoid* data, size_t offset, size_t dataSize);
    void uploadData(const StdVT<const GLvoid*>& data, size_t offset, const StdVT<size_t>& dataSize);
    void uploadDataAsync(const GLvoid* data, size_t offset, size_t dataSize);
    void uploadDataAsync(const StdVT<const GLvoid*>& data, size_t offset, const StdVT<size_t>& dataSize);
    void bind();
    void bindBufferBase();
    void release();

    GLuint getBufferID() const;
    GLuint getBindingPoint() const;
    size_t getBufferSize() const;
    bool   isCreated() const;

private:
    bool   m_isBufferCreated;
    GLuint m_BufferID;
    GLenum m_BufferType;
    GLenum m_BufferUsage;

    size_t        m_BufferSize;
    GLuint        m_BindingPoint;
    static GLuint s_TotalBindingPoints;
};
