#include <libspotify/api.h>
#include <stdio.h>
#include <stdlib.h>
#include "playlist.h"
#include "play.h"
#include "debug.h"

//static sp_playlistcontainer_callbacks pc_callbacks;
sp_playlist *current_playlist;
int playlist_tracks, playlist_index;
extern sp_session *g_session; 

int print_playlists(sp_session *g_session, sp_playlistcontainer* pc) 
{
    printf("\n-- Print playlists --\n");
    sp_playlist *playlist;
    int i; //for the for loop;

    for(i = 0; i < sp_playlistcontainer_num_playlists(pc); ++i) {
        switch (sp_playlistcontainer_playlist_type(pc, i)) {
            case SP_PLAYLIST_TYPE_PLAYLIST: 
                playlist = sp_playlistcontainer_playlist(pc, i);
                printf("%d. %s\n", i, sp_playlist_name(playlist));
                break;
            default:
                break;
        }
    }
    return 0;
}

void print_tracks_in_playlist(sp_session *session, sp_playlist* playlist)
{
    debug("Print tracks_in_playlist");
    printf("\n--Listing songs in playlist: %s--", sp_playlist_name(playlist));
    sp_track* track;
    int i;

	for(i = 0; i < sp_playlist_num_tracks(playlist); ++i)
	{
		track = sp_playlist_track(playlist, i);
		printf("\n%d. %s", i, sp_track_name(track));
	}



}

void playthatlist(sp_session *session, sp_playlist* pl)
{
    printf("\nPlay that playlist!\n");
    sp_error error;

       if(!sp_playlist_is_loaded(pl)) {
        printf("Playlist is not loaded!");
        return;
    }
    
    debug("playlist loaded");

    debug("playing playlist '%s'", sp_playlist_name(pl));

    sp_track* track = sp_playlist_track(pl, 0);

    if(sp_track_is_loaded(track)) {
        printf("This track is loaded\n");
    } else {
        printf("This track is not loaded\n");
    }


    play(session, sp_playlist_track(pl, 0));
}

sp_playlist* playlist_find_by_num(sp_session *session, sp_playlistcontainer* pc)
{
    debug("find playlist by index");
    sp_playlist* find;

    char input[1024];
    int index;
    fputs("Playlist number: ", stdout);
    fgets(input, sizeof(input) - 1, stdin);
    printf("fgets is done\n");
    sscanf(input, "%d", &index);
    printf("sscanf is done\n");

    find = sp_playlistcontainer_playlist(pc, index); 

    if(!sp_playlist_is_loaded(find)) {
        debug("playlist is not loaded");
        return NULL;
    } else debug("found playlist %s\n", sp_playlist_name(find));

    return find;
}

void playlist_find_by_name(char* name)
{

}