#pragma once
#include <fstream>
#include <iostream>
#include <filesystem>

const std::string read_file(const std::string& filePath)
{
    if (!std::filesystem::exists(filePath))
    {
        std::cerr << "file '"+filePath+"' does not exist\n";
        exit(1);
    }

    std::ifstream file(filePath);
    std::string output, content;

    if (file.peek() == std::ifstream::traits_type::eof())
        return "";

    while (std::getline(file, output)) content+=output+'\n';
    content.pop_back();

    return content;
}

void write_file(const std::string& filePath, const std::string& text)
{
    std::ofstream file(filePath);
    file << text;
}

void append_file(const std::string& filePath, const std::string& text)
{
    std::ofstream file(filePath, std::ios_base::app);
    file << text;
}
