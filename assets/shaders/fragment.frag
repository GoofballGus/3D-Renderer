#version 330 core

in vec2 fragUV;

uniform sampler2D texture0;

out vec4 fragColor;

void main() {
//    fragColor = texture(texture0, fragUV);
    // Or, for pure test color:
    fragColor = vec4(1, 0, 1, 1); // bright magenta
}
