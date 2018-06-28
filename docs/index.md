Cross-Platform C aims to provide a better standard library for C. The library includes a growing number of features, common among other languages, which do not exist in the C standard library. When inlined, many of the functions compile down to OS API calls, and therefore do not add any additional runtime overhead to a project.

The library is still in development. If anything does not work, is confusing, or can be simplified, do not hesitate to submit an [issue](https://github.com/milesbarr/cross-platform-c/issues) or a [pull request](https://github.com/milesbarr/cross-platform-c/pulls).

## Documentation

The library is designed to be straightforward to use, however there many features. Here is the documentation for each feature:

- General
   - [Base Functionality](https://milesbarr.github.io/cross-platform-c/base-functionality)
   - [Strings](https://milesbarr.github.io/cross-platform-c/strings)
   - [Characters](https://milesbarr.github.io/cross-platform-c/characters)
   - [Processes](https://milesbarr.github.io/cross-platform-c/processes)
   - [Debugging](https://milesbarr.github.io/cross-platform-c/debugging)
- Memory
   - [Memory](https://milesbarr.github.io/cross-platform-c/memory)
   - [Heap Allocation](https://milesbarr.github.io/cross-platform-c/heap-allocation)
   - [Pool Allocator](https://milesbarr.github.io/cross-platform-c/pool-allocator)
- Concurrency
   - [Threads](https://milesbarr.github.io/cross-platform-c/threads)
   - [Mutexes](https://milesbarr.github.io/cross-platform-c/mutexes)
   - [Semaphores](https://milesbarr.github.io/cross-platform-c/semaphores)
   - [Green Threads](https://milesbarr.github.io/cross-platform-c/green-threads)
- Filesystem
   - [Memory Mapped Files](https://milesbarr.github.io/cross-platform-c/memory-mapped-files)
   - [Files](https://milesbarr.github.io/cross-platform-c/files)
   - [File Streams](https://milesbarr.github.io/cross-platform-c/file-streams)
   - [Directories](https://milesbarr.github.io/cross-platform-c/directories)
   - [Paths](https://milesbarr.github.io/cross-platform-c/paths)
- Networking
   - [URLs](https://milesbarr.github.io/cross-platform-c/urls)
- Data Structures
   - [Arrays](https://milesbarr.github.io/cross-platform-c/arrays)
- Math
   - [Cryptographic Hashing](https://milesbarr.github.io/cross-platform-c/cryptographic-hashing)
   - [Hashing](https://milesbarr.github.io/cross-platform-c/hashing)
   - [Math](https://milesbarr.github.io/cross-platform-c/math)
- UI
   - [Terminal](https://milesbarr.github.io/cross-platform-c/terminal)

## Testing

Tests are defined in the `tests` directory and can be run with `test.bat`.

## License

Cross-Platform C is released under the MIT license.
