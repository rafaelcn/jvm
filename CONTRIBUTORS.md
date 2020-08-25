# Style

The code style used in this project is K&R with the 1TBS variation. Some
guidelines are written below:

**do not** write more than 80 characters in a line

```
// bad
{
    ...
    {
        ...
        {
            ...
            if (some expression && some other expression && which gets other value)
        }
    }
}

// good
{
    ...
    {
        ...
        {
            ...
            // evaluate the expressions to minimize the line length
            bool result = some other expression && which gets other value;
            if (some expression && result)
        }
    }
}

```

**do not** open a parenthesis just after something that isn't a function such
as an if clause.

```
// bad
if(expression) { ... }
// still bad
switch(expression) { ... }

// good
if (expression) { ... }
// very good
switch (expression) { ... }
```

**do** comment on code you think wouldn't be understandable without any
context or to explain why.

```
uint32_t color;

// the code below extracts the color components (RGBA) of a number
uint8_t red = color & 0xFF000000;
uint8_t green = color & 0x00FF0000;
uint8_t blue = color & 0x0000FF00;
uint8_t alpha = color & 0x000000FF;

```

**do** document functions, structures and other kind of metadata to be exported
by doxygen, but only do so on the header files, if such structures are available
there (a structure in a compiling unit wouldn't be exported and the
documentation would have to be avaible there instead).

```
/**
 * @brief This function that sums two values
 * @param param1 An operand for the sum operation
 * @param param2 An operand for the sum operation
 */
int sum(int x, int y) {}
```

**do** when including headers in a compiling unit (a .c file) follow the order:

```
#include "header_file.h"

#include <stdlib.h>
#include <stdio.h>
#include <other_system_headers.h>

#include "other_project_headers.h"
```

If you are reasoning about why or want to modify in any way you can always open
an [issue](https://github.com/jvm/issues/new).

# Modifying code

You are free to modify code the way you see fit but we are no obligated nor we
have the responsability to check (write a test for your case) or to approve the
code in our source, that's why this an _Open Source_ project under the MIT
terms.

Having said that, whenever you feel the urge to fix or implement something
please adhere to the code conventions written in the first section nd send us a
pull request.

# Pull Requests

The style of pull requests we adopt here is the _feature/_, _hotfix/_ branch
style. Is very much like the [gitflow](https://www.gitflow.com/) one.