#include "XMLutils.h"
#include <fstream>

XMLutils::XMLutils(string filename){

	if (this->XML.loadFile(filename))
		cout << "XML File: " << filename << " loaded sucefuly!" << endl;
	else {
		XML.addTag("metadata");
		XML.saveFile(filename);
		if (XML.loadFile(filename))
			cout << "XML File: " << filename << " loaded sucefuly!" << endl;
		else
			cout << "XML File: " << filename << " was not loaded!" << endl;
	}

	
	if (XML.tagExists("metadata")) {
		XML.pushTag("metadata");
		this->nrImages = XML.getNumTags("image");
		this->nrVideos = XML.getNumTags("video");		
		cout << "Previous xml loaded with iamges: " << nrImages << " and videos: " << nrVideos << endl;
	}
	else {
		this->nrImages = 0;
		this->nrVideos = 0;
		XML.addTag("metadata");
		XML.pushTag("metadata");
		cout << "Blank xml file created!" << endl;
	}

	this->xmlFileName = filename;
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
		XML.popTag(); // out of tags
		XML.popTag(); // out of media
	}
	return result;
}

bool XMLutils::setMetadata(string mediaName, bool isImage, string tag, string value) {

	if (findMedia(mediaName, isImage)) {
		if (XML.getNumTags(tag) == 0) {
			XML.addValue(tag, value);
		}
		else {
			XML.setValue(tag, value, 0);
		}
		XML.save(xmlFileName);
		XML.popTag();
		return true;
	}

	return false;
}

bool XMLutils::setTags(string mediaName, bool isImage, list<string> tags) {
	if (findMedia(mediaName, isImage)) {
		if (XML.getNumTags("tags") == 0) {
			XML.addTag("tags");
			XML.pushTag("tags");
			for (string i : tags) {
				XML.addValue("tag", i);
			}
			XML.popTag();
		}
		else {
			XML.clearTagContents("tags");
			XML.pushTag("tags");
			for (string i : tags) {
				XML.addValue("tag", i);
			}
			XML.popTag();
		}
		XML.popTag();
		XML.save(xmlFileName);
		return true;
	}	
	return false;
}

bool XMLutils::exists(string filename, bool isImage) {
	string name;
	if (isImage) {
		if (nrImages > 0) {
			for (int i = 0; i < nrImages; i++) {
				name = XML.getValue("image:filename", "null", i);
				if (name == filename) {
					return true;
				}
			}
		}
	}
	else {
		if (nrVideos > 0) {
			for (int i = 0; i < nrVideos; i++) {
				name = XML.getValue("video:filename", "null", i);
				if (name == filename) {
					return true;
				}
			}
		}
	}

	return false;
}

bool XMLutils::findMedia(string filename, bool isImage) {
	string name;
	if (isImage) {
		if (nrImages > 0) {
			for (int i = 0; i < nrImages; i++) {
				name = XML.getValue("image:filename", "null", i);
				if (name == filename) {
					cout << "currently at media: " << name << endl;
					XML.pushTag("image", i);
					return true;
				}
			}
		}
	}
	else {
		if (nrVideos > 0) {
			for (int i = 0; i < nrVideos; i++) {
				name = XML.getValue("video:filename", "null", i);
				if (name == filename) {
					XML.pushTag("video", i);
					return true;
				}
			}
		}
	}
	cout << "currently at FALSE media: " << name << endl;
	return false;
}

void XMLutils::createMedia(string mediaName, bool isImage) {
	if (!exists(mediaName, isImage)) {
		if (isImage) {
			XML.addValue("image:filename", mediaName);
			this->nrImages++;
		}
		else {
			XML.addValue("video:filename", mediaName);
			this->nrVideos++;
		}
		XML.save(xmlFileName);
	}
}