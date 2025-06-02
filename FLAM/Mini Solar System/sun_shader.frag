#version 330 core
out vec4 FragColor;
uniform float time;

void main() {
    float glow = abs(sin(time * 2.0));
    FragColor = vec4(glow, glow * 0.8, 0.1, 1.0);
}
