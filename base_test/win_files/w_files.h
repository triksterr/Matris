#pragma once

#include <fstream>
#include <sstream>
#include <filesystem>
#include <system_error>

#include <string>
#include <vector>
#include <cstdint>

#include "..\interface\i_files.h" // err_codes.h - уже здесь

// Реализация iFiles для Windows
class wFiles : public iFiles 
{
protected:
    // Проверка существования файла (и что это именно файл, а не директория)
    ErrC fExists(const std::string& path) const override 
	{
        std::error_code ec;
        if (!std::filesystem::exists(path, ec)) 
		{
            if(ec)
            {
                return ErrC::UnknownError;
            }
            return ErrC::FileNotFound;
        }
        if (!std::filesystem::is_regular_file(path, ec)) 
		{
            return ErrC::NotAFile;
        }
        return ErrC::Ok;
    }

    // Чтение текстового файла (кодировка: системная ANSI/UTF-8, без BOM)
    ErrC readText(const std::string& path, std::string& text) const override 
	{
        // проверяем, что файл существует и является файлом
        ErrC ec = fExists(path);
        if (ec != ErrC::Ok) 
            return ec;

        //// std::ifstream ifs(path);
        // std::ios::binary гарантирует чтение байт UTF-8 без искажений
        std::ifstream ifs(path, std::ios::binary);
        if(!ifs.is_open()) 
            return ErrC::FileAccessFailed;

        // Читаем весь файл в строку через streambuf
        std::stringstream buffer;
        buffer << ifs.rdbuf();

        if(ifs.bad()) 
            return ErrC::FileReadFailed;

        text = buffer.str();
        return ErrC::Ok;
    }

    // Запись текстового файла (создаётся или перезаписывается)
    ErrC writeText(const std::string& path, const std::string& text) override 
	{
        // Опционально: проверить, что путь не указывает на существующую директорию
        std::error_code ec;
        if (std::filesystem::exists(path, ec) && std::filesystem::is_directory(path, ec)) 
            return ErrC::NotAFile;

        ////std::ofstream ofs(path);
        ////if (!ofs.is_open()) 
        ////    return ErrC::FileAccessFailed;
        ////ofs << text;
        ////if (ofs.fail()) 
        ////    return ErrC::FileWriteFailed;

        // Атомарная запись через .tmp файл
        std::string tmp_path = path + ".tmp";

        // std::ios::binary сохраняет UTF-8, trunc очищает файл
        std::ofstream ofs(tmp_path, std::ios::binary | std::ios::trunc);
        if(!ofs.is_open()) 
            return ErrC::FileAccessFailed;

        ofs << text;
        ofs.close(); // КРИТИЧНО! закрыть дескриптор перед rename

        if(ofs.fail()) 
        {
            std::filesystem::remove(tmp_path, ec); // Удаляем битый tmp
            return ErrC::FileWriteFailed;
        }

        // Атомарное переименование (NTFS гарантирует целостность)
        std::filesystem::rename(tmp_path, path, ec);
        if(ec)
        {
            std::filesystem::remove(tmp_path, ec);
            return ErrC::FileWriteFailed;
        }

        return ErrC::Ok;
    }

    // Чтение бинарного файла
    ErrC readBinary(const std::string& path, std::vector<uint8_t>& data) const override 
	{
        ErrC ec = fExists(path);
        if (ec != ErrC::Ok) return ec;

        std::ifstream ifs(path, std::ios::binary);
        if (!ifs.is_open()) 
		{
            return ErrC::FileAccessFailed;
        }

        // Определяем размер файла
        ifs.seekg(0, std::ios::end);
        std::streamsize size = ifs.tellg();
        if (size == -1) {
            return ErrC::FileReadFailed;
        }
        ifs.seekg(0, std::ios::beg);

        data.resize(static_cast<size_t>(size));
        if (!ifs.read(reinterpret_cast<char*>(data.data()), size)) 
		{
            return ErrC::FileReadFailed;
        }
        return ErrC::Ok;
    }

    // Запись бинарного файла
    ErrC writeBinary(const std::string& path, const std::vector<uint8_t>& data) override 
	{
        std::error_code ec;
        if (std::filesystem::exists(path, ec) && std::filesystem::is_directory(path, ec)) 
		{
            return ErrC::NotAFile;
        }

        std::ofstream ofs(path, std::ios::binary);
        if (!ofs.is_open()) 
		{
            return ErrC::FileAccessFailed;
        }
        ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
        if (ofs.fail()) 
		{
            return ErrC::FileWriteFailed;
        }
        return ErrC::Ok;
    }

    // Переопределяем backupFile для использования быстрого copy_file - избавляет от лишнего чтения в память и повториной записи
    ErrC backupFile(const std::string& path, const std::string& suffix) override
    {
        using namespace std::chrono;
        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch());
        auto sec = duration_cast<seconds>(ms);
        time_t t = sec.count();
        struct tm tm_buf;
        localtime_s(&tm_buf, &t);

        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y%m%d_%H%M%S", &tm_buf);

        std::string backup_path = path + "." + time_str + suffix;
        std::error_code ec;

        std::filesystem::copy_file(path, backup_path, std::filesystem::copy_options::overwrite_existing, ec);

        // Если копирование не удалось (файл бит/удален), не мешаем основной логике
        return ErrC::Ok;
    }
};

