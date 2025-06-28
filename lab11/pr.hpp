#pragma once
#define SIZE 50
#define N 256


void get_filename(char*);
int open_file(char*);
void read_and_pull(char*, char***, int);
void print_words(char**, int);
int count_words(char*);
