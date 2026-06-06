#pragma once

#include <fstream>
#include <sstream>
#include <filesystem>
#include <system_error>

#include <string>
#include <vector>
#include <cstdint>

#include "err_codes.h"

// Реализация для Windows
class wFiles : public iFiles 
{
public:
    // Проверка существования файла (и что это именно файл, а не директория)
    ErrC exists(const std::string& path) const override 
	{
        std::error_code ec;
        if (!std::filesystem::exists(path, ec)) 
		{
            if (ec) return ErrC::UNKNOWN_ERROR;
            return ErrC::FILE_NOT_FOUND;
        }
        if (!std::filesystem::is_regular_file(path, ec)) 
		{
            return ErrC::NOT_A_FILE;
        }
        return ErrC::SUCCESS;
    }

    // Чтение текстового файла (кодировка: системная ANSI/UTF-8, без BOM)
    ErrC readText(const std::string& path, std::string& text) const override 
	{
        // Сначала проверяем, что файл существует и является файлом
        ErrC ec = exists(path);
        if (ec != ErrC::SUCCESS) return ec;

        std::ifstream ifs(path);
        if (!ifs.is_open()) 
		{
            return ErrC::PERMISSION_DENIED;
        }

        // Читаем весь файл в строку через streambuf
        std::stringstream buffer;
        buffer << ifs.rdbuf();
        if (ifs.bad()) 
		{
            return ErrC::READ_ERROR;
        }
        text = buffer.str();
        return ErrC::SUCCESS;
    }

    // Запись текстового файла (создаётся или перезаписывается)
    ErrC writeText(const std::string& path, const std::string& text) override 
	{
        // Опционально: проверить, что путь не указывает на существующую директорию
        std::error_code ec;
        if (std::filesystem::exists(path, ec) && std::filesystem::is_directory(path, ec)) 
		{
            return ErrC::NOT_A_FILE;
        }

        std::ofstream ofs(path);
        if (!ofs.is_open()) 
		{
            return ErrC::PERMISSION_DENIED;
        }
        ofs << text;
        if (ofs.fail()) 
		{
            return ErrC::WRITE_ERROR;
        }
        return ErrC::SUCCESS;
    }

    // Чтение бинарного файла
    ErrC readBinary(const std::string& path, std::vector<uint8_t>& data) const override 
	{
        ErrC ec = exists(path);
        if (ec != ErrC::SUCCESS) return ec;

        std::ifstream ifs(path, std::ios::binary);
        if (!ifs.is_open()) 
		{
            return ErrC::PERMISSION_DENIED;
        }

        // Определяем размер файла
        ifs.seekg(0, std::ios::end);
        std::streamsize size = ifs.tellg();
        if (size == -1) {
            return ErrC::READ_ERROR;
        }
        ifs.seekg(0, std::ios::beg);

        data.resize(static_cast<size_t>(size));
        if (!ifs.read(reinterpret_cast<char*>(data.data()), size)) 
		{
            return ErrC::READ_ERROR;
        }
        return ErrC::SUCCESS;
    }

    // Запись бинарного файла
    ErrC writeBinary(const std::string& path, const std::vector<uint8_t>& data) override 
	{
        std::error_code ec;
        if (std::filesystem::exists(path, ec) && std::filesystem::is_directory(path, ec)) 
		{
            return ErrC::NOT_A_FILE;
        }

        std::ofstream ofs(path, std::ios::binary);
        if (!ofs.is_open()) 
		{
            return ErrC::PERMISSION_DENIED;
        }
        ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
        if (ofs.fail()) 
		{
            return ErrC::WRITE_ERROR;
        }
        return ErrC::SUCCESS;
    }
};