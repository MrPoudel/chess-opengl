#version 120

varying vec3 f_corRGB;

varying vec3 fN;
varying vec3 fL;
varying vec3 fE;

uniform vec4 ambientTerm, diffuseTerm, specularTerm;
uniform mat4x4 matrizModelView;
uniform vec4 posicaoFLuz;
uniform float coefPhong;

void main( void )
{
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
    vec3 L = normalize(fL);

    vec3 H = normalize( L + E );
    vec4 ambient = ambientTerm;

    float Kd = max(dot(L, N), 0.0);

    vec4 diffuse = Kd * diffuseTerm;
    
    float Ks = pow(max(dot(N, H), 0.0), coefPhong);
    vec4 specular = Ks * specularTerm;

    // discard the specular highlight if the light's behind the vertex
    if( dot(L, N) < 0.0 ) {
		specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    vec4 fColor = ambient + diffuse + specular;
    fColor.a = 1.0;

    gl_FragColor = fColor;
}
