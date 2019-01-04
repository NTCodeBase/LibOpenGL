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

#include <LibOpenGL/OpenGLMacros.h>
#include <LibOpenGL/LightAndMaterialData.h>
#include <LibOpenGL/Forward.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
namespace NTCodeBase {
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class Lights : public OpenGLCallable {
public:
    Lights();
    Lights(int numLights);

    void setNumLights(int numLights) { m_NumActiveLights = numLights; }
    int  getNumLights() const { return m_NumActiveLights; }
    void createUniformBuffer();

    virtual void setLightAmbient(const Vec4f& ambient, int lightID   = 0) = 0;
    virtual void setLightDiffuse(const Vec4f& diffuse, int lightID   = 0) = 0;
    virtual void setLightSpecular(const Vec4f& specular, int lightID = 0) = 0;

    virtual const Vec4f& getLightAmbient(int lightID  = 0) const = 0;
    virtual const Vec4f& getLightDiffuse(int lightID  = 0) const = 0;
    virtual const Vec4f& getLightSpecular(int lightID = 0) const = 0;

    void   bindUniformBuffer();
    GLuint getBufferBindingPoint();
    size_t getUniformBufferSize() const { return LightData::MaxNLights* getLightSize() + sizeof(GLint); }
    size_t getLightDataSize() const { return LightData::MaxNLights* getLightSize(); }

    // data for shadow map
    void   setSceneCenter(const Vec3f& sceneCenter) { m_SceneCenter = sceneCenter; }
    void   bindUniformBufferLightMatrix();
    GLuint getBufferLightMatrixBindingPoint();
    void   uploadLightMatrixToGPU();
    ////////////////////////////////////////////////////////////////////////////////
    virtual void   updateLightMatrixBuffer() = 0;
    virtual void   uploadDataToGPU()         = 0;
    virtual size_t getLightSize() const      = 0;

protected:
    GLint                   m_NumActiveLights;
    SharedPtr<OpenGLBuffer> m_UniformBuffer;
    SharedPtr<OpenGLBuffer> m_UniformBufferLightMatrix;
    LightMatrix             m_LightMatrices[LightData::LightData::MaxNLights];
    Vec3f                   m_SceneCenter;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class DirectionalLights : public Lights {
public:
    void        setLight(const DirectionalLightData& lightData, int lightID = 0) { assert(lightID < m_NumActiveLights); m_Lights[lightID] = lightData; }
    const auto& getLight(int lightID = 0) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID]; }

    void        setLightDirection(const Vec4f& direction, int lightID = 0) { assert(lightID < m_NumActiveLights); m_Lights[lightID].direction = direction; }
    const auto& getLightDirection(int lightID = 0) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID].direction; }

    virtual void setLightAmbient(const Vec4f& ambient, int lightID   = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].ambient = ambient; }
    virtual void setLightDiffuse(const Vec4f& diffuse, int lightID   = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].diffuse = diffuse; }
    virtual void setLightSpecular(const Vec4f& specular, int lightID = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].specular = specular; }

    virtual const Vec4f& getLightAmbient(int lightID  = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].ambient; }
    virtual const Vec4f& getLightDiffuse(int lightID  = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].diffuse; }
    virtual const Vec4f& getLightSpecular(int lightID = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].specular; }

    virtual void uploadDataToGPU() override;
    virtual size_t getLightSize() const override { return 4 * sizeof(Vec4f); }

    // shadow map helpers
    virtual void updateLightMatrixBuffer() override;
    void         setShadowMapBox(GLfloat minX, GLfloat maxX, GLfloat minY, GLfloat maxY, GLfloat minZ, GLfloat maxZ);

