# elfexec

Utility to execute ELF binary directly from stdin pipe. It is useful to run binary via SSH without copy or install it on remote systems.

## Examples

Run binary via ssh:

```
$ cat build-1234 | ssh user@host 'elfexec --test=integration --env=production'
```

Decode base64 encoded binary and run it directly:

```
$ echo 'IyEvYmluL3NoCmVjaG8gIkhlbGxvISIK' | base64 -d | elfexec
```

Compile source code and run it without temporary files:

```
$ echo '
#include <unistd.h>

int main(int argc, char* argv[])
{
    write(STDOUT_FILENO, "Hello!\n", 7);
    return 0;
}
' | cc -xc - -o /dev/stdout | elfexec
```

## Download / Install

Require Linux 3.17 or higher:

* [Debian, Ubuntu](http://software.opensuse.org/download.html?project=home:antonbatenev:elfexec&package=elfexec)
* [Fedora, openSUSE, CentOS](http://software.opensuse.org/download.html?project=home:antonbatenev:elfexec&package=elfexec)
* [Ubuntu PPA](https://launchpad.net/~abbat/+archive/ubuntu/elfexec) - `ppa:abbat/elfexec`
* [Arch AUR](https://aur.archlinux.org/packages/elfexec/) (see also [AUR Helpers](https://wiki.archlinux.org/index.php/AUR_Helpers))
* From source code:

```
$ git clone https://github.com/abbat/elfexec.git
$ make && sudo make install
```

To compile with own flags use `USER_CFLAGS` and `USER_LDFLAGS` variables. For example for i386 static binary with [musl libc](https://www.musl-libc.org):

```
$ CC=musl-gcc32 USER_CFLAGS=-m32 USER_LDFLAGS='-m32 -static -Wl,-melf_i386' make
```

## Usage

```
elfexec [options]
```

Where `options` is executed binary options.

## Exit code

Executed binary exit code or `1` if self failed.

## How to help

* Translate this document or [man page](https://github.com/abbat/elfexec/blob/master/elfexec.1) to your native language;
* Proofreading README.md or man page with your native language;
* Share, Like, RT to your friends;
* Send PRs if you are developer.
