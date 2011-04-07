/*
 *  ofxGuiPanel.cpp
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
#include "ofxGuiPanel.h"

//--------------------------------------------------------------
ofxGuiPanel::ofxGuiPanel()
{
	mParamType = kofxGui_Object_Panel;
}

//--------------------------------------------------------------
ofxGuiPanel::~ofxGuiPanel() {

	// this is done below
	//delete enableDisableButton;
	//delete minMaxButton;
	
	childObjects.clear(); // erase all objects and call all of their destructors
	
	cout <<"PANEL DESTRUCTOR CALLED!!"<<endl;

	ofRemoveListener(enableDisableButton->genericOfxGuiEvent, this,  &ofxGuiPanel::buttonEvent);
	ofRemoveListener(minMaxButton->genericOfxGuiEvent, this,  &ofxGuiPanel::buttonEvent);
	
}

void ofxGuiPanel::init(string _name, int _x, int _y, int _border, int _spacing)
{
	int	textHeight	= (_name == "") ? 2 * _border :  2 * _border +mGlobals->mHeadFontHeight;

	canDisable = false;
	
	mParamName	= _name;

	x	= _x; 
	y	= _y;

	mBorder		= _border;
	mSpacing	= _spacing;
	
	windowButtonWidth	=	OFXGUI_BUTTON_WIDTH;
	windowButtonHeight	=	OFXGUI_BUTTON_HEIGHT;
	
	isMinimized		= false;
	
	isDragMoveable		= true;
	

	// draw the min max/ active inactive buttons
	enableDisableButton = new ofxGuiButton();
	enableDisableButton->init("", 0, 0, windowButtonWidth, windowButtonHeight, kofxGui_Button_On, kofxGui_Button_Switch, "");
	enableDisableButton->renderType = kofxGui_Button_Render_X;
	enableDisableButton->parentObject = this;
	enableDisableButton->canDisable = false;
//	enableDisableButton->addKeyMap((int)'m', &ofxGuiPanel::toggleMaxMin);
	childObjects.push_back(enableDisableButton);
	
	
	minMaxButton = new ofxGuiButton();
	minMaxButton->init("", windowButtonWidth, 0, windowButtonWidth, windowButtonHeight, kofxGui_Button_Off, kofxGui_Button_Switch, "");
	minMaxButton->renderType = kofxGui_Button_Render_PlusMinus;
	minMaxButton->parentObject = this;
	minMaxButton->canDisable = false;
	//enableDisableButton->addKeyMap((int)'e', &ofxGuiPanel::toggleEnable);
	childObjects.push_back(minMaxButton);
	
	adjustToNewContent(windowButtonWidth*2, windowButtonHeight ); // make room for both buttons
	adjustToNewContent(roundInt(mGlobals->mHeadFont.stringWidth(_name)), textHeight); // make room for title

	ofAddListener(enableDisableButton->ofxGuiButtonEvent, this, &ofxGuiPanel::buttonEvent); // add local listener for enable
	ofAddListener(minMaxButton->ofxGuiButtonEvent, this, &ofxGuiPanel::buttonEvent);		 // add local listener for min/max

}

//--------------------------------------------------------------
void ofxGuiPanel::buttonEvent(const void * sender, int & i)
{
	
	cout << "XXXXXXXXXXXXXXXXXXXXXXX GOT MOUSE BUTTON EVENT "<< endl;;
	
	if(sender == minMaxButton) {
		ofxGuiButton* b = (ofxGuiButton*) sender;
		if(b->mValue == 0) maximize(); else minimize();
		
	} else if (sender == enableDisableButton) {
		ofxGuiButton* b = (ofxGuiButton*) sender;
		if(b->mValue == 0) disable(); else enable();
	} else {
		ofLog(OF_LOG_ERROR, "unknown button on the panel ...");
	}
	
	
}


//--------------------------------------------------------------
void ofxGuiPanel::draw()
{
	glPushMatrix();
		
		glTranslatef(x, y, 0.0f);

	
		ofFill();
		
		//	background
		if(mouseOver) {
			glColor4f(0,0,1, mGlobals->mCoverColor.a);
		} else {
			glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		}
	
		if(isMinimized) {
			ofRect(0.0f, 0.0f, width, windowButtonHeight + 1);
		} else {
			ofRect(0.0f, 0.0f, width, height);
		}
		ofNoFill();
		
		if(mParamName != "") {
			if(isMinimized) {
				drawParamString(windowButtonWidth*2+4, 0, mParamName, false);	
			} else {
				drawHeadString(mBorder, mBorder + windowButtonHeight, mParamName, false);
			}
		}
		
		if(mBorder > 0)
		{
			//	border
			glColor4f(mGlobals->mBorderColor.r, mGlobals->mBorderColor.g, mGlobals->mBorderColor.b, mGlobals->mBorderColor.a);
		
			if(isMinimized) {
				ofRect(0.0f, 0.0f, width, windowButtonHeight );
			} else {
				ofRect(0.0f, 0.0f, width, height);
			}
		}
	
		if(isEnabled && !isMinimized) {
			ofxGuiObject* tmpObj;
			for(int i = 0; i < childObjects.size(); i++)
			{
				tmpObj = (ofxGuiObject*)childObjects.at(i);
				tmpObj->draw();
			}
		} else {
			minMaxButton->draw();
			enableDisableButton->draw();
		}
	
	
		if(mouseDown) {
			
			glColor4f(1,0,0,1); // red

			
			//	border
			if(isDragging) {
				glColor4f(1,1,0,1); // yellow
			}
						
			if(isDropSenderReady) {
				glColor4f(0,1,1,1); // fugly
			}
			
			
				
			if(isMinimized) {
				ofRect(-2.0f, -2.0f, minimizedRect.width+4, minimizedRect.height+4 );
			} else {
				ofRect(-2.0f, -2.0f, width+4, height+4);
			}
			
		}
	
		
		if(isDragging) {
			glColor4f(0,1,.5,1); // green
			ofRect(-6.0f, -6.0f, width+12, height+12);
		}

	
	
	if(isDropReceiverReady) {
		glColor4f(0,.5,.5,1); // green
		ofRect(-10.0f, -10.0f, width+20, height+20);

	}
	
	
	
	glPopMatrix();
}
//--------------------------------------------------------------
void ofxGuiPanel::exit() {
	cout << "exiting ... " << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::onRollOver(int x, int y)
{
//	cout << "Panel " << mParamName << " roll on! " << x << "/" << y << endl;
}
//--------------------------------------------------------------
void ofxGuiPanel::onRollOut()
{
//	cout << "Panel " << mParamName << " roll out! " << endl;

}

//--------------------------------------------------------------
void ofxGuiPanel::onMouseMove(int x, int y)
{	
	//cout << "Panel " << mParamName << " mouse move on! " << x << "/" << y << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::onDragOver(int _x, int _y, int button)
{
//	cout << "Panel " << mParamName << " drag over! " << x << "/" << y << "/" << button << endl;
	
	
	//x = _x;
	//y = _y;
}


void ofxGuiPanel::onDragging(int _x, int _y, int button)
{
//	cout << "Panel " << mParamName << " IS DRAGGING! " << x << "/" << y << "/" << button << endl;
}

void ofxGuiPanel::onObjectDragStart(int x, int y, int button)
{
//	cout << "OBJECT DRAGSTART Panel " << mParamName << " ! " << x << "/" << y << "/" << button << endl;
}

void ofxGuiPanel::onObjectDragging(int x, int y, int button)
{
//	cout << "OBJECT DRAGGING Panel " << mParamName << " ! " << x << "/" << y << "/" << button << endl;
}




//--------------------------------------------------------------
void ofxGuiPanel::onDragOutside(int x, int y, int button)
{
//	cout << "Panel " << mParamName << " drag outside! " << x << "/" << y << "/" << button << endl;
}


//--------------------------------------------------------------
void ofxGuiPanel::onObjectDropReceived(int x, int y, int button, ofxGuiObject* sentObject)
{
//	cout << "Panel " << mParamName << " OBJECT DROP RECEIVED: " << sentObject->mParamName << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::onObjectDropSent(int x, int y, int button, ofxGuiObject* receiverObject)
{
//	cout << "Panel " << mParamName << " OBJECT DROP SENT TO: " << receiverObject->mParamName << endl;
}


//--------------------------------------------------------------
void ofxGuiPanel::onPress(int x, int y, int button)
{
//	cout << "Panel " << mParamName << " press! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::onPressOutside(int x, int y, int button)
{
//	cout << "Panel " << mParamName << " press outside! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::onRelease(int x, int y, int button)
{
//	cout << "Panel " << mParamName << " released! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::onReleaseOutside(int x, int y, int button)
{
//	cout << "Panel " << mParamName << " released outside! " << x << "/" << y << "/" << button << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::onDropOver(int x, int y, int button, ofxGuiObject* object) {
//	cout << "just recieved the object called " << object->mParamName << endl;
}

//--------------------------------------------------------------
void ofxGuiPanel::keyPressed( int key )
{
//	cout << "Panel " << mParamName << " key pressed! " << key << endl;

}

//--------------------------------------------------------------
void ofxGuiPanel::keyReleased( int key )
{
//	cout << "Panel " << mParamName << " key released! " << key << endl;
}




//--------------------------------------------------------------
void ofxGuiPanel::toggleMaxMin()
{
	if(isMinimized) {
		maximize();		
	} else {
		minimize();
	}
	
}

//--------------------------------------------------------------

void ofxGuiPanel::maximize() {
	cout << "MAXIMIZED" << endl;
	
	minMaxButton->mValue=1;
	
	isMinimized = false;
	setHitRegion(0, 0, width, height);
}

//--------------------------------------------------------------
void ofxGuiPanel::minimize() {
	cout << "MINIMIZED" << endl;
	
	minMaxButton->mValue=0;
	
	isMinimized = true;
	setHitRegion(0, 0, minimizedRect.width, minimizedRect.height);
}




ofxGuiSlider* ofxGuiPanel::addSlider(string _name, 
                                     int _width, int _height, 
                                     float _min, float _max, 
                                     float _value, 
                                     int _display, 
                                     int _steps)
{
	ofxGuiSlider* obj = new ofxGuiSlider();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}

//--------------------------------------------------------------
/*
ofxGuiXYPad* ofxGuiPanel::addXYPad(string _name, int _width, int _height, ofxPoint2f _min, ofxPoint2f _max, ofxPoint2f _value, int _display, int _steps)
{
	ofxGuiXYPad* obj = new ofxGuiXYPad();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
*/

