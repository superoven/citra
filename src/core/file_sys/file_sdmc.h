// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "common/file_util.h"

#include "core/file_sys/file.h"
#include "core/file_sys/archive_sdmc.h"
#include "core/loader/loader.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSys namespace

namespace FileSys {

class File_SDMC final : public File {
public:
    File_SDMC();
    File_SDMC(const Archive_SDMC* archive, const std::string& path, const Mode mode);
    ~File_SDMC() override;

    /**
     * Read data from the file
     * @param offset Offset in bytes to start reading data from
     * @param length Length in bytes of data to read from file
     * @param buffer Buffer to read data into
     * @return Number of bytes read
     */
    size_t Read(const u64 offset, const u32 length, u8* buffer) const override;

    /**
     * Write data to the file
     * @param offset Offset in bytes to start writing data to
     * @param length Length in bytes of data to write to file
     * @param buffer Buffer to write data from
     * @param flush The flush parameters (0 == do not flush)
     * @return Number of bytes written
     */
    size_t Write(const u64 offset, const u32 length, const u32 flush, const u8* buffer) const override;

    /**
     * Get the size of the file in bytes
     * @return Size of the file in bytes
     */
    size_t GetSize() const override;

    /**
     * Close the file
     * @return true if the file closed correctly
     */
    bool Close() const override;

private:
    FileUtil::IOFile* file;
};

} // namespace FileSys
