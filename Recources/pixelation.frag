#version 330 core

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D screenTexture; // The texture containing the scene

vec2 u_resolution = vec2(2460, 1440);
uniform float u_downscale_factor = 3.0f;
uniform int u_dither = 1;

const float offset = 1.0 / 300.0;  
vec3 color;

mat4 psx_dither_table=mat4
(
    0,8,2,10,
    12,4,14,6,
    3,11,1,9,
    15,7,13,5
);


vec3 dither(vec3 color, vec2 p){
    //extrapolate 16bit color float to 16bit integer space
    color*=255.;

    //get dither value from dither table (by indexing it with column and row offsets)
    highp int col = int(mod(p.x, 4.));
    highp int row= int(mod(p.y, 4.));
    float dither = psx_dither_table[col][row];

    //dithering process as described in PSYDEV SDK documentation
    color += (dither/2. - 4.);

    //clamp to 0
    color = max(color,0.);
    
    //truncate to 5bpc precision via bitwise AND operator, and limit value max to prevent wrapping.
    //PS1 colors in default color mode have a maximum integer value of 248 (0xf8)
    ivec3 c = ivec3(color) & ivec3(0xf8);
    color = mix( vec3(c), vec3(0xf8),  step(vec3(0xf8),color) );
  
    //bring color back to floating point number space
    color/=255.; 
    return color;
}
void main() {

  //pixelate the texture (i.e. many pixels are mapped to the same texel/block)
  vec2 target_res = u_resolution/u_downscale_factor;
  vec2 pixelated_uv = floor(TexCoord*target_res)/target_res;
  vec3 color= texture(screenTexture,  pixelated_uv).rgb; 
  vec3 result = dither(color, floor(gl_FragCoord.xy/u_downscale_factor) );

  float darkeningFactor = 1.0f;
  result *= darkeningFactor;
  FragColor=vec4(result,1.0f);
}