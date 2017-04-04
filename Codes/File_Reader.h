#ifndef _FILE_READER_H
#define _FILE_READER_H

#include "includes.h"

class File_Reader {
private:
	FILE * file;
public:
	File_Reader() {
		
	}
	File_Reader(string file_name) {
		file = fopen(file_name.c_str(), "r");
		if (file == NULL)
			printf("File Reader Error: \'%s\' not found!\n", file_name.c_str());
	}
	bool getString(char * str) {
		return fscanf(file, "%s", str) != EOF; 
	}
	~File_Reader() {
		fclose(file);
	}
};

#endif