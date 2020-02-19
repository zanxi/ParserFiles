#include "stdwin.h"
#include ".\StructInfoFile.h"
#include ".\Read_File_From_Directory.h"
#include ".\ParseFile.h"
#include ".\Write_to_file.h"
#include ".\WorkersParse.h"

concurrency::concurrent_vector<StructInfoFile> cv;
int main(int argc, char* argv[])
{
    std::cout << "Parser files!\n";
	std::string path_;
	if (argc==1) {
		//path2 =argv[1];
		std::cout << "Exit press key - No arguments?????????!!!!!!!!\n";
		getchar();
		cout << path_ << endl;
		return 0;
	}
	path_ = argv[1];

	for (int i = 0; i < argc; ++i) {
		string str = argv[i];
		std::cout << str << std::endl;
	}
		
	string callSymb = "\\";
	string addprefCat = "*";
	string addprefFile = "";	
	//path_ = "D:\\md\\pr-master\\";	
	vector<StructInfoFile> v;
	v = scandir(path_+callSymb, addprefCat); // создание списка файлов каталога

	concurrency::concurrent_vector<StructInfoFile> cv;
	for (int i = 0; i < v.size(); i++)
	{
		cv.push_back(v[i]);
		std::cout<< "{"<<i<<"}: " << v[i].fileName << "\n";
	}
	ResetFile("hd.txt");
	WorkersParse wp(cv); // передача парсеру списка файлов каталога

    std::cout << "Press key!\n";
    getchar();
	return 0;
}
