#version 430

// INPUT
layout(location = 1) in vec3 position_in;

// UNIFORM
layout(location = 0) uniform mat4 uViewMatrix;
layout(location = 1) uniform mat4 uProjectionMatrix;
out vec3 pos;
// MAIN PROGRAM
void main()
{
	pos = position_in;
	gl_Position = uProjectionMatrix * uViewMatrix * vec4(position_in, 1.0);
}