#version 430

layout(location = 1) in vec3 position_in;
layout(location = 2) in vec2 uv_in;//uv interpolées

layout(location = 0) uniform mat4 uModelMatrix;
layout(location = 1) uniform mat4 uViewMatrix;
layout(location = 2) uniform mat4 uProjectionMatrix;

out vec2 uv;

void main()
{
	uv = uv_in;
	vec4 viewPos = uViewMatrix * uModelMatrix * vec4(position_in, 1.0);
	
	gl_Position = uProjectionMatrix * viewPos;
}