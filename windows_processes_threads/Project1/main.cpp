#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "atlstr.h"
#include "cmath"
#include <chrono>
using namespace std::chrono;

struct integralArguments {
	double from;
	double to;
	int polynomialDegree;
	int steps;
	double* result;
};

DWORD WINAPI calculateIntegral(void* arg) {
	integralArguments* arguments = (struct integralArguments*)arg;
	double step = (arguments->to - arguments->from) / arguments->steps;
	double area = 0.0;

	for (int i = 0; i < arguments->steps; i++) {
		area += pow(arguments->from + (i + 0.5) * step, arguments->polynomialDegree) * step;
	}

	*(arguments->result) += area;

	return 0;
}

double calculateIntegralUsingThreads(const double from, const double to, const double polynomialDegree, const int threads) {
	double result = 0;
	HANDLE* hThreads = (HANDLE*)malloc(threads * sizeof(HANDLE));
	integralArguments* arguments = (integralArguments*)malloc(threads * sizeof(integralArguments));

	for (int i = 0; i < threads; i++) {
		arguments[i].from = from + i * double(to / threads);;
		arguments[i].to = from + (i + 1) * (to / threads);
		arguments[i].polynomialDegree = polynomialDegree;
		arguments[i].steps = 500 / threads;
		arguments[i].result = &result;
		hThreads[i] = CreateThread(NULL, 0, &calculateIntegral, (void*)&arguments[i], 0, NULL);
	}

	WaitForMultipleObjects(threads, hThreads, true, INFINITE);

	for (int i = 0; i < threads; i++) {
		CloseHandle(hThreads[i]);
	}

	return result;
}

int main() {
	bool exit = false;
	while (!exit) {
		std::cout << "1 - open Notepad\n";
		std::cout << "2 - calulcate integral chosen in-code on 1-10 threads\n";
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
			int threadsNumbers[10];
			int durrations[10];
			double result;
			for (int i = 0; i < 10; i++) {
				int threadsNumber = i + 1;

				auto start = high_resolution_clock::now();
				result = calculateIntegralUsingThreads(0, 5, 3, threadsNumber);
				auto stop = high_resolution_clock::now();

				auto duration = duration_cast<microseconds>(stop - start);

				durrations[i] = duration.count();
				threadsNumbers[i] = threadsNumber;
			}

			printf("Result: %f\n", result);
			printf("Threads number: \t");
			for (int i = 0; i < 10; i++) {
				printf("%d\t", threadsNumbers[i]);
			}
			printf("\nTime:\t\t\t");
			for (int i = 0; i < 10; i++) {
				printf("%d\t", durrations[i]);
			}
			printf("\n\n");
		}
		else if (option == 3) {
			exit = true;
		}
	}
}