#pragma once

#include <Windows.h>
#include <vector>
#include <Psapi.h>

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

class pattern;

DWORD Findrekt(std::string moduleName, std::string Mask);
void *FindString(void *, const char *);
void *FindProlog(void *);
void *FindPattern(void *, unsigned int, const pattern *);
void *FindPattern(const char *, const pattern *);