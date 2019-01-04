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

#include <LibOpenGL/OpenGLBuffer.h>
#include <LibOpenGL/Lights.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
namespace NTCodeBase {
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// Light base class
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Lights::Lights() : m_NumActiveLights(1), m_UniformBuffer(std::make_shared<OpenGLBuffer>()),
    m_UniformBufferLightMatrix(std::make_shared<OpenGLBuffer>()) {
    static_assert(sizeof(Vec4f) == sizeof(GLfloat) * 4, "Size of Vec4f != 4 * sizeof(GLfloat).");
    assert(m_UniformBuffer != nullptr && m_UniformBufferLightMatrix != nullptr);
}

Lights::Lights(int numLights) : m_NumActiveLights(numLights), m_UniformBuffer(std::make_shared<OpenGLBuffer>()),
    m_UniformBufferLightMatrix(std::make_shared<OpenGLBuffer>()) {
    static_assert(sizeof(Vec4f) == sizeof(GLfloat) * 4, "Size of Vec4f != 4 * sizeof(GLfloat).");
    assert(m_UniformBuffer != nullptr && m_UniformBufferLightMatrix != nullptr);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void Lights::createUniformBuffer() {
    m_UniformBuffer->createBuffer(GL_UNIFORM_BUFFER, getUniformBufferSize());
    m_UniformBufferLightMatrix->createBuffer(GL_UNIFORM_BUFFER, 2 * LightData::MaxNLights* sizeof(Mat4x4f));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void Lights::bindUniformBuffer() {
    assert(m_UniformBuffer->isCreated());
    m_UniformBuffer->bindBufferBase();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
GLuint Lights::getBufferBindingPoint() {
    if(!m_UniformBuffer->isCreated()) {
        createUniformBuffer();
    }
    return m_UniformBuffer->getBindingPoint();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void Lights::bindUniformBufferLightMatrix() {
    assert(m_UniformBufferLightMatrix->isCreated());
    m_UniformBufferLightMatrix->bindBufferBase();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
GLuint Lights::getBufferLightMatrixBindingPoint() {
    if(!m_UniformBufferLightMatrix->isCreated()) {
        createUniformBuffer();
    }
    return m_UniformBufferLightMatrix->getBindingPoint();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void Lights::uploadLightMatrixToGPU() {
    assert(m_UniformBufferLightMatrix->isCreated());
    m_UniformBufferLightMatrix->uploadData(m_LightMatrices, 0, 2 * LightData::MaxNLights* sizeof(Mat4x4f));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// DirectionalLight class
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectionalLights::uploadDataToGPU() {
    if(!m_UniformBuffer->isCreated()) {
        createUniformBuffer();
    }
    m_UniformBuffer->uploadData(m_Lights,           0,        getLightDataSize());
    m_UniformBuffer->uploadData(&m_NumActiveLights, getLightDataSize(), sizeof(GLint));

    updateLightMatrixBuffer();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectionalLights::updateLightMatrixBuffer() {
    for(int i = 0; i < m_NumActiveLights; ++i) {
        Mat4x4f lightView       = glm::lookAt(m_SceneCenter - glm::make_vec3(m_Lights[i].direction), m_SceneCenter, Vec3f(0.0f, -0.91f, 0.01f));
        Mat4x4f lightProjection = glm::ortho(m_ShadowMinX, m_ShadowMaxX, m_ShadowMinY, m_ShadowMaxY, m_ShadowMinZ, m_ShadowMaxZ);

        m_LightMatrices[i].lightViewMatrix       = lightView;
        m_LightMatrices[i].lightProjectionMatrix = lightProjection;
    }
    uploadLightMatrixToGPU();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void DirectionalLights::setShadowMapBox(GLfloat minX, GLfloat maxX, GLfloat minY, GLfloat maxY, GLfloat minZ, GLfloat maxZ) {
    m_ShadowMinX = minX;
    m_ShadowMaxX = maxX;
    m_ShadowMinY = minY;
    m_ShadowMaxY = maxY;
    m_ShadowMinZ = minZ;
    m_ShadowMaxZ = maxZ;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// PointLight class
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void PointLights::uploadDataToGPU() {
    if(!m_UniformBuffer->isCreated()) {
        createUniformBuffer();
    }
    m_UniformBuffer->uploadData(m_Lights,           0,        getLightDataSize());
    m_UniformBuffer->uploadData(&m_NumActiveLights, getLightDataSize(), sizeof(GLint));
    updateLightMatrixBuffer();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void PointLights::updateLightMatrixBuffer() {
    for(int i = 0; i < m_NumActiveLights; ++i) {
        Mat4x4f lightView       = glm::lookAt(glm::make_vec3(m_Lights[i].position), m_SceneCenter, Vec3f(0.0f, -0.91f, 0.01f));
        Mat4x4f lightProjection = glm::perspective(glm::radians(m_ShadowFOV), m_ShadowAspect, m_ShadowNearZ, m_ShadowFarZ);

        m_LightMatrices[i].lightViewMatrix       = lightView;
        m_LightMatrices[i].lightProjectionMatrix = lightProjection;
    }
    uploadLightMatrixToGPU();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void PointLights::setLightViewPerspective(GLfloat fov, GLfloat asspect /*= 1.0*/, GLfloat nearZ /*= 0.1f*/, GLfloat farZ /*= 1000.0f*/) {
    m_ShadowFOV    = fov;
    m_ShadowAspect = asspect;
    m_ShadowNearZ  = nearZ;
    m_ShadowFarZ   = farZ;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// SpotLight class
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void SpotLights::setLightCuffOffAngles(float innerAngle, float outerAngle, int lightID /*= 0*/) {
    assert(lightID < m_NumActiveLights);
    m_Lights[lightID].innerCutOffAngle = innerAngle;
    m_Lights[lightID].outerCutOffAngle = outerAngle;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void SpotLights::uploadDataToGPU() {
    if(!m_UniformBuffer->isCreated()) {
        createUniformBuffer();
    }
    m_UniformBuffer->uploadData(m_Lights,           0,        getLightDataSize());
    m_UniformBuffer->uploadData(&m_NumActiveLights, getLightDataSize(), sizeof(GLint));
    updateLightMatrixBuffer();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void SpotLights::updateLightMatrixBuffer() {
    for(int i = 0; i < m_NumActiveLights; ++i) {
        Mat4x4f lightView       = glm::lookAt(glm::make_vec3(m_Lights[i].position), m_SceneCenter, Vec3f(0.0f, -0.91f, 0.01f));
        Mat4x4f lightProjection = glm::perspective(glm::radians(m_ShadowFOV), m_ShadowAspect, m_ShadowNearZ, m_ShadowFarZ);

        m_LightMatrices[i].lightViewMatrix       = lightView;
        m_LightMatrices[i].lightProjectionMatrix = lightProjection;
    }
    uploadLightMatrixToGPU();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void SpotLights::setLightViewPerspective(GLfloat fov, GLfloat asspect /*= 1.0*/, GLfloat nearZ /*= 0.1f*/, GLfloat farZ /*= 1000.0f*/) {
    m_ShadowFOV    = fov;
    m_ShadowAspect = asspect;
    m_ShadowNearZ  = nearZ;
    m_ShadowFarZ   = farZ;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
} // end namespace NTCodeBase
