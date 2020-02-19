#pragma once
#include ".\stdwin.h"

class StructInfoFile
{
public: 
	string path;
	string fileName;
	StructInfoFile()
	{

	}

	void SetNameFile(string path, string fileName)		
	{
		this->path=path;
		this->fileName = fileName;

	}

	/*StructInfoFile& operator=(const StructInfoFile& rhs)
	{
		StructInfoFile sf;		
		sf.path = rhs.path;
		sf.fileName = rhs.fileName;
		return sf;
	}*/
};