//--------------------------------------------------------------
/*
ofxGuiPoints* ofxGuiPanel::addPoints(string _name, int _width, int _height, ofxPoint2f _min, ofxPoint2f _max, ofxPoint2f _value, int _display, int _steps)
{
	ofxGuiPoints* obj = new ofxGuiPoints();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, _value, _display, _steps);
	addChild(obj);
	return obj;
}
*/

//--------------------------------------------------------------
ofxGuiButton* ofxGuiPanel::addButton(string _name, int _width, int _height, int _value, int _mode, string _image)
{
	ofxGuiButton* obj = new ofxGuiButton();
	obj->init(_name, mBorder, height - mBorder + getOffset(), _width, _height, _value, _mode, _image);
	addChild(obj);
	return obj;
}

//--------------------------------------------------------------
ofxGuiButton* ofxGuiPanel::addButtonTrigger(string name)
{
	return addButton(name, OFXGUI_BUTTON_WIDTH, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Trigger, "");
}

//--------------------------------------------------------------
ofxGuiButton* ofxGuiPanel::addButtonSwitch(string name)
{
	return addButton(name, OFXGUI_BUTTON_WIDTH, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch, "");
}



//--------------------------------------------------------------

/*
ofxGuiFiles* ofxGuiPanel::addFiles(string name, int _width, int _height, string value, string subPath, string suffix)
{
	ofxGuiFiles* obj = new ofxGuiFiles();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, value, subPath, suffix);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------

/*
ofxGuiColor* ofxGuiPanel::addColor(string name, int _width, int _height, ofRGBA value, int mode)
{
	ofxGuiColor* obj = new ofxGuiColor();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, value, mode);
	addChild(obj);
	return obj;
}
 */

