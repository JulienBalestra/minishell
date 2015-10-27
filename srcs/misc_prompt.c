#include "sh1.h"
#include <unistd.h>

void display_prompt(void)
{
    write(1, PROMPT, PROMPT_SIZE);
}