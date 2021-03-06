/*
 @ 0xCCCCCCCC
*/

#include <iostream>

#include "gtest/gtest.h"

#include "kbase/file_version_info.h"
#include "kbase/path.h"

namespace {

const kbase::Path kTargetFile(L"C:\\windows\\notepad.exe");

}   // namespace

namespace kbase {

TEST(FileVersionInfoTest, FixedFileInfo)
{
    auto version_info = kbase::FileVersionInfo::CreateForFile(kTargetFile);
    auto ffi = version_info->fixed_file_info();
    EXPECT_NE(ffi, nullptr);
    std::cout << ffi->dwFileVersionMS << ":" << ffi->dwFileVersionLS << std::endl;
}

TEST(FileVersionInfoTest, Values)
{
    // only test few values.
    auto version_info = kbase::FileVersionInfo::CreateForFile(kTargetFile);
    auto product_version = version_info->product_version();
    auto file_version = version_info->file_version();
    auto company = version_info->company_name();
    EXPECT_FALSE(product_version.empty());
    EXPECT_FALSE(file_version.empty());
    EXPECT_FALSE(company.empty());
    std::wcout << product_version << std::endl << file_version << std::endl << company << std::endl;
}

}   // namespace kbase
