#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;

//! [0]
void main()
{
    // Set fragment color from texture
    //gl_FragColor = vec4(0.85, 0.86, 0.0, 1.0);
    gl_FragColor = (noise4(v_texcoord.x) + 1.0) / 2.0;
}
//! [0]

