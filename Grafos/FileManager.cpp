#include "Components.h"
#include <fstream>
using namespace std;

FileManager::FileManager(OPERATION op, string file_path)
{
	try
	{
		switch (op)
		{
		case WRITE:
			write_file.open(file_path, ios::out);
			break;
		case READ:
			read_file.open(file_path);
			break;
		default:
			throw "OPERACION INCORRECTA PARA MANEJO DE ARCHIVOS";
			break;
		}
		string_line = "";
		char_pos = 0;
		operation = op;
		end_of_file = false;
		end_of_line = false;
	}
	catch (const char* e)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << e;
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
}

string FileManager::getThisLine()
{
	if (string_line.compare("")==0)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << "NO SE CARGO NINGUNA LINEA DEL ARCHIVO ANTES, NO SE PERMITE NINGUNA LLAMADA A getThisLine()";
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
	return string_line;
}

void FileManager::loadLine()
{
	try
	{
		if (operation == WRITE)
		{
			throw "LA OPERACION A EJECUTAR ES READ, NO SE PUEDE EJECUTAR OTRA OPERACION EN ESTA INSTANCIA";
		}
		if (end_of_file)
		{
			throw "YA SE LLEGO AL FINAL DEL ARCHIVO NO SE PERMITEN MAS LLAMADAS A loadLine()";
		}
		getline(read_file, string_line);
		char_pos = 0;
		end_of_line = false;
		if (read_file.eof())
		{
			end_of_file = true;
		}
	}
	catch (const char* e)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << e;
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
}

bool FileManager::isEndOfLine()
{
	return end_of_line;
}

void FileManager::pushLine(string ss)
{
	if (operation == OPERATION::READ)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << "LA OPERACION ACTUAL ES READ NO SE PERMITEN LLAMADAS A pushLine()";
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}
	else
	{
		cout << ss;
		ss += "\n";
		write_file << ss;
	}
}

bool FileManager::isEndOfFile()
{
	return end_of_file;
}

char FileManager::nextChar()
{
	try
	{
		if (operation == WRITE)
		{
			throw "LA OPERACION A EJECUTAR ACTUAL ES - READ - || NO SE PUEDE EJECUTAR OTRA OPERACION EN ESTA INSTANCIA";
		}
		if (end_of_line)
		{
			throw "YA SE LLEGO AL FINAL DE ESTA LINEA NO SE PERMITEN MAS LLAMADAS A nextChar()";
		}
		char a = string_line[char_pos];
		char_pos++;
		if (char_pos == string_line.length())
		{
			end_of_line = true;
		}
		return a;
	}
	catch (const char* e)
	{
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		cout << e;
		cout << "\n\nEXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION EXCEPTION\n\n";
		abort();
	}

}

bool FileManager::isFileFine()
{
	switch (operation)
	{
	case WRITE:
		return write_file.is_open();
	case READ:
		return !read_file.fail();
	default:
		cout << "UN ERROR EN FileManager\n";
		abort();
		break;
	}
}

void FileManager::end()
{
	switch (operation)
	{
	case WRITE:
		write_file.close();
		break;
	case READ:
		read_file.close();
		break;
	default:
		break;
	}
}
