#include <filesystem>
#include <vector>
#include <thread>
#include <iostream>

void parseDir(const std::filesystem::path& path, std::vector<std::filesystem::path>& files)
{
	// std::cout << "Starting thread for: " << path << '\n';
	std::vector<std::thread> childrenThreads;
	std::vector<std::vector<std::filesystem::path>> childrenFiles;
	for(const auto& file : std::filesystem::directory_iterator(path))
	{
		// std::cout << "Visiting: " << file << '\n';
		files.push_back(file.path());
		if(file.is_directory())
		{
			// std::cout << "In directory: " << file << '\n';
			childrenFiles.emplace_back();
			// childrenThreads.emplace_back([&childrenFiles, file](){
				parseDir(file, childrenFiles.back());
			// });
		}
	}

	for(size_t i = 0; i < childrenThreads.size(); i++)
	{
		// childrenThreads[i].join();
		files.insert(files.end(), childrenFiles[i].begin(), childrenFiles[i].end());
	}
}

int main(int argc, char** argv)
{
	const char* PATH = ".";
	std::vector<std::filesystem::path> files;

	parseDir(std::filesystem::path(PATH), files);

	for(auto& path : files)
		std::cout << path << '\n';
}