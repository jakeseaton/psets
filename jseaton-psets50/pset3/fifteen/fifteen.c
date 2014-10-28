 #define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);
void swap(int* a, int* b);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();
 
    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

// Clears screen.

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

// Greets player.
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

// Initializes the board.
void init(void)
{
    // iterates over board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // places blank space
            if ((i == d-1) && (j == d-1))
            {
                board[i][j] = 0;
            }
            // fills rest of array with numbers
            else
            {
                board[i][j] = (d*d)-(d * i + j + 1);
            }
            
        }
    }
    // prevents glitch
    if (d % 2 == 0)
    {
        int temp;
        temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
    }
}

// Prints the board in its current state

void draw(void)
{
     for (int i = 0; i < d; i++)
     {
        for (int j = 0; j < d; j++)
        {
            // prints blank space
            if (board[i][j] == 0)
            {
                printf("__");
            }
            // prints numbers
            else
            {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
     }          
}


// swaps the values stored in two adresses
void swap(int* a, int* b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;    
    }
//If tile borders blank space, moves tile and returns true, else false
bool move(int tile)
{
    // prototypes
    int spacei;
    int spacej;
    int tilei;
    int tilej;
    
    //iterates over board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // finds blank space
            if (board[i][j] == 0)
            {
                // tracks location of blank space
                spacei = i;
                spacej = j;
            }
        }
    }
    // iterates over board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // finds tile
            if (board[i][j] == tile)
            {
                // tracks location of tile
                tilei = i;
                tilej = j;
            }
        }
    }
    // if blank space and tile are in the same row
    if (tilei == spacei)
    {
        // if adjascent
        if ((tilej == spacej + 1) || (tilej == spacej - 1))
        {
            swap(&board[spacei][spacej], &board[tilei][tilej]);
            return true;
        }
        else
        {
            return false;
        }
    }
    // if blank space and tile are in the same column
    if (tilej == spacej)
    {
        // if adjascent
        if ((tilei == spacei + 1) || (tilei == spacei - 1))
        {
            swap(&board[spacei][spacej], &board[tilei][tilej]);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
       return false; 
    }
}
// Returns true if game is won

bool won(void)
{
    // initializes temporary variable
    int temp = 1;
    // checks location of blank space first
    if (board[d-1][d-1] == 0)
    {
        // iterates over board
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                // if not on the blank space
                if (board[i][j] != 0)
                {
                    // if number is correct, continue
                    if (board[i][j] == temp)
                    {
                        temp++;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}
/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
	fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
	fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