//--------------------------------------------------------------

/*
ofxGuiMatrix* ofxGuiPanel::addMatrix(string name, int _width, int _height, int _xGrid, int _yGrid, int value, int mode, int spacing)
{
	ofxGuiMatrix* obj = new ofxGuiMatrix();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _xGrid, _yGrid, value, mode, spacing);
	addChild(obj);
	return obj;
}
*/
 
//--------------------------------------------------------------

/*
ofxGuiScope* ofxGuiPanel::addScope(string name, int _width, int _height, int _length, ofxPoint2f value, int mode)
{
	ofxGuiScope* obj = new ofxGuiScope();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _length, value, mode);
	addChild(obj);
	return obj;
}
 */


//--------------------------------------------------------------

/*
ofxGuiKnob* ofxGuiPanel::addKnob(string name, int _width, int _height, int _min, int _max, float value, int display, int steps)
{
	ofxGuiKnob* obj = new ofxGuiKnob();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, value, display, steps);
	addChild(obj);
	return obj;
}

//--------------------------------------------------------------
ofxGuiRadar* ofxGuiPanel::addRadar(string name, int _width, int _height, int _min, int _max, float value, int display, int steps)
{
	//	todo
	return NULL;
}

//--------------------------------------------------------------
ofxGuiSwitch* ofxGuiPanel::addSwitch(string name, int _width, int _height, int _min, int _max, int value, const string* paramStrings)
{
	ofxGuiSwitch* obj = new ofxGuiSwitch();
	obj->init(name, mBorder, height - mBorder + getOffset(), _width, _height, _min, _max, value, paramStrings);
	addChild(obj);
	return obj;
}
*/


