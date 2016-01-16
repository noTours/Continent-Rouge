#include "VHPtrueTypeFont.h"

//constructor

//----------------------------------------------------------------
VHPtrueTypeFont::VHPtrueTypeFont() { 
    paragraph_w = 0;
}

// methods

//----------------------------------------------------------------

void VHPtrueTypeFont::setParagraphWidth(float _w) {
    paragraph_w = _w;
}


void VHPtrueTypeFont::drawSpecialString(string c, float x, float y) {
    
    if (!bLoadedOk){
    	ofLog(OF_LOG_ERROR,"ofTrueTypeFont::drawString - Error : font not allocated -- line %d in %s", __LINE__,__FILE__);
    	return;
    };
    
	GLint		index	= 0;
	GLfloat		X		= x;
	GLfloat		Y		= y;
    
    
	bool alreadyBinded = binded;
    
	if(!alreadyBinded) bind();
    
	int len = (int)c.length();
    
	while(index < len){
		int cy = (unsigned char)c[index] - NUM_CHARACTER_TO_START;
        
		if (cy < nCharacters){ 			// full char set or not?
            if (c[index] == '{') {
                //int next = index + 1;
                int n;
                if (c[index+2] == '}') {
                    n = ofToInt(ofToString(c[index+1]));
                    index+=2;
                } else if (c[index+3] == '}') {
                    n = ofToInt(ofToString(c[index+1]) +""+ ofToString(c[index+2]));
                    index+=3;
                } else if (c[index+4] == '}') {
                    n = ofToInt(ofToString(c[index+1]) +""+ ofToString(c[index+2]) +""+ ofToString(c[index+3]));
                    index+=4;
                }
                drawChar(n, X, Y);
                X += cps[n].setWidth * letterSpacing;
                /*
                switch (c[next]) {
                    case 'a':
                        drawChar(192, X, Y);
                        X += cps[192].setWidth * letterSpacing;
                        break;
                    case 'e':
                        drawChar(200, X, Y);
                        X += cps[200].setWidth * letterSpacing;
                        break;
                    case 'i':
                        drawChar(204, X, Y);
                        X += cps[204].setWidth * letterSpacing;
                        break;
                    case 'o':
                        drawChar(210, X, Y);
                        X += cps[210].setWidth * letterSpacing;
                        break;
                    case 'u':
                        drawChar(217, X, Y);
                        X += cps[217].setWidth * letterSpacing;
                        break;
                    case 'A':
                        drawChar(160, X, Y);
                        X += cps[160].setWidth * letterSpacing;
                        break;
                    case 'E':
                        drawChar(168, X, Y);
                        X += cps[168].setWidth * letterSpacing;
                        break;
                    case 'I':
                        drawChar(173, X, Y);
                        X += cps[173].setWidth * letterSpacing;
                        break;
                    case 'O':
                        drawChar(178, X, Y);
                        X += cps[178].setWidth * letterSpacing;
                        break;
                    case 'U':
                        drawChar(185, X, Y);
                        X += cps[185].setWidth * letterSpacing;
                        break;
                    case 'n':
                        drawChar(208, X, Y);
                        X += cps[208].setWidth * letterSpacing;
                        break;
                    case 'N':
                        drawChar(176, X, Y);
                        X += cps[176].setWidth * letterSpacing;
                        break;
                    case '{':
                        drawChar(90, X, Y);
                        X += cps[90].setWidth * letterSpacing;
                        break;
                    default:
                        break;
                }
                index+=2;
                 */
            } else if (c[index] == '\n') {
                Y += lineHeight;
				X = x ; //reset X Pos back to zero
            }else if (c[index] == ' ') {
                if ((paragraph_w>0.0)&&(X>=paragraph_w)) {
                    //ofLog(OF_LOG_VERBOSE, "x = %f, w = %f", X, paragraph_w);
                    Y += lineHeight;
                    X = x ; //reset X Pos back to zero
                } else {
                    int cy = (int)'p' - NUM_CHARACTER_TO_START;
                    X += cps[cy].width * letterSpacing * spaceSize;
                }
            } else {
				drawChar(cy, X, Y);
				X += cps[cy].setWidth * letterSpacing;
            }
            
		}
		index++;
	}
    
	if(!alreadyBinded) unbind();
    
}

