/*
// Пример 2

#include <windows.h>
#include <stdio.h>
CRITICAL_SECTION cs;
int a[5];
HANDLE hThr;
unsigned long uThrID;

void Thread(void* pParams)
{
	int i, num = 0;
	while (1)
	{
		EnterCriticalSection(&cs);
		for (i = 0; i < 5; i++) a[i] = num;
		num++;
		LeaveCriticalSection(&cs);
	}
}

int main(void)
{
	InitializeCriticalSection(&cs);
	hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &uThrID);
	while (1)
	{
		EnterCriticalSection(&cs);
		printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
		LeaveCriticalSection(&cs);
	}
	return 0;
}
*/

// Пример 3
// 
//#include <windows.h>
//#include <stdio.h>
//HANDLE hMutex;
//int a[5];
//HANDLE hThr;
//unsigned long uThrID;
//
//void Thread(void* pParams)
//{
//	int i, num = 0;
//	while (1)
//	{
//		WaitForSingleObject(hMutex, INFINITE);
//		for (i = 0; i < 5; i++) a[i] = num;
//		num++;
//		ReleaseMutex(hMutex);
//	}
//}
//
//int main(void)
//{
//	hMutex = CreateMutex(NULL, FALSE, NULL);
//	hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &uThrID);
//	while (1)
//	{
//		WaitForSingleObject(hMutex, INFINITE);
//		printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
//		ReleaseMutex(hMutex);
//	}
//	return 0;
//}

//Пример 4
//#include <windows.h>
//#include <stdio.h>
//HANDLE hEvent1, hEvent2;
//int a[5];
//HANDLE hThr;
//unsigned long uThrID;
//void Thread(void* pParams)
//{
//	int i, num = 0;
//	while (1)
//	{
//		WaitForSingleObject(hEvent2, INFINITE);
//		for (i = 0; i < 5; i++) a[i] = num;
//		num++;
//		SetEvent(hEvent1);
//	}
//}
//
//int main(void)
//{
//	hEvent1 = CreateEvent(NULL, FALSE, TRUE, NULL);
//	hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
//	hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &uThrID);
//	while (1)
//	{
//		WaitForSingleObject(hEvent1, INFINITE);
//		printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
//		SetEvent(hEvent2);
//	}
//	return 0;
//}

//Пример 5
//#include <windows.h>
//#include <stdio.h>
//HANDLE hSem;
//int a[5];
//HANDLE hThr;
//unsigned long uThrID;
//
//void Thread(void* pParams)
//{
//	int i, num = 0;
//	while (1)
//	{
//		WaitForSingleObject(hSem, INFINITE);
//		for (i = 0; i < 5; i++) a[i] = num;
//		num++;
//		ReleaseSemaphore(hSem, 1, NULL);
//	}
//}
//
//int main(void)
//{
//	hSem = CreateSemaphore(NULL, 1, 1, L"MySemaphore1");
//	hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &uThrID);
//	while (1)
//	{
//		WaitForSingleObject(hSem, INFINITE);
//		printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
//		ReleaseSemaphore(hSem, 1, NULL);
//	}
//	return 0;
//}
