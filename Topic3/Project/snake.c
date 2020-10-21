
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>

#include "conio.h"
#include "snake.h"

#ifdef DEBUG
#define DBG(fmt, args...) fprintf (stderr, fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

/* Default 0.2 sec between snake movement. */
unsigned int usec_delay = DEFAULT_DELAY;


/* Parameter for thread 
 *  struct paramThread1 stored parameters of function show_score()
 *  struct paramThread2 stored parameters of function setup_level()
 *  struct paramThread3 stored parameters of function move()
 */





/*
 **********************************************************
 */
int sigsetup (int signo, void (*callback)(int))
{
   struct sigaction action;

   sigemptyset(&action.sa_mask);
   //sigaddset(&action.sa_mask, signo);
   action.sa_flags = 0;
   action.sa_handler = callback;
   if (SIGALRM == signo)
   {
#ifdef SA_INTERRUPT
      action.sa_flags |= SA_INTERRUPT; /* SunOS 4.x */
#endif
   }
   else
   {
#ifdef SA_RESTART
      action.sa_flags |= SA_RESTART; /* SVR4, 4.4BSD */
#endif
   }

   return sigaction (signo, &action, NULL);
}



/*
 **********************************************************
 */
void sig_handler (int signal __attribute__ ((unused)))
{
   clrscr ();
   DBG("Received signal %d\n", signal);
   exit (WEXITSTATUS(system ("stty sane")));
}

void alarm_handler (int signal __attribute__ ((unused)))
{
   static struct itimerval val;

   if (!signal)
   {
      sigsetup (SIGALRM, alarm_handler);
   }

   val.it_value.tv_sec  = 0;
   val.it_value.tv_usec = usec_delay;

   setitimer (ITIMER_REAL, &val, NULL);
}

/*
 * Show score , using struct screen_t
 */
void show_score (screen_t *screen)
{
   textcolor (LIGHTCYAN);
   gotoxy (3, MAXROW + 2);
   printf ("Level: %d\t\t", screen->level);

   textcolor (YELLOW);
   gotoxy (21, MAXROW + 2);
   printf ("Gold Left: %d\t\t", screen->gold);

   textcolor (LIGHTGREEN);
   gotoxy (43, MAXROW + 2);
   printf ("Score: %d\t\t", screen->score);

   textcolor (LIGHTMAGENTA);
   gotoxy (61, MAXROW + 2);
   printf ("High Score: %d\t\t", screen->high_score);
}


/*
 * draw line 
 */
void draw_line (int col, int row)
{
   int i;
   gotoxy (col, row);
   textcolor (LIGHTBLUE);
   for (i = 0; i < MAXCOL + 2; i++)
   {
      if (i == 0 || i == MAXCOL + 1)
         printf ("+");
      else
         printf ("-");
   }
   textattr (RESETATTR);
}

/* If level==0 then just move on to the next level
 * if level==1 restart game
 * Otherwise start game at that level. 
 */
void setup_level (screen_t *screen, snake_t *snake, int level)
{
   int i, row, col;

   srand ((unsigned int)time (NULL));

   /* Initialize on (re)start */
   if (1 == level)
   {
      screen->score = 0;
      screen->obstacles = 4;
      screen->level = 1;
      snake->speed = 14;
      snake->dir = RIGHT;
   }
   else
   {
      //screen->score += screen->level * 1000;
      screen->obstacles += 2;    /* add to obstacles */
      screen->level++;          

      if ((screen->level % 5 == 0) && (snake->speed > 1))
      {
         snake->speed--;        /* increase snake->speed every 5 levels */
      }
   }

   /* Set up global variables for new level */
   screen->gold = 0;
   snake->len = level + 4;
   usec_delay = DEFAULT_DELAY - level * 10000;

   /* Fill grid with blanks */
   for (row = 0; row < MAXROW; row++)
   {
      for (col = 0; col < MAXCOL; col++)
      {
         screen->grid[row][col] = ' ';
      }
   }

   /* Fill grid with objects */
   for (i = 0; i < screen->obstacles * 2; i++)
   {
      /* Find free space to place an object on. */
      do
      {
         row = rand () % MAXROW;
         col = rand () % MAXCOL;
      }
      while (screen->grid[row][col] != ' ');

      if (screen->obstacles < i)
      {
         screen->gold++;
         screen->grid[row][col] = GOLD;
      }
   }

   /* Create snake array of length snake->len */
   for (i = 0; i < snake->len; i++)
   {
      snake->body[i].row = START_ROW;
      snake->body[i].col = snake->dir == LEFT ? START_COL - i : START_COL + i;
   }

   /* Draw playing board */
   clrscr();
   draw_line (1, 1);

   for (row = 0; row < MAXROW; row++)
   {
      gotoxy (1, row + 2);
      textcolor (LIGHTBLUE);
      printf ("|");
      textattr (RESETATTR);

      textcolor (LIGHTBLUE);
      for (col = 0; col < MAXCOL; col++)
      {
         printf ("%c", screen->grid[row][col]);
      }
      printf ("|");
      textattr (RESETATTR);
   }

   draw_line (1, MAXROW + 2);

   show_score (screen);

   textcolor (CYAN);
   gotoxy (26, 1);
   printf ("<<<[DCHloft Studio]>>>");
}