//--------------------------------------------------------------
int	ofxGuiPanel::getOffset() {
	return (childObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;
}

//--------------------------------------------------------------
void ofxGuiPanel::adjustToNewContent(int _width, int _height)
{
	if(_width > width - mBorder * 2)
		width = _width + mBorder * 2;

	height += _height;
	
	minimizedRect.x = 0;
	minimizedRect.y = 0;
	minimizedRect.width = width;
	minimizedRect.height = windowButtonHeight;
	
	// setHitRegion(0, 0, width, height);
	//	setControlRegion(mBorder, mBorder, mObjWidth - mBorder, mObjHeight - mBorder);
	
	
	

}

void ofxGuiPanel::addChild(ofxGuiObject* obj) {
	adjustToNewContent(obj->width, obj->height + getOffset());
	childObjects.push_back(obj);
	obj->parentObject = this;
}


//--------------------------------------------------------------
void ofxGuiPanel::buildFromXml()
{
	
	/*
	int numberOfTags = mGlobals->mXml.getNumTags("OBJECT");
	
	if(numberOfTags > 0)
	{
		for(int i = 0; i < numberOfTags; i++)
		{
			mGlobals->mXml.pushTag("OBJECT", i);

			//int		id		= mGlobals->mXml.getValue("ID", 0);
			string	type	= mGlobals->mXml.getValue("TYPE", "");
			string	name	= mGlobals->mXml.getValue("NAME", "");
			int		width	= mGlobals->mXml.getValue("WIDTH", 0);
			int		height	= mGlobals->mXml.getValue("HEIGHT", 0);
			int		display	= mGlobals->mXml.getValue("DISPLAY", 0);
			int		steps	= mGlobals->mXml.getValue("STEPS", 0);
			int		mode	= mGlobals->mXml.getValue("MODE", 0);
			string	image	= mGlobals->mXml.getValue("IMAGE", "");
			
			if(type == "SLIDER")
			{
				float	min		= mGlobals->mXml.getValue("MIN", 0.0f);
				float	max		= mGlobals->mXml.getValue("MAX", 0.0f);
				float	value	= mGlobals->mXml.getValue("VALUE", 0.0f);

				ofxGuiSlider* slider = addSlider(name, width, height, min, max, value, display, steps);
				slider->buildFromXml();
			}
			else if(type == "XYPAD")
			{
				float	minx	= mGlobals->mXml.getValue("MIN_X", 0.0f);
				float	miny	= mGlobals->mXml.getValue("MIN_Y", 0.0f);
				float	maxx	= mGlobals->mXml.getValue("MAX_X", 0.0f);
				float	maxy	= mGlobals->mXml.getValue("MAX_Y", 0.0f);
				float	valuex	= mGlobals->mXml.getValue("VALUE_X", 0.0f);
				float	valuey	= mGlobals->mXml.getValue("VALUE_Y", 0.0f);
				
				ofxPoint2f min	= ofxPoint2f(minx, miny);
				ofxPoint2f max	= ofxPoint2f(maxx, maxy);
				ofxPoint2f value	= ofxPoint2f(valuex, valuey);
				
				ofxGuiXYPad* xypad = addXYPad(name, width, height, min, max, value, display, steps);
				xypad->buildFromXml();
			}
			else if(type == "POINTS")
			{
				float	minx	= mGlobals->mXml.getValue("MIN_X", 0.0f);
				float	miny	= mGlobals->mXml.getValue("MIN_Y", 0.0f);
				float	maxx	= mGlobals->mXml.getValue("MAX_X", 0.0f);
				float	maxy	= mGlobals->mXml.getValue("MAX_Y", 0.0f);
				float	valuex	= mGlobals->mXml.getValue("VALUE_X", 0.0f);
				float	valuey	= mGlobals->mXml.getValue("VALUE_Y", 0.0f);
				
				ofxPoint2f min	= ofxPoint2f(minx, miny);
				ofxPoint2f max	= ofxPoint2f(maxx, maxy);
				ofxPoint2f value	= ofxPoint2f(valuex, valuey);
				
				ofxGuiPoints* points = addPoints(name, width, height, min, max, value, display, steps);
				points->buildFromXml();
			}
			else if(type == "BUTTON")
			{
				bool value = mGlobals->mXml.getValue("VALUE", 0);
				
				ofxGuiButton* button = addButton(name, width, height, value, mode, image);
				button->buildFromXml();
			}
			else if(type == "FILES")
			{
				string	subPath	= mGlobals->mXml.getValue("SUBPATH", "");
				string	suffix	= mGlobals->mXml.getValue("SUFFIX", "");
				
				ofxGuiFiles* files = addFiles(name, width, height, mGlobals->mXmlfile, subPath, suffix);
				files->buildFromXml();
			}
			else if(type == "COLOR")
			{
				ofRGBA value = ofRGBA(mGlobals->mXml.getValue("VALUE", "FFFFFFFF"));
				
				ofxGuiColor* color = addColor(name, width, height, value, mode);
				color->buildFromXml();
			}
			else if(type == "MATRIX")
			{
				int	xGrid	= mGlobals->mXml.getValue("XGRID", 0);
				int	yGrid	= mGlobals->mXml.getValue("YGRID", 0);
				int	value	= mGlobals->mXml.getValue("VALUE", 0);
				int	spacing	= mGlobals->mXml.getValue("SPACING", 0);
				
				ofxGuiMatrix* matrix = addMatrix(name, width, height, xGrid, yGrid, value, mode, spacing);

				matrix->buildFromXml();
			}
			else if(type == "SCOPE")
			{
				int			length	= mGlobals->mXml.getValue("LENGTH", 0);
				float		valuex	= mGlobals->mXml.getValue("VALUE_X", 0.0f);
				float		valuey	= mGlobals->mXml.getValue("VALUE_Y", 0.0f);
				ofxPoint2f	value	= ofxPoint2f(valuex, valuey);
				
				ofxGuiScope* scope = addScope(name, width, height, length, value, mode);
				scope->buildFromXml();
			}
			else if(type == "KNOB")
			{
				float	min		= mGlobals->mXml.getValue("MIN", 0.0f);
				float	max		= mGlobals->mXml.getValue("MAX", 0.0f);
				float	value	= mGlobals->mXml.getValue("VALUE", 0.0f);
				
				ofxGuiKnob* knob = addKnob(name, width, height, min, max, value, display, steps);
				knob->buildFromXml();
			}
			else if(type == "SWITCH")
			{
				float	min		= mGlobals->mXml.getValue("MIN", 0.0f);
				float	max		= mGlobals->mXml.getValue("MAX", 0.0f);
				float	value	= mGlobals->mXml.getValue("VALUE", 0.0f);
				
				//	const string* strings = 
				
				ofxGuiSwitch* swtch = addSwitch(name, width, height, min, max, value, NULL);
				swtch->buildFromXml();
			}
			
			mGlobals->mXml.popTag();
		}
	}
	 */
}

//--------------------------------------------------------------
void ofxGuiPanel::saveToXml()
{
	ofxGuiObject* tmpObj;
	
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:BORDER", mBorder, id);
	mGlobals->mXml.setValue("OBJECT:SPACING", mSpacing, id);
	mGlobals->mXml.pushTag("OBJECT", id);
	
	for(int i = 0; i < childObjects.size(); i++)
	{
		tmpObj = (ofxGuiObject*)childObjects.at(i);
		tmpObj->saveToXml();
	}
	
	mGlobals->mXml.popTag();
}

//--------------------------------------------------------------

