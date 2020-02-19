
#include "stdwin.h"

class WriteInfoAboutCatalog
{

private:

	std::mutex m_lock;
	std::ofstream m_file_stream;
	std::string m_file_path;

public:

	WriteInfoAboutCatalog(const std::string& file_path);
	void write(const std::string& writeStr);
};

WriteInfoAboutCatalog::WriteInfoAboutCatalog(const std::string& file_path) :
	m_file_path(file_path)
{
	m_file_stream.open(m_file_path.c_str());
	if (!m_file_stream.is_open() || !m_file_stream.good())
	{
		//throw relevant exception.
	}
}

void WriteInfoAboutCatalog::write(const std::string& writeStr)
{
	std::lock_guard<std::mutex> lock(m_lock);
	m_file_stream << writeStr << '\n';
}