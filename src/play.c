#include <stdio.h>
#include <libspotify/api.h>
#include "debug.h"
#include "play.h"

void play(sp_session *session, sp_track *track)
{
    debug("in player");
    g_playing = 1;
    debug("loading track into player");
	sp_error error = sp_session_player_load(session, track);
	if (error != SP_ERROR_OK) {
		fprintf(stderr, "\nError: %s\n", sp_error_message(error));
		printf("track: %s, artist: %s\n", sp_track_name(track), sp_artist_name(sp_track_artist(track, 0)));
		sp_session_player_unload(session);
		//if (g_selectedList != NULL){ playlistGoNext(); printf("playing next song...\n\n");}
		return;
	}
    debug("calling sp_session_player_play");
	sp_session_player_play(session, 1);
}
