#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <linux/kd.h>

static unsigned char default_cmap[] = {
	0x00, 0x00, 0x00,
	0xaa, 0x00, 0x00,
	0x00, 0xaa, 0x00,
	0xaa, 0x55, 0x00,
	0x00, 0x00, 0xaa,
	0xaa, 0x00, 0xaa,
	0x00, 0xaa, 0xaa,
	0xaa, 0xaa, 0xaa,
	0x55, 0x55, 0x55,
	0xff, 0x55, 0x55,
	0x55, 0xff, 0x55,
	0xff, 0xff, 0x55,
	0x55, 0x55, 0xff,
	0xff, 0x55, 0xff,
	0x55, 0xff, 0xff,
	0xff, 0xff, 0xff
};

static unsigned char slate_cmap[] = {
	0x18, 0x1b, 0x1f,
	0xcd, 0x00, 0x00,
	0x00, 0xcd, 0x00,
	0xcd, 0xcd, 0x00,
	0x00, 0x5f, 0xff,
	0xcd, 0x00, 0xcd,
	0x00, 0xcd, 0xcd,
	0xe5, 0xe5, 0xe5,
	0x4d, 0x4d, 0x4d,
	0xff, 0x68, 0x68,
	0x7f, 0xef, 0x7f,
	0xf3, 0xe6, 0xad,
	0x8d, 0x88, 0xe6,
	0xf4, 0x9a, 0xc2,
	0x6e, 0xcf, 0xf6,
	0xd0, 0xd0, 0xd0
};

int get_cmap(int fd, unsigned char *cmap) {
	return ioctl(fd, GIO_CMAP, cmap);
}

int set_cmap(int fd, unsigned char *cmap) {
	return ioctl(fd, PIO_CMAP, cmap);
}

void set_underlined_color(int c) {
	printf("\x1b[1;%d]", c);
}

void set_italic_color(int c) {
	printf("\x1b[2;%d]", c);
}

int main(int argc, char *argv[]) {

	const char *tty = "/dev/tty";
	const char *cmd = "default";
	int fd;

	if (argc > 1)
		cmd = argv[1];

	fd = open(tty, O_RDWR);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	if (strcmp(cmd, "default") == 0) {
		if (set_cmap(fd, default_cmap) == -1) {
			perror("set_cmap");
		}
	} else if (strcmp(cmd, "slate") == 0) {
		if (set_cmap(fd, slate_cmap) == -1) {
			perror("set_cmap");
		}
	} else if (strcmp(cmd, "dump") == 0) {
		unsigned char cmap[3*16];
		if (get_cmap(fd, cmap) != -1) {
			for (int i = 0; i < sizeof(cmap); i += 3) {
				printf("0x%02x, 0x%02x, 0x%02x,\n", cmap[i], cmap[i+1], cmap[i+2]);
			}
		} else {
			perror("get_cmap");
		}
	} else if (strcmp(cmd, "underlined") == 0 || strcmp(cmd, "italic") == 0) {
		int c;
		if (argc < 3) {
			fprintf(stderr, "missing color index\n");
			return 1;
		}
		c = atoi(argv[2]);
		if (c < 0 || c > 15) {
			fprintf(stderr, "color index out of range\n");
			return 1;
		}

		if (cmd[0] == 'u') {
			set_underlined_color(c);
		} else {
			set_italic_color(c);
		}
	} else {
		fprintf(stderr, "unknown cmd %s\n", cmd);
		return 1;
	}

	return 0;
}
