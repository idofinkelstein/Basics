#define _DEFAULT_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>


void set_canonical_mode(int state);

int main()
{
    int count;
    char c;

    set_canonical_mode(0);

    printf("Sleeping...\n");
    sleep(5);   /* during the sleep - hit some keys on the keyboard */

    printf("Waking up...\n");

    ioctl(0, FIONREAD, &count); /* counts num of typings */
    printf("count: %d\n", count);

    c = read(0, &c, 1);

    ioctl(0, FIONREAD, &count);
    printf("count: %d\n", count);

    set_canonical_mode(1);

    /* explain... */

    return 0;
}



void set_canonical_mode(int state)
{
    struct termios ttystate;

    /* get the terminal state */
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state == 0)
    {
        /* turn off canonical mode */
        ttystate.c_lflag &= ~(ICANON);
        /* minimum of number input read */
        ttystate.c_cc[VMIN] = 1;
    }
    else
    {
        /* turn on canonical mode */
        ttystate.c_lflag |= ICANON;
    }

    /* set the terminal attributes */
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
