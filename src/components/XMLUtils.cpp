#include "XMLutils.h"

XMLutils::XMLutils(string filename){
	this->XML.loadFile(filename);
	if (XML.tagExists("metadata")) {
		this->nrImages = XML.getNumTags("image");
		this->nrVideos = XML.getNumTags("video");
		XML.pushTag("metadata");
	}
	else {
		this->nrImages = 0;
		this->nrVideos = 0;
		XML.addTag("metadata");
		XML.pushTag("metadata");
	}
}

map <string, string> XMLutils::getMetadata(string mediaName, bool isImage) {
	string name;
	map <string, string> result;

	if (isImage) {
		if (nrImages > 0) {
			if (findMedia(mediaName, true)) {
				result.insert(pair<string, string>("luminance", XML.getValue("luminance", "luminance")));
				result.insert(pair<string, string>("color", XML.getValue("color", "color")));
				result.insert(pair<string, string>("nrFaces", XML.getValue("nrFaces", "nrFaces")));
				result.insert(pair<string, string>("edgeDistribution", XML.getValue("edgeDistribution", "edgeDistribution")));
				result.insert(pair<string, string>("textureCaracteristics", XML.getValue("textureCaracteristics", "textureCaracteristics")));
				result.insert(pair<string, string>("nrTimes", XML.getValue("nrTimes", "nrTimes")));
				XML.popTag();
				return result;
			}
		}
	}
	else {
		if (nrVideos > 0) {
			if (findMedia(mediaName, false)) {
				result.insert(pair<string, string>("luminance", XML.getValue("luminance", "luminance")));
				result.insert(pair<string, string>("color", XML.getValue("color", "color")));
				result.insert(pair<string, string>("nrFaces", XML.getValue("nrFaces", "nrFaces")));
				result.insert(pair<string, string>("edgeDistribution", XML.getValue("edgeDistribution", "edgeDistribution")));
				result.insert(pair<string, string>("textureCaracteristics", XML.getValue("textureCaracteristics", "textureCaracteristics")));
				result.insert(pair<string, string>("nrTimes", XML.getValue("nrTimes", "nrTimes")));
				result.insert(pair<string, string>("nrTimes", XML.getValue("rhythm", "rhythm")));
				XML.popTag();
				return result;
			}
		}
	}

	return result;
}

list <string> XMLutils::getTags(string mediaName, bool isImage) {
	list <string> result;
	
	if (findMedia(mediaName, isImage)) {
		XML.pushTag("tags");
		int nrTags = XML.getNumTags("tag");

		for (int i = 0; i < nrTags; i++) {
			result.push_back(XML.getValue("tag", "tag"));
		}
	}
	return result;
}

bool XMLutils::findMedia(string filename, bool isImage) {
	string name;
	if (isImage) {
		if (nrImages > 0) {
			for (int i = 0; i < nrImages; i++) {
				name = XML.getValue("image:filename", "null");
				if (name == filename) {
					XML.pushTag("image");
					return true;
				}
			}
		}
	}
	else {
		if (nrVideos > 0) {
			for (int i = 0; i < nrVideos; i++) {
				name = XML.getValue("video:filename", "null");
				if (name == filename) {
					XML.pushTag("video");
					return true;
				}
			}
		}
	}
	return false;
}