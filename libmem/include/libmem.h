/*
 *  ----------------------------------
 * |         libmem - by rdbo         |
 * |      Memory Hacking Library      |
 *  ----------------------------------
 */

#pragma once
#ifndef LIBMEM_H
#define LIBMEM_H

/* Operating System */
#define LM_OS_WIN     0
#define LM_OS_LINUX   1
#define LM_OS_BSD     2
#define LM_OS_ANDROID 3

#if defined(LM_FORCE_OS_WIN)
#	define LM_OS LM_OS_WIN
#elif defined(LM_FORCE_OS_LINUX)
#	define LM_OS LM_OS_LINUX
#elif defined(LM_FORCE_OS_BSD)
#	define LM_OS LM_OS_BSD
#elif defined(LM_FORCE_OS_ANDROID)
#	define LM_OS LM_OS_ANDROID
#endif

#ifndef LM_OS
#	if (defined(WIN32) || defined(_WIN32) || defined(__WIN32)) \
		&& !defined(__CYGWIN__) && !defined(linux)
#		define LM_OS LM_OS_WIN
#	elif defined(__ANDROID__)
#		define LM_OS LM_OS_ANDROID
#	elif defined(linux) || defined(__linux__)
#		define LM_OS LM_OS_LINUX
#	elif defined(BSD) || defined(__FreeBSD__) \
		|| defined(__OpenBSD__) || defined(__NetBSD__)
#		define LM_OS LM_OS_BSD
#	endif
#endif

/* Architecture */
#define LM_ARCH_X86 0
#define LM_ARCH_ARM 1

#if defined(LM_FORCE_ARCH_X86)
#	define LM_ARCH LM_ARCH_X86
#elif defined(LM_FORCE_ARCH_ARM)
#	define LM_ARCH LM_ARCH_ARM
#endif

#ifndef LM_ARCH
#	if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) \
		|| defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) \
		|| defined (i386) || defined(__i386) || defined(__i386__) \
		|| defined(_M_IX86)
#		define LM_ARCH LM_ARCH_X86
#	elif defined(__arm__) || defined(_ARM) \
		|| defined(_M_ARM) || defined(__aarch64__)
#		define LM_ARCH LM_ARCH_ARM
#	endif
#endif

/* Bits */
#if defined(LM_FORCE_BITS_64)
#	define LM_BITS 64
#elif defined(LM_FORCE_BITS_32)
#	define LM_BITS 32
#endif

#ifndef LM_BITS
#	if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) \
		|| defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64) \
		|| defined(__aarch64__) \
		|| defined(__LP64__) || defined(_LP64) \
		|| (defined(__WORDSIZE) && __WORDSIZE == 64)
#		define LM_BITS 64
#	else
#		define LM_BITS 32
#	endif
#endif

/* Compiler */
#define LM_COMPILER_MSVC 0
#define LM_COMPILER_CC   1

#if defined(LM_FORCE_COMPILER_MSVC)
#	define LM_COMPILER LM_COMPILER_MSVC
#elif defined(LM_FORCE_COMPILER_CC)
#	define LM_COMPILER LM_COMPILER_CC
#endif

#ifndef LM_COMPILER
#	ifdef _MSC_VER
#		define LM_COMPILER LM_COMPILER_MSVC
#	else
#		define LM_COMPILER LM_COMPILER_CC
#	endif
#endif

/* Charset */
#define LM_CHARSET_UC 0
#define LM_CHARSET_MB 1

#if defined(LM_FORCE_CHARSET_UC)
#	define LM_CHARSET LM_CHARSET_UC
#elif defined(LM_FORCE_CHARSET_MB)
#	define LM_CHARSET LM_CHARSET_MB
#endif

#ifndef LM_CHARSET
#	if defined(_UNICODE) && LM_OS == LM_OS_WIN
#		define LM_CHARSET LM_CHARSET_UC
#	else
#		define LM_CHARSET LM_CHARSET_MB
#	endif
#endif

