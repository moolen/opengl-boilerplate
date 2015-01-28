#ifndef TEST_FILE_H
#define TEST_FILE_H

#include <string>

class File{
public:
	File(const char* filename);
	std::string Get();
	virtual ~File();

protected:
	const char* m_filename;
	std::string m_content;
};


#endif