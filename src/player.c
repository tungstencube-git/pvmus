#include "player.h"
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void init_player(MusicPlayer *player) {
    player->count = 0;
    player->selected = 0;
    player->playing = -1;
    player->player_pid = -1;
}

void cleanup_player(MusicPlayer *player) {
    for (int i = 0; i < player->count; i++) {
        free(player->files[i]);
    }

    if (player->player_pid > 0) {
        kill(player->player_pid, SIGTERM);
        waitpid(player->player_pid, NULL, 0);
    }
}

void play_file(MusicPlayer *player, int index) {
    if (index < 0 || index >= player->count) return;

    if (player->player_pid > 0) {
        kill(player->player_pid, SIGTERM);
        waitpid(player->player_pid, NULL, 0);
        player->player_pid = -1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = {"mpv", "--no-video", "--no-terminal", player->files[index], NULL};
        execvp("mpv", args);
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        player->player_pid = pid;
        player->playing = index;
    }
}
