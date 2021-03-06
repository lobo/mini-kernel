#include <stdint.h>
#include "../libcModule/include/stdio.h"
#include "../libcModule/include/ctype.h"
#include "../libcModule/include/stdlib.h"
#include "../libcModule/include/string.h"
#include "./include/commands.h"
#include "../syscallModule/include/syscall.h"

int exec_echo(int argc, char **argv)
{
    args_shift(1, &argc, &argv);

    while (argc)
    {
        printf("%s", *argv++);
        if (--argc != 0)
            putchar(' ');
    }
    
    putchar('\n');

	return 0;
}

int
exec_help(int argc, char **argv)
{
	args_shift(1, &argc, &argv);

    printf("help         print this message\n");
    printf("echo         prints the arguments to stdout\n");    
    printf("prtc         print time\n");
    printf("srtc         set time\n");
    printf("sstest       display screensaver\n");
    printf("sstime       set screensaver timer\n");
    printf("malloc       reserves the number of bytes passed as arguments\n");
    printf("free         free an allocated address (in decimal format)\n");
    printf("smalloc      malloc strings passed as argument\n");
    printf("pheap        prints the heap structures\n");
    return 0;
}

int 
exec_set_rtc(int argc, char **argv)
{
    args_shift(1, &argc, &argv);

    if (argc != 3){
        printf("Incorrect clock format: srtc H M $S\n");
    }

    int hour = atoi(*argv++);
    int min = atoi(*argv++);
    int sec = atoi(*argv++);

    if (hour < 0 || hour > 24){
        printf("Invalid hour \n");
    }

    if (min < 0 || min > 60){
        printf("Invalid minutes \n");
    }

    if (sec < 0 || sec > 60){
        printf("Invalid seconds \n");
    }

    sc_rtc_set(hour * 10000 + min * 100 + sec);

    return 0;
}

int
exec_print_rtc(int argc, char **argv)
{
    int rtc = sc_rtc_get();

    int hour = rtc / 10000;
    int min = (rtc / 100) % 100;
    int sec = rtc % 100;

    printf("%d:%d:%d\n", hour, min, sec);

	return 0;
}

int
exec_test_ss(int argc, char **argv)
{
    sc_screensaver_test();
	return 0;
}

int
exec_set_ss(int argc, char **argv)
{
    args_shift(1, &argc, &argv);

    int newTime = atoi(*argv);

    if (newTime <= 0) {
        printf("New trigger time must be greater than 0\n");
        return 1;
    }

    sc_set_screensaver_timer(atoi(*argv));

	return 0;
}

int exec_string_malloc(int argc, char **argv){
    args_shift(1, &argc, &argv);

    while (argc)
    {
        char * s = (char *)malloc(strlen(*argv)+1);
        if (s){
            strcpy(s, *argv++);
            printf("Malloc string \"%s\" at address %u\n",s,s); 
        }else{
            printf("Not enough heap for \"%s\"", *argv++);
        }
        argc--;
    }
    return 0;
}

int exec_malloc(int argc, char **argv){
    args_shift(1, &argc, &argv);

    void * s = malloc(uatoi(*argv));
    if (s){
        printf("Malloc %d bytes at address %u\n", uatoi(*argv), s);
    }else{
        printf("Not enough heap for %d bytes\n", uatoi(*argv));
    }
    return 0;
}

int exec_print_heap(int argc, char **argv){
    type_block curBlock = getBaseBlock();
    
    if (!curBlock){
        printf("Heap is empty bro\n");
        return 1;
    }
    while (curBlock){
        printf("Block address: %u\nData address: %u\nBlock size: %d\nPrev block: %u\nNext block: %u\nFree: %d\nString: %s\n\n", curBlock, curBlock + 1, curBlock->size, curBlock->prev, curBlock->next, curBlock->free, curBlock + 1);
        curBlock = curBlock->next;
    }
    return 0;
}

int exec_free(int argc, char **argv){
    args_shift(1, &argc, &argv);

    while (argc)
    {
        void * dir = (void *)atoi(*argv++);
        free(dir);
        printf("Freeing address %u\n",dir);
        argc--;
    }
    return 0;
}

int
args_shift(int n, int *argc, char ***argv)
{
    if (*argc >= n)
    {
        *argc -= n;
        *argv += n;
    }
    return *argc - n;
}