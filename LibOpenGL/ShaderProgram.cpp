//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//    .--------------------------------------------------.
//    |  This file is part of NTGraphics                 |
//    |  Created 2018 by NT (https://ttnghia.github.io)  |
//    '--------------------------------------------------'
//                            \o/
//                             |
//                            / |
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#include <LibOpenGL/ShaderProgram.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::addVertexShaderFromSource(const GLchar* shaderSource)
{
    addShader(GL_VERTEX_SHADER, shaderSource);
    m_ShaderSourceCodes[GL_VERTEX_SHADER] = String(shaderSource);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::addGeometryShaderFromSource(const GLchar* shaderSource)
{
    addShader(GL_GEOMETRY_SHADER, shaderSource);
    m_ShaderSourceCodes[GL_GEOMETRY_SHADER] = String(shaderSource);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::addFragmentShaderFromSource(const GLchar* shaderSource)
{
    addShader(GL_FRAGMENT_SHADER, shaderSource);
    m_ShaderSourceCodes[GL_FRAGMENT_SHADER] = String(shaderSource);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::addVertexShaderFromFile(const char* fileName)
{
    String shaderSource;
    loadFile(shaderSource, fileName);

    addShader(GL_VERTEX_SHADER, shaderSource.c_str());
    m_ShaderSourceFiles[GL_VERTEX_SHADER] = String(fileName);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::addGeometryShaderFromFile(const char* fileName)
{
    String shaderSource;
    loadFile(shaderSource, fileName);

    addShader(GL_GEOMETRY_SHADER, shaderSource.c_str());
    m_ShaderSourceFiles[GL_GEOMETRY_SHADER] = String(fileName);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::addFragmentShaderFromFile(const char* fileName)
{
    String shaderSource;
    loadFile(shaderSource, fileName);

    addShader(GL_FRAGMENT_SHADER, shaderSource.c_str());
    m_ShaderSourceFiles[GL_FRAGMENT_SHADER] = String(fileName);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool ShaderProgram::link()
{
    GLuint newProgramID = glCall(glCreateProgram());

    for(GLuint shader : m_ShaderIDs) {
        glCall(glAttachShader(newProgramID, shader));
    }

    glCall(glLinkProgram(newProgramID));

    bool linkSuccess = glCall(checkLinkError(newProgramID));
    if(linkSuccess) {
        if(m_isProgramLinked) {
            glCall(glDeleteProgram(m_ProgramID));
        }

        m_ProgramID       = newProgramID;
        m_isProgramLinked = true;
    }

    for(GLuint shader : m_ShaderIDs) {
        glCall(glDeleteShader(shader));
    }

    m_ShaderIDs.clear();
    return linkSuccess;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool ShaderProgram::reloadShaders()
{
    bool result = true;
    for(auto it = m_ShaderSourceFiles.begin(); it != m_ShaderSourceFiles.end(); ++it) {
        String shaderSouce;
        loadFile(shaderSouce, it->second.c_str());
        result = result && addShader(it->first, shaderSouce.c_str());
    }

    for(auto it = m_ShaderSourceCodes.begin(); it != m_ShaderSourceCodes.end(); ++it) {
        result = result && addShader(it->first, it->second.c_str());
    }

    return (result && link());
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::clearCachedSource()
{
    m_ShaderSourceCodes.clear();
    m_ShaderSourceFiles.clear();
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
GLuint ShaderProgram::getAtributeLocation(const char* atributeName,
                                          bool        dieOnError /* = true*/)
{
    GLint location = glCall(glGetAttribLocation(m_ProgramID, atributeName));

    if(location < 0 && dieOnError) {
#ifdef __NT_QT__
        __NT_DIE(QString("%1: Attribute %2 not found!").arg(QString::fromStdString(m_ProgramName)).arg(atributeName));
#else
        __NT_DIE(("%s: Attribute %s not found!\n", m_ProgramName.c_str(), atributeName));
#endif
    }

    return static_cast<GLuint>(location);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
GLuint ShaderProgram::getUniformLocation(const char* uniformName,
                                         bool        dieOnError /* = true*/)
{
    GLint location = glCall(glGetUniformLocation(m_ProgramID, uniformName));

    if(location < 0 && dieOnError) {
#ifdef __NT_QT__
        __NT_DIE(QString("%1: Uniform location %2 not found!").arg(QString::fromStdString(m_ProgramName)).arg(QString(uniformName)));
#else
        __NT_DIE(("%s: Uniform location %s not found!\n", m_ProgramName.c_str(), uniformName));
#endif
    }

    return static_cast<GLuint>(location);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
GLuint ShaderProgram::getUniformBlockIndex(const char* uniformBlockName, bool dieOnError /*= true*/)
{
    GLuint location = glCall(glGetUniformBlockIndex(m_ProgramID, uniformBlockName));

    if(location == GL_INVALID_INDEX && dieOnError) {
#ifdef __NT_QT__
        __NT_DIE(QString("%1: Uniform block index %2 not found!").arg(QString::fromStdString(m_ProgramName)).arg(QString(uniformBlockName)));
#else
        __NT_DIE(("%s: Uniform location %s not found!\n", m_ProgramName.c_str(), uniformBlockName));
#endif
    }

    return location;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::ShaderProgram::bindUniformBlock(GLuint blockIndex, GLuint bindingPoint)
{
    glCall(glUniformBlockBinding(m_ProgramID, blockIndex, bindingPoint));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::setUniformValue(GLint location, const Mat4x4f& mat)
{
    glCall(glUniformMatrix4fv(location,
                              1 /*only setting 1 matrix*/,
                              false /*transpose?*/,
                              glm::value_ptr(mat)));
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::setUniformValue(GLint location, const GLfloat* data, GLuint count)
{
    switch(count) {
        case 1u:
            glCall(glUniform1f(location, data[0]));
            break;
        case 2u:
            glCall(glUniform2fv(location, 1, data));
            break;
        case 3u:
            glCall(glUniform3fv(location, 1, data));
            break;
        case 4u:
            glCall(glUniform4fv(location, 1, data));
            break;
        default:
            glCall(glUniform1fv(location, count, data));
    }
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::setUniformValue(GLint location, const GLint* data, GLuint count)
{
    switch(count) {
        case 1u:
            glCall(glUniform1i(location, data[0]));
            break;
        case 2u:
            glCall(glUniform2iv(location, 1, data));
            break;
        case 3u:
            glCall(glUniform3iv(location, 1, data));
            break;
        case 4u:
            glCall(glUniform4iv(location, 1, data));
            break;
        default:
            glCall(glUniform1iv(location, count, data));
    }
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool ShaderProgram::addShader(GLenum shaderType, const GLchar* shaderSource)
{
    GLuint shader = glCall(glCreateShader(shaderType));
    glCall(glShaderSource(shader, 1, &shaderSource, NULL));
    glCall(glCompileShader(shader));

    // => add shader into list
    if(checkCompileError(shader, shaderType)) {
        m_ShaderIDs.push_back(shader);
        return true;
    }

    return false;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool ShaderProgram::checkCompileError(GLuint shader, GLenum shaderType)
{
    GLint  success;
    GLchar infoLog[1024];

    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));

    if(!success) {
        glCall(glGetShaderInfoLog(shader, 1024, NULL, infoLog));

        String shaderName = "Unknown";

        if(shaderType == GL_VERTEX_SHADER) {
            shaderName = "VertexShader";
        } else if(shaderType == GL_GEOMETRY_SHADER) {
            shaderName = "GeometryShader";
        } else if(shaderType == GL_FRAGMENT_SHADER) {
            shaderName = "FragmentShader";
        } else {
            shaderName = "InvalidShader";
        }

#ifdef __NT_QT__
        __NT_INFO(QString("%1: %2 failed to compile!\n  => : %3").arg(QString::fromStdString(m_ProgramName)).arg(QString::fromStdString(shaderName)).arg(infoLog));
#else
        std::cout << "ERROR: " << shaderName << " failed to compile!" << std::endl << "  => : " << infoLog << std::endl;
#endif
    }

    return (success != 0);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
bool ShaderProgram::checkLinkError(GLuint program)
{
    GLint  success;
    GLchar infoLog[1024];
    glCall(glGetProgramiv(program, GL_LINK_STATUS, &success));

    if(!success) {
        glCall(glGetProgramInfoLog(program, 1024, NULL, infoLog));
#ifdef __NT_QT__
        __NT_DIE(QString("%1: Program failed to link!\n  => : ").arg(QString::fromStdString(m_ProgramName)) + QString(infoLog));
#else
        __NT_DIE(("%s: Program failed to link!\n   => : ", m_ProgramName.c_str(), infoLog));
#endif
    }

    return (success != 0);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
void ShaderProgram::loadFile(String& fileContent, const char* fileName)
{
    std::ifstream file(fileName);
    if(!file.is_open()) {
#ifdef __NT_QT__
        __NT_DIE(QString("%1: Cannot open file %2 for reading!").arg(QString::fromStdString(m_ProgramName)).arg(QString(fileName)));
#else
        __NT_DIE(("%s: Cannot open file %s for reading!\n", m_ProgramName.c_str(), fileName));
#endif
    }

    // => allocate memory up front
    file.seekg(0, std::ios::end);
    fileContent.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    // => read file
    fileContent.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::ShaderProgram::getSimpleVertexColorShader(String programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Color;
out vec3 f_Color;

void main()
{
    gl_Position = vec4(v_Position, 1.0);
    f_Color = v_Color;
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

in vec3 f_Color;
out vec4 outColor;

void main()
{
    outColor = vec4(f_Color, 1.0f);
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::ShaderProgram::getSimpleUniformColorShader(String programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(location = 0) in vec3 v_Position;

void main()
{
    gl_Position = vec4(v_Position, 1.0);
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

uniform vec3 f_Color;
out vec4 outColor;

void main()
{
    outColor = vec4(f_Color, 1.0f);
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::ShaderProgram::getSimpleTextureShader(String programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec2 v_TexCoord;
out vec2 f_TexCoord;

void main()
{
    gl_Position = vec4(v_Position, 1.0);
    f_TexCoord = v_TexCoord;
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

uniform sampler2D u_TexSampler;
in vec2 f_TexCoord;
out vec4 outColor;

void main()
{
    outColor = texture(u_TexSampler, f_TexCoord);
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getSimpleLightSpaceDepthShader(String programName /*= String("SimpleDepthShader")*/)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(std140) uniform ModelMatrix
{
    mat4 modelMatrix;
    mat4 normalMatrix;
};

#define NUM_TOTAL_LIGHTS 4
struct LightMatrix
{
    mat4 viewMatrix;
    mat4 prjMatrix;
};

layout(std140) uniform LightMatrices
{
    LightMatrix lightMatrices[NUM_TOTAL_LIGHTS];
};

uniform int u_LightID;
in vec3 v_Position;
out float f_LightDistance;

void main()
{
    vec4 lightCoord = lightMatrices[u_LightID].viewMatrix * modelMatrix * vec4(v_Position, 1.0);
    f_LightDistance = lightCoord.z;
    gl_Position     = lightMatrices[u_LightID].prjMatrix * lightCoord;
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

in float f_LightDistance;
out float outDepth;

void main()
{
    outDepth = f_LightDistance;
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getSimpleCameraSpaceDepthShader(String programName /*= String("SimpleCameraSpaceDepthShader")*/)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(std140) uniform ModelMatrix
{
    mat4 modelMatrix;
    mat4 normalMatrix;
};

layout(std140) uniform CameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 invViewMatrix;
    mat4 invProjectionMatrix;
    mat4 shadowMatrix;
    vec4 camPosition;
    vec4 camFocus;
};

in vec3 v_Position;
out float f_CameraDistance;

void main()
{
    vec4 eyeCoord    = viewMatrix * modelMatrix * vec4(v_Position, 1.0);
    f_CameraDistance = eyeCoord.z;
    gl_Position      = projectionMatrix * eyeCoord;
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

in float f_CameraDistance;
out float outDepth;

void main()
{
    outDepth = f_CameraDistance;
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getObjUniformColorShader(String programName)
{
    const GLchar* vertexShader   = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(std140) uniform ModelMatrix
{
    mat4 modelMatrix;
    mat4 normalMatrix;
};

layout(std140) uniform CameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 invViewMatrix;
    mat4 invProjectionMatrix;
    mat4 shadowMatrix;
    vec4 camPosition;
    vec4 camFocus;
};

layout(location = 0) in vec3 v_Position;

void main()
{
    vec4 worldCoord = modelMatrix * vec4(v_Position, 1.0);
    gl_Position     = projectionMatrix * viewMatrix * worldCoord;
}
)";
    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

uniform vec3 f_Color;
out vec4 outColor;

void main()
{
    outColor = vec4(f_Color, 1.0f);
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getObjTextureShader(String programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(std140) uniform ModelMatrix
{
    mat4 modelMatrix;
    mat4 normalMatrix;
};

layout(std140) uniform CameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 invViewMatrix;
    mat4 invProjectionMatrix;
    mat4 shadowMatrix;
    vec4 camPosition;
    vec4 camFocus;
};

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec2 v_TexCoord;
out vec2 f_TexCoord;

void main()
{
    vec4 worldCoord = modelMatrix * vec4(v_Position, 1.0);
    f_TexCoord      = v_TexCoord;
    gl_Position     = projectionMatrix * viewMatrix * worldCoord;
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

uniform sampler2D u_TexSampler;
in vec2 f_TexCoord;
out vec4 outColor;

void main()
{
    outColor = texture(u_TexSampler, f_TexCoord);
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::ShaderProgram::getPhongShader(String programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(std140) uniform ModelMatrix
{
    mat4 modelMatrix;
    mat4 normalMatrix;
};

#define NUM_TOTAL_LIGHTS 4
struct LightMatrix
{
    mat4 viewMatrix;
    mat4 prjMatrix;
};

layout(std140) uniform LightMatrices
{
    LightMatrix lightMatrices[NUM_TOTAL_LIGHTS];
};

struct PointLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
};

layout(std140) uniform Lights
{
    PointLight lights[NUM_TOTAL_LIGHTS];
    int u_NumLights;
};

layout(std140) uniform CameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 invViewMatrix;
    mat4 invProjectionMatrix;
    mat4 shadowMatrix;
    vec4 camPosition;
    vec4 camFocus;
};

uniform int u_HasShadow;

layout(location = 0) in vec3 v_Position;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TexCoord;
out VS_OUT
{
    float f_LightDistance[NUM_TOTAL_LIGHTS];
    vec4  f_FragPosLightSpace[NUM_TOTAL_LIGHTS];
    vec3 f_Normal;
    vec3 f_FragPos;
    vec3 f_ViewDir;
    vec2 f_TexCoord;
};

void main()
{
    f_Normal = vec3(normalMatrix* vec4(v_Normal, 1.0));
    vec4 worldCoord = modelMatrix * vec4(v_Position, 1.0);
    f_FragPos = vec3(worldCoord);
    f_ViewDir = vec3(camPosition)- vec3(worldCoord);
    f_TexCoord = v_TexCoord;
    if(u_HasShadow == 1)
    {
        for(int i = 0; i < u_NumLights; ++i)
        {
            vec4 lightCoord = lightMatrices[i].viewMatrix * worldCoord;
            f_LightDistance[i] = lightCoord.z;
            f_FragPosLightSpace[i] = lightMatrices[i].prjMatrix * lightCoord;
        }
    }
    gl_Position = projectionMatrix * viewMatrix * worldCoord;
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

#define NUM_TOTAL_LIGHTS 4
struct PointLight
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
};

layout(std140) uniform Lights
{
    PointLight lights[NUM_TOTAL_LIGHTS];
    int u_NumLights;
};

layout(std140) uniform Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
} material;

uniform int u_HasTexture;
uniform int u_HasShadow;
uniform sampler2D u_TexSampler;
uniform sampler2D u_ShadowMap[NUM_TOTAL_LIGHTS];
#define SHADOW_BIAS -0.05

uniform float u_Exposure = 1.0f;

in VS_OUT
{
    float f_LightDistance[NUM_TOTAL_LIGHTS];
    vec4  f_FragPosLightSpace[NUM_TOTAL_LIGHTS];
    vec3 f_Normal;
    vec3 f_FragPos;
    vec3 f_ViewDir;
    vec2 f_TexCoord;
};
out vec4 outColor;

vec3 shadeLight(int lightID, vec3 normal, vec3 fragPos, vec3 viewDir, vec2 f_TexCoord)
{
    float inShadow = 0.0;
    if(u_HasShadow == 1)
    {
        vec3 projCoords = f_FragPosLightSpace[lightID].xyz / f_FragPosLightSpace[lightID].w;
        projCoords = clamp(projCoords * 0.5 + 0.5, 0, 1); // Transform to [0,1] range
        vec2 texelSize = 1.0 / textureSize(u_ShadowMap[lightID], 0);
        for(int x = -1; x <= 1; ++x)
        {
            for(int y = -1; y <= 1; ++y)
            {
                float pcfDepth = texture(u_ShadowMap[lightID], projCoords.xy + vec2(x, y) * texelSize).r;
                inShadow += (f_LightDistance[lightID] < pcfDepth + SHADOW_BIAS) ? 1.0 : 0.0;
            }
        }
        inShadow /= 9.0;
    }
    vec3 lightDir = normalize(vec3(lights[lightID].position) - fragPos);
    vec3 halfDir  = normalize(lightDir + viewDir);

    vec4 ambientColor  = lights[lightID].ambient;
    vec4 diffuseColor  = lights[lightID].diffuse * vec4(max(dot(normal, lightDir), 0.0));;
    vec4 specularColor = lights[lightID].specular * pow(max(dot(halfDir, normal), 0.0), material.shininess);
    if(u_HasTexture == 1)
    {
        vec4 objColor  = texture(u_TexSampler, f_TexCoord);
        ambientColor  *= (objColor * 0.2);
        diffuseColor  *= objColor;
        specularColor *= objColor;
    }
    else
    {
        ambientColor  *= material.ambient;
        diffuseColor  *= material.diffuse;
        specularColor *= material.specular;
    }

    return vec3(ambientColor + (1.0 - inShadow)*(diffuseColor + specularColor));
}

void main()
{
    vec3 normal = normalize(f_Normal);
    vec3 viewDir = normalize(f_ViewDir);
    vec3 shadeColor = vec3(0, 0, 0);

    for(int i = 0; i < u_NumLights; ++i)
        shadeColor += shadeLight(i, normal, f_FragPos, viewDir, f_TexCoord);

    outColor = vec4(u_Exposure * shadeColor, 1.0);
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::ShaderProgram::getSkyBoxShader(String programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

layout(std140) uniform ModelMatrix
{
    mat4 modelMatrix;
    mat4 normalMatrix;
};

layout(std140) uniform CameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 invViewMatrix;
    mat4 invProjectionMatrix;
    mat4 shadowMatrix;
    vec4 camPosition;
    vec4 camFocus;
};

layout(location = 0) in vec3 v_Position;
out vec3 f_ViewDir;

void main()
{
    vec4 worldCoord = modelMatrix * vec4(v_Position, 1.0);
    f_ViewDir = vec3(worldCoord) - vec3(camPosition);
    gl_Position = projectionMatrix * viewMatrix * worldCoord;
}
)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
#version 410 core

uniform samplerCube u_TexSampler;
in vec3 f_ViewDir;
out vec4 outColor;

void main()
{
   vec3 viewDir = normalize(f_ViewDir);
   outColor = texture(u_TexSampler, viewDir);

}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getScreenQuadShader(const char* fragmentShaderSource,
                                                            String      programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
// vertex shader, screen quad
#version 410 core

out vec2 f_TexCoord;
void main()
{
    vec2 pos[] = vec2[](vec2(-1.0, -1.0),
                        vec2(1.0, -1.0),
                        vec2(-1.0, 1.0),
                        vec2(1.0, 1.0));

    vec2 tex[] = vec2[](vec2(0.0, 0.0),
                        vec2(1.0, 0.0),
                        vec2(0.0, 1.0),
                        vec2(1.0, 1.0));

    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
    f_TexCoord = tex[gl_VertexID];
}
)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShaderSource);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getScreenQuadShaderFromFile(const char* fragmentShaderFile, String programName /*=String("ScreenQuadShader")*/)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
// vertex shader, screen quad
#version 410 core

out vec2 f_TexCoord;
void main()
{
    vec2 pos[] = vec2[](vec2(-1.0, -1.0),
                        vec2(1.0, -1.0),
                        vec2(-1.0, 1.0),
                        vec2(1.0, 1.0));

    vec2 tex[] = vec2[](vec2(0.0, 0.0),
                        vec2(1.0, 0.0),
                        vec2(0.0, 1.0),
                        vec2(1.0, 1.0));

    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
    f_TexCoord = tex[gl_VertexID];
}

)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromFile(fragmentShaderFile);
    shader->link();
    return shader;
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getCheckerboardBackgroundShader(String programName)
{
    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
// fragment shader, CheckerboardBackground
#version 410 core

uniform vec4 u_Color1 = vec4(1, 1, 1, 1);
uniform vec4 u_Color2 = vec4(0, 0, 0, 1);
uniform ivec2 u_Scales = ivec2(20, 20);
uniform int u_ScreenWidth = 2;
uniform int u_ScreenHeight= 2;
in vec2 f_TexCoord;
out vec4 outColor;

void main()
{
   int xPixel = int(floor(f_TexCoord.x * float(u_ScreenWidth) / float(u_Scales.x)));
   int yPixel = int(floor(f_TexCoord.y * float(u_ScreenHeight) / float(u_Scales.y)));
   bool isEven = mod(xPixel + yPixel, 2) == 0;
   outColor = isEven ? u_Color1 : u_Color2;

}
)";
    return getScreenQuadShader(fragmentShader, programName);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getGridBackgroundShader(String programName)
{
    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
// fragment shader, CheckerboardBackground
#version 410 core

uniform vec4 m_UBackgroundColor = vec4(1, 1, 1, 1);
uniform vec4 m_ULineColor = vec4(0, 0, 0, 1);
uniform ivec2 u_Scales = ivec2(20, 20);
uniform int u_ScreenWidth = 1;
uniform int u_ScreenHeight= 1;
in vec2 f_TexCoord;
out vec4 outColor;

void main()
{
   int xPixel = int(floor(f_TexCoord.x * float(u_ScreenWidth)));
   int yPixel = int(floor(f_TexCoord.y * float(u_ScreenHeight)));
   bool inLine_x = mod(xPixel, u_Scales.x) == 0;
   bool inLine_y = mod(yPixel, u_Scales.y) == 0;
   outColor = (inLine_x || inLine_y) ? m_ULineColor : m_UBackgroundColor;

}
)";
    return getScreenQuadShader(fragmentShader, programName);
}

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
SharedPtr<ShaderProgram> ShaderProgram::getGizmoShader(String programName)
{
    const GLchar* vertexShader = R"(
// This is the shader statically generated by ShaderProgram class
// vertex shader, gizmo render
#version 410 core
layout(std140) uniform CameraData
{
    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 invViewMatrix;
    mat4 invProjectionMatrix;
    mat4 shadowMatrix;
    vec4 camPosition;
    vec4 camFocus;
};

uniform float u_Width = 0.1f;
const mat4 c_OrthogonalPrjMatrix = mat4(vec4(15.0f / 32.0f, 0, 0, 0),
                                        vec4(0, 5.0f / 6.0f, 0,     0),
                                        vec4(0,    0,        -0.01, 0),
                                        vec4(0,    0,        0,     1));

out vec3 fColor;

////////////////////////////////////////////////////////////////////////////////
void main()
{
    vec3 gizmo_data[] = vec3[] (
        // Z
        vec3(-u_Width / 2.0,            -u_Width / 2.0,        1.0),
        vec3(u_Width / 2.0,             -u_Width / 2.0,        1.0),
        vec3(-u_Width / 2.0,      u_Width / 2.0,               1.0),
        vec3(u_Width / 2.0,       u_Width / 2.0,               1.0),

        vec3(-u_Width / 2.0,            -u_Width / 2.0,        0.0 - u_Width / 2.0),
        vec3(u_Width / 2.0,             -u_Width / 2.0,        0.0 - u_Width / 2.0),
        vec3(-u_Width / 2.0,      u_Width / 2.0,               0.0 - u_Width / 2.0),
        vec3(u_Width / 2.0,       u_Width / 2.0,               0.0 - u_Width / 2.0),

        // Y
        vec3(-u_Width / 2.0,          1.0,                       -u_Width / 2.0),
        vec3(u_Width / 2.0,           1.0,                       -u_Width / 2.0),
        vec3(-u_Width / 2.0,          1.0,                 u_Width / 2.0),
        vec3(u_Width / 2.0,           1.0,                 u_Width / 2.0),

        vec3(-u_Width / 2.0,          0.0 + u_Width / 2.0,       -u_Width / 2.0),
        vec3(u_Width / 2.0,           0.0 + u_Width / 2.0,       -u_Width / 2.0),
        vec3(-u_Width / 2.0,          0.0 + u_Width / 2.0, u_Width / 2.0),
        vec3(u_Width / 2.0,           0.0 + u_Width / 2.0, u_Width / 2.0),

        // X
        vec3(1.0,                       -u_Width / 2.0,          -u_Width / 2.0),
        vec3(1.0,                 u_Width / 2.0,                 -u_Width / 2.0),
        vec3(1.0,                       -u_Width / 2.0,    u_Width / 2.0),
        vec3(1.0,                 u_Width / 2.0,           u_Width / 2.0),

        vec3(0.0 + u_Width / 2.0,       -u_Width / 2.0,          -u_Width / 2.0),
        vec3(0.0 + u_Width / 2.0, u_Width / 2.0,                 -u_Width / 2.0),
        vec3(0.0 + u_Width / 2.0,       -u_Width / 2.0,    u_Width / 2.0),
        vec3(0.0 + u_Width / 2.0, u_Width / 2.0,           u_Width / 2.0)
        );

    int gizmo_indices[] = int[] (
        // Z
        0, 1, 2, 2, 1, 3,
        4, 5, 6, 6, 5, 7,
        0, 4, 1, 1, 4, 5,
        1, 5, 3, 3, 5, 7,
        3, 7, 2, 2, 7, 6,
        2, 6, 0, 0, 6, 4,

        // Y
        0 + 8, 1 + 8, 2 + 8, 2 + 8, 1 + 8, 3 + 8,
        4 + 8, 5 + 8, 6 + 8, 6 + 8, 5 + 8, 7 + 8,
        0 + 8, 4 + 8, 1 + 8, 1 + 8, 4 + 8, 5 + 8,
        1 + 8, 5 + 8, 3 + 8, 3 + 8, 5 + 8, 7 + 8,
        3 + 8, 7 + 8, 2 + 8, 2 + 8, 7 + 8, 6 + 8,
        2 + 8, 6 + 8, 0 + 8, 0 + 8, 6 + 8, 4 + 8,

        // X
        0 + 16, 1 + 16, 2 + 16, 2 + 16, 1 + 16, 3 + 16,
        4 + 16, 5 + 16, 6 + 16, 6 + 16, 5 + 16, 7 + 16,
        0 + 16, 4 + 16, 1 + 16, 1 + 16, 4 + 16, 5 + 16,
        1 + 16, 5 + 16, 3 + 16, 3 + 16, 5 + 16, 7 + 16,
        3 + 16, 7 + 16, 2 + 16, 2 + 16, 7 + 16, 6 + 16,
        2 + 16, 6 + 16, 0 + 16, 0 + 16, 6 + 16, 4 + 16
        );

    if(gl_VertexID < 36) {
        fColor = vec3(0.0, 0.0, 1.0);
    } else if(gl_VertexID < 2 * 36) {
        fColor = vec3(0.0, 1.0, 0.0);
    } else if(gl_VertexID < 3 * 36) {
        fColor = vec3(1.0, 0.0, 0.0);
    }

    vec4 eyeCoord = viewMatrix * vec4(gizmo_data[gizmo_indices[gl_VertexID]] + camFocus.xyz, 1.0f);
    gl_Position = c_OrthogonalPrjMatrix * eyeCoord;
};

)";

    const GLchar* fragmentShader = R"(
// This is the shader statically generated by ShaderProgram class
// fragment shader, gizmo render
#version 410 core

out vec4 outColor;
in vec3  fColor;
////////////////////////////////////////////////////////////////////////////////
void main()
{
    outColor = vec4(fColor, 1);
}

)";

    auto shader = std::make_shared<ShaderProgram>(programName);
    shader->addVertexShaderFromSource(vertexShader);
    shader->addFragmentShaderFromSource(fragmentShader);
    shader->link();
    return shader;
}
