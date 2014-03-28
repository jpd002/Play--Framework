## Play! Framework Readme ##

### Dependencies ###

General dependencies:

- [boost](http://boost.org) - v1.55.0
- [zlib](http://zlib.org) - v1.2.8

MySQL sub-library dependencies:

- [libmysqlclient](http://dev.mysql.com/downloads/connector/c/) - v6.1.1

OpenAL sub-library dependencies:

- OpenAL - v1.1

OpenGL sub-library dependencies:

- [glew](http://glew.sourceforge.net/) - v1.9.0

### Compiling for Win32 ###

Compiling on Win32 requires Visual Studio 2013. Header and library paths are defined in property sheets, so they'll need to be modified before compiling. Projects and property sheets can be found in the `build_win32` sub-directory.

### Compiling for MacOS X and iOS ###

Compiling on Apple platforms requires Xcode 5. On iOS, header search paths are defined in xcconfig files present in the `build_iphone` sub-directory.

### Compiling for other UNIX platforms ###

Compiling on UNIX platforms requires CMake 2.6 and +. I only tested compiling on clang v3.3, but it should work on the latest versions of GCC as well.