/* Language */
#define LM_LANG_C   0
#define LM_LANG_CPP 1

#if defined(LM_FORCE_LANG_C)
#	define LM_LANG LM_LANG_C
#elif defined(LM_FORCE_LANG_CPP)
#	define LM_LANG LM_LANG_CPP
#endif

#ifndef LM_LANG
#	if defined(LIBMEM_HPP) || defined(__cplusplus)
#		define LM_LANG LM_LANG_CPP
#	else
#		define LM_LANG LM_LANG_C
#	endif
#endif

/* Helpers */
#define LM_MALLOC   malloc
#define LM_CALLOC   calloc
#define LM_REALLOC  realloc
#define LM_FREE     free
#define LM_MEMCPY   memcpy
#define LM_MEMSET   memset
#define LM_ASSERT   assert
#define LM_FOPEN    fopen
#define LM_FCLOSE   fclose
#define LM_GETLINE  getline /* TODO: Add wchar_t variant */

#define LM_CSTR(str) str
#define LM_CSTRCMP   strcmp
#define LM_CSTRNCMP  strncmp
#define LM_CSTRCPY   strcpy
#define LM_CSTRNCPY  strncpy
#define LM_CSTRLEN   strlen
#define LM_CSTRCHR   strchr
#define LM_CSTRRCHR  strrchr
#define LM_CSTRSTR   strstr
#define LM_CSNPRINTF snprintf
#define LM_CSTRTOP   strtoul
#define LM_CATOI     atoi

#define LM_WSTR(str) L##str
#define LM_WSTRCMP   wcscmp
#define LM_WSTRNCMP  wcsncmp
#define LM_WSTRCPY   wcscpy
#define LM_WSTRNCPY  wcsncpy
#define LM_WSTRLEN   wcslen
#define LM_WSTRCHR   wcschr
#define LM_WSTRRCHR  wcsrchr
#define LM_WSTRSTR   wcsstr
#define LM_WSNPRINTF snwprintf
#define LM_WSTRTOP   wcstoul
#define LM_WATOI     wtoi

#if LM_CHARSET == LM_CHARSET_UC
#	define LM_STR      LM_WSTR
#	define LM_STRCMP   LM_WSTRCMP
#	define LM_STRNCMP  LM_WSTRNCMP
#	define LM_STRCPY   LM_WSTRCPY
#	define LM_STRNCPY  LM_WSTRNCPY
#	define LM_STRLEN   LM_WSTRLEN
#	define LM_STRCHR   LM_WSTRCHR
#	define LM_STRRCHR  LM_WSTRRCHR
#	define LM_STRSTR   LM_WSTRSTR
#	define LM_SNPRINTF LM_WSNPRINTF
#	define LM_STRTOP   LM_WSTRTOP
#	define LM_ATOI     LM_WATOI
#else
#	define LM_STR      LM_CSTR
#	define LM_STRCMP   LM_CSTRCMP
#	define LM_STRNCMP  LM_CSTRNCMP
#	define LM_STRCPY   LM_CSTRCPY
#	define LM_STRNCPY  LM_CSTRNCPY
#	define LM_STRLEN   LM_CSTRLEN
#	define LM_STRCHR   LM_CSTRCHR
#	define LM_STRRCHR  LM_CSTRRCHR
#	define LM_STRSTR   LM_CSTRSTR
#	define LM_SNPRINTF LM_CSNPRINTF
#	define LM_STRTOP   LM_CSTRTOP
#	define LM_ATOI     LM_CATOI
#endif
#define LM_ARRLEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define LM_CHKMASK(c) (c == LM_MASK_KNOWN || c == LM_MASK_KNOWN2)
#define LM_RCHKMASK(c) (c == LM_MASK_UNKNOWN || c == LM_MASK_UNKNOWN2)
#define LM_OFFSET(base, offset) (&((lm_byte_t *)base)[offset])
#if LM_OS == LM_OS_WIN
#	define _LM_VALID_PROCESS(proc) (proc.pid != LM_GetProcessId() && proc.handle != NULL)
#else
#	define _LM_VALID_PROCESS(proc) LM_TRUE
#endif
#define LM_VALID_PROCESS(proc) (proc.pid != LM_PID_BAD && _LM_VALID_PROCESS(proc))

