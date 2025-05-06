#ifndef PLAYER_H
#define PLAYER_H

#include <sys/types.h>

#define MAX_FILES 1000
#define MAX_PATH_LEN 512

typedef struct {
    char *files[MAX_FILES];
    int count;
    int selected;
    int playing;
    pid_t player_pid;
} MusicPlayer;

void init_player(MusicPlayer *player);
void cleanup_player(MusicPlayer *player);
void play_file(MusicPlayer *player, int index);

#endif
