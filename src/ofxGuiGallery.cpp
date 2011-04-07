/*
 *  ofxGuiGallery.cpp
 *  ofxGui_Example
 *
 *  Created by Christopher P. Baker on 2/13/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#include "ofxGuiGallery.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiGallery::ofxGuiGallery()
{
	mParamType = kofxGui_Object_XYPad;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiGallery::init(string name, int x, int y, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps)
{
	
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
	
	mDisplay		= display;
	mSteps			= steps;
	
	//setRange(min, max);
	//setValue(value);
	//setControlRegion(0, textHeight, width, height);
	 
}

//	----------------------------------------------------------------------------------------------------

/*
 bool ofxGuiXYPad::update(int id, int task, void* data, int length)
 {
 bool handled = false;
 
 if(id == mParamId && length == sizeof(ofxPoint2f))
 {
 setValue(*(ofxPoint2f*)data);
 handled = true;
 }
 
 return handled;
 }
 */

//	----------------------------------------------------------------------------------------------------

void ofxGuiGallery::draw()
{
	
	/*
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0f);
	
	if(mParamName != "")
		drawParamString(0.0, 0.0, mParamName + ": " + pointToString(mValue, mDisplay), false);
	
	ofxPoint2f	p	= fractionToLocal(valueToFraction(mValue));
	
	float		d	= mGlobals->mPointSize;
	float		r	= d / 2.0;
	
	ofFill();
	
	//	background
	glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	//	x-bar
	glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals-> mAxisColor.a);
	ofLine(p.x + 0.5, mCtrY, p.x + 0.5, mCtrBottom);
	
	//	y-bar
	glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals->mAxisColor.a);
	ofLine(mCtrX, p.y + 0.5, mCtrRight, p.y + 0.5);
	
	ofNoFill();
	
	//	handle
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(p.x - r, p.y - r, d, d);
	
	//	frame
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
	 */
}
//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiFiles::mouseMoved(int x, int y)
{
	return NULL;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGallery::mouseDragged(int x, int y, int button)
{
	/*
	if(mMouseIsDown)
	{
		ofxPoint2f value = fractionToValue(mouseToFraction(mouseToLocal(x, y)));
		
		if(value != mValue)
		{
			setValue(value);
			//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mValue, sizeof(ofxPoint2f));
		}
	}
	*/
	 
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGallery::mousePressed(int x, int y, int button)
{
	/*
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));
	
	if(mMouseIsDown)
		mouseDragged(x, y, button);
	
	 */
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGallery::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	/*
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	 */
	return handled;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGallery::keyPressed(int key){ cout << "Keypress unimplemented." << endl; }

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGallery::keyReleased(int key){ cout << "Keypress unimplemented." << endl; }

//	----------------------------------------------------------------------------------------------------

void ofxGuiGallery::buildFromXml()
{
	//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Point, &mValue, sizeof(ofxPoint2f));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiGallery::saveToXml()
{
	/*
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:MIN_X", mMinVal.x, id);
	mGlobals->mXml.setValue("OBJECT:MIN_Y", mMinVal.y, id);
	mGlobals->mXml.setValue("OBJECT:MAX_X", mMaxVal.x, id);
	mGlobals->mXml.setValue("OBJECT:MAX_Y", mMaxVal.y, id);
	mGlobals->mXml.setValue("OBJECT:VALUE_X", mValue.x, id);
	mGlobals->mXml.setValue("OBJECT:VALUE_Y", mValue.y, id);
	 */
}

//	----------------------------------------------------------------------------------------------------