/*
 * function control snake
 */
void move (snake_t *snake, char keys[], char key)
{
   int i;
   //direction_t prev = snake->dir;

   if (key == keys[RIGHT])
   {
      snake->dir = RIGHT;
   }
   else if (key == keys[LEFT])
   {
      snake->dir = LEFT;
   }
   else if (key == keys[UP])
   {
      snake->dir = UP;
   }
   else if (key == keys[DOWN])
   {
      snake->dir = DOWN;
   }
   

   switch (snake->dir)
   {
      case LEFT:
         snake->body[snake->len].row = snake->body[snake->len - 1].row;
         snake->body[snake->len].col = snake->body[snake->len - 1].col - 1;
         break;

      case RIGHT:
         snake->body[snake->len].row = snake->body[snake->len - 1].row;
         snake->body[snake->len].col = snake->body[snake->len - 1].col + 1;
         break;

      case UP:
         snake->body[snake->len].row = snake->body[snake->len - 1].row - 1;
         snake->body[snake->len].col = snake->body[snake->len - 1].col;
         break;

      case DOWN:
         snake->body[snake->len].row = snake->body[snake->len - 1].row + 1;
         snake->body[snake->len].col = snake->body[snake->len - 1].col;
         break;

      default:
         /* NOP */
         break;
   }

   /* Blank last segment of snake */
   textattr (RESETATTR);
   gotoxy (snake->body[0].col + 1, snake->body[0].row + 1);
   puts (" ");

   /* ... and remove it from the array */
   for (i = 1; i <= snake->len; i++)
   {
      snake->body[i - 1] = snake->body[i];
      if (i < 5){
         textbackground (WHITE); 
      }
   }
   textbackground (YELLOW);
   /* Display snake in while */
   
   for (i = 0; i < snake->len; i++)
   {
      gotoxy (snake->body[i].col + 1, snake->body[i].row + 1);
      puts (" ");
   }
   textattr (RESETATTR);
#ifdef DEBUG
#endif
}


/* Collision for head snake */
int collide (snake_t *snake)
{
   int i;
   snake_segment_t *head = &snake->body[snake->len - 1];

   /* dau ran va cham voi tuong */
   if ((head->row > MAXROW) || (head->row < 1) ||
       (head->col > MAXCOL) || (head->col < 1))
   {
      DBG("Wall collision.\n");
      return 1;
   }

   /* tu huy */
   for (i = 0; i < snake->len - 1; i++)
   {
      snake_segment_t *body = &snake->body[i];

      if (head->row == body->row && head->col == body->col)
      {
         DBG("Self collision.\n");
         return 1;
      }
   }
   return 0;
}


/*
 * Collision with object (GOLDEN)
 */

int collide_object (snake_t *snake, screen_t *screen, char object)
{
   snake_segment_t *head = &snake->body[snake->len - 1];

   if (screen->grid[head->row - 1][head->col - 1] == object)
   {
      DBG("Object '%c' collision.\n", object);
      screen->grid[head->row - 1][head->col - 1] = ' ';
      screen->gold--;
      //screen->score += snake->len * screen->obstacles;
      screen->score += 5;
      snake->len++;

      if (screen->score > screen->high_score)
      {
         screen->high_score = screen->score; /* New high score! */
      }
      show_score (screen);
      if (0 == screen->gold) return 1;
  
   }
   return 0;
}



int main (void)
{
   char keypress;
   snake_t snake;
   screen_t screen;
   char keys[NUM_KEYS] = DEFAULT_KEYS;

   if (WEXITSTATUS(system ("stty cbreak -echo stop u")))
   {
      fprintf (stderr, "Failed setting up the screen, is 'stty' missing?\n");
      return 1;
   }

   /* Call it once to initialize the timer. */
   alarm_handler (0);

   sigsetup (SIGINT, sig_handler);
   sigsetup (SIGHUP, sig_handler);
   sigsetup (SIGTERM, sig_handler);

   do
   {
      setup_level (&screen, &snake, 1);

      do
      {
         keypress = (char)getchar ();

         /* Move the snake one position. */
         move (&snake, keys, keypress);

         /* keeps cursor flashing in one place instead of following snake */
         gotoxy (1, 1);


         if (collide(&snake)){
            gotoxy (32, 6);
            textcolor (LIGHTRED);
            printf ("-G A M E  O V E R-");
            break;
         }
         if (1 == collide_object (&snake, &screen, GOLD)){
            setup_level (&screen, &snake, 0);     
         }
      }
      while (keypress != keys[QUIT]);

      show_score (&screen);
      gotoxy (32, 9);
      textcolor (YELLOW);
      printf ("Quit the game (y/n)? ");

      do
      {
         keypress = getchar ();
      }
      while ((keypress != 'y') && (keypress != 'n'));
   }
   while (keypress == 'y');

   clrscr ();

   return WEXITSTATUS(system ("stty sane"));
}

