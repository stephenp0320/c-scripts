#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct pcap_hdr {
    uint32_t magic;
    uint16_t version_major, version_minor;
    int32_t  thiszone;
    uint32_t sigfigs, snaplen, network;
};

uint32_t reverse_bytes(uint32_t bytes){
    uint32_t aux = 0;
    uint8_t byte;
    int i;

    for(i = 0; i < 32; i+=8)
    {
        byte = (bytes >> i) & 0xff;
        aux |= byte << (32 - 8 - i);
    }
    return aux;
}
int parser(char *target){
	FILE *fp_tar;
	fp_tar = fopen(target, "rb");
	if (!fp_tar){
		perror(target);
		return -1;
	}
	int normal_order = 0xa1b2c3d4;
	int swapped_order = 0xd4c3b2a1;
	struct pcap_hdr hdr;
	if (fread(&hdr, sizeof hdr, 1, fp_tar) != 1){
		fprintf(stderr, "%s: file too short for pcap header\n", target);
        	fclose(fp_tar);
        	return -1;
	}
	bool is_swapped;
	if(hdr.magic == swapped_order){
		is_swapped = true;
	} else if (hdr.magic == normal_order) {
		is_swapped = false;
	} else {
		fprintf(stderr, "not a pcap file (magic: %08x)\n", hdr.magic);
    		fclose(fp_tar);
    		return -1;
	}

	if (is_swapped){
		hdr.magic = reverse_bytes(hdr.magic);
		hdr.version_major = (hdr.version_major >> 8) | (hdr.version_major << 8) & 0xFF00;
        	hdr.version_minor = (hdr.version_minor >> 8) | (hdr.version_minor << 8) & 0xFF00;
		hdr.snaplen = reverse_bytes(hdr.snaplen);
        	hdr.network = reverse_bytes(hdr.network);
	}
	printf("pcap version %u.%u, snaplen %u, linktype %u\n", hdr.version_major, hdr.version_minor, hdr.snaplen, hdr.network);
	fclose(fp_tar);
	return 0;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr, "Usage: %s target\n", argv[0]);
		return -1;
	}
	char *target = argv[1];
	int packet_parse = parser(target);
	return packet_parse;
}
