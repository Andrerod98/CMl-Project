#pragma once

#ifndef XMLutils_h
#define XMLutils_h

#include "ofxXmlSettings.h"
#endif /* XMLutils_hpp */

class XMLutils {
	ofxXmlSettings XML;
	int nrImages;
	int nrVideos;

	string xmlFileName;

public: 
	XMLutils(string filename);

	void createMedia(string mediaName, bool isImage);

	map <string, string> getMetadata(string mediaName, bool isImage);

	list <string> getTags(string mediaName, bool isImage);

	int getNrImages() {
		return nrImages;
	}

	int getNrVideos() {
		return nrVideos;
	}

	bool setMetadata(string mediaName, bool isImage, string tag, string value);

	bool setTags(string mediaName, bool isImage, list <string> tags);

	bool exists(string mediaName, bool isImage);

private:
	/*
		If it finds the media with given filename, pushes the stack to it and returns true
		Otherwise returns false
	*/
	bool findMedia(string mediaName, bool isImage);
};

