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
#include "ebo.h"

#define macro_str(s) #s
#define macro_xstr(s) macro_str(s)
#define DATA_PATH std::string(macro_xstr(DEF_DATA_PATH))
#define SHADERS_PATH std::string(macro_xstr(DEF_SHADERS_PATH))

// using namespace EZCOGL;

class Viewer: public EZCOGL::GLViewer
{
	EZCOGL::ShaderProgram::UP shaderPrg;
	EZCOGL::VAO::UP vao;
	EZCOGL::EBO::SP ebo;

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
	shaderPrg = EZCOGL::ShaderProgram::create({{GL_VERTEX_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO1.vs")}, {GL_FRAGMENT_SHADER, EZCOGL::load_src(SHADERS_PATH + "/TUTO1.fs")}}, "Tore");
	
    // CREATE A TORUS :

	float lr = 0.5f; // large radius
	float sr = 0.16f; // samll radius
	int na = 32; // #part on the large radius
	int nb = 16; // #part on the small radius
	// create a std vector to store the 3D positions of the vertices
	std::vector<EZCOGL::GLVec3> positions;
	// "resize" the vector with enough place to push all the vertices needed for the tore
	positions.reserve((na + 1)*(nb + 1));
	// loop to define the 3D positions of all the vertices needed for the tore
	for (int i = 0; i <= na; ++i)
	{
		float alpha = (float)i * 2.0 * M_PI / (float)na;
		for (int j = 0; j <= nb; ++j)
		{
			float beta = (float)j * 2.0 * M_PI / (float)nb;
			EZCOGL::GLVec3 position(
			/*x*/ (sr * cos(beta) + lr) * cos(alpha),
			/*y*/ (sr * cos(beta) + lr) * sin(alpha),
			/*z*/ sr * sin(beta));
			positions.emplace_back(position);
		}
	}
	// INIT some OpenGL params
	EZCOGL::VBO::SP vbo = EZCOGL::VBO::create(EZCOGL::GLVVec3{positions});
	// create a std vector to store the indexes (int) of the vertices
	std::vector<GLuint> indices;
	// "resize" the vector with enough place to push all the indexes needed for the tore
	indices.reserve(na*nb * 2 * 3);
	for (int i = 0; i < na; ++i)
	{
		for (int j = 0; j < nb; ++j)
		{
		indices.emplace_back(i*(nb + 1) + j);
		indices.emplace_back((i + 1)*(nb + 1) + j);
		indices.emplace_back(i*(nb + 1) + j + 1);
		indices.emplace_back((i + 1)*(nb + 1) + j);
		indices.emplace_back(i*(nb + 1) + j + 1);
		indices.emplace_back((i + 1)*(nb + 1) + j + 1);
		}
	}
	// Create and fill a EBO with indices
	ebo = EZCOGL::EBO::create(indices);
	
	vao = EZCOGL::VAO::create({{1, vbo}});

	set_scene_center(EZCOGL::GLVec3(0.f, 0.f, 0.f));
	set_scene_radius(0.3f);

	// Define the color to use when refreshing screen
    glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Viewer::draw_ogl()
{
	// Clear the buffer before to draw the next frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//model
	shaderPrg->bind();
	vao->bind();
	ebo->bind();

	const EZCOGL::GLMat4& model = EZCOGL::Transfo::rotateX(-60.f) * EZCOGL::Transfo::scale(.5f) * EZCOGL::Transfo::translate(0, .2, 0);
	const EZCOGL::GLMat4& view = this->get_view_matrix();
	const EZCOGL::GLMat4& proj = this->get_projection_matrix();
	EZCOGL::set_uniform_value(1, model);
	EZCOGL::set_uniform_value(2, view);
	EZCOGL::set_uniform_value(3, proj);

	// *************
	// Rendering
	// *************
	//PREMIERE PASSE POUR UPDATE LE Z BUFFER
	glEnable(GL_DEPTH_TEST);
	glColorMask(false, false, false, false);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, ebo->length(), GL_UNSIGNED_INT, nullptr);

	glColorMask(true, true, true, true);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, 1.f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDepthMask(false);//ON DISABLE LE DEPTH MASK VU QU'ON L'A FILL JUSTE AVANT
	glDrawElements(GL_TRIANGLES, ebo->length(), GL_UNSIGNED_INT, nullptr);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(true);
}

void Viewer::interface_ogl()
{
	ImGui::GetIO().FontGlobalScale = 1.0f;
	ImGui::Begin("Torus", nullptr, ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetWindowSize({0,0});

	ImGui::Text("FPS :(%2.2lf)", fps_);
	ImGui::End();
}
