#ifndef TESS_HELER_H
#define TESS_HELER_H

#include <vector>
#include "gtl\vec3.hpp"

typedef gtl::Vec3f vec3_t;
typedef std::vector<vec3_t> vertices_t;

class TessHelper
{
public:
	
	enum {
		ADD_POLY,
		ADD_HOLE
	};

	void test_render();

	void render();
	void add_pnt(int mode, int x, int y);
	void backspace(int mode);

	void clear();

	void save(const char* fname);
	void restore(const char* fname);

private:

	void on_vertices_changed();

	vertices_t path;
	vertices_t hole;

};

#endif
