#ifndef Media_h
#define Media_h


class Media{
     bool isImg;
     string filename;
    ofImage* image;
    ofVideoPlayer* video;
    
public:
    Media(string filename, ofVideoPlayer* video){
        this->filename = filename;
        this->isImg = false;
        this->video = video;
    };
    
    Media(string filename, ofImage* image){
        this->filename = filename;
        this->isImg = true;
        this->image = image;
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
};

class MediaGUI : public Media{

    ofVec2f position;
    
    int width;
    int height;

public:
    MediaGUI(ofVideoPlayer* video, string filename):Media(filename, video){
    };
    
    MediaGUI(ofImage* image, string filename):Media(filename, image){
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
