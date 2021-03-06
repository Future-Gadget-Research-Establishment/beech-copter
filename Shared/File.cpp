#include "File.hpp"

#include <string>

File::File(std::string Path, std::ios::openmode mode) :
Stream(Path, std::ios::binary | mode)
{
}

void File::Close()
{
    Stream.close();
}

File::operator bool() const
{
    return !Stream.eof() && Stream.good();
}

template <>
#ifdef _MSC_VER
inline
#endif
File& File::operator>> (std::string& Data)
{
    std::getline(Stream, Data, '\0');
    return *this;
}

template <>
#ifdef _MSC_VER
inline
#endif
File& File::operator<< (std::string Data)
{
    char null = 0;
    Stream.write(Data.c_str(), Data.size());
    Write<char>(null);
    return *this;
}

template <>
#ifdef _MSC_VER
inline
#endif
File& File::operator<< (const char* Data)
{
    *this << std::string(Data);
    return *this;
}
