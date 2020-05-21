#ifndef Media_h
#define Media_h


class Media{
     bool isImg;
     string filename;
    
public:
    Media(string filename, bool isImg){
        this->filename = filename;
        this->isImg = isImg;
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
};

class MediaGUI : public Media{
    
    ofImage* image;
    ofVideoPlayer* video;
    
   
    ofVec2f position;
    
    int width;
    int height;
    

    
   
public:
    MediaGUI(ofVideoPlayer* video, string filename):Media(filename, false){
        this->video = video;
    };
    
    MediaGUI(ofImage* image, string filename):Media(filename, true){
        this->image = image;
    };
    
    
    
    ofVideoPlayer* getVideo(){
        return video;
    };
    
    ofImage* getImage(){
        return image;
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
