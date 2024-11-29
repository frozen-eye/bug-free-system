# bug-free-system

## Initializing and Updating Git Submodules (required)

To initialize the submodules in the repository, run the following command:

```sh
$ git submodule update --init --recursive
```

## Build OpenOCD (required)

Preconfigure:

```sh
$ ./bootstrap
```

Configure:

```sh
$ ./configure
```

Build:

```sh
$ make
```

Optionally it is possible to install openocd in the system (required root privileges). Please note that the current version of the openocd is a fork specially created for raspberry pi pico:

```sh
$ sudo make install
```


## Logging

Only compile-time logging is supported for now. To change the logging level, change settings in CMakeLists.txt:

```cmake
add_compile_definitions(${CMAKE_PROJECT_NAME} LOG_LEVEL=LOG_LEVEL_xxx)
```

`LOG_LEVEL` can be one of the defined values in [./src/include/common.h#L3-L8](./src/include/common.h#L3-L8) header file:

```c
#define LOG_LEVEL_VERBOSE 5
#define LOG_LEVEL_DEBUG   4
#define LOG_LEVEL_INFO    3
#define LOG_LEVEL_WARNING 2
#define LOG_LEVEL_ERROR   1
#define LOG_LEVEL_NONE    0
```
