#ifndef TEST_FILE_CPP
#define TEST_FILE_CPP

#include "file.h"
#include <iostream>
#include <fstream>

File::File(const char* filename):
m_filename(filename),
m_content("")
{
	std::cout << "File constructor" << std::endl;

	std::string line;

	std::ifstream myfile(m_filename);
	
	if (myfile.is_open()){
		while ( getline (myfile,line) ){
			m_content += line;
			m_content += "\n";
    	}
    	myfile.close();
  	}
  	else std::cout << "Unable to open file" << std::endl;

}

std::string File::Get(){
	return m_content;
}

File::~File(){
	std::cout << "File destructor" << std::endl;
}

#endif