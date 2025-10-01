#include "io/file_io.hpp"

#include <filesystem>
#include <fstream>
#include <format>
#include <iostream>

using namespace IO;

std::vector<char> FileIO::read(const std::string& filename)
{
	size_t size = fileSize(filename);

	std::ifstream file(filename, std::ios::binary);
	if (!file) throw std::runtime_error(std::format("cannot open file \"{}\".", filename));

	std::vector<char> buffer;
	buffer.resize(size);
	if (!file.read(buffer.data(), size)) throw std::runtime_error(std::format("read of file \"{}\" failed.", filename));

	file.close();
	return buffer;
}

size_t FileIO::fileSize(const std::string& filename)
{
	try
	{
		return std::filesystem::file_size(filename);
	}
	catch (std::exception& e)
	{
		throw std::runtime_error(std::format("cannot find file \"{}\": {}", filename, e.what()));
	}
}

void FileIO::write(const std::string& contents, const std::string& filename)
{
	std::ofstream file(filename, std::ios::binary);
	if (!file) throw std::runtime_error(std::format("cannot write to file \"{}\".", filename));

	file.write(contents.data(), contents.size());
	if (!file.good()) throw std::runtime_error(std::format("cannot write to file \"{}\".", filename));

	file.flush();
	file.close();
}
