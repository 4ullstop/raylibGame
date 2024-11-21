#version 330

in vec2 fragTexCoord;
out vec4 finalColor;

uniform sampler2D texture0;
uniform vec2 uvOffset;
uniform vec2 uvScale;

void main() 
{
    vec2 adjustedUV = fragTexCoord * uvScale + uvOffset;
    finalColor = texture(texture0, adjustedUV);
}