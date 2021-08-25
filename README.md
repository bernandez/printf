# _printf

_printf is a simple custom printf function that formats and prints data to the standard output.

# Description
_printf() functiion formats and prints data to the standard output according to the format specified.

The function has the following conversion specifies:

+ %c - prints a character
+ %d - prints a decimal integer
+ %s - prints a string
+ %i - prints an integer


# Installation
 you can clone this repository  and use the function on your local machine.

```bash 
git clone https://github.com/andrew21-mch/printf.git
```

# Adding man_3_prinf to you mandb

To add the man_3_prinf page to your mandb run this script

```bash
sudo ./install
```

# Usage
+ include the `holberton.h ` header file on the function for using _printf().
+ All the files are to be compiled on Ubuntu 14.04 LTS
```bash
Compile your code with `gcc -Wall -Werror -Wextra -pedantic *.c`
```

### see example below
```c
#include <stdio.h>
#include "holberton.h"

int main(void)
{
    int i = 10;
    int print;
    char *s = "printf still under test by Andrew";
    _printf("%d %s %c\n", i, s, 'c');
     print =  _printf("%d", s); /* get number of characters */
     printf("%d\n", print); /* print number of characters */
    return 0;
}


```

# License
[GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.en.html)

# Copyright
Copyright (c) 2021 Nfon Andrew





