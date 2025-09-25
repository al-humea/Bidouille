layout(binding = 0) uniform sampler2D usampler;
layout(location = 4) uniform vec4 colormap[255];

void main(){
    int height = int(v_terrainheight * 255);
    if (height < 25) ofragmentcolor = colormap[height];
    else ofragmentcolor = vec4(v_terrainheight) * colormap[height];
}