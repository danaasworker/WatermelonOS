#include <system.h>

char mouse_cycle = 0;
char mouse_byte[3];
int mouse_x = 0;
int mouse_y = 0;
char left_click;
char right_click;
char middle_click;

void mouse_handler(Register* regs) {
	//char status = inportb(0x64);
	/*if ((status&1)==0) {
		return;
	}
	if ((status&0x20)==0) {
		return;
	}*/
	if (mouse_cycle == 0) {
        mouse_byte[0]=inportb(0x60);
      	left_click = mouse_byte[0]&0x1;
      	right_click = mouse_byte[0]&0x2;
      	middle_click = mouse_byte[0]&0x4;
      	mouse_cycle = 1;
    } else if (mouse_cycle == 1) {
        mouse_byte[1]=inportb(0x60);
      	mouse_cycle = 2;
    } else if (mouse_cycle == 2) {
      	mouse_byte[2]=inportb(0x60);
      	mouse_x+=mouse_byte[1];
      	mouse_y-=mouse_byte[2];
        mouse_cycle=0;
  	}
}

void mouse_wait(char a_type) {
  	unsigned int _time_out=100000;
  	if(a_type==0) {
    	while(_time_out--) {
      		if((inportb(0x64) & 1)==1) {
        		return;
      		}
    	}
    	return;
  	} else {
    	while(_time_out--) {
      		if ((inportb(0x64) & 2)==0) {
        		return;
      		}
    	}
    	return;
  	}
}

void mouse_write(char a_write) {
  	mouse_wait(1);
  	outportb(0x64, 0xD4);
  	mouse_wait(1);
  	outportb(0x60, a_write);
}

bool is_left_clicked() {
	if (left_click) {
		//left_click = 0;
		return true;
	}
	return false;
}

bool is_right_clicked() {
	if (right_click) {
		right_click = 0;
		return true;
	}
	return false;
}

bool is_middle_clicked() {
	if (middle_click) {
		middle_click = 0;
		return true;
	}
	return false;
}

char mouse_read() {
  	mouse_wait(0);
  	return inportb(0x60);
}

void init_mouse() {
  	char _status;
  	mouse_wait(1);
  	outportb(0x64, 0xA8);
  	mouse_wait(1);
  	outportb(0x64, 0x20);
  	mouse_wait(0);
  	_status=(inportb(0x60) | 2);
  	mouse_wait(1);
  	outportb(0x64, 0x60);
  	mouse_wait(1);
  	outportb(0x60, _status);
  	mouse_write(0xF6);
  	mouse_read();
  	mouse_write(0xF4);
  	mouse_read();
  	irq_set_handler(12, mouse_handler);
}

int get_cursor_x() {
	return mouse_x;
}

int get_cursor_y() {
	return mouse_y;
}

void draw_cursor() {
	draw_image((char*)&cursor, get_cursor_x(), get_cursor_y(), 0);
}

bool is_clicked(int x1, int y1, int x2, int y2) {
	if (is_left_clicked()) {
		int x = get_cursor_x();
		int y = get_cursor_y();
		if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
			return true;
		}
	}
	return false;
}
