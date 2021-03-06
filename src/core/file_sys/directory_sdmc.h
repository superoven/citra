// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"
#include "common/file_util.h"

#include "core/file_sys/directory.h"
#include "core/file_sys/archive_sdmc.h"
#include "core/loader/loader.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSys namespace

namespace FileSys {

class Directory_SDMC final : public Directory {
public:
    Directory_SDMC();
    Directory_SDMC(const Archive_SDMC* archive, const std::string& path);
    ~Directory_SDMC() override;

    /**
     * List files contained in the directory
     * @param count Number of entries to return at once in entries
     * @param entries Buffer to read data into
     * @return Number of entries listed
     */
    u32 Read(const u32 count, Entry* entries) override;

    /**
     * Close the directory
     * @return true if the directory closed correctly
     */
    bool Close() const override;

private:
    u32 entry_count;
    u32 current_entry;
    FileUtil::FSTEntry entry;
};

} // namespace FileSys
