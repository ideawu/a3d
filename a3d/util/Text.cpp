//  Created by ideawu on 03/02/2018.
//  Copyright © 2018 ideawu. All rights reserved.
//

#include "Text.h"
#include <CoreText/CoreText.h>

static void sizeForAttributedString(CFAttributedStringRef attrString, int maxWidth, int maxHeight, int *outWidth, int *outHeight);

namespace a3d{
	static CFStringEncoding charset = kCFStringEncodingUTF8;
	
	Text::Text(){
		_fontName = "Helvetica";
		_fontSize = 40;
		_fontColor = Color::white();
		_maxWidth = 10000;
		_maxHeight = _maxWidth;
	}
	
	Text::Text(const char *text):Text(){
		this->text(text);
	}

	Text::~Text(){
	}

	void Text::maxWidth(int maxWidth){
		_maxWidth = maxWidth;
	}
	
	void Text::maxHeight(int maxHeight){
		_maxHeight = maxHeight;
	}

	void Text::font(const char *name, float size){
		_fontName = name;
		_fontSize = size;
	}

	void Text::fontSize(float size){
		_fontSize = size;
	}

	void Text::fontColor(const Color &color){
		_fontColor = color;
	}

	void Text::text(const char *text){
		_text = text;
	}
	
	void* Text::createAttributedString(){
		CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();
		CGFloat rgba[] = {_fontColor.r, _fontColor.g, _fontColor.b, _fontColor.a};
		CGColorRef color = CGColorCreate(rgbColorSpace, rgba);
		CGColorSpaceRelease(rgbColorSpace);

		CFStringRef fontFamily = CFStringCreateWithCStringNoCopy(NULL, _fontName.c_str(), charset, kCFAllocatorNull);
		CTFontRef font = CTFontCreateWithName(fontFamily, _fontSize, nil);
		CFStringRef keys[] = {kCTFontAttributeName, kCTForegroundColorAttributeName};
		CFTypeRef values[] = {font, color};
		CFDictionaryRef attrs = CFDictionaryCreate(
												   kCFAllocatorDefault, (const void**)&keys,
												   (const void**)&values, sizeof(keys) / sizeof(keys[0]),
												   &kCFTypeDictionaryKeyCallBacks,
												   &kCFTypeDictionaryValueCallBacks);
		CFStringRef string = CFStringCreateWithCStringNoCopy(NULL, _text.c_str(), charset, kCFAllocatorNull);
		CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attrs);
		CFRelease(fontFamily);
		CFRelease(font);
		CFRelease(attrs);
		CFRelease(string);
		return (void*)attrString;
	}
	
	void Text::calculateSize(int *width, int *height){
		CFAttributedStringRef attrString = (CFAttributedStringRef)createAttributedString();
		sizeForAttributedString(attrString, _maxWidth, _maxHeight, width, height);
		CFRelease(attrString);
	}

	Bitmap* Text::drawToBitmap(){
		int w = 0;
		int h = 0;
		
		CFAttributedStringRef attrString = (CFAttributedStringRef)createAttributedString();
		sizeForAttributedString(attrString, _maxWidth, _maxHeight, &w, &h);
		if(w == 0 || h == 0){
			CFRelease(attrString);
			return NULL;
		}
//		log_debug("%d %d", w, h);
		
		Bitmap *bitmap = Bitmap::create(w, h);
		CGContextRef context = bitmap->CGContext();
		{
			CGMutablePathRef path = CGPathCreateMutable();
			CGRect bounds = CGRectMake(0, 0, w, h);
			CGPathAddRect(path, NULL, bounds);
			CTFramesetterRef framesetter = CTFramesetterCreateWithAttributedString(attrString);
			CTFrameRef frame = CTFramesetterCreateFrame(framesetter, CFRangeMake(0, 0), path, NULL);
			
			CGContextClearRect(context, bounds);
			CTFrameDraw(frame, context);
			
			CFRelease(frame);
			CFRelease(path);
			CFRelease(framesetter);
		}
		CFRelease(attrString);
		
		return bitmap;
	}

}; // end namespace


static void sizeForAttributedString(CFAttributedStringRef attrString, int maxWidth, int maxHeight, int *outWidth, int *outHeight){
	CGMutablePathRef path = CGPathCreateMutable();
	CGRect bounds = CGRectMake(0, 0, maxWidth, maxHeight);
	CGPathAddRect(path, NULL, bounds);
	CTFramesetterRef framesetter = CTFramesetterCreateWithAttributedString(attrString);
	CTFrameRef frame = CTFramesetterCreateFrame(framesetter, CFRangeMake(0, 0), path, NULL);
	
	CFArrayRef lineArray = CTFrameGetLines(frame);
	CFIndex lineCount = CFArrayGetCount(lineArray);
	double width = 0;
	double height = 0;
	
	for(CFIndex i=0; i<lineCount; i++){
		CTLineRef line = (CTLineRef)CFArrayGetValueAtIndex(lineArray, i);
		CGFloat ascent, descent, leading;
		CGPoint origin;
		CTFrameGetLineOrigins(frame, CFRangeMake(i, 1), &origin);
		double w = CTLineGetTypographicBounds(line, &ascent, &descent, &leading);
//		double h = ascent + descent + leading;
//		log_debug("%.2f %.2f %.2f, %.2f %.2f", ascent, descent, leading, w, h);
		width = fmax(width, w);
		if(i == lineCount - 1){
			CGPoint origin;
			CTFrameGetLineOrigins(frame, CFRangeMake(i, 1), &origin);
			height = maxHeight - origin.y + descent;
		}
	}
	CFRelease(frame);
	CFRelease(path);
	CFRelease(framesetter);
	
	size_t w = ceil(width);
	size_t h = ceil(height);
	
	if(outWidth){
		*outWidth = (int)w;
	}
	if(outHeight){
		*outHeight = (int)h;
	}
}
