#include <stdio.h>
#include <string.h>
#include <crypt.h>

int main(void)
{
    char pw[5000];

    memset(pw, 'A', sizeof(pw) - 1);
    pw[sizeof(pw) - 1] = '\0';

    for (int len = 1; len < 4096; len++) {
        pw[len] = '\0';

        char *h = crypt(pw, "$6$salt$");

        if (!h || h[0] == '*') {
            printf("FAILED at len=%d: %s\n",
                   len,
                   h ? h : "(null)");
            return 0;
        }

        pw[len] = 'A';
    }

    printf("No failure up to 4095 bytes\n");
    return 0;
}
