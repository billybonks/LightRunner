#ifdef GL_ES
precision mediump float;
#endif

// 1
varying vec2 v_texCoord;
uniform sampler2D u_texture;
uniform sampler2D u_colorRampTexture;
varying vec4 v_fragmentColor;
uniform float r;
uniform float g;
uniform float b;

void main()
{ // 2
    vec3 normalColor = texture2D(u_texture, v_texCoord).rgb;

    // 3
    float rampedR = texture2D(u_colorRampTexture, vec2(normalColor.r, 0)).r;
    float rampedG = texture2D(u_colorRampTexture, vec2(normalColor.g, 0)).g;
    float rampedB = texture2D(u_colorRampTexture, vec2(normalColor.b, 0)).b;
	float ratio=1;//gl_FragCoord.x/480;
    gl_FragColor = vec4(r*ratio,g*ratio,b*ratio,1);
// 4
}