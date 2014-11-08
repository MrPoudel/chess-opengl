#version 120

attribute vec3 v_coord3d;
attribute vec3 v_normal3d;

uniform mat4x4 matrizProj;
uniform mat4x4 matrizModelView;
uniform vec4 posicaoFLuz;

varying vec3 fN;
varying vec3 fE;
varying vec3 fL;

void main( void )
{
	fN = v_normal3d;
    fE = (matrizModelView * vec4(v_coord3d, 1.0)).xyz;
    fL = posicaoFLuz.xyz;

    gl_Position = matrizProj * matrizModelView * vec4(v_coord3d, 1.0);
}
