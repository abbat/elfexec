# elfexec

Utility to execute ELF binary directly from stdin pipe. It is useful to run binary via SSH without copy or install it on remote systems.

## Example

```
$ cat timegrep | ssh user@host 'elfexec -e nginx -s 60 nginx-access.log'
```
