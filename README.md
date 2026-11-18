*This project has been created as part of the 42 curriculum by irichi.*

# get_next_line — Reading a Line from a File Descriptor

## Description

**get_next_line** is an essential systems programming project in the 42 software engineering curriculum. The primary objective of this project is to design and implement a C function capable of reading and returning a single line terminated by a newline character (`\n`) or EOF from a given file descriptor, one line at a time across successive calls.

Unlike standard high-level I/O abstractions such as `fgets` or `getline`, this implementation interacts directly with the kernel via the low-level `read` system call using a compile-time configurable `BUFFER_SIZE`. By building this mechanism from scratch without external library helpers, the project develops a rigorous understanding of low-level I/O and memory lifecycle management, specifically addressing:

* **Static State Persistence:** Retaining unread leftover bytes between sequential function calls using `static` memory without relying on global variables.
* **Dynamic Memory Management & Safety:** Allocating exact buffer and line sizes on the heap via `malloc` and `free`, preventing buffer overflows, integer overflows on extreme `BUFFER_SIZE` values, and memory leaks across all edge cases.
* **Multi-Descriptor Multiplexing (Bonus):** Managing independent static buffers simultaneously across up to 1024 file descriptors (`static char *stash[1024]`), allowing interleaved reads from multiple open files or standard input without losing track of each stream's position.

---

## Algorithm & Technical Justification

### Selected Approach: Dynamic Accumulation & Remainder Splitting

The implementation uses an incremental accumulation buffer (**stash**) paired with newline detection and remainder splitting:

1. **Incremental Read & Accumulation (`ft_fill_stash`):** On each call, the function checks whether the current `stash[fd]` already contains a newline (`\n`). If not, it allocates a temporary read buffer of `(size_t)BUFFER_SIZE + 1` bytes and reads chunks via `read(fd, buff, BUFFER_SIZE)`, appending each chunk to `stash[fd]` using `ft_strjoin` and immediately freeing the previous stash pointer until either `\n` is encountered or `read` returns `0` (EOF).
2. **Line Extraction & Remainder Preservation (`ft_extract_line`):** Once a newline or EOF is reached, the exact length up to and including `\n` (if present) is measured. A precisely sized string is allocated and copied via `ft_strlcpy` to be returned to the caller, while any trailing bytes after `\n` are duplicated into `stash[fd]` via `ft_strdup`. If no trailing bytes remain, the stash is freed and reset to `NULL` so zero heap memory lingers after EOF.
3. **Multi-FD Indexing (Bonus):** Instead of a single `static char *stash`, the bonus version maintains a fixed-size array of pointers (`static char *stash[1024]`) indexed directly by `fd`.

### Justification

* **Arbitrary Line Length & Buffer Independence:** Because `BUFFER_SIZE` can range from `1` byte to `INT_MAX` (`2147483647`) while a single line may span tens of thousands of characters, fixed-size stack buffers either truncate lines or waste memory. Dynamic heap concatenation adapts to any line length and any `BUFFER_SIZE` seamlessly.
* **O(1) File Descriptor Lookup (Bonus):** Using a direct-indexed `static char *stash[1024]` array provides constant-time $O(1)$ access per file descriptor without the structural overhead or extra pointer allocations of a linked-list node structure, while keeping total static footprint minimal (8 KB on 64-bit systems).
* **Strict Leak Prevention:** Every error path (`read < 0`, failed `malloc`, empty EOF stash, or invalid `fd`) routes through a centralized cleanup helper (`r1`) that frees allocated blocks and resets the corresponding stash pointer to `NULL`.

---

## Instructions

### Repository Structure

All mandatory and bonus source files (`.c`) and header files (`.h`) are organized at the root level of this repository:

* **Mandatory:** `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`
* **Bonus:** `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h`

### Compilation

Because `get_next_line` does not include a standalone `Makefile` or `main` entry point, compile the source files directly alongside your test program while defining `BUFFER_SIZE` via the `-D` compiler flag:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl

```

To compile the **bonus** version supporting multiple file descriptors simultaneously:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o gnl_bonus

```

### Integrating into External Projects

To utilize `get_next_line` within another C program, include the appropriate header at the top of your source file:

```c
#include "get_next_line.h"
// Or for the bonus version:
// #include "get_next_line_bonus.h"

```

#### Usage Example

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("example.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}

```

---

## Function Overview

### 1. Core Function

* `get_next_line` — Reads and returns the next line from file descriptor `fd`, returning `NULL` on EOF or error.

### 2. Internal & Utility Functions

* `ft_fill_stash` — Reads chunks of `BUFFER_SIZE` bytes from `fd` and accumulates them until a newline or EOF is reached.
* `ft_extract_line` — Splits the accumulated buffer at the first `\n`, returning the extracted line and updating the static remainder.
* `is_line_finished` — Checks whether the current buffer contains a newline character or has reached EOF.
* `r1` — Frees allocated memory safely and resets the target pointer to `NULL` on error or EOF.
* `ft_strlen` — Computes the length of a null-terminated string.
* `ft_strjoin` — Concatenates the existing stash and newly read buffer into a newly allocated string.
* `ft_strdup` — Allocates and duplicates a null-terminated string.
* `ft_strlcpy` — Safely copies up to `size - 1` characters into a destination buffer with null-termination.

---

## Resources

### Classic References

* **Linux Programmer's Manual (`man` pages):** `read(2)`, `open(2)`, `close(2)`, `malloc(3)`, and `free(3)` for POSIX file descriptor behavior, return values, and heap allocation semantics.
* **The C Programming Language (2nd Edition) — Brian W. Kernighan & Dennis M. Ritchie:** Chapter 5 (Pointers and Arrays) and Chapter 8 (The UNIX System Interface) for low-level I/O and static storage duration rules.
* **ISO/IEC 9899 (C Standard) — Storage-Class Specifiers:** Specification on `static` duration variables and automatic zero-initialization.

### AI Usage Disclosure

AI was utilized strictly as a learning aid during this project to understand how the allowed system and standard library functions (`read`, `malloc`, `free`) behave under various edge cases, as well as to deepen theoretical understanding of topics directly and indirectly related to the project (such as file descriptor tables, static storage duration, integer overflow limits, and heap memory management).
