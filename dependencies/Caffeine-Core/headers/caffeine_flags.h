#ifndef CAFFEINE_UTILS_FLAGS_H
#define CAFFEINE_UTILS_FLAGS_H


#define CFF_OS UNDEF // values: UNDEF, WINDOWS, UNIX, OSX, IPHONE, MAC, LINUX, BSD, DRAGONFLY, FREEBSD, NETBSD, OPENBSD, ANDROID, SOLARIS
#define CFF_ARCH UNDEF // values: UNDEF, ARM, MIPS, RISCV, X86_32, X86_64
#define CFF_COMP UNDEF // values: GCC, CLANG, MSVC
#define CFF_LANG C // values: C, CPP

#define NO_ALIAS __declspec(noalias)

#define ADDRESS_SIZE_BYTES (sizeof(void*))
#define ADDRESS_SIZE_BITS (ADDRESS_SIZE_BYTES*8)

#pragma region CHECK_OS

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) || defined(_POSIX_VERSION)

#undef CFF_OS
#define CFF_OS WINDOWS
#define ISWINDOWS

#endif // _WIN32 || _WIN64 || __CYGWIN__ || _POSIX_VERSION

#if unix || __unix || __unix__
#undef CFF_OS
#define CFF_OS UNIX
#define ISUNIX
#endif // unix || __unix || __unix__

#if __APLE__ || __MACH__
#undef CFF_OS
#define CFF_OS OSX
#define ISAPPLE

#if TARGET_OS_IPHONE
#undef CFF_OS
#define CFF_OS IPHONE
#endif // TARGET_OS_IPHONE 

#if TARGET_OS_MAC
#undef CFF_OS
#define CFF_OS MAC
#endif // TARGET_OS_MAC 

#endif // __APLE__ || __MACH__

#if __linux__ || linux || __linux
#undef CFF_OS
#define CFF_OS LINUX
#define ISUNIX
#define ISLINUX
#endif // __linux__ || linux || __linux

#if BSD
#undef CFF_OS
#define CFF_OS BSD
#define ISBSD

#if __DragonFly__
#undef CFF_OS
#define CFF_OS DRAGONFLY
#endif // __DragonFly__

#if __FreeBSD__
#undef CFF_OS
#define CFF_OS FREEBSD
#endif // __FreeBSD__

#if __NetBSD__
#undef CFF_OS
#define CFF_OS NETBSD
#endif // __NetBSD__

#if __OpenBSD__
#undef CFF_OS
#define CFF_OS OPENBSD
#endif // __OpenBSD__

#endif // BSD

#if __ANDROID__
#undef CFF_OS
#define CFF_OS ANDROID
#define ISUNIX
#define ISLINUX
#define ISANDROID
#endif // __ANDROID__

#if __sun
#undef CFF_OS
#define CFF_OS SOLARIS
#endif // __sun



#pragma endregion

#pragma region CHECK_ARCH

#if __ARM_ARCH || __TARGET_ARCH_ARM || __TARGET_ARCH_THUMB || _M_ARM || __arm__ || __arm64 || __thumb__ || _M_ARM64 || __aarch64__ || __AARCH64EL__ || __ARM_ARCH_7__ || __ARM_ARCH_7A__ || __ARM_ARCH_7R__ || __ARM_ARCH_7M__ || __ARM_ARCH_6K__ || __ARM_ARCH_6Z__ || __ARM_ARCH_6KZ__ || __ARM_ARCH_6T2__ || __ARM_ARCH_5TE__ || __ARM_ARCH_5TEJ__ || __ARM_ARCH_4T__ || __ARM_ARCH_4__ 
#undef CFF_ARCH
#define CFF_ARCH ARM
#endif // __ARM_ARCH || __TARGET_ARCH_ARM || __TARGET_ARCH_THUMB || _M_ARM || __arm__ || __arm64 || __thumb__ || _M_ARM64 || __aarch64__ || __AARCH64EL__ || __ARM_ARCH_7__ || __ARM_ARCH_7A__ || __ARM_ARCH_7R__ || __ARM_ARCH_7M__ || __ARM_ARCH_6K__ || __ARM_ARCH_6Z__ || __ARM_ARCH_6KZ__ || __ARM_ARCH_6T2__ || __ARM_ARCH_5TE__ || __ARM_ARCH_5TEJ__ || __ARM_ARCH_4T__ || __ARM_ARCH_4__ 

#if __mips__ || __mips || __MIPS__ || __mips || _MIPS_ISA_MIPS1 || _R3000 || _MIPS_ISA_MIPS2 || __MIPS_ISA2__ || _R4000 || _MIPS_ISA_MIPS3 || __MIPS_ISA3__ || _MIPS_ISA_MIPS4 || __MIPS_ISA4__  
#undef CFF_ARCH
#define CFF_ARCH MIPS
#endif // __mips__ || __mips || __MIPS__ || __mips || _MIPS_ISA_MIPS1 || _R3000 || _MIPS_ISA_MIPS2 || __MIPS_ISA2__ || _R4000 || _MIPS_ISA_MIPS3 || __MIPS_ISA3__ || _MIPS_ISA_MIPS4 || __MIPS_ISA4__  

#if __riscv
#undef CFF_ARCH
#define CFF_ARCH RISCV
#endif // __riscv

#if i386 || __i386__ || __i486__ || __i586__ || __i686__ || __i386 || _M_IX86 || _X86_ || __THW_INTEL__ || __I86__ || __INTEL__ || __I86__
#undef CFF_ARCH
#define CFF_ARCH X86_32
#endif // i386 || __i386__ || __i486__ || __i586__ || __i686__ || __i386 || _M_IX86 || _X86_ || __THW_INTEL__ || __I86__ || __INTEL__ || __I86__

#if __x86_64 || __x86_64__ || __amd64__ || __amd64 || _M_X64
#undef CFF_ARCH
#define CFF_ARCH X86_64
#endif // __x86_64 || __x86_64__ || __amd64__ || __amd64 || _M_X64


#pragma endregion

#pragma region CHECK_COMP

#if __clang__
#undef CFF_COMP
#define CFF_COMP CLANG
#define CFF_COMP_CLANG
#endif // __clang__

#if __GNUC__
#undef CFF_COMP
#define CFF_COMP GCC
#define CFF_COMP_GCC
#endif // __GNUC__

#if _MSC_VER
#undef CFF_COMP
#define CFF_COMP MSVC
#define CFF_COMP_MSVC
#endif // _MSC_VER


#pragma endregion

#pragma region CHECK_LANG
#ifdef __cplusplus
#undef CFF_LANG
#define CFF_LANG CPP
#endif // __cplusplus

#pragma endregion

#endif