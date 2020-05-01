#ifndef Media_h
#define Media_h

class Media{
    
    ofImage* image;
    ofVideoPlayer* video;
    
    bool isImg;
    ofVec2f position;
    
    int width;
    int height;
    
    string filename;
public:
    Media(ofVideoPlayer* video, string filename){
        this->video = video;
        this->filename = filename;
        isImg = false;
    };
    
    Media(ofImage* image, string filename){
        this->image = image;
        this->filename = filename;
        isImg = true;
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