//----------------------------------------------------------------
void VHPtrueTypeFont::drawAllCharecters(float x, float y) {
    bool alreadyBinded = binded;
    if(!alreadyBinded) bind();
    float X = x;
    float Y = y;
    for (int u=0; u<40; u++) {
        for (int i=u*10; i<(u+1)*10; i++) {
            if (i<=nCharacters) {
                X += cps[50].width * letterSpacing * spaceSize * 2;
                drawChar(i, X, Y);
                //ofLog(OF_LOG_VERBOSE, "drawChar %i", i);
            }
        }
        X = x;
        Y += lineHeight;
    }
    if(!alreadyBinded) unbind();
}

//-----------------------------------------------------------
float VHPtrueTypeFont::stringWidth(string c) {
    ofRectangle rect = getStringBoundingBox(c, 0,0);
    return rect.width;
}
 
ofRectangle VHPtrueTypeFont::getStringBoundingBox(string c, float x, float y) {
 
    ofRectangle myRect;
 
    if (!bLoadedOk){
        ofLog(OF_LOG_ERROR,"ofTrueTypeFont::getStringBoundingBox - font not allocated");
        return myRect;
    }
 
    GLint		index	= 0;
    GLfloat		xoffset	= 0;
    GLfloat		yoffset	= 0;
    int         len     = (int)c.length();
    float       minx    = -1;
    float       miny    = -1;
    float       maxx    = -1;
    float       maxy    = -1;
 
    if ( len < 1 || cps.empty() ){
        myRect.x        = 0;
        myRect.y        = 0;
        myRect.width    = 0;
        myRect.height   = 0;
        return myRect;
    }
 
    bool bFirstCharacter = true;
    while(index < len){
        int cy = (unsigned char)c[index] - NUM_CHARACTER_TO_START;
        if (cy < nCharacters){ 			// full char set or not?
            if (c[index] == '\n') {
                yoffset += lineHeight;
                xoffset = 0 ; //reset X Pos back to zero
            } else if (c[index] == ' ') {
                int cy = (int)'p' - NUM_CHARACTER_TO_START;
                xoffset += cps[cy].width * letterSpacing * spaceSize;
                // zach - this is a bug to fix -- for now, we don't currently deal with ' ' in calculating string bounding box
            } else {
                if (c[index] == '{') {
                    int next = index + 1;
                    switch (c[next]) {
                        case 'a':
                            cy = 92;
                            break;
                        case 'e':
                            cy = 200;
                            break;
                        case 'i':
                            cy = 204;
                            break;
                        case 'o':
                            cy = 210;
                            break;
                        case 'u':
                            cy = 217;
                            break;
                        case 'A':
                            cy = 160;
                            break;
                        case 'E':
                            cy = 168;
                            break;
                        case 'I':
                            cy = 173;
                            break;
                        case 'O':
                            cy = 178;
                            break;
                        case 'U':
                            cy = 185;
                            break;
                        case 'n':
                            cy = 208;
                            break;
                        case 'N':
                            cy = 176;
                            break;
                        case '{':
                            cy = 90;
                            break;
                        default:
                            break;
                    }
                    index+=2;
                }
                GLint height	= cps[cy].height;
                GLint bwidth	= cps[cy].width * letterSpacing;
                GLint top		= cps[cy].topExtent - cps[cy].height;
                GLint lextent	= cps[cy].leftExtent;
                float	x1, y1, x2, y2, corr, stretch;
                stretch = 0;//(float)visibleBorder * 2;
                corr = (float)(((fontSize - height) + top) - fontSize);
                x1		= (x + xoffset + lextent + bwidth + stretch);
                y1		= (y + yoffset + height + corr + stretch);
                x2		= (x + xoffset + lextent);
                y2		= (y + yoffset + -top + corr);
                xoffset += cps[cy].setWidth * letterSpacing;
                if (bFirstCharacter == true){
                    minx = x2;
                    miny = y2;
                    maxx = x1;
                    maxy = y1;
                    bFirstCharacter = false;
                } else {
                    if (x2 < minx) minx = x2;
                    if (y2 < miny) miny = y2;
                    if (x1 > maxx) maxx = x1;
                    if (y1 > maxy) maxy = y1;
                }
            }
        }
        index++;
    }
 
    myRect.x        = minx;
    myRect.y        = miny;
    myRect.width    = maxx-minx;
    myRect.height   = maxy-miny;
    return myRect;
}

//-----------------------------------------------------------