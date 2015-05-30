#include <stdio.h>
#include <string.h>

struct Pirate {
	char name[100]; //real name
	unsigned int booty;
	unsigned int beard_len;
};

int main(int argc, char **argv) {
	FILE *in, *out;
	struct Pirate new_pirate;
	struct Pirate pirate_lord;

	strcpy(pirate_lord.name, "Egor Gorodov");
	pirate_lord.booty = 1024;
	pirate_lord.beard_len = 100;

	out = fopen("data", "w");

	if(!out) {
		perror("fopen");
		return 1;
	}

	if(!fwrite(&pirate_lord, sizeof(struct Pirate), 1, out)) {
		perror("fwrite");
		return 1;
	}

	if(fflush(out))
		perror("flush");

	fsync(out);

	if(fclose(out)) {
		perror("fclose");
		return 1;
	}

	in = fopen("data", "r");

	if(!in) {
		perror("fopen");
		return 1;
	}

	if(!fread(&new_pirate, sizeof(struct Pirate), 1, in)) {
		perror("fread");
		return 1;
	}

	if(fclose(in)) {
		perror("fclose");
		return 1;
	}

	printf("name = %s, booty = %d, beard_len = %d\n", new_pirate.name, new_pirate.booty, new_pirate.beard_len);
}
