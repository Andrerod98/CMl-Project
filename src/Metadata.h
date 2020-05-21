//
//  Metadata.h
//  CMl-Project
//
//  Created by User on 21/05/2020.
//

#ifndef Metadata_h
#define Metadata_h



class Metadata{
    
    vector<string> tags;
    float luminance;
    float edgeDistribution;
    float rhythm;
    float texture;
    float audioAmplitude;
    int nFaces;
    int nObject;
    ofColor color;
    
public:
    
    Metadata(vector<string> tags,
             float luminance,
             float edgeDistribution,
             float rhythm,
             float texture,
             float audioAmplitude,
             int nFaces,
             int nObject,
             ofColor color){
        
        this.tags = tags;
        this.luminance=luminance;
        this.edgeDistribution=edgeDistribution;
        this.rhythm=rhythm;
        this.texture=texture;
        this.audioAmplitude=audioAmplitude;
        this.nFaces=nFaces;
        this.nObject=nObject;
        this.color = color;
    };
    
    vector<string> getTags(){
        return tags;
    };
    
    float getLuminanceValue(){
        return luminance;
    };
    
    int getFacesNumber(){
        return nFaces;
    };
    
    float getEdgeDistribution(){
        return edgeDistribution;
    };
    
    float getRhythmValue(){
        return rythm;
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


}

#endif /* Metadata_h */
