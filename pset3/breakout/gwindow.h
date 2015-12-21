/*
 * File: gwindow.h
 * ---------------
 * This interface defines an abstract type representing a graphics window.
 */

#ifndef _gwindow_h
#define _gwindow_h

#include "cslib.h"
#include "gtypes.h"

#ifndef _gobjects_h

typedef void *GObject;

/*
 * Type: GWindow
 * -------------
 * This type represents a graphics window that supports simple graphics. 
 * Each GWindow consists of two layers.  The background layer provides a
 * surface for drawing static pictures that involve no animation. 
 * Graphical objects drawn in the background layer are persistent and do
 * not require the client to update the contents of the window.  The
 * foreground layer contains graphical objects that are redrawn as
 * necessary.
 *
 * The GWindow type includes several functions that draw lines, rectangles,
 * and ovals on the background layer without making use of the facilities
 * of the gobjects.h interface.  For example, the following program draws a
 * diamond, rectangle, and oval at the center of the window.
 *
 *    main() {
 *       double width, height;
 *       GWindow gw;
 *
 *       gw = newGWindow(500, 300);
 *       width = getWidth(gw);
 *       height = getHeight(gw);
 *       drawLine(gw, 0, height / 2, width / 2, 0);
 *       drawLine(gw, width / 2, 0, width, height / 2);
 *       drawLine(gw, width, height / 2, width / 2, height);
 *       drawLine(gw, width / 2, height, 0, height / 2);
 *       setColor(gw, "BLUE");
 *       fillRect(gw, width / 4, height / 4, width / 2, height / 2);
 *       setColor(gw, "GRAY");
 *       fillOval(gw, width / 4, height / 4, width / 2, height / 2);
 *    }
 */

typedef struct GWindowCDT *GWindow;

#endif

/*
 * Function: newGWindow
 * Usage: gw = newGWindow(width, height);
 * --------------------------------------
 * Creates and displays a graphics window with the specified dimensions.
 */

GWindow newGWindow(double width, double height);

/*
 * Function: closeGWindow
 * Usage: closeGWindow(gw);
 * ------------------------
 * Deletes the window from the screen.
 */

void closeGWindow(GWindow gw);

/*
 * Function: requestFocus
 * Usage: requestFocus(gw);
 * ------------------------
 * Asks the system to assign the keyboard focus to the window, which brings
 * it to the top and ensures that key events are delivered to the window. 
 * Clicking in the window automatically requests the focus.
 */

void requestFocus(GWindow gw);

/*
 * Function: clear
 * Usage: clear(gw);
 * -----------------
 * Clears the contents of the window.
 */

void clearGWindow(GWindow gw);

/*
 * Function: setVisible
 * Usage: setVisible(gw, flag);
 * ----------------------------
 * Determines whether the window is visible on the screen.
 */

void setVisibleGWindow(GWindow gw, bool flag);

/*
 * Function: isVisible
 * Usage: if (isVisible(gw)) . . .
 * -------------------------------
 * Tests whether the window is visible.
 */

bool isVisibleGWindow(GWindow gw);

/*
 * Function: drawLine
 * Usage: drawLine(gw, x0, y0, x1, y1);
 * ------------------------------------
 * Draws a line connecting the specified points.
 */

void drawLine(GWindow gw, double x0, double y0, double x1, double y1);

/*
 * Function: drawPolarLine
 * Usage: pt = drawPolarLine(gw, x, y, r, theta);
 * ----------------------------------------------
 * Draws a line of length r in the direction theta from the initial point. 
 * The angle theta is measured in degrees counterclockwise from the +x
 * axis.  The method returns the end point of the line.
 */

GPoint drawPolarLine(GWindow gw, double x, double y, double r, double theta);

/*
 * Function: drawOval
 * Usage: drawOval(gw, x, y, width, height);
 * -----------------------------------------
 * Draws the frame of a oval with the specified bounds.
 */

void drawOval(GWindow gw, double x, double y, double width, double height);

/*
 * Function: fillOval
 * Usage: fillOval(gw, x, y, width, height);
 * -----------------------------------------
 * Fills the frame of a oval with the specified bounds.
 */

void fillOval(GWindow gw, double x, double y, double width, double height);

/*
 * Function: drawRect
 * Usage: drawRect(gw, x, y, width, height);
 * -----------------------------------------
 * Draws the frame of a rectangle with the specified bounds.
 */

void drawRect(GWindow gw, double x, double y, double width, double height);

/*
 * Function: fillRect
 * Usage: fillRect(gw, x, y, width, height);
 * -----------------------------------------
 * Fills the frame of a rectangle with the specified bounds.
 */

