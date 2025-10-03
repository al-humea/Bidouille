#version 430
precision highp float;

// OUTPUT
// - the default GL framebuffer is a RGBA color buffer
// - you can choose whatever name you want
// - variable is prefixed by "out"
out vec4 oFragmentColor;
in vec2 uv;
layout(binding = 0) uniform sampler2D uSampler;
layout(location = 3) uniform vec4 uColor[255];

void main()
{
	oFragmentColor = texture(uSampler, uv);
    oFragmentColor = uColor[150];
}