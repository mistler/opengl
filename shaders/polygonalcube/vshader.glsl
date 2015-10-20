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

uniform lightSourceParameters lightSource[maxLights];


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

vec4 norm(vec4 tmp){
    float length = sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
    tmp.x /= length;
    tmp.y /= length;
    tmp.z /= length;
    return tmp;
}


//! [0]
void main()
{
    vec4 tmp = norm(a_position);
    tmp = (1.0 - a_time) * tmp + a_time * a_position;

    vec4 tmp2 = mv_matrix * tmp;
    v = tmp2.xyz;

    gl_Position = mvp_matrix * tmp;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
    vec4 tmp3 = normal_matrix * ((1.0 - a_time) * a_position + a_time * a_normal);
    normal = normalize(tmp3.xyz);
}
//! [0]
