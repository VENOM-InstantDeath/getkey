#include <stdio.h>
#include <termios.h>
#include "getkey.h"

int main() {
	struct termios tty, old;
	tcgetattr(0, &old);
	tty = old;
	cbreak(&tty);
	for (;;) {
		int ch = getkey();
		switch (ch) {
			case KEY_ESC:
				puts("ESC");break;
			case KEY_UP:
				puts("UP");break;
			case KEY_DOWN:
				puts("DOWN");break;
			case KEY_RIGHT:
				puts("RIGHT");break;
			case KEY_LEFT:
				puts("LEFT");break;
			case 'q':
				goto exit_loop;
			case '\n':
				puts("ENTER");break;
			case ' ':
				puts("SPACE");break;
			default:
				puts("ANOTHER KEY");
		}
	}
exit_loop: ;
	tcsetattr(0, TCSADRAIN, &old);
}
