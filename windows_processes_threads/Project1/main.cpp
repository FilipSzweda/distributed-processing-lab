#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "atlstr.h"
#include "cmath"

double integral;

struct integralArguments {
	double from;
	double to;
	int polynomialDegree;
	double& result;
};

DWORD WINAPI calculateIntegral(void* arg) {
	integralArguments* arguments = (struct integralArguments*)arg;
	int steps = 100;
	double step = (arguments->to - arguments->from) / steps;
	double area = 0.0;

	for (int i = 0; i < steps; i++) {
		area += pow(arguments->from + (i + 0.5) * step, arguments->polynomialDegree) * step;
	}

	arguments->result += area;

	return 0;
}

double calculateIntegralUsingThreads(const double from, const double to, const double polynomialDegree, const int threads) {
	double start = 0;
	double *result = &start;

	for (int i = 0; i < threads; i++) {
		double partialFrom = from + i * double (to / threads);
		double partialTo = from + (i + 1) *  (to / threads);
		integralArguments arguments = { partialFrom, partialTo, polynomialDegree, *result};

		if (HANDLE hThread = CreateThread(NULL, 0, calculateIntegral, (void*)&arguments, 0, NULL)) {
			WaitForSingleObject(hThread, INFINITE);
			CloseHandle(hThread);
		}
	}

	return *result;
}

int main() {
	bool exit = false;
	while (!exit) {
		std::cout << "1 - open Notepad\n";
		std::cout << R"(2 - calulcate following integrals (you can choose any other in-code):
	from: 0, to: 5, polynomial degree: 3 (on 2 threads)
	from: 0, to: 5, polynomial degree: 3 (on 4 threads)
)";
		std::cout << "3 - exit\n";

		int option;
		std::cin >> option;

		if (option == 1) {
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
		}
		else if (option == 2) {
			double results[2] = {
				calculateIntegralUsingThreads(0, 5, 3, 2),
				calculateIntegralUsingThreads(0, 5, 3, 4)
			};
			std::cout << "First result: " << results[0] << ", second result: " << results[1] << std::endl;
		}
		else if (option == 3) {
			exit = true;
		}
	}
}