#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <linux/limits.h>
#include <sys/stat.h>

#define PROC_DIR "/proc/"
#define EXE_LINK "/exe"

bool isnumber(const char *string)
{
	while (string[0] != '\0') {
		if (!isdigit(string[0])) {
			return false;
		}

		++string;
	}

	return true;
}

bool getlinkedpath(const char *linkpath, char *linkedpath)
{
	if (!realpath(linkpath, linkedpath)) {
		printf("realpath() failed with error %d\n", errno);
		return false;
	}

	return true;
}

int main()
{
	DIR *dir = opendir(PROC_DIR);
	if (dir == NULL) {
		printf("opendir() failed with error %d\n", errno);
		return 1;
	}

	struct dirent *de;
	while ((de = readdir(dir))) {
		const char *pid = de->d_name;
		if (!isnumber(pid)) {
			continue;
		}

		char exelinkpath[PATH_MAX];
		snprintf(exelinkpath, sizeof(exelinkpath), "%s%s%s", PROC_DIR, pid, EXE_LINK);

		struct stat st;
		if (stat(exelinkpath, &st) == -1) {
			// Either the file doesn't exist or it's not accessible.
			continue;
		}

		char path[PATH_MAX];
		if (!getlinkedpath(exelinkpath, path)) {
			printf("getlinkedpath() failed, skipping entry...\n");
			continue;
		}

		printf("[%s] %s\n", pid, basename(path));
	}

	closedir(dir);

	return 0;
}
