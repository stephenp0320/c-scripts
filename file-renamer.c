#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
int rename_logic(char *directory){
	DIR *dir;
	struct dirent *de;
	dir = opendir(directory);
	char *need = ".png";
	if (dir == NULL){
		fprintf(stderr, "DIR err\n");
		return -1;
	}
	printf("looking for files ending in %s\n", need);
	while ((de = readdir(dir)) != NULL){
		char *file_name = de->d_name;
		if (strcmp(file_name, ".") == 0 || strcmp(file_name, "..") == 0)
			continue;
		
		if (strstr(file_name, need) != NULL){
			char old_path[512], new_name[256], new_path[512];
			snprintf(old_path, sizeof(old_path), "%s/%s", directory, file_name);
			printf("Rename %s to: ", file_name);
			if (scanf("%255s", new_name) == 1){
				snprintf(new_path, sizeof(new_path), "%s/%s", directory, new_name);
				if (rename(old_path, new_path) != 0){
					perror("rename failed");
				} 
			}
			printf("complete\n");
		}
	}
	closedir(dir);
	return 0;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s directory_to_search\n", argv[0]);
		return -1;
	}
	char *dir_entry = argv[1];
	return rename_logic(dir_entry);
}
