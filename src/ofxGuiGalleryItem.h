/*
 *  ofxGuiButton.h
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

#ifndef OFX_GUI_GALLERY_ITEM
#define OFX_GUI_GALLERY_ITEM

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"
#include "ofEvents.h"


//	----------------------------------------------------------------------------------------------------



class ofxGuiGalleryItem : public ofxGuiObject
{
	
public:
	
	ofxGuiGalleryItem();
	~ofxGuiGalleryItem();
	
	void		init(string name, int x, int y, int width, int height, bool value, int mode, string image);
	
	void		draw();
			
	bool		mValue;
	
	ofImage		image;
	
	
	
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
