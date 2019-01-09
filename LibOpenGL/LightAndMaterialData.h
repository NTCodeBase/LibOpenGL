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
#include <LibCommon/CommonSetup.h>

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
namespace NTCodeBase {
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct LightData {
    static constexpr int MaxNLights = 4;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct LightMatrix {
    Mat4x4f lightViewMatrix       = Mat4x4f(1);
    Mat4x4f lightProjectionMatrix = Mat4x4f(1);
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct DirectionalLightData {
    Vec4f ambient   = Vec4f(0.1f);
    Vec4f diffuse   = Vec4f(1.0f);
    Vec4f specular  = Vec4f(1.0f);
    Vec4f direction = Vec4f(1.0f);
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct PointLightData {
    Vec4f ambient  = Vec4f(0.1f);
    Vec4f diffuse  = Vec4f(1.0f);
    Vec4f specular = Vec4f(1.0f);
    Vec4f position = Vec4f(0.0f);
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct SpotLightData {
    Vec4f ambient   = Vec4f(0.1f);
    Vec4f diffuse   = Vec4f(1.0f);
    Vec4f specular  = Vec4f(1.0f);
    Vec4f position  = Vec4f(0.0f);
    Vec4f direction = Vec4f(1.0f);
    float innerCutOffAngle;
    float outerCutOffAngle;
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct MaterialData {
    MaterialData() = default;
    MaterialData(Vec4f ambient_, Vec4f diffuse_, Vec4f specular_, float shininess_, String name_) :
        ambient(ambient_), diffuse(diffuse_), specular(specular_), shininess(shininess_), name(name_) {}
    ////////////////////////////////////////////////////////////////////////////////
    Vec4f  ambient   = Vec4f(0);
    Vec4f  diffuse   = Vec4f(0);
    Vec4f  specular  = Vec4f(1);
    float  shininess = 100.0f;
    String name;
    static size_t getGPUDataSize() { return 3 * sizeof(Vec4f) + sizeof(float); }
};

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
struct BuildInMaterials {
    /*
       Name           Ambient                    Diffuse                        Specular                         Shininess
       Emerald        0.0215   0.1745   0.0215   0.07568  0.61424    0.07568    0.633      0.727811   0.633      0.6
       Jade           0.135    0.2225   0.1575   0.54     0.89       0.63       0.316228   0.316228   0.316228   0.1
       Obsidian       0.05375  0.05     0.06625  0.18275  0.17       0.22525    0.332741   0.328634   0.346435   0.3
       Pearl          0.25     0.20725  0.20725  1 0.829  0.829      0.296648   0.296648   0.296648   0.088
       Ruby           0.1745   0.01175  0.01175  0.61424  0.04136    0.04136    0.727811   0.626959   0.626959   0.6
       Turquoise      0.1      0.18725  0.1745   0.396    0.74151    0.69102    0.297254   0.30829    0.306678   0.1
       Brass          0.329412 0.223529 0.027451 0.780392 0.568627   0.113725   0.992157   0.941176   0.807843   0.21794872
       Bronze         0.2125   0.1275   0.054    0.714    0.4284     0.18144    0.393548   0.271906   0.166721   0.2
       Chrome         0.25     0.25     0.25     0.4      0.4        0.4        0.774597   0.774597   0.774597   0.6
       Copper         0.19125  0.0735   0.0225   0.7038   0.27048    0.0828     0.256777   0.137622   0.086014   0.1
       Gold           0.24725  0.1995   0.0745   0.75164  0.60648    0.22648    0.628281   0.555802   0.366065   0.4
       Silver         0.19225  0.19225  0.19225  0.50754  0.50754    0.50754    0.508273   0.508273   0.508273   0.4
       BlackPlastic   0.0      0.0      0.0      0.01     0.01       0.01       0.50       0.50       0.50       .25
       CyanPlastic    0.0      0.1      0.06     0.0      0.50980392 0.50980392 0.50196078 0.50196078 0.50196078 .25
       GreenPlastic   0.0      0.0      0.0      0.1      0.35       0.1        0.45       0.55       0.45       .25
       RedPlastic     0.0      0.0      0.0      0.5      0.0        0.0        0.7        0.6        0.6        .25
       WhitePlastic   0.0      0.0      0.0      0.55     0.55       0.55       0.70       0.70       0.70       .25
       YellowPlastic  0.0      0.0      0.0      0.5      0.5        0.0        0.60       0.60       0.50       .25
       BlackRubber    0.02     0.02     0.02     0.01     0.01       0.01       0.4        0.4        0.4        .078125
       CyanRubber     0.0      0.05     0.05     0.4      0.5        0.5        0.04       0.7        0.7        .078125
       GreenRubber    0.0      0.05     0.0      0.4      0.5        0.4        0.04       0.7        0.04       .078125
       RedRubber      0.05     0.0      0.0      0.5      0.4        0.4        0.7        0.04       0.04       .078125
       WhiteRubber    0.05     0.05     0.05     0.5      0.5        0.5        0.7        0.7        0.7        .078125
       YellowRubber   0.05     0.05     0.0      0.5      0.5        0.4        0.7        0.7        0.04       .078125
     */
    ////////////////////////////////////////////////////////////////////////////////
    const static inline MaterialData MT_Emerald = MaterialData(Vec4f(0.0125f,    0.1745f,  0.0215f, 1.0f),
                                                                     Vec4f(   0.07568f,    0.61424f,    0.07568f, 1.0f),
                                                                     Vec4f(     0.633f,   0.727811f,      0.633f, 1.0f),
                                                               0.6f * 128.0f,      "Emerald");
    const static inline MaterialData MT_Jade = MaterialData(Vec4f(0.135f,      0.2225f,   0.1575f, 1.0f),
                                                                     Vec4f(      0.54f,       0.89f,       0.63f, 1.0f),
                                                                     Vec4f(  0.316228f,   0.316228f,   0.316228f, 1.0f),
                                                            0.1f * 128.0f,       "Jade");
    const static inline MaterialData MT_Obsidian = MaterialData(Vec4f(0.05375f,      0.05f,  0.06625f, 1.0f),
                                                                     Vec4f(   0.18275f,       0.17f,    0.22525f, 1.0f),
                                                                     Vec4f(  0.332741f,   0.328634f,   0.346435f, 1.0f),
                                                                0.3f * 128.0f,       "Obsidian");
    const static inline MaterialData MT_Pearl = MaterialData(Vec4f(0.25f,      0.20725f,  0.20725f, 1.0f),
                                                                     Vec4f(       1.0f,      0.829f,      0.829f, 1.0f),
                                                                     Vec4f(  0.296648f,   0.296648f,   0.296648f, 1.0f),
                                                             0.088f * 128.0f,     "Pearl");
    const static inline MaterialData MT_Ruby = MaterialData(Vec4f(0.1745f,    0.01175f,  0.01175f, 1.0f),
                                                                     Vec4f(   0.61424f,    0.04136f,    0.04136f, 1.0f),
                                                                     Vec4f(  0.727811f,   0.626959f,   0.626959f, 1.0f),
                                                            0.6f * 128.0f,       "Ruby");
    const static inline MaterialData MT_Turquoise = MaterialData(Vec4f(0.1f,      0.18725f,   0.1745f, 1.0f),
                                                                     Vec4f(     0.396f,    0.74151f,    0.69102f, 1.0f),
                                                                     Vec4f(  0.297254f,    0.30829f,   0.306678f, 1.0f),
                                                                 0.1f * 128.0f,       "Turquoise");
    const static inline MaterialData MT_Brass = MaterialData(Vec4f(0.329412f,  0.223529f, 0.027451f, 1.0f),
                                                                     Vec4f(  0.780392f,   0.568627f,   0.113725f, 1.0f),
                                                                     Vec4f(  0.992157f,   0.941176f,   0.807843f, 1.0f),
                                                             0.21794872f * 128.0f, "Brass");
    const static inline MaterialData MT_Bronze = MaterialData(Vec4f(0.2125f,     0.1275f,    0.054f, 1.0f),
                                                                     Vec4f(     0.714f,     0.4284f,    0.18144f, 1.0f),
                                                                     Vec4f(  0.393548f,   0.271906f,   0.166721f, 1.0f),
                                                              0.2f * 128.0f,       "Bronze");
    const static inline MaterialData MT_Chrome = MaterialData(Vec4f(0.25f,         0.25f,     0.25f, 1.0f),
                                                                     Vec4f(       0.4f,        0.4f,        0.4f, 1.0f),
                                                                     Vec4f(  0.774597f,   0.774597f,   0.774597f, 1.0f),
                                                              0.6f * 128.0f,       "Chrome");
    const static inline MaterialData MT_Copper = MaterialData(Vec4f(0.19125f,    0.0735f,   0.0225f, 1.0f),
                                                                     Vec4f(    0.7038f,    0.27048f,     0.0828f, 1.0f),
                                                                     Vec4f(  0.256777f,   0.137622f,   0.086014f, 1.0f),
                                                              0.1f * 128.0f,       "Copper");
    const static inline MaterialData MT_Gold = MaterialData(Vec4f(0.24725f,    0.1995f,   0.0745f, 1.0f),
                                                                     Vec4f(   0.75164f,    0.60648f,    0.22648f, 1.0f),
                                                                     Vec4f(  0.628281f,   0.555802f,   0.366065f, 1.0f),
                                                            0.4f * 128.0f,       "Gold");
    const static inline MaterialData MT_Silver = MaterialData(Vec4f(0.19225f,   0.19225f,  0.19225f, 1.0f),
                                                                     Vec4f(   0.50754f,    0.50754f,    0.50754f, 1.0f),
                                                                     Vec4f(  0.508273f,   0.508273f,   0.508273f, 1.0f),
                                                              0.4f * 128.0f,       "Silver");
    const static inline MaterialData MT_BlackPlastic = MaterialData(Vec4f(0.0f,   0.0f,  0.0f, 1.0f),
                                                                     Vec4f(      0.01f,       0.01f,       0.01f, 1.0f),
                                                                     Vec4f(      0.50f,       0.50f,       0.50f, 1.0f),
                                                                    0.25f * 128.0f,  "BlackPlastic");
    const static inline MaterialData MT_CyanPlastic = MaterialData(Vec4f(0.0f,               0.1f,       0.06f, 1.0f),
                                                                     Vec4f(       0.0f, 0.50980392f, 0.50980392f, 1.0f),
                                                                     Vec4f(0.50196078f, 0.50196078f, 0.50196078f, 1.0f),
                                                                   0.25f * 128.0f,        "CyanPlastic");
    const static inline MaterialData MT_GreenPlastic = MaterialData(Vec4f(0.0f,   0.0f,  0.0f, 1.0f),
                                                                     Vec4f(       0.1f,       0.35f,        0.1f, 1.0f),
                                                                     Vec4f(      0.45f,       0.55f,       0.45f, 1.0f),
                                                                    0.25f * 128.0f,  "GreenPlastic");
    const static inline MaterialData MT_RedPlastic = MaterialData(Vec4f(0.0f, 0.0f, 0.0f, 1.0f),
                                                                     Vec4f(       0.5f,        0.0f,        0.0f, 1.0f),
                                                                     Vec4f(       0.7f,        0.6f,        0.6f, 1.0f),
                                                                  0.25f * 128.0f, "RedPlastic");
    const static inline MaterialData MT_WhitePlastic = MaterialData(Vec4f(0.0f,   0.0f,  0.0f, 1.0f),
                                                                     Vec4f(      0.55f,       0.55f,       0.55f, 1.0f),
                                                                     Vec4f(      0.70f,       0.70f,       0.70f, 1.0f),
                                                                    0.25f * 128.0f,  "WhitePlastic");
    const static inline MaterialData MT_YellowPlastic = MaterialData(Vec4f(0.0f,   0.0f,  0.0f, 1.0f),
                                                                     Vec4f(       0.5f,        0.5f,        0.0f, 1.0f),
                                                                     Vec4f(      0.60f,       0.60f,       0.50f, 1.0f),
                                                                     0.25f * 128.0f,  "YellowPlastic");
    const static inline MaterialData MT_BlackRubber = MaterialData(Vec4f(0.02f,    0.02f, 0.02f, 1.0f),
                                                                     Vec4f(      0.01f,       0.01f,       0.01f, 1.0f),
                                                                     Vec4f(       0.4f,        0.4f,        0.4f, 1.0f),
                                                                   0.078125f * 128.0f, "BlackRubber");
    const static inline MaterialData MT_CyanRubber = MaterialData(Vec4f(0.0f,     0.05f, 0.05f, 1.0f),
                                                                     Vec4f(       0.4f,        0.5f,        0.5f, 1.0f),
                                                                     Vec4f(      0.04f,        0.7f,        0.7f, 1.0f),
                                                                  0.078125f * 128.0f, "CyanRubber");
    const static inline MaterialData MT_GreenRubber = MaterialData(Vec4f(0.0f,     0.05f,  0.0f, 1.0f),
                                                                     Vec4f(       0.4f,        0.5f,        0.4f, 1.0f),
                                                                     Vec4f(      0.04f,        0.7f,       0.04f, 1.0f),
                                                                   0.078125f * 128.0f, "GreenRubber");
    const static inline MaterialData MT_RedRubber = MaterialData(Vec4f(0.05f,     0.0f,  0.0f, 1.0f),
                                                                     Vec4f(       0.5f,        0.4f,        0.4f, 1.0f),
                                                                     Vec4f(       0.7f,       0.04f,       0.04f, 1.0f),
                                                                 0.078125f * 128.0f, "RedRubber");
    const static inline MaterialData MT_WhiteRubber = MaterialData(Vec4f(0.05f,    0.05f, 0.05f, 1.0f),
                                                                     Vec4f(       0.5f,        0.5f,        0.5f, 1.0f),
                                                                     Vec4f(       0.7f,        0.7f,        0.7f, 1.0f),
                                                                   0.078125f * 128.0f, "WhiteRubber");
    const static inline MaterialData MT_YellowRubber = MaterialData(Vec4f(0.05f,    0.05f,  0.0f, 1.0f),
                                                                     Vec4f(       0.5f,        0.5f,        0.4f, 1.0f),
                                                                     Vec4f(       0.7f,        0.7f,       0.04f, 1.0f),
                                                                    0.078125f * 128.0f, "YellowRubber");

    ////////////////////////////////////////////////////////////////////////////////
    static StdVT<MaterialData> getBuildInMaterials() {
        StdVT<MaterialData> materials;
        materials.push_back(BuildInMaterials::MT_Emerald);
        materials.push_back(BuildInMaterials::MT_Jade);
        materials.push_back(BuildInMaterials::MT_Obsidian);
        materials.push_back(BuildInMaterials::MT_Pearl);
        materials.push_back(BuildInMaterials::MT_Ruby);
        materials.push_back(BuildInMaterials::MT_Turquoise);
        materials.push_back(BuildInMaterials::MT_Brass);
        materials.push_back(BuildInMaterials::MT_Bronze);
        materials.push_back(BuildInMaterials::MT_Chrome);
        materials.push_back(BuildInMaterials::MT_Copper);
        materials.push_back(BuildInMaterials::MT_Gold);
        materials.push_back(BuildInMaterials::MT_Silver);
        materials.push_back(BuildInMaterials::MT_BlackPlastic);
        materials.push_back(BuildInMaterials::MT_CyanPlastic);
        materials.push_back(BuildInMaterials::MT_GreenPlastic);
        materials.push_back(BuildInMaterials::MT_RedPlastic);
        materials.push_back(BuildInMaterials::MT_WhitePlastic);
        materials.push_back(BuildInMaterials::MT_YellowPlastic);
        materials.push_back(BuildInMaterials::MT_BlackRubber);
        materials.push_back(BuildInMaterials::MT_CyanRubber);
        materials.push_back(BuildInMaterials::MT_GreenRubber);
        materials.push_back(BuildInMaterials::MT_RedRubber);
        materials.push_back(BuildInMaterials::MT_WhiteRubber);
        materials.push_back(BuildInMaterials::MT_YellowRubber);
        return materials;
    }
};
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
} // end namespace NTCodeBase
