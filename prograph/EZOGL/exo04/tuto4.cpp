/*******************************************************************************
* EasyCppOGL:   Copyright (C) 2019,                                            *
* Sylvain Thery, IGG Group, ICube, University of Strasbourg, France            *
*                                                                              *
* This library is free software; you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published by the *
* Free Software Foundation; either version 2.1 of the License, or (at your     *
* option) any later version.                                                   *
*                                                                              *
* This library is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
* for more details.                                                            *
*                                                                              *
* You should have received a copy of the GNU Lesser General Public License     *
* along with this library; if not, write to the Free Software Foundation,      *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
*                                                                              *
* Contact information: thery@unistra.fr                                        *
*******************************************************************************/

#include <iostream>
#include "shader_program.h"
#include "gl_viewer.h"
#include "mesh.h"

#define macro_str(s) #s
#define macro_xstr(s) macro_str(s)
#define DATA_PATH std::string(macro_xstr(DEF_DATA_PATH))
#define SHADERS_PATH std::string(macro_xstr(DEF_SHADERS_PATH))

// using namespace EZCOGL;
class Viewer: public EZCOGL::GLViewer
{
    EZCOGL::ShaderProgram::UP shaderPrg;
    //Dimensions plane
    int resolution = 64;
    int scale = 30;
    EZCOGL::VAO::UP vao;
    EZCOGL::EBO::SP ebo;
    // light+mat
    EZCOGL::GLVec3 lightPos;
    float intensity = 1.f;

    //gen
    float terrainElevation = 0.1f;
    EZCOGL::GLVec2 noise;
    EZCOGL::GLVec2 noiseScale;
    float startHeight = 0.01f;
    float weight = 0.017f;
    float mult = 3.f;
    float noisePower = 2.f;
    int frequency = 3;

    public:
    Viewer();
    void init_ogl() override;
    void draw_ogl() override;
    void interface_ogl() override;
};

int main(int, char**)
{
    Viewer v;
    return v.launch3d();
}

Viewer::Viewer(): lightPos(0.f, -40.f, 0.f), noise(0.f, 0.f), noiseScale(0.5f, 0.5f)
{}

void Viewer::init_ogl()
{
    shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO.fs")}}, "Lighting");


    // ***********************************
    // Geometry
    // ***********************************
    // Load geometry
    int resScale = resolution * scale;
    std::vector<EZCOGL::GLVec3> positions;
    positions.reserve(resScale * resScale);
    for (uint j = 0; j < resScale; ++j)
    {
    for (uint i = 0; i < resScale; ++i)
        {
        // vertex between [-0.5;0.5] * scale
        EZCOGL::GLVec3 position(/*x*/ ((float)i / (float)(resScale - 1) - 0.5f) * scale,
        /*y*/ 0.f,
        /*z*/ ((float)j / (float)(resScale - 1) - 0.5f) * scale);
        positions.emplace_back(position);
        }
    }
    EZCOGL::VBO::SP vbo_p = EZCOGL::VBO::create(positions);
    // Create the VAO and associate the VBO to it
	vao = EZCOGL::VAO::create({{1, vbo_p}});
    std::vector<GLuint> indices;
    indices.reserve((resScale - 1) * (resScale - 1) * 2 * 3);
    for (uint j = 0; j < resScale - 1; ++j)
    {
        for (uint i = 0; i < resScale - 1; ++i)
        {
        // triangle 1
        indices.emplace_back(i + j * resScale);
        indices.emplace_back((i + 1) + j * resScale);
        indices.emplace_back(i + (j + 1) * resScale);
        // triangle 2
        indices.emplace_back(i + (j + 1) * resScale);
        indices.emplace_back((i + 1) + j * resScale);
        indices.emplace_back((i + 1) + (j + 1) * resScale);
        }
    }
    // Create and fill a EBO with indices
    ebo = EZCOGL::EBO::create(indices);
    // set scene center and radius for the init of matrix view/proj
    set_scene_center(EZCOGL::GLVec3(0.f, 0.f, 0.f));
    set_scene_radius(80.f);

    // Define the color to use when refreshing screen
    glClearColor(0.64, 0.85, 1.f, 1.0);

}

void Viewer::draw_ogl()
{
    // Clear the buffer before to draw the next frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable Depth test
    glEnable(GL_DEPTH_TEST);

    // Construct MVP matrix
    const EZCOGL::GLMat4& model = EZCOGL::Transfo::rotateX(20.f);
    const EZCOGL::GLMat4& view = this->get_view_matrix();
    const EZCOGL::GLMat4& proj = this->get_projection_matrix();

    // ***********************************
    // Rendering
    // ***********************************
    vao->bind();
    ebo->bind();
    shaderPrg->bind();
    // Uniforms variables send to the GPU
    EZCOGL::set_uniform_value(0, model);
    EZCOGL::set_uniform_value(1, view);
    EZCOGL::set_uniform_value(2, proj);
    EZCOGL::set_uniform_value(3, terrainElevation);
    EZCOGL::set_uniform_value(4, noise);
    EZCOGL::set_uniform_value(5, noiseScale);
    EZCOGL::set_uniform_value(6, startHeight);
    EZCOGL::set_uniform_value(7, weight);
    EZCOGL::set_uniform_value(8, mult);
    EZCOGL::set_uniform_value(9, noisePower);
    EZCOGL::set_uniform_value(10, frequency);
    EZCOGL::set_uniform_value(11, resolution);
    EZCOGL::set_uniform_value(12, EZCOGL::Transfo::inverse_transpose(view * model));
    EZCOGL::set_uniform_value(13, EZCOGL::Transfo::sub33(view * model) * lightPos);
    EZCOGL::set_uniform_value(14, intensity);

    glDrawElements(GL_TRIANGLES, ebo->length(), GL_UNSIGNED_INT, nullptr);
}

void Viewer::interface_ogl()
{
    ImGui::GetIO().FontGlobalScale = 1.0f;
    ImGui::Begin("Tuto 4", nullptr, ImGuiWindowFlags_NoSavedSettings);
    ImGui::SetWindowSize({0,0});

    ImGui::Text("FPS :(%2.2lf)", fps_);
    if (ImGui::Button("Reload shaders"))
        shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO4.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO4.fs")}}, "Lighting");
    ImGui::Text("Resolution : %2d, Scale : %d", resolution, scale);
    ImGui::Text("Generation");
    ImGui::SliderFloat("Elevation", &terrainElevation, 0.f, 140.f); // terrainElevation : float
    ImGui::SliderFloat2("Noise X - Y", noise.data(), -10.f, 10.f); // noise : EZCOGL::GLVec2
    ImGui::SliderFloat2("Noise scale X - Y", noiseScale.data(), 0.5f, 2.f); // noiseScale : EZCOGL::GLVec2
    ImGui::SliderFloat("StartHeight", &startHeight, .01f, 10.f); // startHeight : float
    ImGui::SliderFloat("Weight", &weight, 0.01f, 10.f); // weight : float
    ImGui::SliderFloat("Mult", &mult, 0.01f, 10.f); // mult : float
    ImGui::SliderFloat("Noise power", &noisePower, 1.f, 20.f); // noisePower : float
    ImGui::SliderInt("Frequency", &frequency, 1, 10); // frequency : int
    ImGui::Text("Lumière");
    ImGui::SliderFloat("Intensity", &intensity, .1f, 1.f);
    ImGui::SliderFloat3("lightPos", lightPos.data(), -100.f, 100.f);
    ImGui::End();
}
