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
uniform int lights;

uniform sampler2D texture;
uniform sampler2D normal_map;
uniform sampler2D another_texture;

varying vec2 v_texcoord;
varying vec3 normal;
varying vec3 v;


//! [0]
void main()
{

       vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);

       vec3 global_normal = normalize(normal);

       vec3 textural_normal = texture2D(normal_map, v_texcoord).xyz;
       vec3 tangent = cross(global_normal, vec3(1.0,1.0,1.0));
       vec3 binormal = cross(global_normal, tangent);

       vec3 N = tangent * textural_normal.x + binormal * textural_normal.y + global_normal * textural_normal.z;

       vec4 textural_adding = texture2D(texture, v_texcoord) * texture2D(another_texture, v_texcoord * 5.0);

       for (int i = 0; i < lights; i++){
          if(lightSource[i].inner == 0.0 && lightSource[i].outer == 0.0){ // directional
              if(lightSource[i].attenuation == 0.0){ // directional
                  vec4 Iamb = lightSource[i].ambient * mater.ambient;
                  vec4 Idiff = lightSource[i].diffuse * max(dot(N, -lightSource[i].direction.xyz), 0.0) * mater.diffuse;
                  Idiff = clamp(Idiff, 0.0, 1.0);

                  finalColor += (Iamb + Idiff) * texture2D(texture, v_texcoord);
              }else{    // point
                  vec3 L = normalize(lightSource[i].position.xyz - v);
                  vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
                  vec3 R = normalize(-reflect(L,N));

                  //calculate Ambient Term:
                  vec4 Iamb = lightSource[i].ambient * mater.ambient;
                  //calculate Diffuse Term:
                  vec4 Idiff = lightSource[i].diffuse * max(dot(N,L), 0.0) * mater.diffuse;
                  Idiff = clamp(Idiff, 0.0, 1.0);

                  // calculate Specular Term:
                  vec4 Ispec = lightSource[i].specular
                         * pow(max(dot(R,E),0.0), mater.shininess ) * mater.specular;
                  Ispec = clamp(Ispec, 0.0, 1.0);

                  float length = distance(lightSource[i].position.xyz, v);
                  finalColor += (Iamb + Idiff + Ispec) / length / length / lightSource[i].attenuation * textural_adding;
              }
          }else{    // spot
              vec3 L = normalize(lightSource[i].position.xyz - v);
              vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
              vec3 R = normalize(-reflect(L,N));
              float dotProduct = dot(normalize(lightSource[i].direction.xyz), normalize(v - L));
              float sin = sqrt(1.0 - dotProduct * dotProduct);
              float length = distance(lightSource[i].position.xyz, v);

              if(sin < lightSource[i].inner){
                    vec4 Iamb = lightSource[i].ambient * mater.ambient;
                    //calculate Diffuse Term:
                    vec4 Idiff = lightSource[i].diffuse * max(dot(N,L), 0.0) * mater.diffuse;
                    Idiff = clamp(Idiff, 0.0, 1.0);

                    // calculate Specular Term:
                    vec4 Ispec = lightSource[i].specular
                           * pow(max(dot(R,E),0.0), 10.0 ) * mater.specular;
                    Ispec = clamp(Ispec, 0.0, 1.0);

                    finalColor += (Iamb + Idiff + Ispec) / length / length / lightSource[i].attenuation * textural_adding;
              }else if(sin < lightSource[i].outer){
                    vec4 Iamb = lightSource[i].ambient * mater.ambient;
                    //calculate Diffuse Term:
                    vec4 Idiff = lightSource[i].diffuse * max(dot(N,L), 0.0) * mater.diffuse;
                    Idiff = clamp(Idiff, 0.0, 1.0);

                    // calculate Specular Term:
                    vec4 Ispec = lightSource[i].specular
                             * pow(max(dot(R,E),0.0), 10.0 ) * mater.specular;
                    Ispec = clamp(Ispec, 0.0, 1.0);

                    finalColor += (Iamb + Idiff * max((sin -lightSource[i].outer) / (lightSource[i].inner - lightSource[i].outer) , 0.0) + Ispec) / length / length / lightSource[i].attenuation * textural_adding;

              }else{
                  finalColor += lightSource[i].ambient / length / length / lightSource[i].attenuation * textural_adding;

              }
          }


       }

       // write Total Color:
       gl_FragColor = finalColor;
       //gl_FragColor = vec4(0.5, 0.5, 0.5, 0.5);

}
//! [0]

