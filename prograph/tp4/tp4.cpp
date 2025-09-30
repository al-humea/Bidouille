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
#include "texturecubemap.h"

#define macro_str(s) #s
#define macro_xstr(s) macro_str(s)
#define DATA_PATH std::string(macro_xstr(DEF_DATA_PATH))
#define SHADERS_PATH std::string(macro_xstr(DEF_SHADERS_PATH))

// using namespace EZCOGL;

class Viewer: public EZCOGL::GLViewer
{
	EZCOGL::ShaderProgram::UP shaderPrg, shaderCube;
	// We use one renderer for each mesh part
	std::vector<EZCOGL::MeshRenderer::UP> car_rend;
	int nbMeshParts;

	//cubemap
	EZCOGL::TextureCubeMap::SP tex_envMap;
	EZCOGL::MeshRenderer::UP cube_rend;

	// Params for lightning and reflection
	EZCOGL::GLVec3 lightPos;
    float intensity;
	// Material
    std::vector<EZCOGL::GLVec3> ka; // Ambient
    std::vector<EZCOGL::GLVec3> kd; // Diffus
    std::vector<EZCOGL::GLVec3> ks;	// Specular
    std::vector<float> ns;	// Shininess

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

Viewer::Viewer() : lightPos(0.f, 0.f, 0.f), intensity(1.f)
{}

void Viewer::init_ogl()
{
	shaderCube = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/envmap.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/envmap.fs")}}, "Envmap");
	tex_envMap = EZCOGL::TextureCubeMap::create();
	tex_envMap->load({DATA_PATH + "/left.jpg", DATA_PATH + "/right.jpg", DATA_PATH + "/top.jpg", DATA_PATH + "/bottom.jpg", DATA_PATH + "/back.jpg", DATA_PATH + "/front.jpg"});

	// ***********************************
	// Geometry
	// ***********************************
	auto meshCube = EZCOGL::Mesh::Cube();
	cube_rend = meshCube->renderer(1, -1, -1, -1, -1);

	shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP4.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP4.fs")}}, "Mesh");
    // Load OBJ file mesh
	auto mesh = EZCOGL::Mesh::load(DATA_PATH + "/models/mustang_GT.obj")->data();
	nbMeshParts = mesh.size();
	// set the renderer and the materials for all the meshes parts
	for (int i = 0; i < nbMeshParts; ++i)
	{
		car_rend.push_back(mesh[i]->renderer(1, 2, -1, -1, -1));
		ka.push_back(mesh[i]->material()->Ka / 100.f);
		kd.push_back(mesh[i]->material()->Kd);
		ks.push_back(mesh[i]->material()->Ks);
		ns.push_back(mesh[i]->material()->Ns);
	}

	// set scene center and radius for the init of matrix view/proj
	set_scene_center(EZCOGL::GLVec3(0.f, 0.f, 0.f));
	set_scene_radius(100.f);

	// Define the color to use when refreshing screen
    glClearColor(0.1, 0.1, 0.1, 1.0);

}

void Viewer::draw_ogl()
{
	// Clear the buffer before to draw the next frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

    // VPM
	const EZCOGL::GLMat4& view = this->get_view_matrix();
	EZCOGL::GLMat4 cp = view;
	cp.block<4, 1>(0, 3).setZero();
	cp.normalize();
	const EZCOGL::GLMat4& proj = this->get_projection_matrix();
    // envmap
	shaderCube->bind();
	EZCOGL::set_uniform_value(0, cp);
	EZCOGL::set_uniform_value(1, proj);
	tex_envMap->bind(0);
	cube_rend->draw(GL_TRIANGLES);
	
	// car
/* 	glEnable(GL_DEPTH_TEST);
	const EZCOGL::GLMat4& model = EZCOGL::Transfo::scale(1.5f);
	shaderPrg->bind();
	// Uniforms variables send to the GPU
	EZCOGL::set_uniform_value(0, model);
	EZCOGL::set_uniform_value(1, view);
	EZCOGL::set_uniform_value(2, proj);	
	EZCOGL::set_uniform_value(3, EZCOGL::Transfo::inverse_transpose(view * model));
	EZCOGL::set_uniform_value(4, EZCOGL::GLVec3(intensity, intensity, intensity));
	EZCOGL::set_uniform_value(5, EZCOGL::Transfo::sub33(view) * lightPos);
	for (int i = 0; i < nbMeshParts; ++i)
	{
		EZCOGL::set_uniform_value(6, ka[i]);
		EZCOGL::set_uniform_value(7, kd[i]);
		EZCOGL::set_uniform_value(8, ks[i]);
		EZCOGL::set_uniform_value(9, ns[i]);
		car_rend[i]->draw(GL_TRIANGLES);
	} */

}

void Viewer::interface_ogl()
{
	ImGui::GetIO().FontGlobalScale = 3.0f;
	ImGui::Begin("TP4", nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize({0,0});

	ImGui::Text("FPS :(%2.2lf)", fps_);
	if (ImGui::Button("Reload shaders"))
		shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP4.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TP4.fs")}}, "Mesh");
	
	ImGui::SliderFloat("Light intensity", &intensity, 0.f, 20.f);
	ImGui::SliderFloat("Light pos X", &lightPos[0], -100.f, 100.f);
	ImGui::SliderFloat("Light pos Y", &lightPos[1], -100.f, 100.f);
	ImGui::SliderFloat("Light pos Z", &lightPos[2], -100.f, 100.f);

	ImGui::End();
}
