#ifndef Media_h
#define Media_h
#include "Metadata.h"

class Media{
    bool isImg;
    string filename;
    ofImage* image;
    ofVideoPlayer* video;
    Metadata* metadata;
    
public:
    Media(string filename, ofVideoPlayer* video, Metadata* metadata){
        this->filename = filename;
        this->isImg = false;
        this->video = video;
        this->metadata = metadata;
    };
    
    Media(string filename, ofImage* image, Metadata* metadata){
        this->filename = filename;
        this->isImg = true;
        this->image = image;
        this->metadata = metadata;
    };
    
    string getFileName(){
        return filename;
    }
    
    bool isVideo(){
        return isImg == false;
    };
    
    bool isImage(){
        return isImg;
    }
    
    ofVideoPlayer* getVideo(){
        return video;
    };
    
    ofImage* getImage(){
        return image;
    };
    
    Metadata* getMetadata(){
        return metadata;
    }
};

class MediaGUI : public Media{

    ofVec2f position;
    
    int width;
    int height;

public:
    MediaGUI(ofVideoPlayer* video, string filename, Metadata* metadata):Media(filename, video, metadata){
    };
    
    MediaGUI(ofImage* image, string filename, Metadata* metadata):Media(filename, image, metadata){
    };
    
    void setPosition(ofVec2f pos){
        position = pos;
    }
    
    ofVec2f getPosition(){
        return position;
    }
    
    void setSize(int w, int h){
        width = w;
        height = h;
    }
    
    bool inside(int x, int y){
        return position.x < x && position.x + width > x && position.y < y && position.y + height > y;
    }
    
    
};
#endif /* Media_h */
