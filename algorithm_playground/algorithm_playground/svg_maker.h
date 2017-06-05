#ifndef SVG_MAKER
#define SVG_MAKER
#define _CRT_SECURE_NO_WARNINGS

// /d1 reportAllClassLayout

#include <stdio.h>
#include <string>

struct StyleCfg
{
	int ctrlPntSize;
	char ctrlPntFillColor[30];

	int strokeWidth;
	char strokeColor[30];
	char strokeFillColor[30];
};

class SvgMaker
{
public:

	SvgMaker(int w, int h) : m_fp(0)
	{
		m_size[0] = w;
		m_size[1] = h;

		m_cfg.ctrlPntSize = 5;
		m_cfg.strokeWidth = 3;
		strcpy(m_cfg.ctrlPntFillColor, "red");
		strcpy(m_cfg.strokeColor, "#ff0000");
		strcpy(m_cfg.strokeFillColor, "#0000ff");

	}
	~SvgMaker()
	{

	}

	void open(const char* fname) {
		close();

		m_fp = fopen(fname, "w");
		fprintf(m_fp, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
		fprintf(m_fp, "<svg width=\"%dpx\" height=\"%dpx\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
			m_size[0], m_size[1]);

	}
	
	void close() 
	{
		if (m_fp) 
		{
			fprintf(m_fp, "</svg>\n");
			fclose(m_fp);
			m_fp = 0;
		}
	}

	void WritePath(int* path, int pntSize, bool ctrlPnt) {

		using std::string;
		string pathStr = "M";

		for (int k(0); k < pntSize; k++)
		{
			int x = path[2 * k];
			int y = path[2 * k + 1];
			char tmp[30];
			memset(tmp, 0, 30);
			sprintf(tmp, "%d %d%c", x, y, k == pntSize-1 ? 'Z' : 'L');
			pathStr += tmp;
		}
		fprintf(m_fp, "<path stroke=\"%s\" fill=\"%s\" style=\"stroke-width: %dpx\" d=\"%s\"/>\n",
			m_cfg.strokeColor, m_cfg.strokeFillColor, m_cfg.strokeWidth,
			pathStr.c_str());

		if (!ctrlPnt)
			return;

		fflush(m_fp);
		for (int k(0); k < pntSize; k++)
		{
			int x = path[2 * k];
			int y = path[2 * k + 1];

			fprintf(m_fp, "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"%s\"/>\n",
				x, y, m_cfg.ctrlPntSize, m_cfg.ctrlPntFillColor);
		}
		fflush(m_fp);

	}

private:

	FILE*		m_fp;
	StyleCfg	m_cfg;
	int			m_size[2];

};

#endif
