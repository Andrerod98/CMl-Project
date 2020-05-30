//
//  Metadata.h
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#ifndef Metadata_h
#define Metadata_h
#include "ofMain.h"


class Metadata{
    
    vector<std::string> tags;
    float luminance;
    vector<int> edgeDistribution;
    float rhythm;
    float texture;
    float audioAmplitude;
    int nFaces;
    int nObject;
    ofColor color;
	string thumbPath;
    
public:
    
    Metadata(vector<string> tags,
             float luminance,
             vector<int> edgeDistribution,
             float rhythm,
             float texture,
             float audioAmplitude,
             int nFaces,
             int nObject,
             ofColor color){
        
        this->tags = tags;
        this->luminance=luminance;
        this->edgeDistribution=edgeDistribution;
        this->rhythm=rhythm;
        this->texture=texture;
        this->audioAmplitude=audioAmplitude;
        this->nFaces=nFaces;
        this->nObject=nObject;
        this->color = color;
    };

	Metadata(vector<string> tags,
		float luminance,
		vector<int> edgeDistribution,
		float rhythm,
		float texture,
		float audioAmplitude,
		int nFaces,
		int nObject,
		ofColor color,
		string thumbnailsPath) {

		this->tags = tags;
		this->luminance = luminance;
		this->edgeDistribution = edgeDistribution;
		this->rhythm = rhythm;
		this->texture = texture;
		this->audioAmplitude = audioAmplitude;
		this->nFaces = nFaces;
		this->nObject = nObject;
		this->color = color;
		this->thumbPath = thumbnailsPath;
	};

	Metadata(float luminance,
		vector<int> edgeDistribution,
		float rhythm,
		float texture,
		float audioAmplitude,
		int nrFaces,
		int nrObjects,
		ofColor color) {

		this->luminance = luminance;
		this->edgeDistribution = edgeDistribution;
		this->rhythm = rhythm;
		this->texture = texture;
		this->audioAmplitude = audioAmplitude;
		this->nFaces = nrFaces;
		this->nObject = nrObjects;
		this->color = color;
	}

	vector<string> getTags(){
        return tags;
    };
    
    string getTagsString(){
        string fullS = "";
        for(string s : tags){
            fullS = fullS + s;
        }
        
        return fullS;
    }

	void setTags(vector<string> tags) {
		this->tags = tags;
	}
    
    float getLuminanceValue(){
        return luminance;
    };
    
    int getFacesNumber(){
        return nFaces;
    };
    
    vector<int> getEdgeDistribution(){
        return edgeDistribution;
    };
    
    float getRhythmValue(){
        return rhythm;
    }
    
    float getTextureValue(){
        return texture;
    };
    
    ofColor getColorValue(){
        return color;
    };

    int getObjectNumber(){
        return nObject;
    };
    
    float getAudioAmplitude(){
        return audioAmplitude;
    };

	string getThumbPath() {
		return thumbPath;
	}
};

#endif /* Metadata_h */
