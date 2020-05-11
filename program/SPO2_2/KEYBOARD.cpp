#include "KEYBOARD.h"

HRESULT KEYBOARD::Go(void) {
	SysInfo::Info(&KEYBOARDstr, &KEYBOARD_I);

	return S_OK;
}