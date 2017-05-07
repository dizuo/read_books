#define _CRT_SECURE_NO_WARNINGS

#include "tess_helper.h"

#include "gl/glut.h"
#include "polygonpartation.h"
#include <list>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void make_poly(float* buf, int pnt_sz, TPPLPoly& poly)
{
	poly.Init(pnt_sz);

	for (int k(0); k < pnt_sz; k++)
	{
		poly[k].x = buf[2 * k];
		poly[k].y = buf[2 * k + 1];
	}

	if (poly.GetOrientation() == TPPL_CW)
	{
		poly.SetHole(true);
	}

}

typedef std::list< TPPLPoly > poly_list_t;
typedef poly_list_t::iterator poly_iter_t;

void TessHelper::test_render()
{
	TPPLPoly poly;
	{
		float x = 200.0f;
		float buf[] = { -x, -x, x, -x, x, x, -x, x };
		make_poly(buf, 4, poly);
	}

	TPPLPoly hole;
	{
		float x = 100.0f;
		// float buf[] = { -x, -x, x, -x, x, x, 0, 0, -x, x };
		float buf[] = { -x, -x, -x, x, 0, 0, x, x, x, -x };
		make_poly(buf, 5, hole);
	}

	poly_list_t list;
	list.push_back(poly);
	list.push_back(hole);

	poly_list_t triangles;

	TPPLPartition pp;
	if (!pp.Triangulate_EC(&list, &triangles))
	{
		printf("failed\n");
	}

	// Draw polygons.
	glColor4ub(255, 255, 255, 128);

	glPushMatrix();
	glTranslatef(200, 200, 0);
	for (poly_iter_t it = triangles.begin(); it != triangles.end(); it++)
	{
		TPPLPoly& poly = *it;

		glBegin(GL_TRIANGLES);
		for (int k(0); k < poly.GetNumPoints(); k++)
		{
			glVertex2f(poly.GetPoint(k).x, poly.GetPoint(k).y);
		}
		glEnd();

#if 0
		glLineWidth(2.0f);
		glBegin(GL_LINES);
		for (int k(0); k < poly.GetNumPoints(); k++)
		{
			glVertex2f(poly.GetPoint(k).x, poly.GetPoint(k).y);
		}
		glEnd();
#endif

	}
	glPopMatrix();

}

void make_ttplpoly(vertices_t& src, TPPLPoly& dst)
{
	dst.Init(src.size());

	for (int k(0); k < src.size(); k++)
	{
		dst[k].x = src[k].x();
		dst[k].y = src[k].y();
	}

	if (dst.GetOrientation() == TPPL_CCW)
	{
		dst.SetHole(false);
	}
	else
	{
		dst.SetHole(true);
	}
}

void flip_path_if_need(TPPLPoly& poly)
{
	if (!poly.IsHole())
		return;

	TPPLPoint* pnts = poly.GetPoints();

	for (int k(0); k < poly.GetNumPoints() / 2; k++)
	{
		TPPLPoint& pt = pnts[k];
		TPPLPoint& dst = pnts[poly.GetNumPoints() - 1 - k];
		std::swap(pt, dst);
	}

	if (poly.GetOrientation() == TPPL_CCW)
	{
		poly.SetHole(false);
	}

}

void TessHelper::render()
{
	if (path.size() < 2)
		return;

	glColor4ub(255, 255, 0, 256);

	for (int k(0); k < path.size(); k++)
	{
		int next = (k + 1) % path.size();
		glBegin(GL_LINES);
		glVertex2f(path[k].x(), path[k].y());
		glVertex2f(path[next].x(), path[next].y());
		glEnd();
	}

#if 0
	std::vector<float> vert_vec;
	for (int k(0); k < path.size(); k++)
	{
		vert_vec.push_back(path[k].x());
		vert_vec.push_back(path[k].y());
	}

	std::vector<int> indices_vec;
	for (int k(0); k < path.size(); k++)
	{
		int next = (k + 1) % path.size();
		indices_vec.push_back(k);
		indices_vec.push_back(next);
	}
	glVertexPointer(2, GL_FLOAT, 0, &vert_vec[0]);
	glDrawElements(GL_LINES, indices_vec.size(), GL_UNSIGNED_INT, &indices_vec[0]);
#endif

	if (this->path.size() < 3)
		return;

	TPPLPoly poly;
	make_ttplpoly(this->path, poly);
	flip_path_if_need(poly);

	poly_list_t list;
	list.push_back(poly);

	if (this->hole.size() > 2)
	{
		TPPLPoly hole_poly;
		make_ttplpoly(this->hole, hole_poly);
		list.push_back(hole_poly);
	}

	poly_list_t triangles;

	TPPLPartition pp;
	if (!pp.Triangulate_EC(&list, &triangles))
	{
		printf("failed\n");
	}

	// Draw polygons.
	glColor4ub(255, 255, 255, 256);

	glPushMatrix();
	// glTranslatef(200, 200, 0);
	for (poly_iter_t it = triangles.begin(); it != triangles.end(); it++)
	{
		TPPLPoly& poly = *it;

		glBegin(GL_TRIANGLES);
		for (int k(0); k < poly.GetNumPoints(); k++)
		{
			glVertex2f(poly.GetPoint(k).x, poly.GetPoint(k).y);
		}
		glEnd();

	}
	glPopMatrix();

}

void TessHelper::backspace(int mode)
{
	if (mode == ADD_POLY)
	{
		path.pop_back();
	}
	else
	{
		hole.pop_back();
	}

	on_vertices_changed();
}

void TessHelper::add_pnt(int mode, int x, int y)
{
	if (mode == ADD_POLY)
	{
		path.push_back(vec3_t(x, y, 0));
	}
	else
	{
		hole.push_back(vec3_t(x, y, 0));
	}

	on_vertices_changed();
}

void TessHelper::on_vertices_changed()
{
	save("./data/path.txt");
}

void TessHelper::clear()
{
	path.clear();
	hole.clear();
}

void dump(FILE* fp, vertices_t& path, const char* tag)
{
	fprintf(fp, "%s %d\n", tag, path.size());

	for (int k(0); k < path.size(); k++)
	{
		fprintf(fp, "%f %f\n", path[k].x(), path[k].y());
	}
	fflush(fp);
}

void TessHelper::save(const char* fname)
{
	FILE* fp = fopen(fname, "w");
	if (!fp) return;

	dump(fp, this->path, "path");

	if (!hole.empty())
	{
		dump(fp, this->hole, "hole");
	}

	fclose(fp);
}

void TessHelper::restore(const char* fname)
{
	this->clear();

	std::ifstream infile;
	infile.open(fname);
	if (infile.bad())
		return;

	vertices_t* pvec = 0;
	
	string line;
	while (std::getline(infile, line))
	{
		if (line.find("hole") != string::npos || line.find("path") != string::npos)
		{
			istringstream iss(line);
			string tag;
			int num;
			iss >> tag >> num;

			pvec = tag.find("path") != string::npos ? &path : &hole;
			pvec->reserve(num);
		}
		else
		{
			float vert[3];
			istringstream iss(line);
			iss >> vert[0] >> vert[1];

			pvec->push_back(vec3_t(vert));
		}

	}
	
}

