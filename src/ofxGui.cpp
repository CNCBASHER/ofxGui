/*  ofxGui.cpp
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

#include "ofxGui.h"

//--------------------------------------------------------------
ofxGui* ofxGui::Instance()
{
	static ofxGui gui;
	return &gui;  // returns the global intance
}

//--------------------------------------------------------------
ofxGui::ofxGui() {
	
	cout << "in the constructor" << endl;
	ofAddListener(ofEvents.setup, this, &ofxGui::setup); // sets up any guis
	ofAddListener(ofEvents.update, this, &ofxGui::update);
	ofAddListener(ofEvents.draw, this, &ofxGui::draw);
	// hmmmm not sure
	//ofAddListener(ofEvents.exit, this, &ofxGui::exit);

	ofAddListener(ofEvents.keyPressed, this, &ofxGui::keyPressed);
	ofAddListener(ofEvents.keyReleased, this, &ofxGui::keyReleased);
	ofAddListener(ofEvents.mouseMoved, this, &ofxGui::mouseMoved);
	ofAddListener(ofEvents.mouseDragged, this, &ofxGui::mouseDragged);
	ofAddListener(ofEvents.mouseReleased, this, &ofxGui::mouseReleased);
	ofAddListener(ofEvents.mousePressed, this, &ofxGui::mousePressed);

	mIsActive			= false;
	mDoUpdate			= false;
	mXmlDone			= true;
	
	mGlobals			= ofxGuiGlobals::Instance();
	
	// dragging
	dragObject			= NULL;
	dragPreviousPosition = ofxPoint2f(FLT_MIN, FLT_MIN); // the last poistion in the drag world
}

//--------------------------------------------------------------
/*
ofxGui::~ofxGui() {
	ofRemoveListener(ofEvents.setup, this, &ofxGui::setup); // sets up any guis
	ofRemoveListener(ofEvents.update, this, &ofxGui::update);
	ofRemoveListener(ofEvents.draw, this, &ofxGui::draw);
	// hmmmm not sure
	//ofRemoveListener(ofEvents.exit, this, &ofxGui::exit);
	
	ofRemoveListener(ofEvents.keyPressed, this, &ofxGui::keyPressed);
	ofRemoveListener(ofEvents.keyReleased, this, &ofxGui::keyReleased);
	ofRemoveListener(ofEvents.mouseMoved, this, &ofxGui::mouseMoved);
	ofRemoveListener(ofEvents.mouseDragged, this, &ofxGui::mouseDragged);
	ofRemoveListener(ofEvents.mouseReleased, this, &ofxGui::mouseReleased);
	ofRemoveListener(ofEvents.mousePressed, this, &ofxGui::mousePressed);
	
	//delete mGlobals;
	
}
*/

void ofxGui::setup(ofEventArgs & args) {
	if(mIsActive) {
		for(int i = 0; i < mObjects.size(); i++) {
			mObjects[i]->_setup(args);
		}
	}
}

//--------------------------------------------------------------
void ofxGui::update(ofEventArgs & args) {
	if(mIsActive) {
		for(int i = 0; i < mObjects.size(); i++) {
			mObjects[i]->_update(args);
		}
	}
}

//--------------------------------------------------------------
void ofxGui::draw(ofEventArgs & args)
{  
	int w, h;

	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)w/(float)h, (float)h / 2.0 / tanf(PI * 60.0f / 360.0) / 10.0, (float)h / 2.0 / tanf(PI * 60.0f / 360.0) * 10.0);
	gluLookAt((float)w / 2.0, (float)h / 2.0, (float)h / 2.0 / tanf(PI * 60.0f / 360.0), (float)w / 2.0, (float)h / 2.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0); 

	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);


	if(mIsActive)
	{
		ofEnableAlphaBlending();

		// draw from the back forward
		for(int i = 0; i < mObjects.size(); i++)
		{
			mObjects[i]->_draw(args);
		}
		
		ofDisableAlphaBlending();
	}
}

//--------------------------------------------------------------
void ofxGui::exit(ofEventArgs & args)
{
	if(mIsActive) {
		for(int i = 0; i < mObjects.size(); i++) {
			mObjects[i]->_exit(args);
		}
	}
}

