
#ifndef __SNAKE_H__
#define __SNAKE_H__

#define GOLD      '@'


#define MAXROW    22
#define MAXCOL    72

#define START_LEN (4 + level)
#define START_COL (MAXCOL / 2 - START_LEN)
#define START_ROW ((MAXROW + 1) / 2)

#define DEFAULT_DELAY 200000
#define DEFAULT_KEYS  {'a', 'd', 'w', 's', 'q'}

typedef enum { LEFT=0, RIGHT, UP, DOWN, QUIT, NUM_KEYS } direction_t;

/*
 * struct snake_segment_t using set size of snake
 */
typedef struct
{
   int row, col;
} snake_segment_t;


/*
 * struct snake_t using set attribute for snake
 */
typedef struct
{
   unsigned int    speed;
   direction_t     dir;
   int             len;
   snake_segment_t body[100];
} snake_t;


/*
 * struct screen_t 
 */
typedef struct
{
   int level;
   int score;
   int high_score;
   int gold;
   int obstacles;

   char grid[MAXROW][MAXCOL];
} screen_t;

#endif /* __SNAKE_H__ */

/**
 * Local Variables:
 *  version-control: t
 *  c-file-style: "ellemtel"
 * End:
 */
