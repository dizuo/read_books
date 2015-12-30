uniform sampler2D texture;

void main()
{
	vec2 tex_st = vec2(gl_TexCoord[0].x, 1.0 - gl_TexCoord[0].y);
	gl_FragColor = texture2D(texture, tex_st) * gl_Color;

	// gl_FragColor = gl_Color;
}
