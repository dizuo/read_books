uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 pattern_sz;
uniform int viewport[4];
// uniform vec4 viewport;

attribute vec3 vertex;
attribute vec2 tex_coord;
attribute vec4 color;

void main()
{
	vec4 norm_coord = projection*(view*(model*vec4(vertex,1.0)));

	if (pattern_sz.x != 0)
	{
		vec2 screen_pos = norm_coord.xy / norm_coord.w;
		screen_pos.x = (screen_pos.x + 1.0) * viewport[2] / 2. + viewport[0];
		screen_pos.y = (screen_pos.y + 1.0) * viewport[3] / 2. + viewport[1];

		gl_TexCoord[0].xy = vec2( screen_pos.x /pattern_sz.x, screen_pos.y /pattern_sz.y ) + tex_coord.xy;
	}
	else
	{
		gl_TexCoord[0].xy = tex_coord;
	}

    gl_FrontColor = color;   
	gl_Position = norm_coord;

}
