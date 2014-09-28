#ifndef ANDROID_CANVAS_201409281029_H
#define ANDROID_CANVAS_201409281029_H

class Java_HardwareCanvas
{
public:

	virtual void onPreDraw() = 0;
	virtual void onPostDraw() = 0;

};

class Java_GLES20Canvans : public Java_HardwareCanvas
{
public:

	virtual void onPreDraw() 
	{

	}

	virtual void onPostDraw()
	{

	}

	int nCreateRenderer();
	int nCreateDisplayListRenderer();
	int nCreateLayerRenderer();

	int getDisplayList(int displaylist);	// call DisplayListRender->getDisplayList()

private:

	int m_render;

};

class Java_GLES20RecordingCanvas : public Java_GLES20Canvans
{
public:
	
	void end();		// call Java_GLES20Canvas::getDisplayList();

};

#endif