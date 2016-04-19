#include "fstream"
#include "string"
#include "ctype.h"
#include "stdio.h"

#ifndef baseFile_H_INCLUDED
#define baseFile_H_INCLUDED
class baseFile
{
protected:
	std::string filename;
	std::fstream file;
	int data[5];
	char ch;
	std::string filestring;

public:
	baseFile(baseFile &obj)
	{
		filename = obj.filename;
		ch = obj.ch;
		for(int i=0;i<5;i++)
			data[i] = obj.data[i];
		filestring = obj.filestring;
	}
	baseFile() {}
	void openFile(std::string name)
	{
		int ifDat = checkIfDat(name.c_str());
		if(ifDat == true)
			file.open(name,std::ios::in|std::ios::binary);
		else
			file.open(name,std::ios::in);
		filename = name;
		if(!ifDat)
			readFile();
		else
			filename = name;

	}
	void createFile(std::string name)
	{
		int datFile = checkIfDat(name.c_str());
		if(datFile)
			file.open(name,std::ios::out|std::ios::binary);
		else
			file.open(name,std::ios::out);
		file.close();
		filename = name;

	}
	int checkIfDat(const char *name)
	{
		for(int i=0;name[i] != '\0';i++)
		{
			if(name[i] == '.')
			{
				if(tolower(name[++i]) =='d')
					if(tolower(name[++i]) == 'a')
						if(tolower(name[++i]) == 't')
							return true;
			}
		}
		return false;
	}
	int appendLast(std::string value)
	{
		int datFile = checkIfDat(filename.c_str());
		if(!datFile)
			file.open(filename,std::ios::app);
		if(!file)
			return false;
		if(!datFile)
			file<<value;
		
		file.close();
		return true;

	}
	int deleteIt()
	{
		if(remove(filename.c_str()) == 0)
			return true;
		else
			return false;
	}
	void readFile()
	{
		file.get(ch);
		while(!file.eof())
		{
			filestring.push_back(ch);
			file.get(ch);
		}
		
	}

	std::string giveString()
	{
		return filestring;
	}
	int count()
	{
		return filestring.size();
	}
	baseFile select(int from,int to)
	{
		data[0] = from;
		data[1] = to;
		data[2] = to-from+1;
		return *this;
	}
	template<class Type>
	Type read(Type obj,int post)
	{
		file.open(filename,std::ios::in|std::ios::binary);
		file.seekg(post*sizeof(obj));
		file.read((char*)&obj,sizeof(obj));
		file.close();
		return obj;
	}
	template<class Type>
	int totalRecords(Type obj)
	{
		if(!checkIfDat(filename.c_str()))
			return false;
		file.open(filename,std::ios::in|std::ios::binary);
		int count =0;
		file.seekg(0,std::ios::end);
		count = file.tellg();
		file.close();
		return count/sizeof(obj);
	}
	template<class Type>
	void appendData(Type obj)
	{
		if(checkIfDat(filename.c_str()) != true)
			return;
		file.open(filename,std::ios::app|std::ios::binary);
		file.write((char*)&obj,sizeof(obj));
		file.close();
	}
	template<class Type>
	int deleteRecord(Type obj,int recordNumber)
	{
		if(!fileExists(filename))
			return false;

		file.open(filename,std::ios::in|std::ios::binary);
		std::ofstream fileTemp("temp.dat",std::ios::binary);
		if(!fileTemp)
			return false;
		int record = 1;
		file.read((char*)&obj,sizeof(obj));
		while(!file.eof())
		{
			if(record != recordNumber)
			{	
				
				fileTemp.write((char*)&obj,sizeof(obj));
			}
				file.read((char*)&obj,sizeof(obj));
			record++;

		}
		file.close();
		fileTemp.close();
		remove(filename.c_str());
		rename("temp.dat",filename.c_str());

		if(fileExists(filename))
			return true;
		else
			return false;

	}
	int fileExists(std::string file)
	{
		if(checkIfDat(file.c_str()))
		{
			std::ifstream fileTarget(file,std::ios::binary);
			if(!fileTarget)
				return false;
		}
		else
		{
			std::ifstream fileTarget(file);
			if(!fileTarget)
				return false;
		}
		return true;
	}
	void setName(std::string name)
	{
		filename = name;
	}
	baseFile reName(std::string from,std::string to)
	{
		rename(filename.c_str(),to.c_str());
		filename = to;
		return *this;
	}
};
class File
{

public:

	baseFile static create(std::string name)
	{
		baseFile _file;
		// Truncates everything 
		_file.createFile(name);
		return _file;
	}
	baseFile static createOnly(std::string name)
	{
		baseFile _file;
		/* This method use to create file if not exsist. return false if already exist */
		std::ifstream file(name,std::ios::in);
		if(file)
		{
			_file.setName(name);
			return _file;	
		}
		else
		{
			_file.createFile(name);
			return _file;
		}
	}
	baseFile static get(std::string name)
	{
		baseFile _file;
		 _file.openFile(name);
		return _file;
	}
	baseFile static select(std::string name)
	{
		baseFile _file;
		_file.setName(name);
		return _file;
	}

};

#endif
