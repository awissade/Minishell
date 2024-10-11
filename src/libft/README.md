# Libft @ 42

This is my personal library of commonly used C functions. As a student at 42, we are forbidden from using most standard C library functions, instead we recreate them and use them in our projects.

## Description

Libft is an individual project at 42 that requires us to re-create some standard C library functions including some additional ones that can be used later to build a library of useful functions for the rest of the program.

## Features

- Part 1: Libc functions
  - `ft_memset`: Fills memory with a constant byte.
  - `ft_bzero`: Erases the data in the n bytes of the memory starting at the location pointed to by s.
  - `ft_memcpy`: Copies n bytes from memory area src to memory area dest.
  - `ft_memccpy`: Copies no more than n bytes from memory area src to dest, stopping when the character c is found.
  - `ft_memmove`: Copies n bytes from src to dest, but for overlapping memory blocks, memmove() is a safer approach than memcpy().
  - `ft_memchr`: Scans the initial n bytes of the memory area pointed to by s for the first instance of c.
  - `ft_memcmp`: Compares the first n bytes of the memory areas s1 and s2.
  - `ft_strlen`: Calculates the length of the string pointed to by s, excluding the terminating null byte.
  - `ft_strdup`: Returns a pointer to a new string which is a duplicate of the string s.
  - `ft_strcpy`: Copies the string pointed to by src, including the null byte, to the buffer pointed to by dest.
  - `ft_strncpy`: Similar to ft_strcpy, but copies at most n bytes.
  - `ft_strcat`: Appends the src string to the dest string, overwriting the terminating null byte at the end of dest, and then adds a terminating null byte.
  - `ft_strncat`: Similar to ft_strcat, but appends at most n bytes of src.
  - `ft_strlcat`: Appends string src to the end of dest, and will append at most size - strlen(dest) - 1 bytes, always null-terminating the result.
  - `ft_strchr`: Returns a pointer to the first occurrence of the character c in the string s.
  - `ft_strrchr`: Returns a pointer to the last occurrence of the character c in the string s.
  - `ft_strstr`: Finds the first occurrence of the substring needle in the string haystack.
  - `ft_strnstr`: Similar to ft_strstr, but searches not more than n characters.
  - `ft_strcmp`: Compares the two strings s1 and s2.
  - `ft_strncmp`: Similar to ft_strcmp, but compares not more than n characters.
  - `ft_atoi`: Converts the string pointed to by str to an integer.
  - `ft_isalpha`: Checks whether the passed character is alphabetic.
  - `ft_isdigit`: Checks whether the passed character is a decimal digit character.
  - `ft_isalnum`: Checks whether the passed character is alphanumeric.
  - `ft_isascii`: Checks whether the passed character is a 7-bit unsigned char value that fits into the ASCII character set.
  - `ft_isprint`: Checks whether the passed character is printable.
  - `ft_toupper`: Converts a given letter to uppercase.
  - `ft_tolower`: Converts a given letter to lowercase.

- Part 2: Additional functions
  - `ft_memalloc`: Allocates and returns a “fresh” memory area.
  - `ft_memdel`: Takes as a parameter the address of a memory area that needs to be freed, then puts the pointer to NULL.
  - `ft_strnew`: Allocates and returns a “fresh” string ending with ’\0’.
  - `ft_strdel`: Takes as a parameter the address of a string that need to be freed, then sets its pointer to NULL.
  - `ft_strclr`: Sets every character of the string to the value ’\0’.
  - `ft_striter`: Applies the function f to each character of the string passed as argument.
  - `ft_striteri`: Applies the function f to each character of the string passed as argument, and passing its index as first argument.
  - `ft_strmap`: Applies the function f to each character of the string given as argument to create a “fresh” new string resulting from the successive applications of f.
  - `ft_strmapi`: Applies the function f to each character of the string passed as argument by giving its index as first argument to create a “fresh” new string resulting from the successive applications of f.
  - `ft_strequ`: Lexicographical comparison between s1 and s2. If the 2 strings are identical the function returns 1, or 0 otherwise.
  - `ft_strnequ`: Similar to ft_strequ, but compares at most n characters.
  - `ft_strsub`: Allocates and returns a “fresh” substring from the string given as argument.
  - `ft_strjoin`: Allocates and returns a “fresh” string that is the concatenation of s1 and s2.
  - `ft_strtrim`: Allocates and returns a copy of the string given as argument without whitespaces at the beginning or at the end.
  - `ft_strsplit`: Allocates and returns an array of “fresh” strings all ending with ’\0’, obtained by splitting s using the character c as a delimiter.
  - `ft_itoa`: Convert a number into a string.
  - `ft_putchar`: Outputs the character c to the standard output.
  - `ft_putstr`: Outputs the string s to the standard output.
  - `ft_putendl`: Outputs the string s to the standard output followed by a ’\n’.
  - `ft_putnbr`: Outputs the integer n to the standard output.
  - `ft_putchar_fd`: Outputs the char c to the file descriptor fd.
  - `ft_putstr_fd`: Outputs the string s to the file descriptor fd.
  - `ft_putendl_fd`: Outputs the string s to the file descriptor fd followed by a ’\n’.
  - `ft_putnbr_fd`: Outputs the integer n to the file descriptor fd.

- Part 3: Bonus functions
  - `ft_lstnew`: Allocates and returns a “fresh” link. The variables content and content_size of the new link are initialized by copy of the parameters of the function.
  - `ft_lstdelone`: Takes as a parameter a link’s pointer address and frees the memory of the link’s content using the function del given as a parameter, then frees the link’s memory using free.
  - `ft_lstdel`: Takes as a parameter the adress of a pointer to a link and frees the memory of this link and every successors of that link using the functions del and free.
  - `ft_lstadd`: Adds the element new at the beginning of the list.
  - `ft_lstiter`: Iterates the list lst and applies the function f to each link.
  - `ft_lstmap`: Iterates a list lst and applies the function f to each link to create a “fresh” list resulting from the successive applications of f.

## Getting Started

### Dependencies

- GCC 4.8.4 or later
- GNU make 3.81 or later
- git

### Installing

```bash
git clone https://github.com/username/libft.git
cd libft
make
make bonus
```
This will compile the libft library and generate a libft.a and libft_bonus.a file.

### Usage
Include libft in your C project:
```
#include "libft.h"
```
Compile your project with libft:
```
gcc -L. -lft your_source_file.c // for libft.a
gcc -L. -lft_bonus your_source_file.c // for libft_bonus.a
```
Please replace the placeholders with the actual information about your project.


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
