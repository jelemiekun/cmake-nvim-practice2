#shader vertex
#version 410

layout(location = 0) in vec3 L_coordinate;
layout(location = 1) in vec3 L_normal;

uniform vec3 u_NormalMatrix;
uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;
