
#include "sigs.h"

DWORD Findrekt(std::string moduleName, std::string Mask)
{
	const char* pat = Mask.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
		{
			return firstMatch;
		}
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
			{
				firstMatch = pCur;
			}

			if (!pat[2])
			{
				return firstMatch;
			}


			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
			{
				pat += 3;
			}
			else
			{
				pat += 2; //one ?
			}

		}
		else
		{
			pat = Mask.c_str();
			firstMatch = 0;
		}
	}
	return NULL;
}

bool streq(const char *s1, const char *s2)
{
	for (; *s1 == *s2; s1++, s2++)
	{
		if (*s1 == '\0')
			return true;
	}

	return false;
}

void *FindString(void *ptr, const char *string)
{
	char *start;
	char *str = nullptr;

	for (start = (char *)ptr; str == nullptr; start++)
	{
		if (streq(start, string))
			str = start;
	}

	while (1)
	{
		if (*(char **)start == str)
			return start;

		start--;
	}

	return nullptr;
}

void *FindPattern(void *start, unsigned int len, const pattern *data)
{
	const char *pattern = (char *)data + 5;
	const char *q = (char *)start;

	for (int i = 0, mask = *(int *)((char *)data + 1); i < len; i++, q++)
	{
		const char *seq = pattern;
		const char *mem = q;


		register bool g = true;

		for (int x = 0; x < 32; x++)
		{
			if ((mask & (1 << x)) && (mem[x] != *seq++))
			{
				g = false;
				break;
			}
		}

		if (g) return (void *)(q + (int)*(unsigned char *)data);
	}

	return nullptr;
}

void *FindPattern(const char *l, const pattern *data)
{
	return FindPattern(GetModuleHandle(l), -1, data);
}

void *FindProlog(void *ptr)
{
	unsigned char *ins = (unsigned char *)ptr;

	while (ins > 0)
	{
		if ((ins[0] & 0xf0) == 0x50 &&
			(ins[1] & 0xf0) == 0x80 &&
			(ins[2] & 0x0f) == 0x0c)
		{
			return ins;
		}

		ins--;
	}

	return nullptr;
}
