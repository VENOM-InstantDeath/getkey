#include <unistd.h>
#include <termios.h>
#include <poll.h>
#include "getkey.h"

void cbreak(struct termios *tty) {
	tty->c_cc[VTIME] = 0; tty->c_cc[VMIN] = 1;
	tty->c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSADRAIN, tty);
}

int handleEsc(struct pollfd *rdfd) {
	if (!poll(rdfd, 1, 5)) {
		return KEY_ESC;
	}
	char key[2];
	for (int i=0; i<2; i++) {
		char ch[1];
		read(0, ch, 1);
		key[i] = ch[0];
	}
	if (key[0]==91) {
		switch (key[1]) {
			case 65: return KEY_UP;
			case 66: return KEY_DOWN;
			case 67: return KEY_RIGHT;
			case 68: return KEY_LEFT;
		}
	}
	return 0;
}

int getkey() {
	struct pollfd rdfd[1];
	rdfd[0].fd = 0;
	rdfd[0].events = POLLIN;
	char ch[1];
	poll(rdfd, 1, -1);
	read(0, ch, 1);
	if (ch[0] == 27) return handleEsc(rdfd);
	return ch[0];
}
