// Copyright © 2024 Souto-Naitou. All rights reserved.
// Licensed under the MIT License. See License.txt in the project root for license information.


#include "CSVLoader.h"

#include <fstream>
#include <sstream>
#include <filesystem>
#include <Windows.h>

CSVData* CSVLoader::LoadFile(std::string _fileName)
{
	/// ファイルがすでにロードされていたらりーたん
	for (auto& file : fileData_)
	{
		if (file.first.compare(_fileName) == 0) // 0のときは合致
		{
			return &file.second;
		}
	}

	/// ファイルを読み込む
	std::stringstream fileStream;
	std::ifstream file;
	std::string path = directory_ + _fileName;
	file.open(path);
	if (!file.is_open())
	{
		std::ofstream ofile(path, std::ios::out);
		ofile.close();
		file.open(path);
	}
	fileStream << file.rdbuf();
	file.close();

	/// 中身を保存
	std::string line;
	fileData_.push_back({ _fileName, CSVData() });
	while (std::getline(fileStream, line))
	{
		std::stringstream lineStream(line);
		std::string word;
		// １行分確保
		fileData_.back().second.push_back({});
		while (std::getline(lineStream, word, ','))
		{
			// wordを追加
			fileData_.back().second.back().push_back({});
			fileData_.back().second.back().back() << word;
		}
	}

	return &fileData_.back().second;
	
}

CSVLine* CSVLoader::GetLine(std::string _fileName, std::string _ID)
{
	for (auto& file : fileData_)
	{
		if (file.first.compare(_fileName) == 0)
		{
			for (auto& line : file.second)
			{
				if (line[0].str().compare(_ID) == 0)
				{
					return &line;
				}
			}
		}
	}
	return nullptr;
}

CSVLine* CSVLoader::GetNewLine(std::string _fileName)
{
	for (auto& file : fileData_)
	{
		if (file.first.compare(_fileName) == 0)
		{
			file.second.push_back({});
			return &file.second.back();
		}
	}
	return nullptr;
}

void CSVLoader::SaveFile()
{
	std::filesystem::path dir(directory_);
	if (!std::filesystem::exists(dir)) 
	{
		std::filesystem::create_directory(dir);
	}

	for (auto& file : fileData_)
	{

		std::string path = directory_ + file.first;
		std::ofstream ofile;
		ofile.open(path, std::ios::out | std::ios::trunc);
		if (!ofile.is_open())
		{
			MessageBoxA(nullptr, "ファイル書き込みに失敗", "CSVLoader.SaveFile", 0);
			return;
		}

		for (auto& line : file.second)
		{
			for (auto& word : line)
			{
				ofile << word.str() << ',';
			}
			ofile << '\n';
		}
		ofile.close();
	}

	return;
}

void CSVLoader::SaveLine(std::string _fileName, CSVLine& _line)
{
	std::filesystem::path dir(directory_);
	if (!std::filesystem::exists(dir))
	{
		std::filesystem::create_directory(dir);
	}

	std::string path = directory_ + _fileName;
	std::ofstream ofile(path, std::ios::app);
	if (!ofile.is_open())
	{
		MessageBoxA(nullptr, "ファイル書き込みに失敗", "CSVLoader.SaveLine", 0);
		return;
	}
	for (auto& word : _line)
	{
		ofile << word.str() << ",";
	}
	ofile << '\n';
	ofile.close();
	return;
}

CSVLoader::~CSVLoader()
{
	SaveFile();
}
