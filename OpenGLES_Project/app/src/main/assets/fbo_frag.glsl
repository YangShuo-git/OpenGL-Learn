#version 300 es
precision mediump float;

uniform sampler2D ufbotexture;

in  vec2 o_uv;
out vec4 fragColor;

void main(void)
{
    vec4 color = texture(ufbotexture, o_uv);
    // 计算灰度值（黑白滤镜） 说明离屏渲染有效
    float gray = dot(color.rgb, vec3(0.299, 0.587, 0.114));
    fragColor = vec4(vec3(gray), color.a);
}