#include <stdio.h>
#include <stdbool.h>
#define FILE_NAME_SIZE 32
#define MAX_SLOTS 32
#define TOTAL_BYTES 10485760
struct meta_data {
	int status;
	char filename[32];
	off_t file_size;
	int block_num;
};

int disk_initialiser(char *disk){
	FILE *fp;
	fp = fopen(disk, "wb");
	if (!fp){
		fprintf(stderr, "file err\n");
		return -1;
	}
	struct meta_data md_struct = {0};
	int max_slots = MAX_SLOTS;
	for (int i = 0; i < max_slots; i++){
		fwrite(&md_struct, sizeof(struct meta_data), 1, fp);
	}
	int total_bytes = TOTAL_BYTES;
	int bytes_written = max_slots * sizeof(struct meta_data);
	int bytes_remaining = total_bytes - bytes_written;
	char blank_byte = 0;
	for (int i = 0; i < bytes_remaining; i++){
		fwrite(&blank_byte, 1, 1, fp);
	}
	printf("slots remaining: %d\n", bytes_remaining);
	fclose(fp);
	return 0;
}

int ls(char *initialised_disk){
	FILE *fp;
	fp = fopen(initialised_disk, "rb");
	if (!fp){
		fprintf(stderr, "File err");
		return -1;
	}
	struct meta_data curr_slot;
	int idx = 0;
	while (idx < MAX_SLOTS){
		fread(&curr_slot, sizeof(struct meta_data), 1, fp);
		if (curr_slot.status == 1){
			printf("File: %s (%ld bytes)\n", curr_slot.filename, (long)curr_slot.file_size);
		}
		idx++;
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[]){
	if (argc < 1){
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return -1;
	}
	char *disk_name = "disk.bin";
	disk_initialiser(disk_name);
	ls(disk_name);
	return 0;
}
