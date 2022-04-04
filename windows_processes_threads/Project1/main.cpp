#include <Windows.h>
#include <stdio.h>
#include "atlstr.h"
#include "cmath"

/*HANDLE process;

int main() {
	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	char a[] = "notepad";
	USES_CONVERSION;
	TCHAR* b = A2T(a);

	if (CreateProcess(NULL, b, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}
	return 0;
}*/

struct toThreads {
	double from;
	double to;
	double degree;
};

int main() {
	const int n = 5;
	double from = 0;
	for (int i = 0; i < 2; i++) {
		toThreads str = { from, (i + 1) / 5, 3 };
		if (HANDLE hThread = CreateThread(NULL, 0, calculate_integral, (void*)&str, 0, NULL)) {
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		}
		from = (i + 1) / 5;
	}

	double from = 0;
	for (int i = 0; i < 4; i++) {
		toThreads str = { from, (i + 1) / 5, 3 };
		if (HANDLE hThread = CreateThread(NULL, 0, calculate_integral, (void*)&str, 0, NULL)) {
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		}
		from = (i + 1) / 5;
	}
}

DWORD WINAPI calculate_integral(void* arg) {
	toThreads test = (struct toThreads*)arg;
	return integral((struct toThreads*) arg, arg.to, 100);
}

double integral(double a, double b, int n) {
	double step = (b - a) / n;
	double area = 0.0;
	for (int i = 0; i < n; i++) {
		area += exp(cos(a + (i + 0.5) * step)) * step;
	}
	return area;
}