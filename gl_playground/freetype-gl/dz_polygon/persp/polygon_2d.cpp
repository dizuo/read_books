#include "polyon_2d.h"
#include "triangulate.h"

// 正交投影下，在cpu端预计算好各个顶点的纹理坐标。
// 透视投影下，在vs中转化成屏幕坐标，然后计算顶点的纹理坐标。

// 如果透视必须在vs中计算
// 透视以后，vs中计算的时候，转化成屏幕坐标的顶点z值如何确定？

#define VS_COMPUTE_ST

#define GL_COPY_TEXTURE_DEMO

Polygon2D::Polygon2D()
	: is_dirty_(true)
{
	buffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");
	shader = shader_load("dz_polygon/polygon.vert", "dz_polygon/polygon.frag");

	int num = 0;
	glGetProgramiv(shader, GL_ACTIVE_ATTRIBUTES, &num);
	for (int k = 0; k < num; k++)
	{
		GLsizei length = 0, size = 0;
		GLenum type;
		GLchar name[1024];
		glGetActiveAttrib(shader, k, 1024, &length, &size, &type, name);
		printf("%d %s\n", k, name);
	}

	zoom_.x = zoom_.y = 1.0f;
	angle = 0.0f;
}

Polygon2D::~Polygon2D()
{
	if (buffer)
	{
		vertex_buffer_delete(buffer);
		buffer = 0;
	}
}

void Polygon2D::fufill_test_data(Polygon2D& poly)
{
	float vertices[] = { 365.000000, 142.000000,
		564.000000, 135.000000,
		639.000000, 283.000000,
		529.000000, 379.000000,
		281.000000, 433.000000,
		168.000000, 303.000000,
		162.000000, 165.000000,
		259.000000, 99.000000 };

	int num = sizeof(vertices) / sizeof(vertices[0]);
	for (int k = 0; k < num; k += 2)
	{
		poly.add_point(vertices[k], vertices[k + 1]);
	}
}

void Polygon2D::set_texture_pattern(vec2& pat)
{
	pattern_.x = pat.x;
	pattern_.y = pat.y;
}

void Polygon2D::zoom(float sx, float sy)
{
	zoom_.x += sx;
	zoom_.y += sy;
}

void Polygon2D::add_point(int x, int y)
{
	vec2 pos;
	pos.x = x; pos.y = y;
	points_.push_back(pos);

	is_dirty_ = true;
}

void Polygon2D::clear()
{
	points_.clear();
	is_dirty_ = true;
}

void Polygon2D::reshape(int width, int height)
{
	mat4_set_identity(&projection);
	mat4_set_identity(&model);
	mat4_set_identity(&view);
	
#ifdef ORTHO
	mat4_set_orthographic(&projection, 0, width, 0, height, -1, 1);
#else
	mat4_set_perspective(&projection, 45.0f, width/(float)height, 0.1f, 10.0f);
	mat4_set_translation(&view, 0, 0, -5.0f);
#endif
}

void Polygon2D::_make_render_buffer()
{
	if (points_.size() < 3)
		return;

	Vector2dVector contour;
	TXVECTOR_INIT(contour);

	IndexVector result;
	TXVECTOR_INIT(result);
	
	vec4 bbox = { { 0, 0, 0, 0 } };

	TXVECTOR_CLEAR(contour);
	for (int j = 0; j<points_.size(); j++)
	{
		Vector2d v2d;
		v2d.x = points_[j].x;
		v2d.y = points_[j].y;

		TXVECTOR_PUSH_BACK(contour, v2d);
	}

	TXVECTOR_CLEAR(result);
	if (!Triangulate(contour, result))
	{
		printf("triangulate error\n");
	}

#ifndef ORTHO

	vec2 minp, maxp;
	minp.x = 800; minp.y = 600;
	maxp.x = maxp.y = 0;

	int num = points_.size();
	for (int k = 0; k < num; k ++)
	{
		minp.x = min(minp.x, points_[k].x);
		minp.y = min(minp.y, points_[k].y);
		maxp.x = max(maxp.x, points_[k].x);
		maxp.y = max(maxp.x, points_[k].y);
	}

	vec2 size;
	size.x = maxp.x - minp.x;
	size.y = maxp.y - minp.y;

	for (int k = 0; k < num; k ++)
	{
		points_[k].x = (points_[k].x - minp.x) / size.x - 0.5f;
		points_[k].y = (points_[k].y - minp.y) / size.y - 0.5f;
	}

#endif

	vertex_buffer_clear(buffer);
	
	vertex_t* vertices = (vertex_t*)malloc( points_.size() * sizeof(vertex_t) );
	for (int k = 0; k < points_.size(); k++)
	{
		vertices[k].x = points_[k].x; vertices[k].y = points_[k].y; vertices[k].z = 0;

#ifdef VS_COMPUTE_ST
		vertices[k].s = vertices[k].t = 0.0f;
#else
		vertices[k].s = vertices[k].x / pattern_.x;
		vertices[k].t = vertices[k].y / pattern_.y;
#endif

		vertices[k].r = vertices[k].g = vertices[k].b = 1.0f;
		vertices[k].a = 1.0f;
	}

	vertex_buffer_push_back(buffer, vertices, points_.size(), (GLuint*)&TXVECTOR_AT(result, 0), (GLuint)TXVECTOR_SIZE(result));

	free(vertices);
}

void Polygon2D::render()
{
	if (is_dirty_)
	{
		_make_render_buffer();
		is_dirty_ = false;
	}

	mat4_set_identity(&model);
	mat4_scale(&model, zoom_.x, zoom_.y, 1);
	mat4_rotate(&model, angle, 1.0f, 0.0f, 0.0f);

	vec4 color = { { 0.067, 0.333, 0.486, 1.0 } };
	float a = 1.0f;

	GLint vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);

	glUseProgram(shader);
	{
		float loc_vp[4] = { vp[0], vp[1], vp[2], vp[3] };
		glUniform1i(glGetUniformLocation(shader, "texture"), 0);
		
		// glUniform4fv(glGetUniformLocation(shader, "viewport"), 1, loc_vp);
		glUniform1iv(glGetUniformLocation(shader, "viewport"), 4, vp);
		
#ifdef VS_COMPUTE_ST
		glUniform2fv(glGetUniformLocation(shader, "pattern_sz"), 1, &pattern_.x);
#else
		vec2 pat = { { 0, 0 } };
		glUniform2fv(glGetUniformLocation(shader, "pattern_sz"), 1, &pat.x);
#endif

		glUniformMatrix4fv(glGetUniformLocation(shader, "model"),
			1, 0, model.data);
		glUniformMatrix4fv(glGetUniformLocation(shader, "view"),
			1, 0, view.data);
		glUniformMatrix4fv(glGetUniformLocation(shader, "projection"),
			1, 0, projection.data);
		vertex_buffer_render(buffer, GL_TRIANGLES);
	} 
	glUseProgram(0);

	int error = glGetError();
	if (error)
		printf("error = %d\n", error);

#ifdef GL_COPY_TEXTURE_DEMO
	if (cp_tex_.mId == 0)
	{
		cp_tex_.create_texture(vp[2], vp[3]);
	}
	cp_tex_.copy_from_screen(vp[0], vp[1], vp[2], vp[3]);
	cp_tex_.render_to_screen(vp[2], vp[3]);
#endif

}


