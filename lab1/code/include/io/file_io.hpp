#pragma once

#include <string>
#include <vector>

namespace IO
{
	class FileIO
	{
	private:
		static size_t fileSize(const std::string& filename);
	public:
		static std::vector<char> read(const std::string& filename);
		static void write(const std::string& contents, const std::string& filename);
	};
}
