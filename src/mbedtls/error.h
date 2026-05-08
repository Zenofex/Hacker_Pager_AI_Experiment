#pragma once

#include <stddef.h>

#if defined(__has_include_next)
#if __has_include_next(<mbedtls/error.h>)
#include_next <mbedtls/error.h>
#define PAGER_MBEDTLS_ERROR_HEADER_PROVIDED 1
#endif
#endif

#ifndef PAGER_MBEDTLS_ERROR_HEADER_PROVIDED
#ifdef __cplusplus
extern "C" {
#endif

void mbedtls_strerror(int errnum, char *buffer, size_t buflen);

#ifdef __cplusplus
}
#endif
#endif