/* Flags */
#if LM_OS == LM_OS_WIN
#	define LM_PROT_R   (PAGE_READONLY)
#	define LM_PROT_W   (PAGE_WRITECOPY)
#	define LM_PROT_X   (PAGE_EXECUTE)
#	define LM_PROT_RW  (PAGE_READWRITE)
#	define LM_PROT_XR  (PAGE_EXECUTE_READ)
#	define LM_PROT_XRW (PAGE_EXECUTE_READWRITE)
#	define LM_PROCESS_ACCESS (PROCESS_ALL_ACCESS)
#elif LM_OS == LM_OS_LINUX || LM_OS == LM_OS_BSD || LM_OS == LM_OS_ANDROID
#	define LM_PROT_R   (PROT_READ)
#	define LM_PROT_W   (PROT_WRITE)
#	define LM_PROT_X   (PROT_EXEC)
#	define LM_PROT_RW  (PROT_READ | PROT_WRITE)
#	define LM_PROT_XR  (PROT_EXEC | PROT_READ)
#	define LM_PROT_XRW (PROT_EXEC | PROT_READ | PROT_WRITE)
#endif

/* Imports/Exports */
#if defined(LM_EXPORT)
#	if LM_COMPILER == LM_COMPILER_MSVC
#		define LM_API __declspec(dllexport)
#	elif LM_COMPILER == LM_COMPILER_CC
#		define LM_API __attribute__((visibility("default")))
#	endif
#elif defined(LM_IMPORT)
#	if LM_COMPILER == LM_COMPILER_MSVC
#		define LM_API __declspec(dllimport)
#	elif LM_COMPILER == LM_COMPILER_CC
#		define LM_API extern
#	endif
#else
#	define LM_API
#endif

/* Others */
#define LM_NULL    (0)
#define LM_NULLPTR ((lm_void_t *)LM_NULL)
#define LM_BAD     (-1)
#define LM_OK      (!(LM_BAD))
#define LM_FALSE   (0)
#define LM_TRUE    (!(LM_FALSE))
#define LM_MAX     (-1UL)
#define LM_PID_BAD ((lm_pid_t)LM_NULL) /* tecnically, PID = 0 exists, but should probably never be accessed anyways, unlike the last possible PID, which was the previous error value for lm_pid_t */
#define LM_TID_BAD ((lm_tid_t)LM_NULL)
#define LM_ADDRESS_BAD ((lm_address_t)LM_NULL)
#define LM_MASK_KNOWN    LM_STR('x')
#define LM_MASK_KNOWN2   LM_STR('X')
#define LM_MASK_UNKNOWN  LM_STR('?')
#define LM_MASK_UNKNOWN2 LM_STR('*')
#define LM_INST_SIZE 16
#if LM_OS == LM_OS_WIN
#	define LM_PATH_MAX MAX_PATH
#	define LM_PATH_SEP LM_STR('\\')
#elif LM_OS == LM_OS_LINUX || LM_OS == LM_OS_ANDROID
#	define LM_PATH_MAX PATH_MAX
#	ifndef _GNU_SOURCE
#		define _GNU_SOURCE 1
#	endif
#	define LM_PROCFS LM_STR("/proc")
#	define LM_PATH_SEP LM_STR('/')
#elif LM_OS == LM_OS_BSD
#	define LM_PATH_MAX PATH_MAX
#	define LM_PROCFS LM_STR("/proc")
#	define LM_PATH_SEP LM_STR('/')
#endif

/* Compatibility */
#if defined(LM_OS) && defined(LM_ARCH) && defined(LM_BITS) \
	&& defined(LM_COMPILER) && defined(LM_CHARSET) && defined(LM_LANG)
