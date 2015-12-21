// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h" //<spl/gevents.h>
#include "gobjects.h" //<spl/gobjects.h>
#include "gwindow.h" //<spl/gwindow.h>

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


//paddle width and height in pixels
#define PADDLEW 60
#define PADDLEH 8


//prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GObject detectCollision(GWindow window, GOval ball);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);


int main (void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
    
    
    
    //instantiate bricks
    initBricks(window);
    
    
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    add(window, ball);
    
    //instantiate paddle
    GRect paddle = initPaddle(window);
    
    //number of bricks initially
    int bricks = 50;
    
    //number of lives initially
    int lives = 3;
    
    //scoreboard
    int score = 0;
    // to store 50 through 0 (with '\0'), we need <= 3 chars
    char s[3];
    // convert i from int to string
    sprintf(s, "%i", score);
    GLabel label = initScoreboard(window);
    add(window, label);
    setLabel(label, s);
    
    
    
    //initial velocity of ball
    double velocityX = drand48()    ;
    double velocityY = drand48() * 10;
    
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        
        
        
            //MOVEMENTS
       
        
            //BALL
            //move ball along x and y axis
            move(ball, velocityX, velocityY);
            
            // bounce off right edge of window
            if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                velocityX = -velocityX;
            }
            // bounce off left edge of window
            else if (getX(ball) <= 0)
            {
                velocityX = -velocityX;
            }
            //bounce off top edge of window
            else if (getY(ball) <= 0)
            {
                velocityY = -velocityY;
            }
            
            //bounce off bottom edge of window
            else if (getY(ball) + getHeight(ball) >= 600)
            {
                lives --;
                if (lives <= 0)
                {
                    closeGWindow(window);
                }
                //velocityY = -velocityY;
                waitForClick();
                setLocation(ball, 250, 180);
            }
            
            //COLLISION WITH OTHER OBJECTS
        
            GObject object = detectCollision(window, ball);
        
            
            //If the object is a GRect
            if  (strcmp(getType(object), "GRect") == 0)
            {
                
                    velocityY = -velocityY;
                    //if the object is not the paddle then it is a brick
                    //and we remove it.
                    if (object != paddle)
                    {
                        removeGWindow(window, object);
                        score++;
                        bricks--;
                        //update label
                        sprintf(s, "%i", score);
                        setLabel(label, s);
                    }
            }
            
            // linger before moving again
            pause(5);
            
            //PADDLE
            // follow mouse forever
            // check for mouse event
            GEvent event = getNextEvent(MOUSE_EVENT);

            // if we heard one
            if (event != NULL)
            {
                // if the event was movement
                if (getEventType(event) == MOUSE_MOVED)
                {
                    // ensure circle follows top cursor
                    double x = getX(event) - getWidth(paddle) / 2;
                    double y = 550;
                    setLocation(paddle, x, y);
                }
            }
        
    }
    
    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    
    return 0;
}


//function to instantiate bricks
void initBricks(GWindow window)
{
    for(int i=0; i<100; i=i+20)
    {
        for (int j=0; j<400; j=j+40)
        {
            GRect brick = newGRect(13 + j-10 , 35 + i , 33, 10);
            if (i> 0 && i<= 20)
                setColor(brick, "RED");
            else if (i>20 && i<=40)
                setColor(brick, "YELLOW");
            else if (i>40 && i<=60)
                setColor(brick, "GRAY");
            else if (i>60 && i<=80)
                setColor(brick, "BLUE");
            else
                setColor(brick, "GREEN");
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(175, 275, 25, 25);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(187, 550, PADDLEW, PADDLEH);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    // instantiate label
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    //add(window, label);
    setLocation(label, 175, 200);
     
    return label;
}




/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
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
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}



