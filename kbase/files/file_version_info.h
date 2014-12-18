/*
 @ Kingsley Chen
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef KBASE_FILES_FILE_VERSION_INFO_H_
#define KBASE_FILES_FILE_VERSION_INFO_H_

#include <Windows.h>

#include <memory>
#include <string>
#include <vector>

#include "kbase\basic_types.h"

namespace kbase {

namespace internal {

using VersionData = std::vector<kbase::byte>;

}   // namespace internal

class FilePath;

class FileVersionInfo {
public:
    ~FileVersionInfo() = default;

    FileVersionInfo(const FileVersionInfo&) = delete;

    FileVersionInfo(FileVersionInfo&&) = delete;

    FileVersionInfo& operator=(const FileVersionInfo&) = delete;

    FileVersionInfo& operator=(FileVersionInfo&&) = delete;

    static std::unique_ptr<FileVersionInfo> CreateForFile(const FilePath& file);

    static std::unique_ptr<FileVersionInfo> CreateForModule(HMODULE module);

    // TODO: property fields.

private:
    FileVersionInfo(internal::VersionData&& data);
    
    std::wstring GetValue(const wchar_t* name);

private:
    internal::VersionData data_;
    VS_FIXEDFILEINFO* info_block_ = nullptr;
    unsigned short lang_ = 0U;
    unsigned short code_page_ = 0U;
};

}   // namespace kbase

#endif  // KBASE_FILES_FILE_VERSION_INFO_H_