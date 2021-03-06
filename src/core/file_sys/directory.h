// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"

#include "core/hle/kernel/kernel.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSys namespace

namespace FileSys {

// Structure of a directory entry, from http://3dbrew.org/wiki/FSDir:Read#Entry_format
const size_t FILENAME_LENGTH = 0x20C / 2;
struct Entry {
    char16_t filename[FILENAME_LENGTH]; // Entry name (UTF-16, null-terminated)
    char short_name[8]; // 8.3 file name ('longfilename' -> 'LONGFI~1')
    char unknown1; // unknown (observed values: 0x0A, 0x70, 0xFD)
    char extension[3]; // 8.3 file extension (set to spaces for directories)
    char unknown2; // unknown (always 0x01)
    char unknown3; // unknown (0x00 or 0x08)
    char is_directory; // directory flag
    char is_hidden; // hidden flag
    char is_archive; // archive flag
    char is_read_only; // read-only flag
    u64 file_size; // file size (for files only)
};
static_assert(sizeof(Entry) == 0x228, "Directory Entry struct isn't exactly 0x228 bytes long!");

class Directory : NonCopyable {
public:
    Directory() { }
    virtual ~Directory() { }

    /**
     * List files contained in the directory
     * @param count Number of entries to return at once in entries
     * @param entries Buffer to read data into
     * @return Number of entries listed
     */
    virtual u32 Read(const u32 count, Entry* entries) = 0;

    /**
     * Close the directory
     * @return true if the directory closed correctly
     */
    virtual bool Close() const = 0;
};

} // namespace FileSys
