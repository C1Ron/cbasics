/*
 * Remove comments from a 'C' program
 */

// Includes

#include <stdbool.h>
#include <stdio.h>

// Definitions

#define NOCOMM 0  // Current character is not within a comment
#define BLOCK  1  // Current character is within a block comment
#define LINE   2  // Current character is within a line comment

// Globals

static char prior = '\0';  // Prior character read from stream
static char current;       // Current character in stream
static char next;          // Next character

/*
 * eatchar()
 * Helper function to eat a character from the stream
 */

static void eatchar(void) {
    prior = current;
    current = next;
    next = getchar();
}

/* Main */

int main(void) {

    int commtype = NOCOMM;  // Comment state
    bool inquote = false;   // Inside a quoted string state

    current = getchar();
    while (current != EOF) {

        // Get look-ahead character

        next = getchar();

        // Perform lexical evaluation to determine state

        if (current == '\"' && prior != '\\' && next != '\'') {
            // handle quoted text string start & stop
            (void)putchar('\"');
            inquote = !inquote;
        } else if (!inquote && current == '/' && next == '*') {
            // handle the start of a block comment
            eatchar();
            commtype = BLOCK;
        } else if (!inquote && current == '/' && next == '/') {
            // handle the start of a line comment
            eatchar();
            commtype = LINE;
        } else if (!inquote && current == '*' && next == '/') {
            // handle the end of either a block or line comment
            eatchar();
            commtype = NOCOMM;
        } else if (commtype == NOCOMM || (commtype == LINE && current == '\n')) {
            // echo non-comment, i.e. valide 'c' code, text
            (void)putchar(current);
            commtype = NOCOMM;
        } else {
            // eat comment text
        }

        // Preserve current character as prior and move look-ahead to current

        prior = current;
        current = next;
    }

    return 0;
}
