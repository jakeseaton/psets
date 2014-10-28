// BREAKOUT
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

// Custom GObjects
GLabel scoreboard;
GRect brick;
GRect paddle;
GOval ball;

// Custom Brick Variables
int between = 5;
int topspace = 50;
double brickheight = 10;
double brickwidth = 40;

// Custom Ball Variables 
float ivelocity = .05;
double ballx = (WIDTH / 2) - RADIUS;
double bally = (HEIGHT / 2) - RADIUS;
double diameter = 2 * RADIUS;
double velocityx;
double velocityy;

// Custom Paddle Variables
double PaddleHeight = 10;
double PaddleWidth = 80;
double PaddleY = HEIGHT - 50;
double PaddleX;

// Custom Game Variables
char points = 0;
char* end;

// main
int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // initial random velocity of ball
    velocityx = ivelocity * drand48();
    velocityy = -ivelocity * drand48();
    
    // game proper
    while (lives > 0 && bricks > 0)
    {
        // move ball
        move(ball, velocityx, velocityy);
        
        // detect collisions
        GObject object = detectCollision(window, ball);
        
        // detect mouse movements
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // collisions
        if (object != NULL) 
        {
            // if a rectangle
            if (strcmp(getType(object), "GRect") == 0)
            {
                // bounce off paddle
                if (object == paddle)
                {
                    // if on side
                    if (getY(ball) > PaddleY)
                    {
                        velocityx = -velocityx;
                        
                    }
                    
                    // if above the paddle
                    if (getY(ball) < PaddleY)
                    {
                        velocityy = -velocityy; 
                    }
                }
                
                // bounce off bricks and delete
                if (getY(object) != PaddleY)
                {
                    removeGWindow(window, object);
                    points++;
                    bricks--;
                    updateScoreboard(window, scoreboard, points);
                    velocityy = -velocityy;
                }
            }
        }
        // follow mouse
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                PaddleX = (getX(event) - (PaddleWidth / 2));
                setLocation(paddle, PaddleX, PaddleY);
            }
        }
        // bounce off sides
        if (getX(ball) <= 0 || getX(ball) + diameter >= WIDTH)
        {
            velocityx = -velocityx;  
        }
        
        // bounce off top
        if (getY(ball) <= 0)
        {
            velocityy = -velocityy;
        }
        
        // death
        if (getY(ball) + diameter >= HEIGHT)
        {
            // decrease lives
            lives--;
            
            // check for game over
            if (lives == 0)
            {
                end = "GAME OVER";
                removeGWindow(window, ball);
            }
            
            // reset
            else
            {
                setLocation(ball, ballx, bally);
                waitForClick();
                move(ball, velocityx, velocityy);
        
            }
         }
    }
    
    // check for win
    if (bricks == 0)
    {
        end = "VICTORY!!!";
    }
    
    // remove the scoreboard
    removeGWindow(window, scoreboard);
    
    // add the end banner
    GLabel banner = newGLabel(end);
    setColor(banner, "RED");
    setFont(banner, "SansSerif-36");
    add(window, banner);
    setLocation(banner, (getWidth(window) - getWidth(banner)) / 2, (getHeight(window) - getHeight(banner)) / 2);
    
    // wait for click before exiting
    waitForClick();

    // close
    closeGWindow(window);
    return 0;
}

// initBricks
void initBricks(GWindow window)
{
    // interate over rows and columns
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            // add blue bricks
            brick = newGRect(i * (brickwidth + between), topspace + j * (brickheight + between), brickwidth, brickheight);
            setColor(brick, "BLUE");
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

// initBall
GOval initBall(GWindow window)
{
    // create ball
    ball = newGOval(ballx, bally, diameter, diameter);
    
    // appearance 
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}
// initPaddle
GRect initPaddle(GWindow window)
{
    // center 
    PaddleX = ((WIDTH / 2) - (PaddleWidth / 2));
    paddle = newGRect(PaddleX, PaddleY, PaddleWidth, PaddleHeight);
    
    // appearance
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

// initScoreboard
GLabel initScoreboard(GWindow window)
{
    // create score board starting at 0
    scoreboard = newGLabel("0");
    
    // center
    setLocation(scoreboard, WIDTH / 2, HEIGHT / 2);
    
    // set font
    setFont(scoreboard, "SansSerif-36");
    add(window, scoreboard);
    return scoreboard;
}

// updateScoreboard
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}
// detectCollision
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + diameter, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + diameter);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + diameter, y + diameter);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
