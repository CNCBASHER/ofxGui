/*
 *  ofxGuiObject.cpp
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
#include "ofxGuiObject.h"

//--------------------------------------------------------------
ofxGuiObject::ofxGuiObject()
{
	isEnabled		= true;
	canDisable		= true;

	parentObject	= NULL;

	mParamType		= kofxGui_Object_Base;
	mParamName		= "";
	
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	
	
	mMode			= 0;
	mDisplay		= kofxGui_Display_Float2;
	mSteps			= 0;
	
	mouseDown	= false;
	mouseOver	= false;
	
	mGlobals		= ofxGuiGlobals::Instance();
	
	
	// tooltips
	//timeUntilNextTooltip	= LONG_MAX;
	//timeSinceLastTooltip	= LONG_MIN;
	
	//tooltipFadeOutTime		= 500; // 1/2 second
	//tooltipWaitTime			= 2500; // 2.5 seconds
	
	lastTooltipPoint		= ofxPoint2f(FLT_MIN, FLT_MAX);

	// drag'n'drop
	isDragMoveable			= false;
	isDragging				= false;
	
	isDropSender			= false; // can we drop this thing on something
	isDropSenderReady		= false;
	isDropReceiver			= false; // can we receive a dropped object
	isDropReceiverReady		= false;
	
	
	
	// control rect
	cRect.x = 0;
	cRect.y = 0;
	cRect.width = -1;
	cRect.height = -1;
	
}

ofxGuiObject::~ofxGuiObject() {
	// destructor called
	cout << "OBJECT DESTRUCTOR CALLED" << endl;
}

//--------------------------------------------------------------

void ofxGuiObject::_setup(ofEventArgs &e) {
	if(!isEnabled) return;
	setup();
}


//--------------------------------------------------------------

void ofxGuiObject::_update(ofEventArgs &e) {
	if(!isEnabled) return;
	
	/*
	// check to see if object has moved, and if so update mouse events
	if(oldRect.x != this->x || oldRect.y != this->y || oldRect.width != this->width ||oldRect.height != this->height) {
		ofMouseEventArgs e;
		e.button = _mouseButton;
		e.x = _mouseX;
		e.y = _mouseY;
		
		if(_mouseDown) _mouseDragged(e, false);	
		else _mouseMoved(e, false);
		
		oldRect =  (ofRectangle) (*this);
	}
	 */
	
	
	//isDragging = (this == ofxGui::Instance()->dragObject); // are we currently being dragged?
	
	// tooltip stuff should go in here and in mouse moved
	// tooltips
	//timeUntilNextTooltip	= LONG_MAX;
	//timeSinceLastTooltip	= LONG_MIN;
	
	/*
	if(isMouseDragging()) {
		
		ofxPoint2f screenPosition = localToScreen(ofxPoint2f(x, y));
		
		ofxPoint2f pmouseScreenPosition = ofxPoint2f(_pmouseX, _pmouseY);
		ofxPoint2f mouseScreenPosition = ofxPoint2f(_mouseX, _mouseY);
		
		ofxPoint2f pmouseLocalPosition = screenToLocal(pmouseScreenPosition);
		ofxPoint2f mouseLocalPosition = screenToLocal(mouseScreenPosition);
		
		ofxPoint2f dMousePosition = mouseScreenPosition - pmouseScreenPosition;
		
		x += dMousePosition.x;
		y += dMousePosition.y;
		
		// position is always drawn relative to parent (glTranslate(xParent,yParent) ... of parent ...)
		
	}
	 */
	
	
	
	update();
}

//--------------------------------------------------------------

void ofxGuiObject::_draw(ofEventArgs &e) {
	if(!isEnabled) return;
	draw();
}

//--------------------------------------------------------------

