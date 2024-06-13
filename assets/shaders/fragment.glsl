#version 410 core
out vec4 FragColor;

uniform sampler2D grassSampler;
uniform sampler2D landSampler;
uniform sampler2D noiseSampler;
uniform sampler2D caoshenSampler;

in vec3 color;
in vec2 uv;

void main()
{
    vec4 grassColor = texture(grassSampler, uv);
    vec4 landColor = texture(landSampler, uv);
    vec4 noiseColor = texture(noiseSampler, uv);
    vec4 caoshenColor = texture(caoshenSampler, uv);
//    float weight = noiseColor.r;
////    vec4 finalColor = grassColor * (1.0 - weight) + landColor * weight;
//    vec4 finalColor = mix(grassColor, landColor, weight);
//    FragColor = vec4(finalColor.rgb, 1.0);
    FragColor = vec4(caoshenColor.rgb, 1.0);
}
