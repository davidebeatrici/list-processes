#include <stdbool.h>
#include <stdio.h>

#ifndef UNICODE
# define UNICODE
#endif

#ifndef WIN32_LEAN_AND_MEAN
# define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <tlhelp32.h>

bool utf16ToUtf8(const wchar_t *source, const size_t size, char *destination)
{
	if (!WideCharToMultiByte(CP_UTF8, 0, source, -1, destination, size, NULL, NULL)) {
		printf("WideCharToMultiByte() failed with error %d\n", GetLastError());
		return false;
	}

	return true;
}

int main()
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE) {
		printf("CreateToolhelp32Snapshot() failed with error %d\n", GetLastError());
		return 1;
	}

	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	BOOL ok = Process32First(hSnap, &pe);
	if (!ok) {
		printf("Process32First() failed with error %d\n", GetLastError());
		return 2;
	}

	char name[MAX_PATH];

	while (ok) {
		if (utf16ToUtf8(pe.szExeFile, sizeof(name), name)) {
			printf("[%u] %s\n", pe.th32ProcessID, name);
		} else {
			printf("utf16ToUtf8() failed, skipping entry...\n");
		}

		ok = Process32Next(hSnap, &pe);
	}

	CloseHandle(hSnap);

	return 0;
}