void ofxGuiObject::_exit(ofEventArgs &e) {
	//if(!enabled) return;
	exit();
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_keyPressed(ofKeyEventArgs &e, ofxGuiObject* handled)
{
	
	if(!isEnabled) return NULL;

	ofxGuiObject* newHandler = NULL;
	
	pKey = key;
	key = e.key;

	
	for(int i = (childObjects.size()-1); i >= 0; i--) {
		newHandler = childObjects[i]->_keyReleased(e, handled);
		
		// currently an event can only be handled by one item
		if(newHandler && !handled) {
			handled = newHandler;
		}
	}
	
	
	if(isKeyMapped(key, handled)) {
		onKeyPressed(key);
	}
	
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_keyReleased(ofKeyEventArgs &e, ofxGuiObject* handled)
{
	
	if(!isEnabled) return NULL;
	
	ofxGuiObject* newHandler = NULL;
	
	pKey = key;
	key = e.key;
	
	for(int i = (childObjects.size()-1); i >= 0; i--) {
		newHandler = childObjects[i]->_keyReleased(e, handled);
		
		// currently an event can only be handled by one item
		if(newHandler && !handled) {
			handled = newHandler;
		}
	}
	
	
	if(isKeyMapped(key, handled)) {
		onKeyReleased(key);
	} 
	
	
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_mouseMoved(ofMouseEventArgs &e, ofxGuiObject* handled)
{
	
	if(!isEnabled) return NULL;
	
	ofxGuiObject* newHandler = NULL;
	
	saveMouseEvent(e);
	
	for(int i = (childObjects.size()-1); i >= 0; i--) {
		newHandler = childObjects[i]->_mouseMoved(e, handled);
		
		// currently an event can only be handled by one item
		if(newHandler && !handled) {
			handled = newHandler;
		}
	}
	 
	
	if(!handled && hitTest(mouseX, mouseY)) {			// if mouse is over the object
		
		// if the mouse wasn't over it already
		if(!mouseOver) {		
			onRollOver(mouseX, mouseY);	// call onRollOver
			mouseOver = true;				// update flag
		} else {
			// we were already on it!
			onMouseMove(mouseX, mouseY);	// and trigger onMouseMove
		}
		
		handled = this;

	} else if(mouseOver) {		// if mouse is not over the object, but the flag is true (From previous frame)
		mouseOver = false;		// update flag
		onRollOut();			// call onRollOut
	} else {
		// unaffected
	}
	
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_mouseDragged(ofMouseEventArgs &e, ofxGuiObject* handled, ofxGuiObject* dragObject)
{
	
	
	if(!isEnabled) return NULL;
	
	ofxGuiObject* newHandler = NULL;

	saveMouseEvent(e);
		
	for(int i = (childObjects.size()-1); i >= 0; i--) {
		newHandler = childObjects[i]->_mouseDragged(e, handled, dragObject);
		// currently an event can only be handled by one item
		if(newHandler && !handled) {
			handled = newHandler;
		}
	}
	
	
		
	bool didHit = hitTest(mouseX, mouseY);
	
	if(!handled && (isDragging || didHit)) {						
		
		bool justStartedDragging = false;
		
        
		if(mouseDown) {
            

            
			if(!isDragging) {
				isDragging = true;
				justStartedDragging = true;
				preDragPosition = ofxPoint2f(x, y);
			} 
			
			if(isDragMoveable) {
				// TODO: this seems to result in slippery dragging
				// then we are moving!
				ofxPoint2f dMousePosition = ofxPoint2f(mouseX, mouseY) - ofxPoint2f(pMouseX, pMouseY);
				x += dMousePosition.x;
				y += dMousePosition.y;
				// position is always drawn relative to parent (glTranslate(xParent,yParent) ... of parent ...)
			}
				
			if(justStartedDragging) {
				onObjectDragStart(mouseX, mouseY, mouseButton);
			} else {
				onObjectDragging(mouseX, mouseY, mouseButton);
			}
			
		} 
        
        if(didHit) {
            onDragOver(mouseX, mouseY, mouseButton);
        } else {
            onDragOutside(mouseX, mouseY, mouseButton);
        }
        
        
            /*
        cout << "DRAGGING IN HERE " + 
        mParamName << " IS DRAGGING/HIT/HANDLED/MOUSE: " 
        << isDragging << " / "
        << didHit << " / "
        << handled << " / "
        << mouseDown << " / "
        << endl;
             */


		handled = this;
	
	} else {
		// ALREADY HANDLED OR NOT DRAGGING OR NOT OVER
		if(didHit) {
			isDropReceiverReady = isDropReceiverForObject(dragObject);
            onDragOver(mouseX, mouseY, mouseButton);
		} else {
			isDropReceiverReady = false;
			onDragOutside(mouseX, mouseY, mouseButton);
		}		
	}
		
	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_mousePressed(ofMouseEventArgs &e, ofxGuiObject* handled)
{
	
	if(!isEnabled) return NULL;
	
	ofxGuiObject* newHandler = NULL;

	saveMouseEvent(e);
	
	for(int i = (childObjects.size()-1); i >= 0; i--) {
		newHandler = childObjects[i]->_mousePressed(e, handled);
		// currently an event can only be handled by one item
		if(newHandler && !handled) {
			handled = newHandler;
		}
	}
	
	
	if(!handled && hitTest(mouseX, mouseY)) { 				
		if(!mouseDown) {				
			mouseDown = true;						 
			onPress(mouseX, mouseY, mouseButton);
		}
		handled = this;					// set this as handled
	} else {							// if mouse is not over
		mouseDown = false;
		onPressOutside(mouseX, mouseY, mouseButton); // someone else was pressed
	}

	return handled;
}

//--------------------------------------------------------------

ofxGuiObject* ofxGuiObject::_mouseReleased(ofMouseEventArgs &e, ofxGuiObject* handled, ofxGuiObject* dragObject)
{

	if(!isEnabled) return NULL;

	ofxGuiObject* newHandler = NULL;

	// set the previous
	saveMouseEvent(e);
	
	for(int i = (childObjects.size()-1); i >= 0; i--) {
		newHandler = childObjects[i]->_mouseReleased(e, handled, dragObject);
		// currently an event can only be handled by one item
		if(newHandler && !handled) {
			handled = newHandler;
		}
	}
	
	// hit test
	bool didHit = hitTest(mouseX, mouseY);
	
	if(isDragging || didHit) {		
		// this is either the object being dragged or an object being dropped upon
		
		if(isDragging) {
			
			if(didHit) {
				onRelease(mouseX, mouseY, mouseButton);
			} else {
				onReleaseOutside(mouseX, mouseY, mouseButton);
			}
			
			handled = this;
		} else if(isDropReceiverForObject(dragObject)) {
			// are we a drop receiver? and is there valid drag object?
			onObjectDropReceived(mouseX, mouseY, mouseButton, dragObject); // note that we got it
			dragObject->onObjectDropSent(mouseX, mouseY, mouseButton, this); // note to the object that it was sent
		} else {
			// drop failed
			onRelease(mouseX, mouseY, mouseButton);
		}

	} else {
		onReleaseOutside(mouseX, mouseY, mouseButton);
	}
		
	
	// in any case, the mouse is no longer down
    isDragging = false;
	mouseDown = false;
	
	isDropReceiverReady = false;
	preDragPosition = NULL; // get rid of the reference after

	return handled;
}

//--------------------------------------------------------------
void ofxGuiObject::cancelDrag() {
	if(isDragging) {
		isDragging = false;
		onDragCancelled(preDragPosition.x, preDragPosition.y);
		preDragPosition = NULL; // get rid of the reference after
	}
}
//--------------------------------------------------------------
/*
void ofxGuiObject::releaseDrag() {
	
	if(isMouseDragging()) {
		_isMouseDragging = false;
		onDragReleased(x, y);
		preDragPosition = NULL; // get rid of the reference
	}
}
 */



//--------------------------------------------------------------

bool ofxGuiObject::hitTest(int screenX, int screenY) {
    
    
	ofxPoint2f l = screenToLocal(ofxPoint2f(screenX, screenY));	
	ofRectangle hitRegion = getHitRegion();
	
   // cout << hitRegion.x << "|" << hitRegion.y << hitRegion.width << hitRegion.width 
    
    return (l.x > 0 /*hitRegion.x*/ && l.y > 0/*hitRegion.y*/ && l.x <= hitRegion.width && l.y <= hitRegion.height);
}

//--------------------------------------------------------------

void ofxGuiObject::setEnabled(bool _enabled) {
	
	// tell all of the children (if any)
	for(int i = (childObjects.size()-1); i >= 0; i--) {
		childObjects[i]->setEnabled(_enabled);
	}
	
	if(!canDisable) return; // nothing to do;

	
	if(isEnabled == _enabled) return; // nothing actually changed
	
	isEnabled = _enabled; // else we know there is something to do


	// send the events
	if (isEnabled) {
		onEnabled();
	} else {
		onDisabled();
	}

}


//--------------------------------------------------------------
void ofxGuiObject::enable() { setEnabled(true); }

//--------------------------------------------------------------
void ofxGuiObject::disable() { setEnabled(false); }

//--------------------------------------------------------------
void ofxGuiObject::enableTooltip() 
{
	isTooltipEnabled = true;
	onTooltipEnabled();
}

//--------------------------------------------------------------
void ofxGuiObject::disableTooltip() 
{	
	isTooltipEnabled = false;
	onTooltipDisabled();
}

//--------------------------------------------------------------
void ofxGuiObject::setTooltip(string _tooltip) {
	tooltip = _tooltip;
}

//--------------------------------------------------------------
/*
void ofxGuiObject::drawTooltipString(float _x, float _y)
{
	glColor4f(mGlobals->mTextColor.r, mGlobals->mTextColor.g, mGlobals->mTextColor.b, mGlobals->mTextColor.a);
	
	_x += mGlobals->mHeadFontXOffset;
	_y += mGlobals->mHeadFontYOffset;
	
	mGlobals->mHeadFont.drawString(tooltip, _x, _y);
	
}
*/
//--------------------------------------------------------------
void ofxGuiObject::drawHeadString(float _x, float _y, string _text, bool _center)
{
	if(isEnabled) {
		glColor4f(mGlobals->mTextColor.r, mGlobals->mTextColor.g, mGlobals->mTextColor.b, mGlobals->mTextColor.a);
	} else {
		glColor4f(mGlobals->mDisabledColor.r, mGlobals->mDisabledColor.g, mGlobals->mDisabledColor.b, mGlobals->mDisabledColor.a);
	}
	
	if(_center) {
		_x -= roundInt(mGlobals->mHeadFont.stringWidth(_text) / 2.0f);
	} else {
		_x += mGlobals->mHeadFontXOffset;
	}
	
	_y += mGlobals->mHeadFontYOffset;
	
	mGlobals->mHeadFont.drawString(_text, _x, _y);
	//ofDrawBitmapString(text, x, y);
	
	//	debug rect to position font
	/*
	ofRectangle rect = uiGlobals->headFont.getStringBoundingBox(text, x, y);
	ofNoFill();
	glColor4f(1.0, 0.0, 0.0, 1.0);
	ofRect(x, y, rect.width, OFXGUI_HEAD_HEIGHT);
	*/
}

//--------------------------------------------------------------
void ofxGuiObject::drawParamString(float _x, float _y, string _text, bool _center)
{
	if(isEnabled) {
		glColor4f(mGlobals->mTextColor.r, mGlobals->mTextColor.g, mGlobals->mTextColor.b, mGlobals->mTextColor.a);
	} else {
		glColor4f(mGlobals->mDisabledColor.r, mGlobals->mDisabledColor.g, mGlobals->mDisabledColor.b, mGlobals->mDisabledColor.a);
	}
		
	if(_center) {
		_x -= roundInt(mGlobals->mParamFont.stringWidth(_text) / 2.0f);
	} else {
		_x += mGlobals->mParamFontXOffset;
	}	
		
	_y += mGlobals->mParamFontYOffset;
	
	mGlobals->mParamFont.drawString(_text, _x, _y);
	
	//ofDrawBitmapString(text, x, y);
	
	//	debug rect to position font
	/*
	ofRectangle rect = mGlobals->mParamFont.getStringBoundingBox(text, x, y);
	ofNoFill();
	glColor4f(1.0, 0.0, 0.0, 1.0);
	ofRect(x, y, rect.width, mGlobals->mParamFontHeight);
	*/
}

//--------------------------------------------------------------
string ofxGuiObject::floatToString(float value, int display)
{
	string stringValue = "";
	
	switch(display)
	{
		case kofxGui_Display_Int:
			stringValue = ofToString((int)value, 0);
			break;
			
		case kofxGui_Display_Hex:
			char hex[64];
			sprintf(hex, "%X", (int)value);
			stringValue = hex;
			break;
			
		case kofxGui_Display_Float2:
			stringValue = ofToString(value, 2);	
			break;
			
		case kofxGui_Display_Float4:
			stringValue = ofToString(value, 4);
			break;
			
		default:
			stringValue = ofToString(value);
			break;
	}

	return stringValue;
}

//--------------------------------------------------------------
string ofxGuiObject::pointToString(ofxPoint2f value, int display)
{
	return floatToString(value.x, display) + " " + floatToString(value.y, display);	
}

//--------------------------------------------------------------
string ofxGuiObject::rgbaToString(ofRGBA value, int display)
{
	return value.toString(display);	
}

//--------------------------------------------------------------
ofRectangle ofxGuiObject::getHitRegion() {
	if(hasCustomHitRegion()) {
		return cRect;
	} else {
		return ofRectangle(x,y,width,height); // pass a reference?
	}
}

bool ofxGuiObject::hasCustomHitRegion() {
	return (cRect.width > -1 && cRect.height > -1);
}

//--------------------------------------------------------------
/*
ofxPoint2f ofxGuiObject::screenToFraction(ofxPoint2f p)
{
	
	ofRectangle workingHitRegion = ofRectangle(x,y,width,height);
	
	if(hasCustomHitRegion()) {
		workingHitRegion = cRect;
	}
	
	ofxPoint2f controlRectAnchor = ofxPoint2f(workingHitRegion.x, workingHitRegion.y);
	ofxPoint2f controlRectDims = ofxPoint2f(workingHitRegion.width, workingHitRegion.height);
	
	p.x = CLAMP(p.x, controlRectAnchor.x, workingHitRegion.x + workingHitRegion.width);
	p.y = CLAMP(p.y, controlRectAnchor.y, workingHitRegion.y + workingHitRegion.height);
	
	p-=controlRectAnchor;
	p/=controlRectDims;
	
	//p.x = (p.x - mCtrX) / mCtrWidth;
	//p.y = (p.y - mCtrY) / mCtrHeight;
	
	return p;
}
 */

/*
//--------------------------------------------------------------
ofxPoint2f ofxGuiObject::fractionToLocal(ofxPoint2f p)
{
	
	ofRectangle workingHitRegion = ofRectangle(x,y,width,height);
	
	if(hasCustomHitRegion()) {
		workingHitRegion = cRect;
	}
	
	return ofxPoint2f(workingHitRegion.x + workingHitRegion.width * p.x, workingHitRegion.y + workingHitRegion.height * p.y);
}
 */

//--------------------------------------------------------------
ofxPoint2f	ofxGuiObject::getScreenPosition() {
	return localToScreen(ofxPoint2f(x,y));
}

//--------------------------------------------------------------
ofxPoint2f ofxGuiObject::screenToLocal(ofxPoint2f p) {
	return p - getScreenPosition();
}

//--------------------------------------------------------------
ofxPoint2f ofxGuiObject::localToScreen(ofxPoint2f p) {
	if(hasParent()) {
		return parentObject->getScreenPosition() + p;
	} else {
		return p;
	}
}

//--------------------------------------------------------------
bool ofxGuiObject::hasParent() {
	return parentObject != NULL;
}

//--------------------------------------------------------------

void ofxGuiObject::setHitRegion(int _x, int _y, int _width, int _height)
{
	cRect = ofRectangle(_x,_y,_width,_height);
}

//--------------------------------------------------------------
int ofxGuiObject::saveObjectData()
{
	/*
	int id	= mGlobals->mXml.addTag("OBJECT");
	
	mGlobals->mXml.setValue("OBJECT:ENABLED", isEnabled, id);
	mGlobals->mXml.setValue("OBJECT:TYPE", getTagName(), id);
	mGlobals->mXml.setValue("OBJECT:NAME", mParamName, id);

	mGlobals->mXml.setValue("OBJECT:LEFT", mObjX, id);
	mGlobals->mXml.setValue("OBJECT:TOP", mObjY, id);
	//	mGlobals->mXml.setValue("OBJECT:WIDTH", mObjWidth, id);
	//	mGlobals->mXml.setValue("OBJECT:HEIGHT", mObjHeight, id);
	
	//	mGlobals->mXml.setValue("OBJECT:CTRX", mCtrX, id);
	//	mGlobals->mXml.setValue("OBJECT:CTRY", mCtrY, id);
	
	mGlobals->mXml.setValue("OBJECT:WIDTH", mCtrWidth, id);
	mGlobals->mXml.setValue("OBJECT:HEIGHT", mCtrHeight, id);
	
	mGlobals->mXml.setValue("OBJECT:MODE", mMode, id);
	mGlobals->mXml.setValue("OBJECT:DISPLAY", mDisplay, id);
	mGlobals->mXml.setValue("OBJECT:STEPS", mSteps, id);
	
	return id;
	 */
	return -1;
}


//--------------------------------------------------------------

// this can be overridden to provide more sophisticated drag/drop filtering
bool ofxGuiObject::isDropReceiverForObject(ofxGuiObject* dragObject) {
	return dragObject && isDropReceiver && dragObject->isDropSender;
}

//--------------------------------------------------------------

string ofxGuiObject::getTagName()
{
	return kofxGui_Tags[mParamType];
}

//--------------------------------------------------------------
void ofxGuiObject::saveMouseEvent(ofMouseEventArgs &e) 
{
	pMouseX = mouseX;
	pMouseY = mouseY;
	pMouseButton = mouseButton;
	
	mouseX = e.x;
	mouseY = e.y;
	mouseButton = e.button;
}

//--------------------------------------------------------------
