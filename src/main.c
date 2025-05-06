#include <signal.h>
#include <sys/wait.h>
#include "player.h"
#include "scanner.h"
#include "ui.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    MusicPlayer player;
    char music_dir[MAX_PATH_LEN] = ".";

    if (argc > 1) {
        strncpy(music_dir, argv[1], MAX_PATH_LEN);
    } else {
        char *home = getenv("HOME");
        if (home) {
            snprintf(music_dir, MAX_PATH_LEN, "%s/Music", home);
            if (access(music_dir, F_OK) != 0)
                strcpy(music_dir, ".");
        }
    }

    init_player(&player);
    scan_directory(&player, music_dir);
    if (player.count == 0) {
        printf("no music files found in %s\n", music_dir);
        return EXIT_FAILURE;
    }

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    WINDOW *main_win = newwin(LINES, COLS, 0, 0);

    display_player(&player, main_win);

    int running = 1;
    while (running) {
        display_player(&player, main_win);
        int ch = getch();
        switch (ch) {
            case 'q': running = 0; break;
            case KEY_UP: if (player.selected > 0) player.selected--; break;
            case KEY_DOWN: if (player.selected < player.count - 1) player.selected++; break;
            case 10: play_file(&player, player.selected); break;
            case 's':
                if (player.player_pid > 0) {
                    kill(player.player_pid, SIGTERM);
                    waitpid(player.player_pid, NULL, 0);
                    player.player_pid = -1;
                    player.playing = -1;
                }
                break;
        }
    }

    cleanup_player(&player);
    delwin(main_win);
    endwin();

    return EXIT_SUCCESS;
}
