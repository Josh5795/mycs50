/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    //for each row
    int dsquared = (d*d);
    int count = 0;
    for(int i = 0; i < d; i++)
    {
        //for each column
        for(int j = 0; j < d; j++)
        {
            //set value for tile (if even number dimension swap 1 and 2)
            count = count + 1;
            board[i][j] = (dsquared - count);
        }
    }
    if(d%2==0)
    {
        int rowindex1;
        int rowindex2;
        int columnindex1;
        int columnindex2;
        //for each row
        for(int i = 0; i < d; i++)
        {
            //for each column
            for(int j = 0; j < d; j++)
            {
                if(board[i][j]==1)
                {
                    rowindex1 = i;
                    columnindex1 = j;
                }
                if(board[i][j]==2)
                {
                    rowindex2 = i;
                    columnindex2 = j;
                }
            }
        }

        int temp = board[rowindex1][columnindex1];
        board[rowindex1][columnindex1] = board[rowindex2][columnindex2];
        board[rowindex2][columnindex2] = temp;
    }
}
/**
 * Prints the board in its current state.
 */
void draw(void)
{
    //for each row
    for(int i = 0; i < d; i++)
    {
        //print new line
        printf("\n");
        //for each column
        for(int j = 0; j < d; j++)
        {
            if(board[i][j]==0)
            {
                board[i][j]=95;
                printf("%2c ", board[i][j]);
            }
            else if(board[i][j]==95)
            {
                printf("%2c ", board[i][j]);
            }
            else
            {
                //print one integer at a time
                printf("%2i ", board[i][j]);
            }
        }
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
         //for each row
        for(int i = 0; i < d; i++)
        {
            //for each column
            for(int j = 0; j < d; j++)
            {
                int tilerowindex;
                int tilecolumnindex;
                int belowrowindex;
                int belowcolumnindex;
                int aboverowindex;
                int abovecolumnindex;
                int rightrowindex;
                int rightcolumnindex;
                int leftrowindex;
                int leftcolumnindex;

                if(board[i][j]==tile)
                {
                    tilerowindex=i;
                    tilecolumnindex=j;

                    if(board[tilerowindex+1][tilecolumnindex]==95)
                    {
                        belowrowindex=tilerowindex+1;
                        belowcolumnindex=tilecolumnindex;
                        int tempbelow = board[tilerowindex][tilecolumnindex];
                        board[tilerowindex][tilecolumnindex] = board[belowrowindex][belowcolumnindex];
                        board[belowrowindex][belowcolumnindex] = tempbelow;
                        return true;
                    }
                    if(board[tilerowindex-1][tilecolumnindex]==95)
                    {
                        aboverowindex=tilerowindex-1;
                        abovecolumnindex=tilecolumnindex;
                        int tempabove = board[tilerowindex][tilecolumnindex];
                        board[tilerowindex][tilecolumnindex] = board[aboverowindex][abovecolumnindex];
                        board[aboverowindex][abovecolumnindex] = tempabove;
                        return true;
                    }
                    if(board[tilerowindex][tilecolumnindex+1]==95)
                    {
                        rightrowindex=tilerowindex;
                        rightcolumnindex=tilecolumnindex+1;
                        int tempright = board[tilerowindex][tilecolumnindex];
                        board[tilerowindex][tilecolumnindex] = board[rightrowindex][rightcolumnindex];
                        board[rightrowindex][rightcolumnindex] = tempright;
                        return true;
                    }
                    if(board[tilerowindex][tilecolumnindex-1]==95)
                    {
                        leftrowindex=tilerowindex;
                        leftcolumnindex=tilecolumnindex-1;
                        int templeft = board[tilerowindex][tilecolumnindex];
                        board[tilerowindex][tilecolumnindex] = board[leftrowindex][leftcolumnindex];
                        board[leftrowindex][leftcolumnindex] = templeft;
                        return true;
                    }
                }
            }
        }
    return false;

}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    int count2 = 0;
    //for each row
    for(int i = 0; i < d; i++)
    {
        //for each column
        for(int j = 0; j < d; j++)
        {
            count2 = count2 + 1;
            if(board[i][j]!=(count2))
            {
                if(board[i][j]!=95)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
