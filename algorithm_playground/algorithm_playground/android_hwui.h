#ifndef ANDROID_HWUI_MODEL_201409271755_H
#define ANDROID_HWUI_MODEL_201409271755_H

#include <vector>
#include <string>
#include <iostream>

class SKWriter32
{
public:
	typedef std::vector<unsigned char> buffer_t;

	union Cell
	{
		unsigned int ui;
		float f;
	};

	SKWriter32() {}
	SKWriter32(const SKWriter32& ref)
		: m_buffer(ref.m_buffer)
	{}

	void writeInt(int iv) 
	{
		m_buffer.push_back(iv & 0xff);
		m_buffer.push_back((iv >> 8) & 0xff);
		m_buffer.push_back((iv >> 16) & 0xff);
		m_buffer.push_back((iv >> 24) & 0xff);
	}

	void writeFloat(float fv)
	{
		Cell tmp;
		tmp.f = fv;

		m_buffer.push_back(tmp.ui & 0xff);
		m_buffer.push_back((tmp.ui >> 8) & 0xff);
		m_buffer.push_back((tmp.ui >> 16) & 0xff);
		m_buffer.push_back((tmp.ui >> 24) & 0xff);
	}

	int getInt() 
	{
		int retV = 0;
		for (int k = 3; k >= 0; --k)
		{
			int val = m_buffer.back();
			m_buffer.pop_back();
			int off = 8 * k;
			retV |= (val << off);
		}

		return retV;
	}

	float getFloat()
	{
		Cell tmp;
		tmp.ui = 0;

		for (int k = 3; k >= 0; --k)
		{
			int val = m_buffer.back();
			m_buffer.pop_back();
			int off = 8 * k;
			tmp.ui |= (val << off);
		}

		return tmp.f;
	}

	static void skwriter_test()
	{
		using namespace std;

		SKWriter32 writer;
		writer.writeFloat(0.6f);
		writer.writeInt(1024);

		int ival = writer.getInt();
		float fval = writer.getFloat();

		cout << "ival = " << ival << endl;
		cout << "fval = " << fval << endl;
	}

	bool eof() const { return m_buffer.empty(); }

private:
	
	buffer_t m_buffer;
};

class OpenGLRender;
class DisplayListRender;

class DisplayList
{
public:
	enum OP
	{
		SAVE = 0,
		DRAW_PATCH,
		DRAW_RECT,
		RESTORE,
		TRANSLATEX,
		TRANSLATEY,
		SCALEX,
		SCALEY,
		DRAW_DISPLAY_LIST
	};

	typedef int status_t;

	DisplayList(const DisplayListRender& render);

	status_t initFromDisplayListRenderer(const DisplayListRender& render);

	status_t replay(OpenGLRender& render, int info);

private:
	
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;
	float m_alpha;

	OP m_op;

	SKWriter32 m_reader;

};

class OpenGLRender
{
public:
	typedef DisplayList::status_t status_t;

	OpenGLRender();
	virtual ~OpenGLRender();
	
	virtual status_t drawPatch(float top, float left, float bottom, float right, float alpha) { return drawTextureMesh(); }
	virtual status_t drawRect(int x, int y, int width, int height) { return drawTextureMesh(); }
	virtual status_t drawDisplayList(DisplayList* displaylist) {
		if (displaylist)
		{
			displaylist->replay(*this, 0);
		}
	}
	// virtual void translateX(float x);

	status_t drawTextureMesh()
	{
		// call OpenGL render API.
		// glDrawArrays();
		return 0;
	}
	
};

class DisplayListRender : public OpenGLRender
{
public:
	DisplayList* getDisplayList(DisplayList* displaylist)
	{
		if (!displaylist)
			displaylist = new DisplayList(*this);
		else
			displaylist->initFromDisplayListRenderer(*this);

		return displaylist;
	}

	virtual status_t drawPatch(float top, float left, float bottom, float right, float alpha)
	{
		addOp(DisplayList::DRAW_PATCH);
		addFloat(top);
		addFloat(left);
		addFloat(bottom);
		addFloat(right);
		addFloat(alpha);
		return 0;
	}

	virtual status_t drawRect(int x, int y, int width, int height)
	{
		addOp(DisplayList::DRAW_RECT);
		addInt(x);
		addInt(y);
		addInt(width);
		addInt(height);
		return 0;
	}

	virtual status_t drawDisplayList(DisplayList* displaylist)
	{
		addOp(DisplayList::DRAW_DISPLAY_LIST);
		addInt((int)displaylist);
		return 0;
	}

	void addOp(DisplayList::OP op) { m_writer.writeInt(int(op)); }
	void addInt(int val) { m_writer.writeInt(val); }
	void addFloat(float val) { m_writer.writeFloat(val); }

	friend class DisplayList;

	SKWriter32 m_writer;
	
};

DisplayList::status_t DisplayList::replay(OpenGLRender& render, int info)
{
	status_t ret = 0;

	while (!m_reader.eof())
	{
		OP op = (OP)m_reader.getInt();
		float x, y, width, height;

		switch (op)
		{
		case DisplayList::SAVE:
			break;
		case DisplayList::DRAW_PATCH:
			break;

		case DisplayList::DRAW_RECT:
			x = m_reader.getFloat();
			y = m_reader.getFloat();
			width = m_reader.getFloat();
			height = m_reader.getFloat();
			ret |= render.drawRect(x, y, width, height);
			break;

		case DisplayList::RESTORE:
			break;
		case DisplayList::TRANSLATEX:
			break;
		default:
			break;
		}
	}

	return 0;

}

DisplayList::DisplayList(const DisplayListRender& render)
{
	// initFromDisplayListRenderer(render);
}

DisplayList::status_t DisplayList::initFromDisplayListRenderer(const DisplayListRender& render)
{
	m_reader = render.m_writer;

	return 0;
}

#endif