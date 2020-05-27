//
//  PlaylistManager.cpp
//  CMl-Project
//
//  Created by User on 26/05/2020.
//

#include "PlaylistManager.h"


PlaylistManager::PlaylistManager(){
    
}

vector<MediaGUI*> PlaylistManager::getPlaylist(string tag){
    if ( playlists.find(tag) == playlists.end() ) {
        return {};
    }
    return playlists[tag];
    
}

void PlaylistManager::addToPlaylist(string tag, MediaGUI* media){
    
    if ( playlists.find(tag) == playlists.end() ) {
        playlists.insert( pair<string, MediasVector>(tag, {}) );
    }
    playlists[tag].push_back(media);
    
}