//--------------------------------------------------------------
void ofxGui::keyPressed(ofKeyEventArgs & args)
{
		
	if(mIsActive) {

		ofxGuiObject* handled = NULL;
		ofxGuiObject* lastHandleResponse = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
			lastHandleResponse = mObjects[i]->_keyPressed(args, handled);
			
			if(lastHandleResponse && !handled) {
				handled = lastHandleResponse;
			}
		}
	}
}

//--------------------------------------------------------------
void ofxGui::keyReleased(ofKeyEventArgs & args)
{	
	if(mIsActive) {

		ofxGuiObject* handled = NULL;
		ofxGuiObject* lastHandleResponse = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
			lastHandleResponse = mObjects[i]->_keyReleased(args, handled);
			
			if(lastHandleResponse && !handled) {
				handled = lastHandleResponse;
			}
		}
	}
}
//--------------------------------------------------------------
void ofxGui::mouseMoved(ofMouseEventArgs & args)
{

	if(mIsActive) {
		ofxGuiObject* handled = NULL;
		ofxGuiObject* _lastMouseMovedHandler = lastHandler;

		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
	
			handled = mObjects[i]->_mouseMoved(args, handled);
			
			// currently an event can only be handled by one item
			if(handled) {
				//lastMouseMovedHandler = handled;
				lastHandler = handled;
				break; // jump out of the loop
			}
		}
		
		// if this is not the last one, then let it go
		if(_lastMouseMovedHandler != NULL && _lastMouseMovedHandler != lastHandler) { 
			_lastMouseMovedHandler->_mouseMoved(args, handled);
		}
		
		return;		
	}
	
	lastHandler = NULL;
}

//--------------------------------------------------------------
void ofxGui::mouseDragged(ofMouseEventArgs & args)
{

	
	if(mIsActive) {
		ofxGuiObject* handled = NULL;
		ofxGuiObject* lastHandleResponse = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
			
			lastHandleResponse = mObjects[i]->_mouseDragged(args, handled, dragObject);
			
			if(lastHandleResponse && !handled ) {
				
				handled = lastHandleResponse;

				if (!dragObject) {
					dragObject = handled;
				}

			}
		}
	}
}

//--------------------------------------------------------------
void ofxGui::mousePressed(ofMouseEventArgs & args)
{
	
	if(mIsActive) {
		ofxGuiObject* handled = NULL;
		ofxGuiObject* lastHandleResponse = NULL;

		for(int i = (mObjects.size()-1); i >= 0; i--) {
			
			lastHandleResponse = mObjects[i]->_mousePressed(args, handled);
			
			if(lastHandleResponse && !handled) {
				handled = lastHandleResponse;
				bringToFront(i);
			}
		}
	}
}

//--------------------------------------------------------------
void ofxGui::mouseReleased(ofMouseEventArgs & args)
{
	
	if(mIsActive) {
		ofxGuiObject* handled = NULL;
		ofxGuiObject* lastHandleResponse = NULL;
		
		for(int i = (mObjects.size()-1); i >= 0; i--) {
			
			lastHandleResponse = mObjects[i]->_mouseReleased(args, handled, dragObject);
			
			if(lastHandleResponse && !handled) {
				handled = lastHandleResponse;
			}
		}
	}

	if(dragObject) {
		// if we were dragging, then we need to check and see where it was dropped
		dragObject = NULL;
	} 
	
}

