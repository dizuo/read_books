#ifndef POLYGON_2D_201512291500_H
#define POLYGON_2D_201512291500_H

#include "vertex-buffer.h"
#include "shader.h"
#include "mat4.h"
#include "vec234.h"
#include <vector>

using namespace ftgl;

typedef struct 
{
	float x, y, z;    // position
	float s, t;       // texture
	float r, g, b, a; // color
} vertex_t;

#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

class Polygon2D
{
public:

	Polygon2D();
	~Polygon2D();
	
	void set_texture_pattern(vec2& pat);
	void add_point(int x, int y);
	void clear();		
	void zoom(float sx, float sy);
	void reset_zoom() { zoom_.x = zoom_.y = 1.0f; }

	void render();
	void reshape(int w, int h);

	static void fufill_test_data(Polygon2D& poly);

	float angle;

private:

	void _make_render_buffer();

	GLuint shader;
	vertex_buffer_t *buffer;
	mat4  model, view, projection;

	bool is_dirty_;
	std::vector<vec2> points_;

	vec2 pattern_;
	vec2 zoom_;

};

#endif
