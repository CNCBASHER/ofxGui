/*
 *  ofxGuiGlobals.cpp
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
#include "ofxGuiGlobals.h"

//--------------------------------------------------------------
ofxGuiGlobals* ofxGuiGlobals::Instance()
{
	static ofxGuiGlobals globals;
	return &globals;
}

//--------------------------------------------------------------
ofxGuiGlobals::ofxGuiGlobals()
{
	mXmlfile			= "";

	mHeadFontName		= "resources/fonts/verdana.ttf";
	mHeadFontSize		= 12;
	mHeadFontXOffset	= -2;
	mHeadFontYOffset	= 8;
	mHeadFontHeight		= 12;

	mParamFontName		= "resources/fonts/automat.ttf";
	mParamFontSize		= 6;
	mParamFontXOffset	= -2;
	mParamFontYOffset	= 6;
	mParamFontHeight	= 12;

	mButtonXText		= 4;
	mButtonYText		= 0;

	mFilesXText			= 3;
	mFilesYText			= 3;

	mPointSize			= 6;

	mKnobSize			= 10;

	mCoverColor			= ofRGBA(0x00000088);
	mTextColor			= ofRGBA(0xFFFFFFFF);
	mBorderColor		= ofRGBA(0xFFFFFFFF);
	mFrameColor			= ofRGBA(0xFFFFFFFF);
	mSliderColor		= ofRGBA(0x0099FFFF);
	mAxisColor			= ofRGBA(0x00FF00FF);
	mHandleColor		= ofRGBA(0xFFFFFFFF);
	mButtonColor		= ofRGBA(0xFFDD00FF);
	mCurveColor			= ofRGBA(0xFF9900FF);
	mScopeColor			= ofRGBA(0xFF9900FF);
	mMatrixColor		= ofRGBA(0xFF0000FF);
	
	mDisabledColor		= ofRGBA(0xFFFFFF66);

	loadFonts();
}

//--------------------------------------------------------------
//ofxGuiGlobals::~ofxGuiGlobals()
//{
	// nothing to do ...
	
//}
//--------------------------------------------------------------
void ofxGuiGlobals::buildFromXml()
{
	int numberOfTags = mXml.getNumTags("STYLE");

	if(numberOfTags != 1)
		return;

	mXml.pushTag("STYLE", 0);

	mHeadFontName		= mXml.getValue("HEADFONT", "verdana.ttf");
	mHeadFontSize		= mXml.getValue("HEADSIZE", 10);
	mHeadFontXOffset	= mXml.getValue("HEADXOFF", -2);
	mHeadFontYOffset	= mXml.getValue("HEADYOFF", 8);
	mHeadFontHeight		= mXml.getValue("HEADHEIGHT", 12);

	mParamFontName		= mXml.getValue("PARAMFONT", "automat.ttf");
	mParamFontSize		= mXml.getValue("PARAMSIZE", 6);
	mParamFontXOffset	= mXml.getValue("PARAMXOFF", -2);
	mParamFontYOffset	= mXml.getValue("PARAMYOFF", 6);
	mParamFontHeight	= mXml.getValue("PARAMHEIGHT", 12);

	mButtonXText		= mXml.getValue("BUTTONXTEXT", 4);
	mButtonYText		= mXml.getValue("BUTTONYTEXT", 0);

	mFilesXText			= mXml.getValue("FILESXTEXT", 3);
	mFilesYText			= mXml.getValue("FILESYTEXT", 3);

	mPointSize			= mXml.getValue("POINTSIZE", 6);

	mKnobSize			= mXml.getValue("KNOBSIZE", 10);

	mCoverColor			= ofRGBA(mXml.getValue("COVERCOLOR",	"00000088"));
	mTextColor			= ofRGBA(mXml.getValue("TEXTCOLOR",		"FFFFFFFF"));
	mBorderColor		= ofRGBA(mXml.getValue("BORDERCOLOR",	"FFFFFFFF"));
	mFrameColor			= ofRGBA(mXml.getValue("FRAMECOLOR",	"FFFFFFFF"));
	mSliderColor		= ofRGBA(mXml.getValue("SLIDERCOLOR",	"0099FFFF"));
	mAxisColor			= ofRGBA(mXml.getValue("AXISCOLOR",		"00FF00FF"));
	mHandleColor		= ofRGBA(mXml.getValue("HANDLECOLOR",	"FFFFFFFF"));
	mButtonColor		= ofRGBA(mXml.getValue("BUTTONCOLOR",	"FFDD00FF"));
	mCurveColor			= ofRGBA(mXml.getValue("CURVECOLOR",	"FF9900FF"));
	mScopeColor			= ofRGBA(mXml.getValue("SCOPECOLOR",	"FF9900FF"));
	mMatrixColor		= ofRGBA(mXml.getValue("ACTIVECOLOR",	"FF0000FF"));

	mDisabledColor		= ofRGBA(mXml.getValue("DISABLEDCOLOR",	"C0C0C0FF"));

	
	mXml.popTag();

	loadFonts();
}

//--------------------------------------------------------------
void ofxGuiGlobals::saveToXml()
{
	int id = mXml.addTag("STYLE");

	mXml.setValue("STYLE:HEADFONT",		mHeadFontName, id);
	mXml.setValue("STYLE:HEADSIZE",		mHeadFontSize, id);
	mXml.setValue("STYLE:HEADXOFF",		mHeadFontXOffset, id);
	mXml.setValue("STYLE:HEADYOFF",		mHeadFontYOffset, id);
	mXml.setValue("STYLE:HEADHEIGHT",	mHeadFontHeight, id);

	mXml.setValue("STYLE:PARAMFONT",	mParamFontName, id);
	mXml.setValue("STYLE:PARAMSIZE",	mParamFontSize, id);
	mXml.setValue("STYLE:PARAMXOFF",	mParamFontXOffset, id);
	mXml.setValue("STYLE:PARAMYOFF",	mParamFontYOffset, id);
	mXml.setValue("STYLE:PARAMHEIGHT",	mParamFontHeight, id);

	mXml.setValue("STYLE:BUTTONXTEXT",	mButtonXText, id);
	mXml.setValue("STYLE:BUTTONYTEXT",	mButtonYText, id);

	mXml.setValue("STYLE:FILESXTEXT",	mFilesXText, id);
	mXml.setValue("STYLE:FILESYTEXT",	mFilesYText, id);

	mXml.setValue("STYLE:POINTSIZE",	mPointSize, id);

	mXml.setValue("STYLE:KNOBSIZE",		mKnobSize, id);

	mXml.setValue("STYLE:COVERCOLOR",	mCoverColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:TEXTCOLOR",	mTextColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:BORDERCOLOR",	mBorderColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:FRAMECOLOR",	mFrameColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:SLIDERCOLOR",	mSliderColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:AXISCOLOR",	mAxisColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:HANDLECOLOR",	mHandleColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:BUTTONCOLOR",	mButtonColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:CURVECOLOR",	mCurveColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:SCOPECOLOR",	mScopeColor.toString(kofxGui_Color_RGBA), id);
	mXml.setValue("STYLE:ACTIVECOLOR",	mMatrixColor.toString(kofxGui_Color_RGBA), id);
	
	mXml.setValue("STYLE:DISABLEDCOLOR",	mDisabledColor.toString(kofxGui_Color_RGBA), id);

}

//--------------------------------------------------------------
void ofxGuiGlobals::loadFonts()
{
	mHeadFont.loadFont(mHeadFontName, mHeadFontSize, true, true);
	
	//cout << mParamFontSize << endl;
	//cout << mParamFontName << endl;

	
	mParamFont.loadFont(mParamFontName, mParamFontSize, true, true);
}

//--------------------------------------------------------------

