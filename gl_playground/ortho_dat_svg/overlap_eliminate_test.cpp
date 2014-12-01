#include "overlap_eliminate_test.h"

#include <math.h>
#include <gl/glut.h>

#define RENDER_AREA
#define V2

void OverlayEliminateTest::_render_path(const path_t& path, bool is_framework)
{
	if (path.size() < 2) return;
	
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_DOUBLE, 0, &path[0].x);
	
	glDrawArrays(GL_LINE_STRIP, 0, path.size());	

	if (!is_framework)
	{
		return;
	}

#ifdef RENDER_AREA

	glPolygonMode(GL_FRONT, GL_LINE);
	float last_c4[4] = {0};
	glGetFloatv(GL_CURRENT_COLOR, last_c4);
	glColor4f(0.8f, 0.8f, 0.8f, 0.3f);

	path_t loc_vec;

#ifdef V1
	loc_vec.reserve(path.size() * 2);

	for (int seg = 1;  seg < path.size(); seg++)
	{
		Point delta = path[seg] - path[seg-1];
		double length = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (length == 0)
		{
			continue;
		}

		delta.x /= length;
		delta.y /= length;

		Point offset(-delta.y, delta.x);

		if (seg == 1)
		{
			loc_vec.push_back(path[0] + offset * tolerance_);
			loc_vec.push_back(path[0] - offset * tolerance_);
		}
		
		loc_vec.push_back(path[seg] + offset * tolerance_);
		loc_vec.push_back(path[seg] - offset * tolerance_);
	}
	
	glVertexPointer(2, GL_DOUBLE, 0, &loc_vec[0].x);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, loc_vec.size());
#endif

#ifdef V2
	
	std::vector<unsigned short> loc_indices;
	loc_indices.reserve( (path.size()-1) * 6 );

	loc_vec.reserve( (path.size()-1) * 4 );
	
	for (int seg = 1;  seg < path.size(); seg++)
	{
		Point delta = path[seg] - path[seg-1];
		double length = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (length == 0)
		{
			continue;
		}

		delta.x /= length;
		delta.y /= length;

		Point offset(-delta.y, delta.x);

		loc_vec.push_back(path[seg-1] + offset * tolerance_);
		loc_vec.push_back(path[seg-1] - offset * tolerance_);

		loc_vec.push_back(path[seg] + offset * tolerance_);
		loc_vec.push_back(path[seg] - offset * tolerance_);
	}

	for (int seg = 0; seg < path.size()-1; seg++)
	{
		int beg = 4 * seg;
		
		loc_indices.push_back(beg);
		loc_indices.push_back(beg+1);
		loc_indices.push_back(beg+2);

		loc_indices.push_back(beg+2);
		loc_indices.push_back(beg+1);
		loc_indices.push_back(beg+3);
	}

	glVertexPointer(2, GL_DOUBLE, 0, &loc_vec[0].x);
	glDrawElements(GL_TRIANGLES, loc_indices.size(), GL_UNSIGNED_SHORT, &loc_indices[0]);

#endif

	glColor4fv(last_c4);
	glPolygonMode(GL_FRONT, GL_FILL);

#endif	

}

void OverlayEliminateTest::eliminate()
{
	if (is_dirty_)
	{
#ifdef AOE
		ApproximateOverlapsElimination analyser;
		analyser.eliminateApproximateOverlaps(m_path_vec_, m_flag_vec_, tolerance_, tolerance_ * 0.2);
#else
		for (int k = 0; k < m_path_vec_.size(); k++)
		{
			if (k==0) m_flag_vec_.push_back(true);
			else m_flag_vec_.push_back(false);
		}
#endif

		is_dirty_ = false;
	}

}

void OverlayEliminateTest::render()
{
	if (m_path_vec_.size() == 0) return;

	glLineWidth(2.0f);

	if (cur_path_)
	{
		glColor4f(1.0f, 1.0f, 0.0f, 1.f);
		_render_path(*cur_path_, false);
	}

	glColor4f(1.0f, 0.0f, 0.0f, 1.f);

	// render dumped parts.
	for (int k = 0; k < m_flag_vec_.size(); k++)
	{
		if (k<m_path_vec_.size() && !m_flag_vec_[k])
		{
			_render_path(m_path_vec_[k], false);
		}
	}

	glColor4f(0.0f, 0.0f, 1.0f, 1.f);

	// render wanted parts.
	for (int k = 0; k < m_flag_vec_.size(); k++)
	{
		if (k<m_path_vec_.size() && m_flag_vec_[k])
		{
			_render_path(m_path_vec_[k]);
		}
	}

	glLineWidth(1.0f);

}

