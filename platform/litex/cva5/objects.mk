#
# SPDX-License-Identifier: BSD-2-Clause
#
# Copyright (c) Reconfigurable Computing Lab, Simon Fraser University
#

# Compiler pre-processor flags
platform-cppflags-y =

# C Compiler and assembler flags.
platform-cflags-y =
platform-asflags-y =

# Linker flags: additional libraries and object files that the platform
# code needs can be added here
platform-ldflags-y =

#
# Command for platform specific "make run"
# Useful for development and debugging on plaftform simulator (such as QEMU)
#
platform-runcmd = echo LiteX/CVA5

#
# Platform RISC-V XLEN, ABI, ISA and Code Model configuration.
# These are optional parameters but platforms can optionaly provide it.
# Some of these are guessed based on GCC compiler capabilities
#

PLATFORM_RISCV_XLEN = 32
PLATFORM_RISCV_ABI = lp32
PLATFORM_RISCV_ISA = rv32ima
PLATFORM_RISCV_CODE_MODEL = medany

# Space separated list of object file names to be compiled for the platform
platform-objs-y += platform.o

# Blobs to build
FW_TEXT_START=0x40F00000
FW_DYNAMIC=n
FW_JUMP=y
FW_JUMP_ADDR=0x40000000
FW_JUMP_FDT_ADDR=0x40EF0000
FW_PAYLOAD=y
FW_PAYLOAD_OFFSET=0x40000000
FW_PAYLOAD_FDT_ADDR=0x40EF0000