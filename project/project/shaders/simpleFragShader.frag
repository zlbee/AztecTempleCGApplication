// simple shader functionality: texturing
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D theTexture;

void main()
{
    FragColor = texture(theTexture, TexCoord);
}