/*
 *  ofxGuiGalleryItem.cpp
 *  ofxGui_Example
 *
 *  Created by Christopher P. Baker on 2/13/11.
 *  Copyright 2011 Murmur Labs LLC. All rights reserved.
 *
 */

#include "ofxGuiGalleryItem.h"


ofxGuiGalleryItem::ofxGuiGalleryItem()
{
	mParamType = kofxGui_Object_Gallery_Item;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiGalleryItem::init(string name, int x, int y, int width, int height, bool value, int mode, string image = "")
{
	/*
	int	textWidth	= (name == "") ? 0 : mGlobals->mButtonXText + roundInt(mGlobals->mHeadFont.stringWidth(name));
	
	mParamName		= name;
	
	mObjX			= x;
	mObjY			= y;
	
	mObjWidth		= textWidth + width;
	mObjHeight		= height;
	
	mMode			= mode;
	
	renderType		= kofxGui_Button_Render_Default;
	
	setValue(value);
	setControlRegion(0, 0, width, height);
	
	if(image != "") logo.loadImage(image);
	 */
}

//	----------------------------------------------------------------------------------------------------


//	----------------------------------------------------------------------------------------------------

/*
 bool ofxGuiButton::update(int id, int task, void* data, int length)
 {
 bool handled = false;
 
 if(id == mParamId && length == sizeof(bool))
 {
 setValue(*(bool*)data);
 handled = true;
 }
 
 return handled;
 }
 */

//	----------------------------------------------------------------------------------------------------

void ofxGuiGalleryItem::draw()
{
	

	glPushMatrix();
	
	glTranslatef(x, y, 0.0f);
	
	
	if(mouseOver) {
		glColor4f(0,0,1,1);
	} else {
		glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);

	}
	
	//	frame
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
	
}


//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiFiles::mouseMoved(int x, int y)
{
	return NULL;
}


//	----------------------------------------------------------------------------------------------------

bool ofxGuiGalleryItem::mouseDragged(int x, int y, int button)
{
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGalleryItem::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));
	
	/*
	if(mMouseIsDown)
	{
		if(mMode == kofxGui_Button_Trigger)
			setValue(true);
		else
			setValue(!mValue);
		
		//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
		
		int i = (int)kofxGui_Set_Bool;
		ofNotifyEvent(genericOfxGuiEvent, i, this);
		
		
	}
	 */
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGalleryItem::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;

	/*
	
	if(mMouseIsDown)
	{
		if(mMode == kofxGui_Button_Trigger)
		{
			setValue(false);
			//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
		}
		
		mMouseIsDown = false;
	}
	 */
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGalleryItem::keyPressed(int key){ cout << "Keypress unimplemented." << endl; }

//	----------------------------------------------------------------------------------------------------

bool ofxGuiGalleryItem::keyReleased(int key){ cout << "Keypress unimplemented." << endl; }


//	----------------------------------------------------------------------------------------------------

void ofxGuiGalleryItem::buildFromXml()
{
	//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiGalleryItem::saveToXml()
{
	/*
	int		id		= saveObjectData();
	bool	value	= (mMode == kofxGui_Button_Trigger) ? false : mValue;
	
	mGlobals->mXml.setValue("OBJECT:VALUE", value, id);
	 */
}

//	----------------------------------------------------------------------------------------------------
