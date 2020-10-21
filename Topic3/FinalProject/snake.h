
#ifndef __SNAKE_H__
#define __SNAKE_H__

#define KEYCODE_U 0x41 // Up button
#define KEYCODE_D 0x42 // Down button
#define KEYCODE_L 0x44 // Left button
#define KEYCODE_R 0x43 // Right button
#define KEYCODE_Q 0x71 // Q key

/* Attributes */
#define RESETATTR    0
#define BRIGHT       1
#define DIM          2
#define UNDERSCORE   4
#define BLINK        5           
#define REVERSE      7
#define HIDDEN       8


/* color */
#define BLACK        0x0
#define RED          0x1
#define GREEN        0x2
#define BROWN        0x3
#define BLUE         0x4
#define MAGENTA      0x5
#define CYAN         0x6
#define LIGHTGREY    0x7
#define DARKGREY     0x10
#define LIGHTRED     0x11
#define LIGHTGREEN   0x12
#define YELLOW       0x13
#define LIGHTBLUE    0x14
#define LIGHTMAGENTA 0x15
#define LIGHTCYAN    0x16
#define WHITE        0x17

#define __set_gm(attr,color,val)                                        \
        if (!color)                                                     \
                printf("\e[%dm", attr);                                 \
        else                                                            \
                printf("\e[%d;%dm", color & 0x10 ? 1 : 0, (color & 0xF) + val)

#define textattr(attr)        __set_gm(attr, 0, 0)
#define textcolor(color)      __set_gm(RESETATTR, color, 30)
#define textbackground(color) __set_gm(RESETATTR, color, 40)

#define clrscr()              puts ("\e[2J\e[1;1H")
#define gotoxy(x,y)           printf("\e[%d;%dH", y, x)

#endif /* __SNAKE_H__ */


