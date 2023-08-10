#version 310 es
precision highp float;
precision highp int;

layout(location = COLOR0) in vec4 v_color;

layout(location = SV_Target0) out vec4 FragColor;

void main()
{
    FragColor = v_color;
}