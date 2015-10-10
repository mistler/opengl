#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute float a_time;

varying vec2 v_texcoord;

//! [0]
void main()
{
    vec4 tmp = a_position;
    float length = sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
    tmp.x /= length;
    tmp.y /= length;
    tmp.z /= length;
    tmp = (1.0 - a_time) * tmp + a_time * a_position;
    gl_Position = mvp_matrix * tmp;


    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    v_texcoord = a_texcoord;
}
//! [0]
