#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D text1;
uniform sampler2D text2;
uniform float time;

void main() {
    FragColor = mix(texture(text1, texCoord), texture(text2, texCoord), 0.8);
}