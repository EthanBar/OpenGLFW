#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D text;
uniform float time;

void main() {
    FragColor = texture(text, texCoord + (sin(time) / 2) + 0.5) * vec4(vertexColor, 1.0);
}