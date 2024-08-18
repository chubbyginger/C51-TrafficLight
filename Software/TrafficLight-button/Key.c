// Single-key driver logic

#include <reg52.h>
#include "main.h"
#include "Key.h"

unsigned char ReadKey() {
	unsigned char status = 0;
	if (!button1) {
		Delay1ms(BUTTON_DELAY);
		if (!button1) {
			status = 1;
		}
	}
	return status;
}
