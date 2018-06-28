#include "cpc_terminal.h"

#ifdef CPC_DEBUG
	#include "cpc_bool.h"

	static bool cpc_terminal_initialized = false;
#endif

#ifdef CPC_PLATFORM_WINDOWS
	static CPCTerminalStyle cpc_terminal_default_style;

	void cpc_terminal_init(void) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(!cpc_terminal_initialized);
			cpc_terminal_initialized = true;
		#endif
		CONSOLE_SCREEN_BUFFER_INFO info;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
		cpc_terminal_default_style = info.wAttributes;
	}

	void cpc_terminal_apply_style(CPCTerminalStyle style) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), style);
	}
	
	void cpc_terminal_reset_style(void) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(cpc_terminal_initialized);
		#endif
		cpc_terminal_apply_style(cpc_terminal_default_style);
	}

	void cpc_terminal_set_cursor_pos(unsigned short x, unsigned short y) {
		COORD coord = (COORD){ (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
	
	void cpc_terminal_get_size(unsigned short *restrict width, unsigned short *restrict height) {
		CPC_ASSERT(width != NULL);
		CPC_ASSERT(height != NULL);
		CPC_ASSERT(width != height);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		BOOL result = GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		CPC_ASSERT(!result || csbi.dwSize.X >= 0);
		CPC_ASSERT(!result || csbi.dwSize.Y >= 0);
		*width = result ? (unsigned short)csbi.dwSize.X : 0;
		*height = result ? (unsigned short)csbi.dwSize.Y : 0;
	}
#else
	#include <stdio.h>
	#include <sys/ioctl.h>

	void cpc_terminal_init(void) {
		#ifndef NDEBUG
			CPC_ASSERT(!cpc_terminal_initialized);
			cpc_terminal_initialized = true;
		#endif
	}

	void cpc_terminal_apply_style(CPCTerminalStyle style) {
		CPC_ASSERT(style != NULL);
		int result = fputs(style, stdout);
		CPC_ASSERT(result >= 0);
	}
	
	void cpc_terminal_reset_style(void) {
		#ifdef CPC_DEBUG
			CPC_ASSERT(cpc_terminal_initialized);
		#endif
		cpc_terminal_apply_style("\x1B[0m");
	}
	
	void cpc_terminal_set_cursor_pos(unsigned short x, unsigned short y) {
		int result = printf("\033[<%hu>;<%hu>H", x, y);
		CPC_ASSERT(result >= 0);
	}

	void cpc_terminal_get_size(unsigned short *restrict width, unsigned short *restrict height) {
		CPC_ASSERT(width != NULL);
		CPC_ASSERT(height != NULL);
		CPC_ASSERT(width != height);
		struct winsize window_size;
		int result = ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
		*width = (result == 0) * window_size.ws_col;
		*height = (result == 0) * window_size.ws_row;
	}
#endif