//--------------------------------------------------------------
void ofxGui::bringToFront(int index) 
{
	if(index >= 0 && index < mObjects.size()) {
		if(index < (mObjects.size() - 1)) {
			// keep going until you are at the front
			for(int i = index; i < mObjects.size(); ++i)
				bringForward(i);
		} else {
			ofLog(OF_LOG_VERBOSE, "Already at the front.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "Index out of range.");
	}
	
}

//--------------------------------------------------------------
void ofxGui::bringForward(int index)	
{
	if(index >= 0 && index < mObjects.size()) {
		if(index < (mObjects.size() - 1)) {
			swap(mObjects[index], mObjects[index+1]);
		} else {
			ofLog(OF_LOG_VERBOSE, "Already at the front.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "Index out of range.");
	}	
}

//--------------------------------------------------------------
void ofxGui::sendToBack(int index)
{
	if(index >= 0 && index < mObjects.size()) {
		if(index != 0) {
			for(int i = index; i >= 0; --i)
				sendBackward(i);
		} else {
			ofLog(OF_LOG_VERBOSE, "Already at the back.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "Index out of range.");
	}
}

//--------------------------------------------------------------
void ofxGui::sendBackward(int index)
{
	if(index >= 0 && index < mObjects.size()) {
		if(index != 0) {
			swap(mObjects[index], mObjects[index-1]);
		} else {
			ofLog(OF_LOG_VERBOSE, "Already at the back.");
		}
	} else {
		ofLog(OF_LOG_ERROR, "Index out of range.");
	}
}


//--------------------------------------------------------------
ofxGuiObject* ofxGui::addGuiObject(ofxGuiObject* obj) {
	mObjects.push_back(obj);
	return obj;
}

//--------------------------------------------------------------
bool ofxGui::removeGuiObject(ofxGuiObject* obj) {
	// iterator to vector element:
	mObjectsIter = find (mObjects.begin(), mObjects.end(), obj);
	
	if(mObjectsIter != mObjects.end()) {
		mObjects.erase(mObjectsIter);
		return true;
	} else {
		return false;
	}	
	
}

//--------------------------------------------------------------
ofxGuiPanel* ofxGui::addPanel(string name, int x, int y, int border, int spacing)
{
	ofxGuiPanel* newPanel = new ofxGuiPanel();
	newPanel->init(name, x, y, border, spacing);
	addGuiObject(newPanel);
	return newPanel;
}

//--------------------------------------------------------------
bool ofxGui::removePanel(ofxGuiPanel* panel)
{
	return removeGuiObject(panel);
}

//--------------------------------------------------------------
void ofxGui::activate(bool activate)
{
	mIsActive = activate;
}

//--------------------------------------------------------------
void ofxGui::forceUpdate(bool update)
{
	mDoUpdate = update;
}

//--------------------------------------------------------------
bool ofxGui::buildFromXml(string file)
{
	if(!mXmlDone)
		return false;
	
	if(!mGlobals->mXml.loadFile(file))
		return false;
	
	int numberOfTags = mGlobals->mXml.getNumTags("UI");
	
	if(numberOfTags != 1)
		return false;
	
	mObjects.clear();
	
	mXmlDone			= false;
	mGlobals->mXmlfile	= file;
	
	mGlobals->mXml.pushTag("UI", 0);

	mIsActive	= mGlobals->mXml.getValue("ISACTIVE", 0);
	mDoUpdate	= mGlobals->mXml.getValue("DOUPDATE", 0);

	mGlobals->buildFromXml();
	
	numberOfTags = mGlobals->mXml.getNumTags("OBJECT");
	
	if(numberOfTags > 0)
	{
		for(int i = 0; i < numberOfTags; i++)
		{
			mGlobals->mXml.pushTag("OBJECT", i);
			
			int		id		= mGlobals->mXml.getValue("ID", 0);
			string	type	= mGlobals->mXml.getValue("TYPE", "");
			string	name	= mGlobals->mXml.getValue("NAME", "");
			int		x		= mGlobals->mXml.getValue("LEFT", 0);
			int		y		= mGlobals->mXml.getValue("TOP", 0);
			int		border	= mGlobals->mXml.getValue("BORDER", 0);
			int		spacing	= mGlobals->mXml.getValue("SPACING", 0);
			
			if(type == "PANEL")
			{
				ofxGuiPanel* panel = addPanel(/*id,*/ name, x, y, border, spacing);
				panel->buildFromXml();
			}
			
			mGlobals->mXml.popTag();
		}
	}
	
	mGlobals->mXml.popTag();
	
	mXmlDone = true;
	
	return true;
}

//--------------------------------------------------------------
void ofxGui::saveToXml(string file)
{
	if(!mXmlDone)
		return;

	mXmlDone = false;

	mGlobals->mXml.clear();
		
	int id = mGlobals->mXml.addTag("UI");
	
	mGlobals->mXml.setValue("UI:VERSION", OFXGUI_VERSION, id);

	mGlobals->mXml.setValue("UI:ISACTIVE", mIsActive, id);
	mGlobals->mXml.setValue("UI:DOUPDATE", mDoUpdate, id);
		
	mGlobals->mXml.pushTag("UI", id);

	mGlobals->saveToXml();

	ofxGuiObject* tmpObj;

	for(int i = 0; i < mObjects.size(); i++)
	{
		tmpObj = (ofxGuiObject*)mObjects.at(i);
		tmpObj->saveToXml();
	}
	
	mGlobals->mXml.popTag();
	mGlobals->mXml.saveFile(file);

	mXmlDone = true;
}

//--------------------------------------------------------------

