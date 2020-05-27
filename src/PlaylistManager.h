//
//  PlaylistManager.hpp
//  CMl-Project
//
//  Created by User on 26/05/2020.
//

#ifndef PlaylistManager_h
#define PlaylistManager_h

#include <stdio.h>
#include <Media.h>
typedef std::vector<MediaGUI*> MediasVector;
class PlaylistManager{
    map<string, MediasVector> playlists;
   
    
public:
    PlaylistManager();
    
    MediasVector getPlaylist(string tag);
    void addToPlaylist(string tag, MediaGUI* media);
};
#endif /* PlaylistManager_hpp */
