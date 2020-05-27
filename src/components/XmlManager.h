#pragma once

#ifndef XMLutils_h
#define XMLutils_h

#include "ofxXmlSettings.h"
#include "Metadata.h"
#endif /* XMLutils_hpp */

class XmlManager {
	ofxXmlSettings XML;
	int nrImages;
	int nrVideos;

	string xmlFileName;
    
    static XmlManager *instance;
   
    
    XmlManager(string filename);

public: 
	
    static XmlManager *getInstance();
    
	void createMedia(string mediaName, bool isImage);

	map <string, string> getMetadataMap(string mediaName, bool isImage);

	Metadata* getMetadata(string mediaName, bool isImage);

	list <string> getTagsList(string mediaName, bool isImage);

	int getNrImages() {
		return this->nrImages;
	}

	int getNrVideos() {
		return this->nrVideos;
	}

	bool setMetadata(string mediaName, bool isImage, string tag, string value);

	bool setMetadata(string mediaName, bool isImage, Metadata metadata);

	bool setTags(string mediaName, bool isImage, vector <string> tags);

	bool exists(string mediaName, bool isImage);

private:
	/*
		If it finds the media with given filename, pushes the stack to it and returns true
		Otherwise returns false
	*/
	bool findMedia(string mediaName, bool isImage);
};


