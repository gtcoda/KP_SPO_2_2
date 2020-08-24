#include "menu.h"



static void textcolor(short f, short b);
static char getch();
void gotoxy(int x, int y);


// X - �������, Y - ������.
void clear(int x, int y) {
	COORD topLeft = { x, y };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}

// ������� �����.
// ������ �������� ������ ���������.
void clear_line(int x, int cnt) {
	for (uint8_t i = 0; i < cnt; i++) {
		gotoxy(0, x + i);
		printf("\r%80c\r", ' ');
	}
	// ������ ������ �� �������� �������.
	gotoxy(0, x);
}





void gotoxy(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(short f, short b) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), f | (b << 4));
}

char getch() {
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD rec;
	DWORD event;

	FlushConsoleInputBuffer(hstdin);
	while (ReadConsoleInputA(hstdin, &rec, 1, &event)) {
		if ((rec.EventType == KEY_EVENT)
			&& (rec.Event.KeyEvent.bKeyDown)) {
			return (char)rec.Event.KeyEvent.wVirtualKeyCode;
		}
	}
	return EOF;
}

int menu(int x, int y, const char* items[], int cnt) {
	const short COLOR_FG = 7;
	const short COLOR_BG = 0;

	int i;
	char ch;

	textcolor(COLOR_FG, COLOR_BG);
	for (i = 0; i < cnt; ++i) {
		gotoxy(x, y + i);
		printf("%s", items[i]);
	}
	i = 0;
	gotoxy(x, y); textcolor(COLOR_BG, COLOR_FG);
	printf("%s", items[i]);
	gotoxy(x, y); textcolor(COLOR_FG, COLOR_BG); // �������������� ��������� ����� ������� ��� ��������� ������� ����.

	while (((ch = getch()) != EOF) && (ch != VK_RETURN)) {
		gotoxy(x, y + i); textcolor(COLOR_FG, COLOR_BG);
		printf("%s", items[i]);
		switch (ch) {
		case VK_ESCAPE:
			return 0;
		case VK_UP:
			i = (i == 0) ? (cnt - 1) : (i - 1);
			break;
		case VK_DOWN:
			i = (i == cnt - 1) ? 0 : (i + 1);
			break;
		}
		gotoxy(x, y + i); textcolor(COLOR_BG, COLOR_FG);
		printf("%s", items[i]);
		gotoxy(x, y + i); textcolor(COLOR_FG, COLOR_BG); //�������������� ��������� ����� ������� ��� ��������� ������� ����.
	}
	
	// ������ ����� ��� ���������� ����.
	gotoxy(x, y + i); textcolor(COLOR_FG, COLOR_BG);
	printf("%s", items[i]);

	return i;
}

// ���������� ������ ������ �� �������
int size_menu(const char* items[], int pos) {
	int size = 0;
	for (int i = 0; i < pos; ++i) {
		size  += strlen(items[i]);
	}
	return size;
}


int menu_horizont(int x, int y, const char* items[], int cnt, int pos) {
	const short COLOR_FG = 7;
	const short COLOR_BG = 0;

	int i;
	char ch;

	textcolor(COLOR_FG, COLOR_BG);
	for (i = 0; i < cnt; ++i) {
	//	gotoxy(x+i*he, y);
		gotoxy(size_menu(items, i) + 2 * i, y);
		printf("%s", items[i]);
	}
	
	i = pos;
	
	gotoxy(size_menu(items, i) + 2 * i, y); textcolor(COLOR_BG, COLOR_FG);
	printf("%s", items[i]);
	gotoxy(size_menu(items, i) + 2 * i, y); textcolor(COLOR_FG, COLOR_BG); // �������������� ��������� ����� ������� ��� ��������� ������� ����.

	while (((ch = getch()) != EOF) && (ch != VK_RETURN)) {
		gotoxy(size_menu(items, i) + 2 * i, y); textcolor(COLOR_FG, COLOR_BG);
		printf("%s", items[i]);
		switch (ch) {
		case VK_ESCAPE:
			return 0;
		case VK_LEFT:
			i = (i == 0) ? (cnt - 1) : (i - 1);
			break;
		case VK_RIGHT:
			i = (i == cnt - 1) ? 0 : (i + 1);
			break;
		}
		gotoxy(size_menu(items, i) + 2 * i, y); textcolor(COLOR_BG, COLOR_FG);
		printf("%s", items[i]);
		gotoxy(size_menu(items, i) + 2 * i, y); textcolor(COLOR_FG, COLOR_BG); //�������������� ��������� ����� ������� ��� ��������� ������� ����.
	}

	// ������ ����� ��� ���������� ����.
	gotoxy(size_menu(items, i) + 2 * i, y + i); textcolor(COLOR_FG, COLOR_BG);
	printf("%s", items[i]);

	return i;
}