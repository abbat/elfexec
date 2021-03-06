/**
 * Copyright (c) 2019-2020 Anton Batenev
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef __linux__
    #error "This program is linux-only."
#endif

#define _GNU_SOURCE
#include <features.h>

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/syscall.h>

#ifndef SYS_memfd_create
    #error "memfd_create require Linux 3.17 or higher."
#endif

/**
 * Default chunk size for io.
 */
#ifndef EE_CHUNK_SIZE
    #define EE_CHUNK_SIZE (8 * 1024)
#endif

/**
 * Default memory mapped filename.
 */
#ifndef EE_MEMFD_NAME
    #define EE_MEMFD_NAME "elfexec"
#endif

int exit_failure(const char* msg)
{
    perror(msg);
    return EXIT_FAILURE;
}

int main(int argc, char* argv[])
{
    int     memfd;
    ssize_t nread;
    ssize_t nwrite;
    size_t  offset;
    size_t  length;
    char    buf[EE_CHUNK_SIZE];

    /*
     * memfd_create require Linux 3.17 and was added to:
     * - glibc 2.27 (2018-02-01)
     * - musl 1.1.20 (2018-09-04)
     * use syscall to be compatible with older releases
     */
    memfd = (int)syscall(SYS_memfd_create, EE_MEMFD_NAME, 0);
    if (memfd == -1)
        return exit_failure("memfd_create");

    do {
        nread = read(STDIN_FILENO, buf, EE_CHUNK_SIZE);
        if (nread == -1)
            return exit_failure("read");

        offset = 0;
        length = (size_t)nread;
        while (offset < length) {
            nwrite = write(memfd, buf + offset, length - offset);
            if (nwrite == -1)
                return exit_failure("write");

            offset += (size_t)nwrite;
        }
    } while (nread > 0);

    if (fexecve(memfd, argv, environ) == -1)
        return exit_failure("fexecve");

    /* unused */
    (void)argc;

    /* a successful call to fexecve never returns */
    return EXIT_SUCCESS;
}
