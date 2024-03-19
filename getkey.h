#ifndef GETKEY_H
#define GETKEY_H
typedef enum {
	KEY_ESC = -1,
	KEY_UP = -2,
	KEY_DOWN = -3,
	KEY_LEFT = -4,
	KEY_RIGHT = -5,
} Keyname;
void cbreak(struct termios *tty);
int getkey();
#endif
