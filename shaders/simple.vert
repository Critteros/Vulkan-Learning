#version 450

vec2 vertexes[3]=vec2[](
    vec2(0.0,-0.5),
    vec2(0.5,0.5),
    vec2(-0.5,0.5)
);

void main()
{
    gl_Position=vec4(vertexes[gl_VertexIndex], 0.0, 1.0);
    
}