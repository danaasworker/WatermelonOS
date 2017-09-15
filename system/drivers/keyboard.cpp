#include <system.h>

static bool key_pressed = false;
static char pressed_key = 0;

void keyboard_handler(Register* regs) {
	char key = inportb(0x60);
	if (key&0x80) {
		// Key is pressed
	} else {
		// Key is released
		key_pressed = true;
		pressed_key = key;
	}
}

bool isKeyPressed() {
	if (key_pressed) {
		key_pressed = false;
		return true;
	}
	return false;
}

void waitForKey() {
	while (!key_pressed) {
		wait();
	}
	key_pressed = false;
}

int getPressedKey() {
	return (int)pressed_key;
}

void init_keyboard() {
	irq_set_handler(1, keyboard_handler);
}
