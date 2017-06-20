/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - flashram.h                                              *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2014 Bobby Smiles                                       *
 *   Copyright (C) 2002 Hacktarux                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef M64P_DEVICE_PI_FLASHRAM_H
#define M64P_DEVICE_PI_FLASHRAM_H

#include <stdint.h>

struct pi_controller;
struct storage_backend_interface;

enum { FLASHRAM_SIZE = 0x20000 };

enum flashram_mode
{
    FLASHRAM_MODE_NOPES = 0,
    FLASHRAM_MODE_ERASE,
    FLASHRAM_MODE_WRITE,
    FLASHRAM_MODE_READ,
    FLASHRAM_MODE_STATUS
};

struct flashram
{
    enum flashram_mode mode;
    uint64_t status;
    unsigned int erase_offset;
    unsigned int write_pointer;

    void* storage;
    const struct storage_backend_interface* istorage;
};

void init_flashram(struct flashram* flashram,
                   void* storage,
                   const struct storage_backend_interface* istorage);

void poweron_flashram(struct flashram* flashram);

void format_flashram(uint8_t* flash);

void read_flashram_status(void* opaque, uint32_t address, uint32_t* value);
void write_flashram_status(void* opaque, uint32_t address, uint32_t value, uint32_t mask);
void read_flashram_command(void* opaque, uint32_t address, uint32_t* value);
void write_flashram_command(void* opaque, uint32_t address, uint32_t value, uint32_t mask);

unsigned int flashram_dma_write(void* opaque, uint8_t* dram, uint32_t dram_addr, uint32_t cart_addr, uint32_t length);
unsigned int flashram_dma_read(void* opaque, const uint8_t* dram, uint32_t dram_addr, uint32_t cart_addr, uint32_t length);

#endif
