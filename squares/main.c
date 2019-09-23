#include <stdio.h>
#include <stdlib.h>

// fprintf to write to a file
// args: rows, cols, output file
int main(int argc, char **argv)
{
	if (argc != 4) {
		fprintf(stderr, "Please specify correct arguments:\n%s <start> <end> <output file>\n", *argv);
		return EXIT_FAILURE;
	}
	FILE *fp;
	if (!(fp = fopen(argv[3], "w"))) {
		fprintf(stderr, "Can't open %s\n", argv[3]);
		return EXIT_FAILURE;
	}
	int start = atoi(argv[1]);
	int end = atoi(argv[2]);
	fprintf(fp, "Squares of integers between %d and %d\n", start, end);
	for (int i = start; i < end; i++) {
		fprintf(fp, "%d squared is %d\n", i, i * i);
	}
	if (fclose(fp) != 0) {
		fprintf(stderr, "Could not close file.");
		return EXIT_FAILURE;
	};
	return EXIT_SUCCESS;
}
