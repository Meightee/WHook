#include "dllhook.h"
#include "atltypes.h"
#include <fstream>

HHOOK hMouseHook;
HHOOK hKeyboardHook;
HINSTANCE hInst;

int amount = 0;

EXPORT void CALLBACK SetMouseHook(void)
{
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInst, 0);
}

EXPORT void CALLBACK UnMouseHook(void)
{
	UnhookWindowsHookEx(hMouseHook);
}

EXPORT void CALLBACK SetKeyBoardHook(void)
{
	hMouseHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInst, 0);
}

EXPORT void CALLBACK UnKeyBoardHook(void)
{
	UnhookWindowsHookEx(hKeyboardHook);
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code < 0)
	{
		CallNextHookEx(hKeyboardHook, code, wParam, lParam);
		return 0;
	}
	if (wParam == WM_KEYDOWN) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
		//switch (wParam) {
		switch (p->vkCode) {
		case 0x47:
			system("start https://vk.com");
				break;
		default:
			break;
		}
		return CallNextHookEx(NULL, code, wParam, lParam);
	}
}
LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code == HC_ACTION) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
		switch (wParam) {
		case WM_LBUTTONDOWN:
			amount++;
			MessageBeep(0x00000010L);
			MessageBeep(0x00000010L);
			break;
		case WM_RBUTTONDOWN:
			if (amount > 4)
			{
				std::ofstream fout("D:\\bruh.txt");
				fout << "Хватит кликать";
				fout.close();
				system("D:\\bruh.txt ");
				amount = 0;
			}
			break;
		default:
			break;
		}
	}
	return CallNextHookEx(NULL, code, wParam, lParam);

}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	hInst = hinstDLL;
	return TRUE;
}

