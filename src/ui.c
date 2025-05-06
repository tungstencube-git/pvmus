#include "ui.h"
#include <string.h>

void display_player(MusicPlayer *player, WINDOW *win) {
    int height, width;
    getmaxyx(win, height, width);
    wclear(win);

    mvwprintw(win, 0, (width - 5) / 2, "pvmus");
    mvwhline(win, 1, 0, ACS_HLINE, width);

    int start_idx = (player->selected - height / 2 + 3 > 0) ? player->selected - height / 2 + 3 : 0;
    int max_display = height - 6;

    for (int i = 0; i < max_display && start_idx + i < player->count; i++) {
        if (start_idx + i == player->selected) wattron(win, A_REVERSE);

        const char *filename = strrchr(player->files[start_idx + i], '/');
        filename = filename ? filename + 1 : player->files[start_idx + i];

        if (start_idx + i == player->playing) wattron(win, A_BOLD);

        mvwprintw(win, i + 2, 2, "%.60s", filename);

        if (start_idx + i == player->playing) wattroff(win, A_BOLD);
        if (start_idx + i == player->selected) wattroff(win, A_REVERSE);
    }

    mvwhline(win, height - 4, 0, ACS_HLINE, width);
    mvwprintw(win, height - 3, 2, "controls: up/down: navigate | enter: play | q: quit | s: stop");
    mvwprintw(win, height - 2, 2, "files: %d | selected: %d | %s",
              player->count,
              player->selected + 1,
              player->playing == player->selected ? "▶ playing" : "");

    wrefresh(win);
}