void fillRect(GWindow gw, double x, double y, double width, double height);

/*
 * Function: setColor
 * Usage: setColor(gw, color);
 * ---------------------------
 * Sets the color used for drawing.  The color parameter is usually one of
 * the predefined color names from Java: BLACK, BLUE, CYAN, DARK_GRAY,
 * GRAY, GREEN, LIGHT_GRAY, MAGENTA, ORANGE, PINK, RED, WHITE, or YELLOW. 
 * The case of the individual letters in the color name is ignored, as are
 * spaces and underscores, so that the Java color DARK_GRAY could be
 * written as "Dark Gray".
 */

void setColorGWindow(GWindow gw, string color);

/*
 * Function: getColor
 * Usage: color = getColor(gw);
 * ----------------------------
 * Returns the current color as a string in the form "#rrggbb".  In this
 * string, the values rr, gg, and bb are two-digit hexadecimal values
 * representing the red, green, and blue components of the color,
 * respectively.
 */

string getColorGWindow(GWindow gw);

/*
 * Function: getWidth
 * Usage: width = getWidth(gw);
 * ----------------------------
 * Returns the width of the graphics window in pixels.
 */

double getWidthGWindow(GWindow gw);

/*
 * Function: getHeight
 * Usage: height = getHeight(gw);
 * ------------------------------
 * Returns the height of the graphics window in pixels.
 */

double getHeightGWindow(GWindow gw);

/*
 * Function: repaint
 * Usage: repaint(gw);
 * -------------------
 * Schedule a repaint on the graphics window.
 */

void repaint(GWindow gw);

/*
 * Function: setWindowTitle
 * Usage: setWindowTitle(gw, title);
 * ---------------------------------
 * Sets the title of the graphics window.
 */

void setWindowTitle(GWindow gw, string title);

/*
 * Function: getWindowTitle
 * Usage: title = getWindowTitle(gw);
 * ----------------------------------
 * Returns the title of the graphics window.
 */

string getWindowTitle(GWindow gw);

/*
 * Function: draw
 * Usage: draw(gw, gobj);
 * ----------------------
 * Draws the GObject on the background layer.
 */

void draw(GWindow gw, GObject gobj);

/*
 * Function: drawAt
 * Usage: drawAt(gw, gobj, x, y);
 * ------------------------------
 * Moves the GObject to (x, y) and then draws it on the window.
 */

void drawAt(GWindow gw, GObject gobj, double x, double y);

/*
 * Function: add
 * Usage: add(gw, gobj);
 * ---------------------
 * Adds the GObject to the foreground layer of the window.  Adding a
 * GObject to a GWindow transfers control of the memory for that object
 * from the client to the graphics package.  Freeing a GWindow
 * automatically frees any GObjects it contains.
 */

void addGWindow(GWindow gw, GObject gobj);

/*
 * Function: addAt
 * Usage: addAt(gw, gobj, x, y);
 * -----------------------------
 * Adds the GObject to the foreground layer of the window after moving it
 * to the point (x, y).
 */

void addAt(GWindow gw, GObject gobj, double x, double y);

/*
 * Function: addToRegion
 * Usage: addToRegion(gw, gobj, region);
 * -------------------------------------
 * Adds the GObject (which must be an interactor or a label) to the control
 * strip specified by region.  The region parameter must be one of the
 * strings "NORTH", "EAST", "SOUTH", or "WEST".
 */

void addToRegion(GWindow gw, GObject gobj, string region);

/*
 * Function: remove
 * Usage: remove(gw, gobj);
 * ------------------------
 * Removes the object from its container or region.
 */

void removeGWindow(GWindow gw, GObject gobj);

/*
 * Function: getGObjectAt
 * Usage: gobj = getGObjectAt(gw, x, y);
 * -------------------------------------
 * Returns a pointer to the topmost GObject containing the point (x, y), or
 * NULL if no such object exists.
 */

GObject getGObjectAt(GWindow gw, double x, double y);

/*
 * Function: setRegionAlignment
 * Usage: setRegionAlignment(gw, region, align);
 * ---------------------------------------------
 * Sets the alignment of the specified side region as specified by the
 * string align.  The region parameter must be one of the strings "NORTH",
 * "EAST", "SOUTH", or "WEST" and the align parameter must be "LEFT",
 * "RIGHT", or "CENTER".  By default, side panels use CENTER alignment.
 */

void setRegionAlignment(GWindow gw, string region, string align);

/*
 * Function: pause
 * Usage: pause(milliseconds);
 * ---------------------------
 * Pauses for the indicated number of milliseconds.  This function is
 * useful for animation where the motion would otherwise be too fast.
 */

void pause(double milliseconds);

#endif
