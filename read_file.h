#include <stdio.h>
#include <stdlib.h>
#pragma once

char* readFile(const char* file, size_t* len)
{
	FILE* f = fopen(file, "rb");
	if (f == 0) return 0;

	fseek(f, 0, SEEK_END);
	*len = ftell(f);

	fseek(f, 0, SEEK_SET);

	char* data = new char[*len];
	fread(data, 1, *len, f);
	fclose(f);

	return data;
}