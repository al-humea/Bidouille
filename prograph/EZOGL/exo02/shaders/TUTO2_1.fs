#version 430
precision highp float;

// OUTPUT
out vec4 oFragmentColor;
in vec3 couleurs;

// MAIN PROGRAM
void main()
{
	oFragmentColor = vec4(couleurs*4, 1.f);
}