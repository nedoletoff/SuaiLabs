#pragma once

class String
{
	private:
		char* string;
		int size;
	public:
		String();
		String(char*, int);
		~String();
		String(String&);
	        String& operator=(const String&);
//	      	String& operator-(String&);
		const String operator-(const String&);
		int len();
		int add_string(char* str, int str_size = -1);
		int remove(int, int);
		int remove(int);
		void print();
		void insert(char);
		void conc(String&);
};
