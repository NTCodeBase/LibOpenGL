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

#include <LibOpenGL/OpenGLTexture.h>
#include <future>
#include <vector>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
namespace NTCodeBase {
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::createTexture(GLenum textureTarget) {
    assert(!m_bTextureCreated);
    glCall(glGenTextures(1, &m_TextureID));
    m_bTextureCreated = true;
    m_TexureTarget    = textureTarget;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::generateMipMap() {
    assert(m_bTextureCreated);
    bind();
    glCall(glGenerateMipmap(m_TexureTarget));
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::uploadData(GLenum texTarget, GLint internalFormat, GLsizei width, GLsizei height, GLenum dataFormat, GLenum dataType, const GLvoid* data) {
    assert(m_bTextureCreated);
    bind();
    glCall(glTexImage2D(texTarget, 0, internalFormat, width, height, 0, dataFormat, dataType, data));
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::setTextureParameter(GLenum filterMode, GLenum value) {
    assert(m_bTextureCreated);
    bind();
    glCall(glTexParameteri(m_TexureTarget, filterMode, value));
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::setAnisotropicFilter(bool enable) {
    assert(m_bTextureCreated);
    bind();
    GLfloat fLargest = 1.0;
    if(enable) {
        glCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest));
    }
    glCall(glTexParameterf(m_TexureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest));
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::setBorderColor(glm::vec4 borderColor) {
    assert(m_bTextureCreated);
    bind();
    glCall(glTexParameterfv(m_TexureTarget, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(borderColor)));
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::setBestParametersWithMipMap() {
    assert(m_bTextureCreated);
    bind();
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_R, GL_REPEAT));

    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLfloat fLargest;
    glCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest));
    glCall(glTexParameterf(m_TexureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest));

    if(m_TexureTarget == GL_TEXTURE_CUBE_MAP) {
        glCall(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS));
    }
    glCall(glGenerateMipmap(m_TexureTarget));
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::setBestParametersNoMipMap() {
    assert(m_bTextureCreated);
    bind();
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_R, GL_REPEAT));

    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLfloat fLargest;
    glCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest));
    glCall(glTexParameterf(m_TexureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest));

    if(m_TexureTarget == GL_TEXTURE_CUBE_MAP) {
        glCall(glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS));
    }
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::setSimplestTexture() {
    assert(m_bTextureCreated);
    bind();
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    glCall(glTexParameteri(m_TexureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    release();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::bind(GLuint texUnit /*= 0*/) {
    assert(m_bTextureCreated);
    m_BindedTexUnit = GL_TEXTURE0 + texUnit;
    glCall(glActiveTexture(m_BindedTexUnit));
    glCall(glBindTexture(m_TexureTarget, m_TextureID));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void OpenGLTexture::release() {
    glCall(glActiveTexture(m_BindedTexUnit));
    glCall(glBindTexture(m_TexureTarget, 0));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#ifdef NT_QT_FRAMEWORK
#include <QDir>
#include <QStringList>
#include <QString>

void OpenGLTexture::loadTextures(StdVT<SharedPtr<OpenGLTexture>>& textures, QString textureFolder, bool insertNullTex /*= true*/, bool bGenMipMap /*= true*/) {
    // clear current textures
    textures.resize(0);
    if(insertNullTex) {
        textures.push_back(nullptr);
    }
    QDir dataDir(textureFolder);
    dataDir.setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dataDir.setSorting(QDir::Name);

    QStringList   allTexFiles = dataDir.entryList();
    StdVT<QImage> textureImages;
    textureImages.resize(allTexFiles.count());

    StdVT<std::future<void>> futureObjs;
    for(int i = 0; i < allTexFiles.count(); ++i) {
        QString texFilePath = textureFolder + "/" + allTexFiles[i];
        futureObjs.emplace_back(std::async(std::launch::async, [&, texFilePath, i]() {
                                               textureImages[i] = QImage(texFilePath).convertToFormat(QImage::Format_RGBA8888);
                                           }));
    }
    for(std::future<void>& f : futureObjs) {
        if(f.valid()) {
            f.wait();
        }
    }
    for(const QImage& texImg : textureImages) {
        SharedPtr<OpenGLTexture> tex = std::make_shared<OpenGLTexture>(GL_TEXTURE_2D);
        tex->uploadData(GL_TEXTURE_2D, GL_RGBA, texImg.width(), texImg.height(), GL_RGBA, GL_UNSIGNED_BYTE, texImg.constBits());

        if(bGenMipMap) {
            tex->setBestParametersWithMipMap();
        } else {
            tex->setBestParametersNoMipMap();
        }
        textures.push_back(tex);
    }
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
QStringList OpenGLTexture::getTextureFolders(QString texType, QString texRootFolder /*= QString("Textures")*/) {
    QDir dataDir(QDir::currentPath() + QString("/") + texRootFolder + QString("/") + texType);
    dataDir.setFilter(QDir::NoDotAndDotDot | QDir::Dirs);

    return dataDir.entryList();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
QStringList OpenGLTexture::getTextureFiles(QString texType, QString texRootFolder /*= QString("Textures")*/) {
    QDir dataDir(QDir::currentPath() + QString("/") + texRootFolder + QString("/") + texType);
    dataDir.setFilter(QDir::NoDotAndDotDot | QDir::Files);

    return dataDir.entryList();
}

#endif // NT_QT_FRAMEWORK
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
} // end namespace NTCodeBase