#	define LM_COMPATIBLE 1
#else
#	define LM_COMPATIBLE 0
#endif

#if LM_COMPATIBLE
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#if LM_OS == LM_OS_WIN
#	include <Windows.h>
#	include <TlHelp32.h>
#	include <Psapi.h>
#else
#	include <sys/types.h>
#	include <unistd.h>
#	include <sys/mman.h>
#	include <limits.h>
#endif /* LM_OS */

#if LM_LANG == LM_LANG_CPP
extern "C" {
#endif

/* Types/Enums */
typedef char               lm_char_t;
typedef unsigned char      lm_uchar_t;
typedef int                lm_int_t;
typedef unsigned int       lm_uint_t;
typedef short              lm_short_t;
typedef unsigned short     lm_ushort_t;
typedef long               lm_long_t;
typedef unsigned long      lm_ulong_t;
typedef long long          lm_llong_t;
typedef unsigned long long lm_ullong_t;
typedef wchar_t            lm_wchar_t;
typedef void               lm_void_t;
typedef lm_int_t           lm_bool_t;

#if LM_BITS == 64
typedef lm_llong_t         lm_intmax_t;
typedef lm_ullong_t        lm_uintmax_t;
#else
typedef lm_long_t          lm_intmax_t;
typedef lm_ulong_t         lm_uintmax_t;
#endif

typedef lm_char_t          lm_int8_t;
typedef lm_short_t         lm_int16_t;
typedef lm_int_t           lm_int32_t;
typedef lm_intmax_t        lm_int64_t;

typedef lm_uchar_t         lm_uint8_t;
typedef lm_ushort_t        lm_uint16_t;
typedef lm_uint_t          lm_uint32_t;
typedef lm_uintmax_t       lm_uint64_t;

typedef lm_uint8_t         lm_byte_t;
typedef lm_uint16_t        lm_word_t;
typedef lm_uint32_t        lm_dword_t;
typedef lm_uint64_t        lm_qword_t;

typedef lm_intmax_t        lm_intptr_t;
typedef lm_uintmax_t       lm_uintptr_t;
typedef lm_void_t         *lm_voidptr_t;

typedef lm_voidptr_t       lm_address_t;
typedef lm_uintmax_t       lm_size_t;

#if LM_CHARSET == LM_CHARSET_UC
typedef lm_wchar_t         lm_tchar_t;
#else
typedef lm_char_t          lm_tchar_t;
#endif

typedef lm_byte_t         *lm_bstring_t;
typedef lm_char_t         *lm_cstring_t;
typedef lm_wchar_t        *lm_wstring_t;
typedef lm_tchar_t        *lm_tstring_t;
typedef lm_tstring_t       lm_string_t;

#if LM_OS == LM_OS_WIN
typedef DWORD              lm_pid_t;
typedef DWORD              lm_prot_t;
typedef DWORD              lm_flags_t;
typedef DWORD              lm_tid_t;
#elif LM_OS == LM_OS_LINUX || LM_OS == LM_OS_BSD || LM_OS == LM_OS_ANDROID
typedef pid_t              lm_pid_t;
typedef lm_pid_t           lm_tid_t;
typedef int                lm_prot_t;
typedef int                lm_flags_t;
#endif

typedef struct {
	lm_pid_t pid;
#	if LM_OS == LM_OS_WIN
	HANDLE   handle;
#	endif
} lm_process_t;

typedef struct {
	lm_address_t base;
	lm_address_t end;
	lm_size_t    size;
} lm_module_t;

typedef struct {
	lm_address_t base;
	lm_address_t end;
	lm_size_t    size;
	lm_prot_t    prot;
	lm_flags_t   flags;
} lm_page_t;

/* LM_GetModule(Ex) Flags */
enum {
	LM_MOD_BY_STR = 0,
	LM_MOD_BY_ADDR
};

typedef lm_int_t lm_detour_t;

/* Based from instruction struct from capstone.h */
typedef struct {
	lm_uint_t   id;
	lm_uint64_t address;
	lm_uint16_t size;
	lm_uint8_t  bytes[LM_INST_SIZE];
	lm_char_t   mnemonic[32];
	lm_char_t   op_str[160];
	lm_void_t  *detail;
} lm_inst_t;

typedef lm_int_t lm_arch_t;

/* Imports */
#if LM_OS == LM_OS_WIN && LM_COMPILER == LM_COMPILER_CC && LM_BITS == 64
extern BOOL
Wow64SetThreadContext(HANDLE		   hThread,
		      const WOW64_CONTEXT *lpContext);
extern BOOL
Wow64GetThreadContext(HANDLE		   hThread,
		      const WOW64_CONTEXT *lpContext);
#endif

/* libmem */
LM_API lm_bool_t
LM_EnumProcesses(lm_bool_t(*callback)(lm_pid_t   pid,
				      lm_void_t *arg),
		 lm_void_t *arg);

LM_API lm_pid_t
LM_GetProcessId(lm_void_t);

LM_API lm_pid_t
LM_GetProcessIdEx(lm_tstring_t procstr);

LM_API lm_pid_t
LM_GetParentId(lm_void_t);

LM_API lm_pid_t
LM_GetParentIdEx(lm_pid_t pid);

LM_API lm_bool_t
LM_CheckProcess(lm_pid_t pid);

/* TODO: Make this function return lm_void_t, because it cannot fail */
LM_API lm_bool_t
LM_OpenProcess(lm_process_t *procbuf);

LM_API lm_bool_t
LM_OpenProcessEx(lm_pid_t      pid,
		 lm_process_t *procbuf);

LM_API lm_void_t
LM_CloseProcess(lm_process_t *procbuf);

LM_API lm_size_t
LM_GetProcessPath(lm_tchar_t *pathbuf,
		  lm_size_t   maxlen);

LM_API lm_size_t
LM_GetProcessPathEx(lm_process_t proc,
		    lm_tchar_t  *pathbuf,
		    lm_size_t    maxlen);

LM_API lm_size_t
LM_GetProcessName(lm_tchar_t *namebuf,
		  lm_size_t   maxlen);

LM_API lm_size_t
LM_GetProcessNameEx(lm_process_t proc,
		    lm_tchar_t  *namebuf,
		    lm_size_t    maxlen);

LM_API lm_size_t
LM_GetSystemBits(lm_void_t);

LM_API lm_size_t
LM_GetProcessBits(lm_void_t);

LM_API lm_size_t
LM_GetProcessBitsEx(lm_process_t proc);

/****************************************/

LM_API lm_bool_t
LM_EnumThreads(lm_bool_t(*callback)(lm_tid_t   tid,
				    lm_void_t *arg),
	       lm_void_t *arg);

LM_API lm_bool_t
LM_EnumThreadsEx(lm_process_t proc,
		 lm_bool_t  (*callback)(lm_tid_t   tid,
					lm_void_t *arg),
		 lm_void_t   *arg);

LM_API lm_tid_t
LM_GetThreadId(lm_void_t);

LM_API lm_tid_t
LM_GetThreadIdEx(lm_process_t proc);

/****************************************/

LM_API lm_bool_t
LM_EnumModules(lm_bool_t(*callback)(lm_module_t  mod,
				    lm_tstring_t path,
				    lm_void_t   *arg),
	       lm_void_t *arg);

LM_API lm_bool_t
LM_EnumModulesEx(lm_process_t proc,
		 lm_bool_t  (*callback)(lm_module_t  mod,
					lm_tstring_t path,
					lm_void_t   *arg),
		 lm_void_t   *arg);

LM_API lm_bool_t
LM_GetModule(lm_int_t     flags,
	     lm_void_t   *modarg,
	     lm_module_t *modbuf);

LM_API lm_bool_t
LM_GetModuleEx(lm_process_t proc,
	       lm_int_t     flags,
	       lm_void_t   *modarg,
	       lm_module_t *modbuf);

LM_API lm_size_t
LM_GetModulePath(lm_module_t mod,
		 lm_tchar_t *pathbuf,
		 lm_size_t   maxlen);

LM_API lm_size_t
LM_GetModulePathEx(lm_process_t proc,
		   lm_module_t  mod,
		   lm_tchar_t  *pathbuf,
		   lm_size_t    maxlen);

LM_API lm_size_t
LM_GetModuleName(lm_module_t mod,
		 lm_tchar_t *namebuf,
		 lm_size_t   maxlen);

LM_API lm_size_t
LM_GetModuleNameEx(lm_process_t proc,
		   lm_module_t  mod,
		   lm_tchar_t  *namebuf,
		   lm_size_t    maxlen);

LM_API lm_bool_t
LM_LoadModule(lm_tstring_t path,
	      lm_module_t *modbuf);

LM_API lm_bool_t
LM_LoadModuleEx(lm_process_t proc,
		lm_tstring_t path,
		lm_module_t *modbuf);

LM_API lm_bool_t
LM_UnloadModule(lm_module_t mod);

LM_API lm_bool_t
LM_UnloadModuleEx(lm_process_t proc,
		  lm_module_t  mod);

/****************************************/

LM_API lm_bool_t
LM_EnumSymbols(lm_module_t mod,
	       lm_bool_t (*callback)(lm_cstring_t symbol,
	       			     lm_address_t addr,
	       			     lm_void_t   *arg),
	       lm_void_t *arg);

LM_API lm_bool_t
LM_EnumSymbolsEx(lm_process_t proc,
		 lm_module_t  mod,
	         lm_bool_t  (*callback)(lm_cstring_t symbol,
		 			lm_address_t addr,
					lm_void_t   *arg),
		 lm_void_t *arg);

LM_API lm_address_t
LM_GetSymbol(lm_module_t  mod,
	     lm_cstring_t symstr);

LM_API lm_address_t
LM_GetSymbolEx(lm_process_t proc,
	       lm_module_t  mod,
	       lm_cstring_t symstr);

/****************************************/

LM_API lm_bool_t
LM_EnumPages(lm_bool_t(*callback)(lm_page_t  page,
				  lm_void_t *arg),
	     lm_void_t *arg);

LM_API lm_bool_t
LM_EnumPagesEx(lm_process_t proc,
	       lm_bool_t  (*callback)(lm_page_t  page,
				      lm_void_t *arg),
	       lm_void_t   *arg);

LM_API lm_bool_t
LM_GetPage(lm_address_t addr,
	   lm_page_t   *page);

LM_API lm_bool_t
LM_GetPageEx(lm_process_t proc,
	     lm_address_t addr,
	     lm_page_t   *page);

/****************************************/

LM_API lm_size_t
LM_ReadMemory(lm_address_t src,
	      lm_byte_t   *dst,
	      lm_size_t    size);

LM_API lm_size_t
LM_ReadMemoryEx(lm_process_t proc,
		lm_address_t src,
		lm_byte_t   *dst,
		lm_size_t    size);

LM_API lm_size_t
LM_WriteMemory(lm_address_t dst,
	       lm_bstring_t src,
	       lm_size_t    size);

LM_API lm_size_t
LM_WriteMemoryEx(lm_process_t proc,
		 lm_address_t dst,
		 lm_bstring_t src,
		 lm_size_t    size);

LM_API lm_size_t
LM_SetMemory(lm_byte_t *dst,
	     lm_byte_t  byte,
	     lm_size_t  size);

LM_API lm_size_t
LM_SetMemoryEx(lm_process_t proc,
	       lm_address_t dst,
	       lm_byte_t    byte,
	       lm_size_t    size);

LM_API lm_bool_t
LM_ProtMemory(lm_address_t addr,
	      lm_size_t    size,
	      lm_prot_t    prot,
	      lm_prot_t   *oldprot);

LM_API lm_bool_t
LM_ProtMemoryEx(lm_process_t proc,
		lm_address_t addr,
		lm_size_t    size,
		lm_prot_t    prot,
		lm_prot_t   *oldprot);

LM_API lm_address_t
LM_AllocMemory(lm_size_t size,
	       lm_prot_t prot);

LM_API lm_address_t
LM_AllocMemoryEx(lm_process_t proc,
		 lm_size_t    size,
		 lm_prot_t    prot);

LM_API lm_bool_t
LM_FreeMemory(lm_address_t alloc,
	      lm_size_t    size);

LM_API lm_bool_t
LM_FreeMemoryEx(lm_process_t proc,
		lm_address_t alloc,
		lm_size_t    size);

LM_API lm_address_t
LM_DataScan(lm_bstring_t data,
	    lm_size_t    size,
	    lm_address_t addr,
	    lm_size_t    scansize);

LM_API lm_address_t
LM_DataScanEx(lm_process_t proc,
	      lm_bstring_t data,
	      lm_size_t    size,
	      lm_address_t addr,
	      lm_size_t    scansize);

LM_API lm_address_t
LM_PatternScan(lm_bstring_t pattern,
	       lm_tstring_t mask,
	       lm_address_t addr,
	       lm_size_t    scansize);

LM_API lm_address_t
LM_PatternScanEx(lm_process_t proc,
		 lm_bstring_t pattern,
		 lm_tstring_t mask,
		 lm_address_t addr,
		 lm_size_t    scansize);

LM_API lm_address_t
LM_SigScan(lm_tstring_t sig,
	   lm_address_t addr,
	   lm_size_t    scansize);

LM_API lm_address_t
LM_SigScanEx(lm_process_t proc,
	     lm_tstring_t sig,
	     lm_address_t addr,
	     lm_size_t    scansize);

/****************************************/

LM_API lm_size_t
LM_HookCode(lm_address_t  from,
	    lm_address_t  to,
	    lm_address_t *ptrampoline);

LM_API lm_bool_t
LM_UnhookCode(lm_address_t  from,
	      lm_address_t  trampoline,
	      lm_size_t     size);

LM_API lm_size_t
LM_HookCodeEx(lm_process_t  proc,
	      lm_address_t  from,
	      lm_address_t  to,
	      lm_address_t *ptrampoline);

LM_API lm_bool_t
LM_UnhookCodeEx(lm_process_t  proc,
		lm_address_t  from,
		lm_address_t  trampoline,
		lm_size_t     size);

/****************************************/

LM_API lm_bool_t
LM_Assemble(lm_cstring_t code,
	    lm_inst_t   *inst);

LM_API lm_size_t
LM_AssembleEx(lm_cstring_t code,
	      lm_arch_t    arch,
	      lm_size_t    bits,
	      lm_address_t base_addr,
	      lm_byte_t  **pcodebuf);

LM_API lm_void_t
LM_FreeCodeBuffer(lm_byte_t *codebuf);

LM_API lm_bool_t
LM_Disassemble(lm_address_t code,
	       lm_inst_t   *inst);

LM_API lm_size_t
LM_DisassembleEx(lm_address_t code,
		 lm_arch_t    arch,
		 lm_size_t    bits,
		 lm_size_t    size,
		 lm_size_t    count,
		 lm_address_t base_addr,
		 lm_inst_t  **pinsts);

LM_API lm_void_t
LM_FreeInstructions(lm_inst_t *insts);

LM_API lm_size_t
LM_CodeLength(lm_address_t code,
	      lm_size_t minlength);

LM_API lm_size_t
LM_CodeLengthEx(lm_process_t proc,
		lm_address_t code,
		lm_size_t minlength);

#if LM_LANG == LM_LANG_CPP
}
#endif

#endif /* LM_COMPATIBLE */
#endif /* LIBMEM_H */
