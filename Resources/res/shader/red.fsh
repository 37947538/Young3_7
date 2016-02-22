
#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D u_texture;
varying vec2 v_texCoord;
varying vec4 v_fragmentColor;
void main(void)
{
    // Convert to greyscale using NTSC weightings
    //vec4 col = texture2D(u_texture, v_texCoord);   temp
    vec4 col = texture2D(CC_Texture0, v_texCoord);
    
//    float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114));
    
    float r = col.a>=0.5 ? 255.0 : col.r;
    float g = 0.0;
    float b = 0.0;
    

    
    gl_FragColor = vec4(r, g, b, col.a);
}
