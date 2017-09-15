#include <system.h>

void test1() {
	// Drawing graphics on memory address 0xBEEF0201
	char* scr = (char*)(0xBEEF0201);
	for (int i=0; i<800*600; i++) {
		scr[i] = 0xFF;
	}
}

void drawWindows8Logo() {
	fill_bg(0x000000);
	draw_image((char*)&windows10logo, 0, -125, CENTER_ON_SCREEN);
}

void drawingWindows8() {
	set_font((char*)&arial_font, ARIAL_FONT_SIZE);
	set_font_size(25);
	// Fading-In a transition, windows logo start displaying
	transition(FADE_IN, 100, drawWindows8Logo);
	// Halting windows 8 logo
	draw_image((char*)&windows10logo, 0, -125, CENTER_ON_SCREEN);
	flush();
	sleep(3000);
	schedule(10000, 1);
	while (true) {
		draw_animation((char*)&windows10loadingsprite, 75, 50, 0, 200, CENTER_ON_SCREEN, drawWindows8Logo);
		flush();
		if (isTimerOccured(1)) {
			break;
		}
		drawWindows8Logo();
		flush();
		sleep(300);
	}
	// Fading-Out a transition, windows logo start hiding
	transition(FADE_OUT, 10, drawWindows8Logo);
	loop();
}

void askingForShutdown_Activity() {
	while (true) {
		draw_image((char*)&wallpaper, 0, 0, 0);
		fill_rect(0, 570, 800, 30, 0x000000);
		draw_image((char*)&start_icon, 0, 571, 0);
		draw_image((char*)&file_manager_icon, 45, 573, 0);
		draw_image((char*)&shutdown_icon, 770, 573, 0);
		fill_rect(200, 190, 400, 210, 0xFFFFFF);
		fill_rect(190, 200, 420, 190, 0xFFFFFF);
		fill_circle(200, 200, 10, 0xFFFFFF);
		fill_circle(600, 200, 10, 0xFFFFFF);
		fill_circle(200, 388, 10, 0xFFFFFF);
		fill_circle(599, 389, 10, 0xFFFFFF);
		if (is_clicked(770, 573, 800, 600)) {
			return;
		}
		draw_cursor();
		flush();
	}
}

void shut_down() {
	
}

int main(BootInfo* bootInfo) {
	init_memory(0x2000000, 0x8000000);
	clear_screen();
	init_graphics(bootInfo->vbe_mode_info);
	init_gdt();
	init_idt();
	init_isr();
	init_irq();
	init_syscalls();
	init_pit(1000);
	//init_keyboard();
	init_mouse();
	//init_notifications();
	asm volatile("sti");
	set_utc(7);
	set_time_server(CMOS);
	init_devices();
	enumerate_devices();
	//init_ide();
	//init_storages();
	//run_app((char*)&app1, 0, NULL);
	//printf("\nDone\n");
	//while (1);
	
	//File* wallpaper = open_file("C:/eiffel.bmp");
	set_font((char*)&arial_font, ARIAL_FONT_SIZE);
	while (1) {
		draw_image((char*)&wallpaper, 0, 0, 0);
		fill_rect(0, 570, 800, 30, 0x000000);
		draw_image((char*)&start_icon, 0, 571, 0);
		draw_image((char*)&file_manager_icon, 45, 573, 0);
		draw_image((char*)&shutdown_icon, 770, 573, 0);
		if (is_clicked(770, 573, 800, 600)) {
			askingForShutdown_Activity();
		}
		draw_cursor();
		flush();
	}
	//printf("%d\n", file->size);
	//init_audio_driver();
	//drawingWindows8();
	return 0;
	
	set_font((char*)&arial_font, ARIAL_FONT_SIZE);
	set_font_size(50);
	while (1) {
		fill_bg(0xFFFFFF);
		TextField* tf = new TextField(50, 50, 300, 50, 0xFFFFFF, 0x000000, (char*)&arial_font, ARIAL_FONT_SIZE, 20, 0x000000);
		tf->setText("This is text");
		tf->apply();
		flush();
	}
	return 0;
}
