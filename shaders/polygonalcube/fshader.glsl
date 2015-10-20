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
uniform int lights;

uniform sampler2D texture;

varying vec2 v_texcoord;
varying vec3 normal;
varying vec3 v;



//! [0]
void main()
{
    vec3 N = normalize(normal);
       vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);

       for (int i = 0; i < lights; i++){
          if(lightSource[i].inner == 0.0 && lightSource[i].outer == 0.0){ // directional
              if(lightSource[i].attenuation == 0.0){ // directional
                  vec4 Iamb = lightSource[i].ambient;
                  vec4 Idiff = lightSource[i].diffuse * max(dot(N, -lightSource[i].direction.xyz), 0.0);
                  Idiff = clamp(Idiff, 0.0, 1.0);

                  finalColor += (Iamb + Idiff);
              }else{    // point
                  vec3 L = normalize(lightSource[i].position.xyz - v);
                  vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
                  vec3 R = normalize(-reflect(L,N));

                  //calculate Ambient Term:
                  vec4 Iamb = lightSource[i].ambient;
                  //calculate Diffuse Term:
                  vec4 Idiff = lightSource[i].diffuse * max(dot(N,L), 0.0);
                  Idiff = clamp(Idiff, 0.0, 1.0);

                  // calculate Specular Term:
                  vec4 Ispec = lightSource[i].specular
                         * pow(max(dot(R,E),0.0), 10.0 );
                  Ispec = clamp(Ispec, 0.0, 1.0);

                  float length = distance(lightSource[i].position.xyz, v);
                  finalColor += (Iamb + Idiff + Ispec) / length / length / lightSource[i].attenuation;
              }
          }else{    // spot
              vec3 L = normalize(lightSource[i].position.xyz - v);
              vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
              vec3 R = normalize(-reflect(L,N));
              float dotProduct = dot(normalize(lightSource[i].direction.xyz), normalize(v - L));
              float sin = sqrt(1.0 - dotProduct * dotProduct);
              float length = distance(lightSource[i].position.xyz, v);

              if(sin < lightSource[i].inner){
                    vec4 Iamb = lightSource[i].ambient;
                    //calculate Diffuse Term:
                    vec4 Idiff = lightSource[i].diffuse * max(dot(N,L), 0.0);
                    Idiff = clamp(Idiff, 0.0, 1.0);

                    // calculate Specular Term:
                    vec4 Ispec = lightSource[i].specular
                           * pow(max(dot(R,E),0.0), 10.0 );
                    Ispec = clamp(Ispec, 0.0, 1.0);

                    finalColor += (Iamb + Idiff + Ispec) / length / length / lightSource[i].attenuation;
              }else if(sin < lightSource[i].outer){
                    vec4 Iamb = lightSource[i].ambient;
                    //calculate Diffuse Term:
                    vec4 Idiff = lightSource[i].diffuse * max(dot(N,L), 0.0);
                    Idiff = clamp(Idiff, 0.0, 1.0);

                    // calculate Specular Term:
                    vec4 Ispec = lightSource[i].specular
                             * pow(max(dot(R,E),0.0), 10.0 );
                    Ispec = clamp(Ispec, 0.0, 1.0);

                    finalColor += (Iamb + Idiff * max((sin -lightSource[i].outer) / (lightSource[i].inner - lightSource[i].outer) , 0.0) + Ispec) / length / length / lightSource[i].attenuation;

              }else{
                  finalColor += lightSource[i].ambient / length / length / lightSource[i].attenuation;

              }
          }


       }

       // write Total Color:
       gl_FragColor = finalColor;


    // Set fragment color from texture
    //gl_FragColor = vec4(tmp22, 0.86, 0.0, 1.0);
    //gl_FragColor = vec4((normal.x + 1.0), normal.y + 1.0, normal.z + 1.0, 1.0f) / 2.0;
}
//! [0]

