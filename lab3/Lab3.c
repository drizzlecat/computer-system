//Submitter: jiany1(Yao, Jian)	000974455
//Partner: fangjunl(Liu, Fangjun)	000972140

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 128
#define HEADER_SIZE 2

static int block_number = 1;

void allocate(unsigned char * heap) {
	int input;
	scanf("%i", &input);
	if (input <= 0 || input > MAX_LEN - HEADER_SIZE) {
		printf("Invalid allocation size.\n");
		return;
	}
	unsigned char size = (unsigned char) input;
	unsigned char * p = heap + 1;
	while (p < heap + MAX_LEN && (*p & 1 || (*p >> 1) < size))
		p += (*p >> 1) + HEADER_SIZE;
	if (p >= heap + MAX_LEN) {
		printf("No suitable block in the heap.\n");
		return;
	}
	*(p-1) = block_number++;
	unsigned char current_size = *p >> 1;
	if (current_size - size > HEADER_SIZE) { //decide whether need padding
		*p = (size << 1) | 1;
		*(p + size + HEADER_SIZE) = (current_size - size - HEADER_SIZE) << 1;
	}
	else
		*p = (current_size << 1) | 1;
	printf("%i\n", *(p-1));
}

void free_block(unsigned char * heap) {
	int block_num;
	scanf("%i", &block_num);
	if (block_num < 0 || block_num >= 256) {
		printf("Invalid block index.\n");
		return;
	}
	unsigned char index = (unsigned char) block_num;
	unsigned char * p = heap + 1;
	while (p < heap + MAX_LEN) {
		if (*p & 1 && *(p-1) == index) {
			//*p = (*p >> 1) << 1;
			*p = *p & -2;
			return;
		}
		p += (*p >> 1) + HEADER_SIZE;
	}
	printf("Block index is not in the heap.\n");
}

void blocklist(unsigned char * heap) {
	printf("Size\tAllocated\tStart\t\tEnd\n");
	unsigned char * p = heap + 1;
	while (p < heap + MAX_LEN) {
		printf("%i\t", (int)(*p >> 1) + HEADER_SIZE);
		if (*p & 1)
			printf("%s\t\t", "yes");
		else
			printf("%s\t\t", "no");
		printf("%p\t%p\n", (p - 1), (p + (*p >> 1)));
		p += (*p >> 1) + HEADER_SIZE;
	}
}

void writeheap(unsigned char * heap) {
	int block_num;
	char write_char;
	int copy_num;
	if (scanf("%i %c %i", &block_num, &write_char, &copy_num) != 3) {
		printf("Invalid input format.\n");
		char c;
		while ((c = getchar()) != '\n' && c != EOF);
		return;
	}
	if (block_num < 0 || block_num >= 256) {
		printf("Invalid block index.\n");
		return;
	}
	unsigned char * p = heap + 1;
	while (p < heap + MAX_LEN) {
		if (*p & 1 && *(p-1) == (unsigned char) block_num) {
			if ((*p >> 1) < (unsigned char) copy_num) {
				printf("Wrtie too big\n");
				return;
			}
			int i = 0;
			while (i < copy_num) {
				*(p + ++i) = write_char;
			}
			return;
		}
		p += (*p >> 1) + HEADER_SIZE;
	}
	printf("Block index is not in the heap.\n");
}

void printheap(unsigned char * heap) {
	int block_num;
	int print_num;
		if (scanf("%i %i", &block_num, &print_num) != 2) {
		printf("Invalid input format.\n");
		char c;
		while ((c = getchar()) != '\n' && c != EOF);
		return;
	}
	if (block_num < 0 || block_num >= 256) {
		printf("Invalid block index.\n");
		return;
	}
	int flag = 0;
	unsigned char * p = heap + 1;
	while (p < heap + MAX_LEN) {
		if (*p & 1 && *(p-1) == (unsigned char) block_num || flag) {
			int i = 0;
			int payload_size = *p >> 1;
			while (i < print_num && i < payload_size) {
				printf("%c", *(p + ++i));
			}
			print_num -= i;
			flag = 1;
			if (print_num == 0) {
				printf("\n");
				return;
			}
		}
		p += (*p >> 1) + HEADER_SIZE;
	}
	if (!flag)
		printf("Block index is not in the heap.\n");
}

void printheader(unsigned char * heap) {
	int block_num;
	scanf("%i", &block_num);
	if (block_num < 0 || block_num >= 256) {
		printf("Invalid block index.\n");
		return;
	}
	unsigned char index = (unsigned char) block_num;
	unsigned char * p = heap + 1;
	while (p < heap + MAX_LEN) {
		if (*p & 1 && *(p-1) == index) {
			printf("%02x%02x\n", *(p-1), *p);
			return;
		}
		p += (*p >> 1) + HEADER_SIZE;
	}
	printf("Block index is not in the heap.\n");
}

void print(unsigned char * heap) { //for debug
	int i = 0;
	while ( i < MAX_LEN)
		printf("%x ", heap[i++]);
	printf("\n");
}

int main() {
	//initialization
	char command[20];
	unsigned char * heap = malloc(MAX_LEN);
	heap[1] = (MAX_LEN - HEADER_SIZE) << 1;
	
	// body program
	printf("> ");
	scanf("%s", command);
	
	while (strcmp(command, "quit") != 0) {
		if (strcmp(command, "allocate") == 0){allocate(heap);}
		else if (strcmp(command, "free") == 0) {free_block(heap);}
		else if (strcmp(command, "blocklist") == 0) {blocklist(heap);}
		else if (strcmp(command, "writeheap") == 0) {writeheap(heap);}
		else if (strcmp(command, "printheap") == 0) {printheap(heap);}
		else if (strcmp(command, "printheader") == 0) {printheader(heap);}
		else if (strcmp(command, "print") == 0) {print(heap);}
		else {
			printf("%s\n", "Invalid Command.");
			char c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
		printf("> ");
		scanf("%s", command);
	}
	
	free(heap);
	return 0;
}