#ifndef OVERLAP_ELIMINATE_TEST_201411261504_H
#define OVERLAP_ELIMINATE_TEST_201411261504_H

// #define AOE

#ifdef AOE
#include "PolygonClosureComputation/ApproximateOverlapsElimination.h"
#else
#include <vector>
#include "PolygonClosureComputation/Point.h"
#endif

class OverlayEliminateTest
{
public:

#ifdef AOE
	typedef ApproximateOverlapsElimination::Polyline path_t;
#else
	typedef std::vector<Point> path_t;
#endif
	
	typedef std::vector< path_t > path_vec_t;

	OverlayEliminateTest() : tolerance_(0), is_dirty_(false), cur_path_(NULL)
	{}

	void add_path(const path_t& path) { 
		m_path_vec_.push_back(path);
		cur_path_ = &m_path_vec_[ m_path_vec_.size() - 1];
	}

	void set_tolerance(float t) { tolerance_ = t; _set_dirty(true); }

	void clear() { m_path_vec_.clear(); _set_dirty(true); }

	void render();
	
	void eliminate();

	path_t* get_cur_path() { 
		return cur_path_;
	}

	void reset_cur_path() 
	{
		cur_path_ = NULL; 
		_set_dirty(true);
	}

	void load_from_file(const char* fname);
	void save_to_file(const char* fname, bool to_file = true);
	void save_to_svg(const char* fname);

private:
	
	void _render_path(const path_t& path, bool is_framework=true);

	void _set_dirty(bool f) { is_dirty_ = f; }

	float tolerance_;
	path_vec_t m_path_vec_;
	std::vector<bool> m_flag_vec_;

	path_t* cur_path_;

	bool is_dirty_;

};

class SVGHelper
{
public:
	typedef OverlayEliminateTest::path_t path_t;
	typedef OverlayEliminateTest::path_vec_t path_vec_t;
	
	enum COLOR
	{
		WHITE = 0,
		RED = 1,
		YELLOW = 2,
		BLUE = 3,
		GRAY = 4,
		LIGHT_GRAY = 5,

		COLOR_MAX = 0xffff
	};

	void write_svg(const char* fname, const path_vec_t& path_vec, const std::vector<bool>& flag_vec, float tolerance);

private:

	void save_path(const path_t& path, COLOR c, int width, bool is_closed, FILE* fp);

	char* get_color(COLOR c);

};

#endif
