/*
 *  ofxGuiScope.h
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

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_SCOPE
#define OFX_GUI_SCOPE

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiScope : public ofxGuiObject
{
	
	public:
		
		 ofxGuiScope();
		~ofxGuiScope();
		
		void		init(/*int id,*/ string name, int x, int y, int width, int height, int length, ofxPoint2f value, int mode);
		
		void		setValue(ofxPoint2f value);
		
		void		draw();
			
		ofxGuiObject*	mouseMoved(int x, int y);
		ofxGuiObject*	mouseDragged(int x, int y, int button);
		ofxGuiObject*	mousePressed(int x, int y, int button);
		ofxGuiObject*	mouseReleased(int x, int y, int button);
		ofxGuiObject*	keyPressed(int key);
		ofxGuiObject*	keyReleased(int key);
		
		void		buildFromXml();
		void		saveToXml();
			
		ofxPoint2f	valueToFraction(ofxPoint2f value);
		ofxPoint2f	fractionToValue(ofxPoint2f fraction);

		ofxPoint2f	mValue;
		
		float*		mBuffer;
		int			mBufferLength;
	};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
