#ifndef ANDROID_DISPLAY_LIST_201409281010_H
#define ANDROID_DISPLAY_LIST_201409281010_H

#include "android_canvas.h"

class Java_DisplayList
{
public:

	virtual void setScaleX(float scalex) = 0;
	virtual void setScaleY(float scaley) = 0;
	virtual void end();

};

class Java_GLES20DisplayList : public Java_DisplayList
{
public:

	//Override
	virtual void setScaleX(float scalex) {
		nSetScaleX(nativeDisplayList, scalex);
	}

	virtual void setScaleY(float scaley) {
		nSetScaleY(nativeDisplayList, scaley);
	}

	// native interfaces.
	void nSetScaleX(int displaylist, float scalex) {}
	void nSetScaleY(int displaylist, float scaley) {}
	
	void end()
	{
		m_canvas.end();
	}

private:

	int nativeDisplayList;	// void* => int value.

	Java_GLES20RecordingCanvas m_canvas;

};

#endif