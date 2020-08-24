#ifndef MENU_H
#define MENU_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#define VELCOM "	Разработка программного комплекса сбора информации о вычислительной системе\n\r	KP_SPO_2_2 \n\r "

#define COUNT_LINE_VELCOM 2			// Количество строк занимаемое приветствием.
#define COLUMN_LINE_LEVCOM 0		// Начальная колонка строк с приветствием.

#define COUNT_LINE_MAIN_MENU 1			// Количество строк занятых основной менюшкой.
#define COLUMN_LINE_MAIN_MENU 0			// Начальная колонка строк меню.

#define COUNT_LINE_MENU 14			// Количество строк занятых вторичной менюшкой.
#define COLUMN_LINE_MENU 1			// Начальная колонка строк меню.

#define DB_ACTIVE_WORK (COUNT_LINE_VELCOM) // Позиция занимаемая именем активной базы
#define MEMU_MAIN (COUNT_LINE_VELCOM) // ПОЗИция строки начала меню
#define LINE_MAIN (COUNT_LINE_MENU + COUNT_LINE_VELCOM) // Позиция начальной строки под меню.


#define INDENT_MENU (MEMU_MAIN + COUNT_LINE_MAIN_MENU) // Позиция начала вторичного меню






#define INDENT 1 // Отступ основной


#define MENU_CPU 		"CPU"
#define MENU_BIOS 		"BIOS"
#define MENU_PARTITION 	"PART"
#define MENU_HDD 		"HDD"
#define MENU_BASEBOARD 	"BASEBORD"
#define MENU_KEYBOARD	"KEYBOARD"
#define MENU_MOUSE 		"MOUSE"
#define MENU_VIDEO 		"VIDEO"
#define MENU_MONITOR 	"MONITOR"
#define MENU_NETWORK 	"NETWORK"
#define MENU_PROCESS 	"PROCESS"
#define MENU_UPTIME 	"UPTIME"
#define MENU_USERS	 	"USERS"
#define MENU_EXIT 		"EXIT"

#define ALL "Все."

#define MENU_SHOW			"Показать"
#define MENU_PUSH_DB		"Отправить"
#define MENU_PUSH_FILE		"Записать"



#define he 2


int menu(int x, int y, const char* items[], int cnt);
void clear(int X, int Y);
void clear_line(int x, int cnt);


int menu_horizont(int x, int y, const char* items[], int cnt, int pos);

#endif
