#include <stdio.h>

#define CSI "\x1b["

#define NORMAL 0
#define BOLD 1
#define ITALIC 3
#define UNDERLINE 4
#define BLINK 5
#define REVERSE 7

void csi_m(int n) {
	printf("%s%dm", CSI, n);
}

int main(int argc, char *argv[]) {
	for (int color = 0; color < 8; color++) {
		csi_m(NORMAL);
		csi_m(30 + color);
		printf("color%d", color);
		csi_m(NORMAL);
		putchar(' ');
		csi_m(30 + color);
		csi_m(BOLD);
		printf("bold%d", color);
		csi_m(NORMAL);
		putchar(' ');
		csi_m(30 + color);
		csi_m(ITALIC);
		printf("italic%d", color);
		csi_m(NORMAL);
		putchar(' ');
		csi_m(30 + color);
		csi_m(UNDERLINE);
		printf("underlined%d", color);
		csi_m(NORMAL);
		putchar(' ');
		csi_m(30 + color);
		csi_m(BLINK);
		printf("blink%d", color);
		csi_m(NORMAL);
		putchar(' ');
		csi_m(30 + color);
		csi_m(REVERSE);
		printf("reverse%d\n", color);
	}
	csi_m(NORMAL);

}
