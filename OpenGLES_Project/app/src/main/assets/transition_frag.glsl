#version 300 es
precision mediump float;

uniform float uValue;

uniform sampler2D utexture0;
uniform sampler2D utexture1;

in vec2 o_uv;
out vec4 fragColor;

void main(void)
{
    vec4 newColor = vec4(0,0,0,0);
    // 从左向右转场
//    if(o_uv.x <= uValue){
//        newColor = texture(utexture1, vec2(o_uv.x+(1.0f-uValue), o_uv.y));
//    }else{
//        newColor = texture(utexture0,o_uv);
//    }

    // 从右向左转场
//    if(o_uv.x > (1.0-uValue)){
//        newColor = texture(utexture1, vec2(o_uv.x-(1.0f-uValue), o_uv.y));
//    }else{
//        newColor = texture(utexture0,o_uv);
//    }

    // 从左下向右上转场
    if(o_uv.x <= uValue){
        if(o_uv.y <= uValue){
            newColor = texture(utexture1, vec2(o_uv.x+(1.0f-uValue), o_uv.y+(1.0f-uValue)));
        }else{
            newColor = texture(utexture0,o_uv);
        }

    } else{
        newColor = texture(utexture0,o_uv);
    }

    fragColor = newColor;
}