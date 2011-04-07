/*
 *  ofxGuiSlider.cpp
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
#include "ofxGuiSlider.h"

//--------------------------------------------------------------
ofxGuiSlider::ofxGuiSlider()
{
	mParamType = kofxGui_Object_Slider;
}

//--------------------------------------------------------------
void ofxGuiSlider::init(/*int id,*/ string _name, int _x, int _y, int _width, int _height, float _min, float _max, float _value, int _display, int _steps)
{
	int	textHeight	= (_name == "") ? 0 : mGlobals->mParamFontHeight;
	
	//mParamId		= id;
	mParamName		= _name;

	x               = _x; 
	y               = _y;
	
	width           = _width;
	height          = textHeight + _height; // text height + slider height
	
	mDisplay		= _display;
	mSteps			= _steps;
			
	setRange(_min, _max);
	setValue(_value);
    
    // custom, just for the button itself
	setHitRegion(0, // no x offset 
                 textHeight,  // move control region down below text
                 width,       // the full width
                 height);    // the intended height

    
    
}

//--------------------------------------------------------------
void ofxGuiSlider::setValue(float value)
{
	if(mSteps > 1)
	{
		float	fraction	= valueToFraction(value);
		float	steps		= (float)mSteps - 1;
		float	slice		= roundInt(fraction * steps) / steps;
							   
		value = mMinVal + mValDlt * slice;

		if (mDisplay == kofxGui_Display_String && value != mValue)
		{
			int id = (int)value;
            
		
        }
	}
	
	mValue = value;	
    
    ofNotifyEvent(ofxGuiSliderEvent, mValue, this);

}

//--------------------------------------------------------------
void ofxGuiSlider::setRange(float min, float max) 
{
	mMinVal	= min;
	mMaxVal	= max;
	mValDlt	= mMaxVal - mMinVal;
}


//--------------------------------------------------------------
void ofxGuiSlider::draw()
{
	glPushMatrix();
		glTranslatef(x, y, 0.0);
	
		if(mParamName != "")
		{
			if (mDisplay == kofxGui_Display_String && mSteps > 1){
				drawParamString(0.0, 0.0, mParamName + ": " + mDisplaySting, false);
			}
			    
			else {
				drawParamString(0.0, 0.0, mParamName + ": " + floatToString(mValue, mDisplay), false);
            }
		}
    
        
    
	
		float xx = (cRect.width * valueToFraction(mValue));
	
		ofFill();
	
		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		ofRect(cRect.x, cRect.y, cRect.width, cRect.height);

		//	action
		glColor4f(mGlobals->mSliderColor.r, mGlobals->mSliderColor.g, mGlobals->mSliderColor.b, mGlobals->mSliderColor.a);
		ofRect(cRect.x, cRect.y, xx, cRect.height);


   

    //	handle
		glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
		ofRect(xx+1, cRect.y, 1.0, cRect.height);
		
		ofNoFill();

    //	frame
		glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
		ofRect(cRect.x, cRect.y, cRect.width, cRect.height);
	
    
    ofSetColor(255,255,0);
    ofNoFill();
    ofRect(0,0,width,height);
    
    
	glPopMatrix();
}

/*
//--------------------------------------------------------------
ofxGuiObject* ofxGuiSlider::mouseMoved(int x, int y)
{
	return NULL;
}
*/

void ofxGuiSlider::onRollOver(int x, int y) {
    cout << "slider got rollover!!" << endl;
    
}

void ofxGuiSlider::onRollOut() {
    cout << "slider got rollout!!" << endl;
    
}

void ofxGuiSlider::onMouseMove(int x, int y) {
    
}

void ofxGuiSlider::sliderDragging(int x, int y, int button) {
    ofxPoint2f screenPos = getScreenPosition();
    
    int xx = CLAMP(screenToLocal(ofxPoint2f(x, y)).x,0,cRect.width);
    
    float _value = fractionToValue( xx / (width));
    
    cout << "SLIDER GOT DRAG OVER " 
    << screenPos.x << "x" << screenPos.y
    << " {} " 
    << xx << " // " 
    << y << "| isDragging " 
    << isDragging << "|" 
    << _value << "|"
    << mValDlt << "|"
    << mMinVal << "|" 
    << endl;
    
    
    //return (mValDlt * fraction) + mMinVal;
    
    
    
    if(_value != mValue)
    {
        setValue(_value);
    }
}


void ofxGuiSlider::onDragOver(int x, int y, int button) {
    if(isDragging) {
        sliderDragging(x,y,button);
    }
    
}

void ofxGuiSlider::onDragOutside(int x, int y, int button) {
    if(isDragging) {
        sliderDragging(x,y,button);
    }
}


void ofxGuiSlider::onPress(int x, int y, int button) {
    cout << "SLIDER GOT PRESS " << x << " // " << y << endl;

}

void ofxGuiSlider::onPressOutside(int x, int y, int button) {
    cout << "SLIDER GOT PRESS OUTSIDE " << x << " // " << y << endl;
}

void ofxGuiSlider::onRelease(int x, int y, int button) {
    cout << "SLIDER GOT RELEASE " << x << " // " << y << endl;
}

void ofxGuiSlider::onReleaseOutside(int x, int y, int button) {
    cout << "SLIDER GOT RELEASE OUTSIDE " << x << " // " << y << endl;
}


/*
//--------------------------------------------------------------
bool ofxGuiSlider::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		float value = fractionToValue(mouseToFraction(mouseToLocal(x, y)).x);

		if(value != mValue)
		{
			setValue(value);
			//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Float, &mValue, sizeof(float));
		}
	}
	
	return mMouseIsDown;
}

//--------------------------------------------------------------
bool ofxGuiSlider::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));

	if (mMouseIsDown)
		mouseDragged(x, y, button);
	
	return mMouseIsDown;
}

//--------------------------------------------------------------
bool ofxGuiSlider::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	return handled;
}
 
 */

/*

//--------------------------------------------------------------
bool ofxGuiSlider::keyPressed(int key){ cout << "Keypress unimplemented." << endl; }

//--------------------------------------------------------------
bool ofxGuiSlider::keyReleased(int key){ cout << "Keypress unimplemented." << endl; }
*/
 
//--------------------------------------------------------------
void ofxGuiSlider::buildFromXml()
{
	//mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Float, &mValue, sizeof(float));
}

//--------------------------------------------------------------
void ofxGuiSlider::saveToXml()
{
	int id = saveObjectData();

	mGlobals->mXml.setValue("OBJECT:MIN", mMinVal, id);
	mGlobals->mXml.setValue("OBJECT:MAX", mMaxVal, id);
	mGlobals->mXml.setValue("OBJECT:VALUE", mValue, id);
}

//--------------------------------------------------------------
float ofxGuiSlider::valueToFraction(float value)
{
	return (value - mMinVal) / mValDlt;
}

//--------------------------------------------------------------
float ofxGuiSlider::fractionToValue(float fraction)
{
	return (mValDlt * fraction) + mMinVal;
}

//--------------------------------------------------------------

