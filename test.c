#include <stdio.h>
#include <string.h>
#include <crypt.h>

int main(void)
{
    char pw[1024];

    memset(pw, 'A', sizeof(pw)-1);
    pw[sizeof(pw)-1] = '\0';

    for (int len = 250; len <= 270; len++) {
        pw[len] = '\0';

        char *h = crypt(pw, "$6$salt$");

        printf("len=%d -> %s\n", len, h ? h : "(null)");

        pw[len] = 'A';
    }

    return 0;
}
