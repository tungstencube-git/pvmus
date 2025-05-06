#include "scanner.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void scan_directory(MusicPlayer *player, const char *path) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path))) return;

    while ((entry = readdir(dir)) != NULL && player->count < MAX_FILES) {
        if (entry->d_type == DT_REG) {
            const char *ext = strrchr(entry->d_name, '.');
            if (ext && (strcasecmp(ext, ".mp3") == 0 ||
                        strcasecmp(ext, ".flac") == 0 ||
                        strcasecmp(ext, ".wav") == 0 ||
                        strcasecmp(ext, ".ogg") == 0)) {
                char fullpath[MAX_PATH_LEN];
                snprintf(fullpath, MAX_PATH_LEN, "%s/%s", path, entry->d_name);
                player->files[player->count++] = strdup(fullpath);
            }
        }
    }

    closedir(dir);
}
