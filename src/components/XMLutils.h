#pragma once

#ifndef XMLutils_h
#define XMLutils_h

#include "ofxXmlSettings.h"
#endif /* XMLutils_hpp */

class XMLutils {
	ofxXmlSettings XML;
	int nrImages;
	int nrVideos;

public: 
	XMLutils(string filename);

	map <string, string> getMetadata(string mediaName, bool isImage);

	list <string> getTags(string mediaName, bool isImage);

	int getNrImages() {
		return nrImages;
	}

	int getNrVideos() {
		return nrVideos;
	}

private:
	/*
		If it finds the media with given filename, pushes the stack to it and returns true
		Otherwise returns false
	*/
	bool findMedia(string mediaName, bool isImage);
};

