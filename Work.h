#pragma once
#include ".\stdwin.h"
#include ".\ParseFile.h"
#include ".\Write_to_file.h"
#include ".\StructInfoFile.h"

class Work
{
public:	
	explicit Work() {	}
	
	explicit Work(StructInfoFile& _sf)
	{
		sf = _sf;
	}
	StructInfoFile sf;

	Work& operator=(const Work& rhs) 
	{  
		Work w;
		w.sf = sf;
		return w;		
	}

	void Save()
	{
		string pth = sf.path + sf.fileName;
		ParseFile pf;
		pf.ParsingFile(pth);
		vector<string> parse_stroki = pf.Get_ParsingStroki();
		WriteInfoAboutCatalog writeInfoCatalog;

		writeInfoCatalog.write("[" + sf.fileName + "]");		
		for (int i = 1; i < parse_stroki.size(); i++)
		{
			writeInfoCatalog.write(parse_stroki[i] + "");
		}
	};
};
