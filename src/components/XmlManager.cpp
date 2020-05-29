#include "XmlManager.h"
#include <fstream>

XmlManager::XmlManager(string filename) {
    
	if (this->XML.loadFile(filename))
		cout << "XML File: " << filename << " loaded sucefuly!" << endl;
	else {
		XML.addTag("metadata");
		XML.saveFile(filename);
		if (XML.loadFile(filename))
			cout << "XML Created File: " << filename << " loaded sucefuly!" << endl;
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

XmlManager* XmlManager::getInstance() {
    if (!instance)
        instance = new XmlManager("metadata.xml");
    return instance;
}

map <string, string> XmlManager::getMetadataMap(string mediaName, bool isImage) {
	map <string, string> result;
	string tags[7] = { "luminance", "color", "nrFaces", "edgeDistribution", "textureCaracteristics", "nrTimes", "rhythm" };

	if (isImage) {
		if (nrImages > 0) {
			if (findMedia(mediaName, true)) {
				for (int i = 0; i < 6; i++) {
					if (XML.tagExists(tags[i])) {
						result.insert(pair<string, string>(tags[i], XML.getValue(tags[i], tags[i])));
					}
				}
				XML.popTag();
				return result;
			}
		}
	}
	else {
		if (nrVideos > 0) {
			if (findMedia(mediaName, false)) {
				for (int i = 0; i < 7; i++) {
					if (XML.tagExists(tags[i])) {
						result.insert(pair<string, string>(tags[i], XML.getValue(tags[i], tags[i])));
					}
				}
				XML.popTag();
				return result;
			}
		}
	}

	return result;
}

Metadata* XmlManager::getMetadata(string mediaName, bool isImage) {
	vector<std::string> tags = {};
	float luminance = 0.0;
	vector<int> edgeDistribution = {};
	float rhythm = 0.0;
	float texture = 0.0;
	float audioAmplitude = 0.0;
	int nFaces = 0;
	int nObject = 0;
	ofColor color = ofColor(0,0,0);

	if (findMedia(mediaName, isImage)) {
        /*
		XML.pushTag("tags");
		const int nrTags = XML.getNumTags("tag");
		for (int i = 0; i < nrTags; i++)
			tags.insert(tags.begin() + i, XML.getValue("tag", "tag", i));
		XML.popTag(); // out of tags

		XML.pushTag("edges");
		edgeDistribution.insert(edgeDistribution.begin(), XML.getValue("vertical", 1));
		edgeDistribution.insert(edgeDistribution.begin()+1, XML.getValue("horizontal", 1));
		edgeDistribution.insert(edgeDistribution.begin()+2, XML.getValue("d45", 1));
		edgeDistribution.insert(edgeDistribution.begin()+3, XML.getValue("d135", 1));
		edgeDistribution.insert(edgeDistribution.begin()+4, XML.getValue("nonDirectional", 1));
		XML.popTag(); // out of edges
*/
		luminance = (float) XML.getValue("luminance", -1.0);
		rhythm = (float)XML.getValue("rhythm", -1.0);
		texture = (float)XML.getValue("texture", -1.0);
		audioAmplitude = (float)XML.getValue("audioAmplitude", -1.0);
		nFaces = (int)XML.getValue("nFaces", -1);
		nObject = (int)XML.getValue("nObject", -1);
		color = ofColor(XML.getValue("color:red", 0), XML.getValue("color:green", 0), XML.getValue("color:blue", 0));

		XML.popTag(); // out of media
	}

	return new Metadata(tags, luminance, edgeDistribution, rhythm, texture, audioAmplitude, nFaces, nObject, color);
}

list <string> XmlManager::getTagsList(string mediaName, bool isImage) {
	list <string> result;
	
	if (findMedia(mediaName, isImage)) {
		XML.pushTag("tags");
		int nrTags = XML.getNumTags("tag");

		for (int i = 0; i < nrTags; i++) {
			result.push_back(XML.getValue("tag", "tag", i));
		}
		XML.popTag(); // out of tags
		XML.popTag(); // out of media
	}
	return result;
}

bool XmlManager::setMetadata(string mediaName, bool isImage, string tag, string value) {

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

bool XmlManager::setMetadata(string mediaName, bool isImage, Metadata metadata) {
	if (findMedia(mediaName, isImage)) {
		XML.removeTag("tags"); // removes previous content
		XML.addTag("tags");
		XML.pushTag("tags");
		vector<std::string> tags = metadata.getTags();
		for (int i = 0; i < tags.size(); i++) {
			XML.addValue("tag", tags[i]);
		}
		XML.popTag(); // out of tags
 
        
		XML.removeTag("edges");
		XML.addTag("edges");
		XML.pushTag("edges");
		vector<int> edges = metadata.getEdgeDistribution();
		XML.addValue("vertical",edges[0]);
		XML.addValue("horizontal", edges[1]);
		XML.addValue("d45", edges[2]);
		XML.addValue("d135", edges[3]);
		XML.addValue("nonDirectional", edges[4]);
		XML.popTag(); // out of edges

		XML.addValue("luminance", metadata.getLuminanceValue());
		XML.addValue("rhythm", metadata.getRhythmValue());
		XML.addValue("texture", metadata.getTextureValue());
		XML.addValue("audioAmplitude", metadata.getAudioAmplitude());
		XML.addValue("nFaces", metadata.getFacesNumber());
		XML.addValue("nObject", metadata.getObjectNumber());
        
        
		ofColor color = metadata.getColorValue();
        XML.addTag("color");
        XML.pushTag("color");
		XML.addValue("red", color.r);
		XML.addValue("green", color.g);
		XML.addValue("blue", color.b);
        XML.popTag();
		XML.popTag();
		return true;
	}
	return false;
}

bool XmlManager::setTags(string mediaName, bool isImage, vector<string> tags) {
    cout << mediaName;
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
		XML.saveFile(xmlFileName);
		return true;
	}	
	return false;
}

bool XmlManager::exists(string filename, bool isImage) {
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

bool XmlManager::findMedia(string filename, bool isImage) {
	string name;
	if (isImage) {
		if (this->nrImages > 0) {
			for (int i = 0; i < nrImages; i++) {
				name = XML.getValue("image:filename", "null", i);
				if (name == filename) {
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
	return false;
}

void XmlManager::createMedia(string mediaName, bool isImage) {
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
