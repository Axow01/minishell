# LibMms

## Description

Libmms is a library in C (memory management system). It manages the memory of a program by allocating and freeing memory blocks.

Changing the readme file for no reasons.

## Installation

```bash
make
gcc -Lpath/to/libmms -lmms program.c
```

## Usage

```c
#include "path/to/libmms/libmms.h"
#include <stdlib.h>

int main(void)
{
	mms_set_alloc_fn(calloc);
	int *ptr = mms_alloc(10, sizeof(int));
	*ptr = 42;
	mms_kill("message", false, exitcode);
	return EXIT_SUCCESS;
}

/// @brief This function deletes all the pointers assigned with the lib.
/// @param message The message to print when quitting.
/// @param quit Quitting of not.
/// @param code The exit code when quitting.
void		mms_kill(char *message, bool quit, int code);

/// @brief Allocate memory.
/// @param size the size in bytes.
/// @param typesize The type size in bytes.
/// @return An allocated pointer.
void		*mms_alloc(size_t size, size_t typesize);

/// @brief Frees a single pointer allocated with the lib.
/// @param ptr The pointer to free.
/// @return NULL in all cases.
void		*mms_free(void *ptr);

/// @brief Used to change the default function for allocation.
/// @param f The function ex: calloc. Default is calloc.
void		mms_set_alloc_fn(void *(*f)(size_t, size_t));

```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Credits

- [TheMickQc](https://github.com/Axow01)
- [Axhar005](https://github.com/Axhar005)

## License

None for now.
