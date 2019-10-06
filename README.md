## Build instructions

In the example commands the output binary is specified by the `-o` argument.

### Windows

Build **list-processes_windows.c** with your compiler of choice.

For example, the command for GCC (MinGW) would be:
`gcc list-processes_windows.c -o list-processes.exe`

### Linux

Build **list-processes_linux.c** with your compiler of choice.

For example, the command for GCC would be:
`gcc list-processes_linux.c -o list-processes`

### FreeBSD

Build **list-processes_freebsd.c** with your compiler of choice.

If you get a linker error, make sure you're linking to the `util` library.

For example, the command for Clang would be:
`cc list-processes_freebsd.c -lutil -o list-processes`

### macOS

Build **list-processes_macos.c** with your compiler of choice.

If you get a linker error, make sure you're linking to the `AppKit` framework.

For example, the command for Clang would be:
`cc list-processes_macos.c -framework AppKit -o list-processes`

### Generic BSD

Build **list-processes_bsd.c** with your compiler of choice.

If you get a linker error, make sure you're linking to the `kvm` library.

For example, the command for Clang would be:
`cc list-processes_bsd.c -lkvm -o list-processes`
