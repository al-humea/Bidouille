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
	EZCOGL::MeshRenderer::UP cube_rend;
	float tps;
	EZCOGL::Texture2D::SP tex;

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

Viewer::Viewer()
{}

void Viewer::init_ogl()
{
	shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP3_2.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP3_2.fs")}}, "Square");
	
	//texture
	tex = EZCOGL::Texture2D::create({GL_LINEAR, GL_REPEAT});
	tex->load(DATA_PATH + "/lined_woolen.png", false);
	// ***********************************
	// Geometry
	// ***********************************
	auto meshCube = EZCOGL::Mesh::Cube();
	cube_rend = meshCube->renderer(1, -1, 2, -1, -1);
	// create a VBO with the position of 4 2D vertices (for point and line loop draw)
	set_scene_center(EZCOGL::GLVec3(0.f, 0.f, 0.f));
	set_scene_radius(5.f);
	// Define the color to use when refreshing screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
}

void Viewer::draw_ogl()
{
	// Clear the buffer before shaders/TP3.fs shaders/TP3.vs= this->get_view_matrix();
	const EZCOGL::GLMat4& proj = this->get_projection_matrix();
	const EZCOGL::GLMat4& modelCube = EZCOGL::Transfo::scale(1.f);
	// ***********************************
	// Rendering
	// ***********************************
	glEnable(GL_DEPTH_TEST);
	// Bind the shader program (EZCOGL wrapper)
	tex->bind(0);
	shaderPrg->bind();
	// Bind the VAO (EZCOGL wrapper)
	tps = EZCOGL::current_time();
	EZCOGL::set_uniform_value(0, modelCube);
	EZCOGL::set_uniform_value(1, view);
	EZCOGL::set_uniform_value(2, proj);
	// 1st pass : Draw Points
	cube_rend->draw(GL_TRIANGLES);
}

void Viewer::interface_ogl()
{
	ImGui::GetIO().FontGlobalScale = 3.0f;
	ImGui::Begin("TP1 Introduction",nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize({0,0});

	ImGui::Text("FPS :(%2.2lf)", fps_);
	if (ImGui::Button("Reload shaders"))
		shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP3_2.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP3_2.fs")}}, "Square");
	if (ImGui::CollapsingHeader("Texture content"))
	ImGui::Image(reinterpret_cast<ImTextureID>(tex->id()), ImVec2(400, 400), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::End();
}
