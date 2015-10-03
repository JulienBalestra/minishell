void str_clear(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = '\0';
        i++;
    }
}

void buf_init(char *buf, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        buf[i] = '\0';
        i++;
    }
}