#ifndef FILE_UTIL_H
#define FILE_UTIL_H

void file_gen(char *p_filename, size_t size);
int* read_file(char *p_filename, int* arr);
void write_file(char* p_filename, int* arr);

#endif
