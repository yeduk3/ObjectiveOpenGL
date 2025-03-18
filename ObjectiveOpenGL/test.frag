#version 410 core

uniform sampler2D tex;
uniform vec2 invSize;

out vec4 FragColor;

void main() {
    vec2 texCoord = gl_FragCoord.xy * invSize;
    FragColor = texture(tex, texCoord);
}
