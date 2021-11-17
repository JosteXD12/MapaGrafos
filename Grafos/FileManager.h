
#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

 //una clasilla para el manejo de archivos
enum OPERATION {WRITE=0, READ};
class FileManager
{
private:
	fstream write_file;
	ifstream read_file;
	string string_line;
	bool end_of_line;
	bool end_of_file;
	int char_pos;
	OPERATION operation;
public:
	FileManager(OPERATION operation, string file_path);
	string getThisLine();
	void loadLine();
	bool isEndOfLine();
	void pushLine(string new_line);
	bool isEndOfFile();
	char nextChar();
	bool isFileFine();
	void end();
};


#endif // !FILE_MANAGER_H
