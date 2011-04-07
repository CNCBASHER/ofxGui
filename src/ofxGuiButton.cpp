/*
 *  ofxGuiButton.cpp
 *  openFrameworks
 *
 *  Copyright 2008 alphakanal/Stefan Kirch.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


//--------------------------------------------------------------
#include "ofxGuiButton.h"

//--------------------------------------------------------------
ofxGuiButton::ofxGuiButton()
{
	mParamType = kofxGui_Object_Button;
}

//--------------------------------------------------------------
void ofxGuiButton::init(string _name, int _x, int _y, int _width, int _height, int _value, int _mode, string _image = "")
{
	int	textWidth	= (_name == "") ? 0 : mGlobals->mButtonXText + roundInt(mGlobals->mHeadFont.stringWidth(_name));

	mParamName		= _name;
	
	x			= _x;
	y			= _y;

	width		= textWidth + _width;
	height		= _height;

	mMode			= _mode;
	
	renderType		= kofxGui_Button_Render_Default;

	setValue(_value);
	
	// custom, just for the button itself
	setHitRegion(0, 0, _width, _height);

	if(_image != "") logo.loadImage(_image);
}

//--------------------------------------------------------------
void ofxGuiButton::setValue(int value)
{
	mValue = value;
}

//--------------------------------------------------------------
void ofxGuiButton::draw()
{
	glPushMatrix();

	// go to this control box area
	glTranslatef(x, y, 0.0f);
	
	if(mParamName != "")
		drawParamString(cRect.width + mGlobals->mButtonXText, mGlobals->mButtonYText, mParamName, false);

	if(renderType == kofxGui_Button_Render_X) {
		
		if(mValue == 1) {
			ofLine(cRect.x+2, cRect.y+3, cRect.width-3, cRect.height-2);
			ofLine(cRect.width-3, cRect.y+3, cRect.x+2, cRect.height-2);
		} else {
			
		}
		
	} else if(renderType == kofxGui_Button_Render_PlusMinus) {

		// horz
		ofLine(cRect.x+2, floor(cRect.height / 2), cRect.width - 3, floor(cRect.height / 2));
		
		// vert 
		if(mValue == 1) {
			ofLine(floor(cRect.width / 2), 3, ceil(cRect.width / 2), cRect.height -2);
		}
		
	} else {
		// ddefault
		ofFill();
		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);

		// makes it NOT see through
		ofRect(cRect.x, cRect.y, cRect.width, cRect.height);
		
		//logo.draw(cRect.x, cRect.y, cRect.width, cRect.height);
		
		if(mValue == 1)
		{
			//	handle
			if(isEnabled) {
				glColor4f(mGlobals->mButtonColor.r, mGlobals->mButtonColor.g, mGlobals->mButtonColor.b, mGlobals->mButtonColor.a);
			} else {
				glColor4f(mGlobals->mDisabledColor.r, mGlobals->mDisabledColor.g, mGlobals->mDisabledColor.b, mGlobals->mDisabledColor.a);
			}
			
			
			ofRect(cRect.x, cRect.y, cRect.width, cRect.height);
		}
		
		ofNoFill();

	}
		
	//	frame
	
	if (isEnabled) {
		if(mouseOver) {
			glColor4f(1,1,0,1);
		} else {
			glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
		}
	} else {
		glColor4f(mGlobals->mDisabledColor.r, mGlobals->mDisabledColor.g, mGlobals->mDisabledColor.b, mGlobals->mDisabledColor.a);
	
		//glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);

	}

	// we have already translated to x/y
	ofRect(cRect.x, cRect.y, cRect.width, cRect.height);
	
	glPopMatrix();
}


//--------------------------------------------------------------
void ofxGuiButton::onRollOver(int x, int y)
{
	//cout << "Button: " << mParamName << " roll on! " << x << "/" << y << endl;
}
//--------------------------------------------------------------
void ofxGuiButton::onRollOut()
{
	//cout << "Button: " << mParamName << " roll out! " << endl;
	
}

//--------------------------------------------------------------
void ofxGuiButton::onMouseMove(int x, int y)
{	
	//cout << "Button: " << mParamName << " mouse move on! " << x << "/" << y << endl;
}

//--------------------------------------------------------------
void ofxGuiButton::onDragOver(int x, int y, int button)
{
	//cout << "Button: " << mParamName << " drag over! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiButton::onDragOutside(int x, int y, int button)
{
	//cout << "Button: " << mParamName << " drag outside! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiButton::onPress(int x, int y, int button)
{

	
	if(button == 0) {
		// left click
		
		if (mMode == kofxGui_Button_Switch) {
			mValue ^= 1; // toggle
		} else if(mMode == kofxGui_Button_Trigger) {
			mValue = 1; // turn on
		}
		
		ofNotifyEvent(ofxGuiButtonEvent, mValue, this);
	}
	
	//cout << "Button: " << mParamName << " press! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiButton::onPressOutside(int x, int y, int button)
{
	//cout << "Button: " << mParamName << " press outside! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiButton::onRelease(int x, int y, int button)
{
	
	if(button == 0) {
		// left click
		if(mMode == kofxGui_Button_Trigger) {
			mValue = 0; // turn on
		}
		
		ofNotifyEvent(ofxGuiButtonEvent, mValue, this);
	}
	
	
	//cout << "Button: " << mParamName << " released! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiButton::onReleaseOutside(int x, int y, int button)
{
	
	if(mouseDown && button == 0) {
		// left click
		if(mMode == kofxGui_Button_Trigger) {
			mValue = 0; // turn on
		}
		
		ofNotifyEvent(ofxGuiButtonEvent, mValue, this);
		
	}
	
	//cout << "Button: " << mParamName << " released outside! " << x << "/" << y << "/" << button << endl;
	
}

//--------------------------------------------------------------
void ofxGuiButton::keyPressed( int key )
{
	//cout << "Button: " << mParamName << " key pressed! " << key << endl;
	
}

//--------------------------------------------------------------
void ofxGuiButton::keyReleased( int key )
{
	//cout << "Button: " << mParamName << " key released! " << key << endl;
}





//--------------------------------------------------------------
void ofxGuiButton::buildFromXml()
{
	//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
}

//--------------------------------------------------------------
void ofxGuiButton::saveToXml()
{
	int		id		= saveObjectData();
	bool	value	= (mMode == kofxGui_Button_Trigger) ? false : (mValue == 1);

	mGlobals->mXml.setValue("OBJECT:VALUE", value, id);
}

//--------------------------------------------------------------