private:
    DirectionalLightData m_Lights[LightData::MaxNLights];

    GLfloat m_ShadowMinX;
    GLfloat m_ShadowMaxX;
    GLfloat m_ShadowMinY;
    GLfloat m_ShadowMaxY;
    GLfloat m_ShadowMinZ;
    GLfloat m_ShadowMaxZ;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class PointLights : public Lights {
public:
    virtual void setLight(const PointLightData& lightData, int lightID = 0) { assert(lightID < m_NumActiveLights); m_Lights[lightID] = lightData; }
    const auto& getLight(int lightID) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID]; }

    void        setLightPosition(const Vec4f& position, int lightID = 0) { assert(lightID < m_NumActiveLights); m_Lights[lightID].position = position; }
    const auto& getLightPosition(int lightID = 0) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID].position; }

    virtual void setLightAmbient(const Vec4f& ambient, int lightID   = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].ambient = ambient; }
    virtual void setLightDiffuse(const Vec4f& diffuse, int lightID   = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].diffuse = diffuse; }
    virtual void setLightSpecular(const Vec4f& specular, int lightID = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].specular = specular; }

    virtual const Vec4f& getLightAmbient(int lightID  = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].ambient; }
    virtual const Vec4f& getLightDiffuse(int lightID  = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].diffuse; }
    virtual const Vec4f& getLightSpecular(int lightID = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].specular; }

    virtual void uploadDataToGPU() override;
    virtual size_t getLightSize() const override { return 4 * sizeof(Vec4f); }

    // shadow map helpers
    virtual void updateLightMatrixBuffer() override;
    void         setLightViewPerspective(GLfloat fov, GLfloat asspect = 1.0, GLfloat nearZ = 0.1f, GLfloat farZ = 1000.0f);

private:
    PointLightData m_Lights[LightData::MaxNLights];
    GLfloat        m_ShadowFOV;
    GLfloat        m_ShadowAspect;
    GLfloat        m_ShadowNearZ;
    GLfloat        m_ShadowFarZ;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class SpotLights : public Lights {
public:
    void        setLight(const SpotLightData& lightData, int lightID = 0) { assert(lightID < m_NumActiveLights); m_Lights[lightID] = lightData; }
    const auto& getLight(int lightID = 0) { assert(lightID < m_NumActiveLights); return m_Lights[lightID]; }

    void setLightPosition(const Vec4f& position, int lightID   = 0) { assert(lightID < m_NumActiveLights); m_Lights[lightID].position = position; }
    void setLightDirection(const Vec4f& direction, int lightID = 0) { assert(lightID < m_NumActiveLights); m_Lights[lightID].direction = direction; }
    void setLightCuffOffAngles(float innerAngle, float outerAngle, int lightID = 0);

    const auto& getLightPosition(int lightID    = 0) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID].position; }
    const auto& getLightDirection(int lightID   = 0) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID].direction; }
    auto        getInnerCutOffAngle(int lightID = 0) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID].innerCutOffAngle; }
    auto        getOuterCutOffAngle(int lightID = 0) const { assert(lightID < m_NumActiveLights); return m_Lights[lightID].outerCutOffAngle; }

    virtual void setLightAmbient(const Vec4f& ambient, int lightID   = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].ambient = ambient; }
    virtual void setLightDiffuse(const Vec4f& diffuse, int lightID   = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].diffuse = diffuse; }
    virtual void setLightSpecular(const Vec4f& specular, int lightID = 0) override { assert(lightID < m_NumActiveLights); m_Lights[lightID].specular = specular; }

    virtual const Vec4f& getLightAmbient(int lightID  = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].ambient; }
    virtual const Vec4f& getLightDiffuse(int lightID  = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].diffuse; }
    virtual const Vec4f& getLightSpecular(int lightID = 0) const override { assert(lightID < m_NumActiveLights); return m_Lights[lightID].specular; }

    virtual void uploadDataToGPU() override;
    virtual size_t getLightSize() const override { return 5 * sizeof(Vec4f) + 2 * sizeof(GLfloat); }

    // shadow map helpers
    virtual void updateLightMatrixBuffer() override;
    void         setLightViewPerspective(GLfloat fov, GLfloat asspect = 1.0f, GLfloat nearZ = 0.1f, GLfloat farZ = 1000.0f);

private:
    SpotLightData m_Lights[LightData::MaxNLights];
    GLfloat       m_ShadowFOV;
    GLfloat       m_ShadowAspect;
    GLfloat       m_ShadowNearZ;
    GLfloat       m_ShadowFarZ;
};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
} // end namespace NTCodeBase
