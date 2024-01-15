#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include "Stream.hpp"
#include <fstream>

enum class FileMode : int
{
    //
    // Summary:
    //     Specifies that the operating system should create a new file. This requires System.Security.Permissions.FileIOPermissionAccess.Write
    //     permission. If the file already exists, an System.IO.IOException exception is
    //     thrown.
    CreateNew = 1,
    //
    // Summary:
    //     Specifies that the operating system should create a new file. If the file already
    //     exists, it will be overwritten. This requires System.Security.Permissions.FileIOPermissionAccess.Write
    //     permission. FileMode.Create is equivalent to requesting that if the file does
    //     not exist, use System.IO.FileMode.CreateNew; otherwise, use System.IO.FileMode.Truncate.
    //     If the file already exists but is a hidden file, an System.UnauthorizedAccessException
    //     exception is thrown.
    Create = 2,
    //
    // Summary:
    //     Specifies that the operating system should open an existing file. The ability
    //     to open the file is dependent on the value specified by the System.IO.FileAccess
    //     enumeration. A System.IO.FileNotFoundException exception is thrown if the file
    //     does not exist.
    Open = 3,
    //
    // Summary:
    //     Specifies that the operating system should open a file if it exists; otherwise,
    //     a new file should be created. If the file is opened with FileAccess.Read, System.Security.Permissions.FileIOPermissionAccess.Read
    //     permission is required. If the file access is FileAccess.Write, System.Security.Permissions.FileIOPermissionAccess.Write
    //     permission is required. If the file is opened with FileAccess.ReadWrite, both
    //     System.Security.Permissions.FileIOPermissionAccess.Read and System.Security.Permissions.FileIOPermissionAccess.Write
    //     permissions are required.
    OpenOrCreate = 4,
    //
    // Summary:
    //     Specifies that the operating system should open an existing file. When the file
    //     is opened, it should be truncated so that its size is zero bytes. This requires
    //     System.Security.Permissions.FileIOPermissionAccess.Write permission. Attempts
    //     to read from a file opened with FileMode.Truncate cause an System.ArgumentException
    //     exception.
    Truncate = 5,
    //
    // Summary:
    //     Opens the file if it exists and seeks to the end of the file, or creates a new
    //     file. This requires System.Security.Permissions.FileIOPermissionAccess.Append
    //     permission. FileMode.Append can be used only in conjunction with FileAccess.Write.
    //     Trying to seek to a position before the end of the file throws an System.IO.IOException
    //     exception, and any attempt to read fails and throws a System.NotSupportedException
    //     exception.
    Append = 6
};

enum class FileAccess : int
{
    //
    // Summary:
    //     Read access to the file. Data can be read from the file. Combine with Write for
    //     read/write access.
    Read = 1,
    //
    // Summary:
    //     Write access to the file. Data can be written to the file. Combine with Read
    //     for read/write access.
    Write = 2,
    //
    // Summary:
    //     Read and write access to the file. Data can be written to and read from the file.
    ReadWrite = 3
};

class FileStream : public Stream
{
private:
    std::fstream file;
public:
    FileStream(const std::string &filepath, FileMode mode, FileAccess access);
    ~FileStream() override;
    std::string Read(size_t size) override;
    size_t Read(void *buffer, size_t offset, size_t size) override;
    size_t Write(void *buffer, size_t offset, size_t size) override;
    ssize_t Seek(ssize_t offset, SeekOrigin origin) override;
    void Dispose() override;
};

#endif