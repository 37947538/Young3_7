
#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
void main(void)
{
    // Convert to greyscale using NTSC weightings
    vec4 col = texture2D(CC_Texture0, v_texCoord);
//    float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114));
    
    //变蓝色
    //float r = 0.0;
    //float g = col.a>=0.5 ? 255.0 : col.g;
    //float b = col.a>=0.5 ? 255.0 : col.b;
    
    float r = col.a>=0.5 ? 0.0 : col.g;
    float g = col.a>=0.5 ? 255.0 : col.g;
    float b = col.a>=0.5 ? 255.0 : col.b;
    gl_FragColor = vec4(r, g, b, col.a);
}
