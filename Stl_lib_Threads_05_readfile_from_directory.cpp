#include "stdwin.h"
#include ".\StructInfoFile.h"
#include ".\Read_File_From_Directory.h"
#include ".\ParseFile.h"
#include ".\Write_to_file.h"
#include ".\WorkersParse.h"

concurrency::concurrent_vector<StructInfoFile> cv;
int main(int argc, char* argv[])
{
    std::cout << "Hello World!\n";
	std::string path2;
	if (!argv) {
		path2 =argv[1];
		cout << path2 << endl;
	}
		
	string addprefCat = "*";
	string addprefFile = "";
	string path_ = "D:\\_V2020_\\_Rabota_2020__\\_elveesneotek_com__\\cat\\";
	vector<StructInfoFile> v;
	v = scandir(path_, addprefCat);

	concurrency::concurrent_vector<StructInfoFile> cv;
	for (int i = 0; i < v.size(); i++)
	{
		cv.push_back(v[i]);
		std::cout<< "{"<<i<<"}: " << v[i].fileName << "\n";
	}

	WorkersParse wp(cv);

    std::cout << "Press key!\n";
    getchar();
	return 0;
}