void OverlayEliminateTest::load_from_file(const char* fname)
{
	FILE* fp = fopen(fname, "r");
	if (!fp) return;

	int path_sz = 0;
	while (fscanf(fp, "path %d\n", &path_sz) == 1)
	{
		path_t loc_path;
		for (int t = 0; t < path_sz; t++)
		{
			float x;
			float y;
			fscanf(fp, "%f %f\n", &x, &y);
			loc_path.push_back(Point(x, y));
		}
		m_path_vec_.push_back(loc_path);
	}

}

void OverlayEliminateTest::save_to_file(const char* fname, bool to_file)
{
	FILE* fp = NULL;
	if (to_file)
	{
		fp = fopen(fname, "w");
	}
	else
	{
		fp = stdout;
	}
	
	if (!fp)
	{
		return;
	}

	for (int k = 0; k < m_path_vec_.size(); k++)
	{
		path_t& ref = m_path_vec_[k];
		fprintf(fp, "path %d\n", ref.size());
		for (int p = 0; p < ref.size(); p++)
		{
			fprintf(fp, "%f %f\n", ref[p].x, ref[p].y);
		}
	}

	fflush(fp);

	if (to_file)
	{
		fclose(fp);
	}

}

void OverlayEliminateTest::save_to_svg(const char* fname)
{
	SVGHelper svg_writer;
	svg_writer.write_svg(fname, m_path_vec_, m_flag_vec_, tolerance_);
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

void SVGHelper::write_svg(const char* fname, const path_vec_t& path_vec,
						  const std::vector<bool>& flag_vec, float tolerance)
{
	FILE* fp = fopen(fname, "w");
	if (!fp) return;

	const char header[] = "<?xml version=\"1.0\" standalone=\"no\"?>\n"
		"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n"
		"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">";
	
	const char svg_tag_beg[] = "<svg width=\"100%\" height=\"100%\" version=\"1.1\"\n"
		"xmlns = \"http://www.w3.org/2000/svg\">";
	
	const char svg_tag_end[] = "</svg>";

	fprintf(fp, "%s\n", header);

	fprintf(fp, "%s\n", svg_tag_beg);

	for (int t = 0; t < flag_vec.size(); t++)
	{
		COLOR c = flag_vec[t] ? BLUE : RED;
		int width = flag_vec[t] ? 2 : 1;

		if (t >= path_vec.size())
		{
			continue;
		}

		const path_t& path = path_vec[t];
		
		COLOR rect_c = flag_vec[t] ? GRAY : LIGHT_GRAY;

		// Write sensitive rect list.
		for (int seg = 1;  seg < path.size(); seg++)
		{
			Point delta = path[seg] - path[seg-1];
			double length = sqrt(delta.x * delta.x + delta.y * delta.y);
			if (length == 0)
			{
				continue;
			}

			delta.x /= length;
			delta.y /= length;

			Point offset(-delta.y, delta.x);

			path_t rect;
			rect.reserve(4);


			rect.push_back(path[seg-1] + offset * tolerance);
			rect.push_back(path[seg-1] - offset * tolerance);
			
			rect.push_back(path[seg] - offset * tolerance);
			rect.push_back(path[seg] + offset * tolerance);

			save_path(rect, rect_c, 1, true, fp);
		}

		save_path(path_vec[t], c, width, false, fp);
	}

	fprintf(fp, "</svg>\n");
}

void SVGHelper::save_path(const path_t& path, COLOR c, int width, bool is_closed, FILE* fp)
{
	if (path.size() < 2 || !fp)
	{
		return;
	}

	const char* color = get_color(c);
	if (!color) 
	{
		return;
	}

	for (int p = 0; p < path.size(); p++)
	{
		int x = (int)path[p].x;
		int y = (int)path[p].y;

		if (p == 0) 
		{
			fprintf(fp, "<path d=\"M%d %d\n", x, y);
			continue;
		}
		
		if (p == path.size()-1)
		{
			char tag = is_closed ? 'Z' : ' ';
			fprintf(fp, "\tL%d %d %c\"\n", x, y, tag);
					
			break;
		}

		fprintf(fp, "\tL%d %d\n", x, y);
	}

	// Not to fill.
	fprintf(fp, "style=\"fill:none;stroke:%s;stroke-width:%d\"/>\n", color, width);
}

char* SVGHelper::get_color(COLOR c)
{
	char* color = NULL;

	switch (c)
	{
	case WHITE: color = "white"; break;
	case RED: color = "red"; break;
	case YELLOW: color = "yellow"; break;
	case BLUE: color = "blue"; break;
	case GRAY: color = "gray"; break;
	case LIGHT_GRAY: color = "lightgray"; break;
	default: break;
	}

	return color;
}