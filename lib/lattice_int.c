#include <time.h>
#include <dlfcn.h>
#include <fstream.h>
#ifndef LATTICE_H
#define LATTICE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A generic error type, 0 means success, nonzero values indicate an error */
typedef int lattice_error_t;

void simple() {
	int ret;
	void* handle;
	void (*base_fn_name)();
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, simple);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name();
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

int single_int(int a) {
	//Manipulating int parameters.
	a *= 2;
	printf("Modified param to %d.\n", param);
	int ret;
	void* handle;
	void (*base_fn_name)(int a);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, single_int);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(int a);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}
int multiple_ints(int a, int b, int c) {
	//Manipulating int parameters.
	a *= 2;
	printf("Modified param to %d.\n", param);
	//Manipulating int parameters.
	b *= 2;
	printf("Modified param to %d.\n", param);
	//Manipulating int parameters.
	c *= 2;
	printf("Modified param to %d.\n", param);
	int ret;
	void* handle;
	void (*base_fn_name)(int a, int b, int c);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, multiple_ints);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(int a, int b, int c);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}
int different_ints(size_t s, uint32_t u, char c) {
	//Manipulating size_t parameters.
	s *= 2;
	printf("Modified param to %d.\n", param);
	int ret;
	void* handle;
	void (*base_fn_name)(size_t s, uint32_t u, char c);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, different_ints);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(size_t s, uint32_t u, char c);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}
int output_int(int a, int b, int* out) {
	//Manipulating int parameters.
	a *= 2;
	printf("Modified param to %d.\n", param);
	//Manipulating int parameters.
	b *= 2;
	printf("Modified param to %d.\n", param);
	int ret;
	void* handle;
	void (*base_fn_name)(int a, int b, int* out);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, output_int);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(int a, int b, int* out);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

lattice_error_t single_string(const char* s) {
	//Manipulating char* parameters.
	char *s_temp = strrev(s);
	printf("Reversed string %s to %s.\n", s, str2);
	strcpy(s, str2);
	int ret;
	void* handle;
	void (*base_fn_name)(const char* s);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, single_string);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(const char* s);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}
lattice_error_t multiple_strings(const char* sa, const char* sb, const char* sc) {
	//Manipulating char* parameters.
	char *sa_temp = strrev(sa);
	printf("Reversed string %s to %s.\n", sa, str2);
	strcpy(sa, str2);
	//Manipulating char* parameters.
	char *sb_temp = strrev(sb);
	printf("Reversed string %s to %s.\n", sb, str2);
	strcpy(sb, str2);
	//Manipulating char* parameters.
	char *sc_temp = strrev(sc);
	printf("Reversed string %s to %s.\n", sc, str2);
	strcpy(sc, str2);
	int ret;
	void* handle;
	void (*base_fn_name)(const char* sa, const char* sb, const char* sc);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, multiple_strings);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(const char* sa, const char* sb, const char* sc);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

/* Modifies the string, but not past its strlen() */
lattice_error_t modify_string(char* s) {
	//Manipulating char* parameters.
	char *s_temp = strrev(s);
	printf("Reversed string %s to %s.\n", s, str2);
	strcpy(s, str2);
	int ret;
	void* handle;
	void (*base_fn_name)(char* s);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, modify_string);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(char* s);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

/* Takes a read-only input buffer buf with size len */
lattice_error_t single_buffer(const void *buf, size_t len) {
	//Manipulating size_t parameters.
	len *= 2;
	printf("Modified param to %d.\n", param);
	int ret;
	void* handle;
	void (*base_fn_name)(const void *buf, size_t len);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, single_buffer);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(const void *buf, size_t len);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

/* Fills an output buffer buf up to size len */
lattice_error_t modify_buffer(int a, void *buf, size_t len) {
	//Manipulating int parameters.
	a *= 2;
	printf("Modified param to %d.\n", param);
	//Manipulating size_t parameters.
	len *= 2;
	printf("Modified param to %d.\n", param);
	int ret;
	void* handle;
	void (*base_fn_name)(int a, void *buf, size_t len);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, modify_buffer);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(int a, void *buf, size_t len);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

/* These are not buffers, but just pointers to random memory, and never read or written to */
lattice_error_t just_pointers(const void* pa, void* pb) {
	int ret;
	void* handle;
	void (*base_fn_name)(const void* pa, void* pb);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, just_pointers);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(const void* pa, void* pb);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

/*
 * The output string out_name will be modified, but not past its strlen().
 * The buffers buf and out_buf will be read and written into, but not past len
 */
lattice_error_t kitchen_sink(int a, const char* name, char* out_name, const void* buf, void* out_buf, size_t len) {
	//Manipulating int parameters.
	a *= 2;
	printf("Modified param to %d.\n", param);
	//Manipulating char* parameters.
	char *name_temp = strrev(name);
	printf("Reversed string %s to %s.\n", name, str2);
	strcpy(name, str2);
	//Manipulating char* parameters.
	char *out_name_temp = strrev(out_name);
	printf("Reversed string %s to %s.\n", out_name, str2);
	strcpy(out_name, str2);
	//Manipulating size_t parameters.
	len *= 2;
	printf("Modified param to %d.\n", param);
	int ret;
	void* handle;
	void (*base_fn_name)(int a, const char* name, char* out_name, const void* buf, void* out_buf, size_t len);
	handle = dlopen("./liblatticeinterposed.so", RTLD_NOW);
	*(void*)(base_fn_name) = dlsym(handle, kitchen_sink);
	 if (!base_fn_name) {
		printf("Error");
		dlclose(handle);
		return 0;
	}
	ret = base_fn_name(int a, const char* name, char* out_name, const void* buf, void* out_buf, size_t len);
	dlclose(handle);
	FILE* fout;
	fout = fopen("lattice_lib.log", "w+");
	struct tm* current_time; time_t s;
	s = time(NULL);
	current_time = localtime(&s);
	fprintf(fout, "%d:%d:%d::%s%s",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, fn_sign);
	fprintf(fout, "%d:%d:%d::%s::return value = %d",current_time->tm_hour, current_time->tm_min, current_time->tm_sec, fn_name, ret);
	fclose(fout);

	return ret;
}

#ifdef __cplusplus
}
#endif

#endif // LATTICE_H

