#include <stdio.h>
#include <math.h>

#define BLOCK_LENGTH 1024
#define CHARACTERS 256
#define THRESHOLD 6.677
#define NUMBER_OF_FILES 8

struct Files {
	float entropy_value;
	char* file_name;
	FILE* file_pointer;
};

void entropy(struct Files filesToTest[]) {
	for (int i = 0; i < NUMBER_OF_FILES; i++) {
		if (filesToTest[i].file_pointer == NULL) {
			i++;
		}
		else {
			int count = 0;
			int size = 0;
			float entropy = 0;

			unsigned char buffer[BLOCK_LENGTH] = { 0 };
			unsigned int character_counts[CHARACTERS] = { 0 };

			while (count = fread(buffer, sizeof(unsigned char), BLOCK_LENGTH, filesToTest[i].file_pointer)) {
				for (int i = 0; i < count; i++) {
					character_counts[buffer[i]]++;
					size++;
				}
			}

			for (int i = 0; i < CHARACTERS; i++) {
				if (character_counts[i] > 0) {
					float p = (float)character_counts[i] / (float)size;
					entropy += -p * log2(p);
				}
			}
			filesToTest[i].entropy_value = entropy;
		}
	}
}

void results(struct Files filesToTest[]) {
	for (int i = 0; i < NUMBER_OF_FILES; i++) {
		if (filesToTest[i].file_name == NULL)
			i++;
		else {
			printf("Entropy of %s: %f\n", filesToTest[i].file_name, filesToTest[i].entropy_value);
			printf("Given a threshold of %f, this file is ", THRESHOLD);

			if (filesToTest[i].entropy_value > (float)THRESHOLD) {
				printf("likely to be encrypted or packed.\n");
			}

			else {
				printf("unlikely to be encrypted or packed.\n");
			}
			printf("\n");
		}
	}
}

int main(int argc, char** argv) {
	struct Files filesToTest[NUMBER_OF_FILES] = { 0, NULL, NULL };
	int index = 0;

	for (int i = 1; i <= argc; i++) {
		for (index; index < NUMBER_OF_FILES;) {
			if (argv[i] != NULL) {
				FILE* file = fopen(argv[i], "rb");

				if (file == NULL) {
					printf("Failed to open file: %s\n\n", argv[i]);
					break;
				}

				else {
					filesToTest[index].file_name = argv[i];
					filesToTest[index].file_pointer = file;
					index++;
					break;
				}
			}

			else {
				break;
			}
		}
	}

	entropy(filesToTest);

	results(filesToTest);

}
