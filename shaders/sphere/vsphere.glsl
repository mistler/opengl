#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

const int maxLights = 5;


struct lightSourceParameters{
   int type;
   vec4 ambient;
   vec4 diffuse;
   vec4 specular;
   vec4 position;
   vec4 direction;
   float attenuation;
   float inner;
   float outer;

};

struct material{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

uniform lightSourceParameters lightSource[maxLights];
uniform material mater;


uniform mat4 mvp_matrix;
uniform mat4 mv_matrix;
uniform mat4 normal_matrix;

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec4 a_normal;
attribute float a_time;

varying vec2 v_texcoord;
varying vec3 normal;
varying vec3 v;

void main()
{
    vec4 tmp = a_position;

    gl_Position = mvp_matrix * tmp;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
    vec4 tmp3 = (normal_matrix * a_normal);
    normal = normalize(tmp3.xyz);
    vec4 tmp2 = mv_matrix * a_position;
    v = tmp2.xyz;
}
//! [0]
