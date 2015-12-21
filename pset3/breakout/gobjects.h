/*
 * File: gobjects.h
 * ----------------
 * This interface exports a hierarchy of graphical shapes based on the
 * model developed for the ACM Java Graphics.
 */

#ifndef _gobjects_h
#define _gobjects_h

#include "cslib.h"
#include "generic.h"
#include "gtypes.h"
#include "vector.h"

#ifndef _gwindow_h

typedef struct GWindowCDT *GWindow;

/*
 * Type: GObject
 * -------------
 * This type represents an abstract type that unifies the set of all
 * graphics objects.  As with an abstract class in an object-oriented
 * language, it is not legal to create a GObject directly.  Graphical
 * objects are created instead by calling the constructor for one of the
 * concrete subclasses, as follows:
 *
 *
 * 
 *     >newGRect(x, y, width, height)
 * 
 *     >newG3DRect(x, y, width, height, raised)
 * 
 *     >newGRoundRect(x, y, width, height, corner)
 * 
 *     >newGOval(x, y, width, height)
 * 
 *     >newGLine(x0, y0, x1, y1)
 * 
 *     >newGArc(x, y, width, height, start, sweep)
 * 
 *     >newGImage(filename, x, y)
 * 
 *     >newGLabel(str, x, y)
 * 
 *     >newGPolygon
 * 
 *     >newCompound
 *
 *
 * Even though C has no object-oriented hierarchies, this interface defines
 * the types GArc, GCompound, GImage, GLabel, GLine, GOval, GPolygon,
 * GRect, GRoundRect, and G3DRect as synonyms for GObject.  Doing so helps
 * to clarify what types are expected by each function and simplifies the
 * process of converting code from languages that implement full
 * hierarchies.
 */

typedef struct GObjectCDT *GObject;

#endif

/*
 * Function: freeGObject
 * Usage: freeGObject(gobj);
 * -------------------------
 * Frees the memory associated with the object.  This operation is not
 * necessary for objects that have been installed in a window.  Adding a
 * GObject to a GWindow or a GCompound transfers ownership to the
 * container, which assumes responsibility for freeing the object.
 */

void freeGObject(GObject gobj);

/*
 * Function: getX
 * Usage: x = getX(gobj);
 * ----------------------
 * Returns the x-coordinate of the object.
 */

double getXGObject(GObject gobj);

/*
 * Function: getY
 * Usage: y = getY(gobj);
 * ----------------------
 * Returns the y-coordinate of the object.
 */

double getYGObject(GObject gobj);

/*
 * Function: getLocation
 * Usage: pt = getLocation(gobj);
 * ------------------------------
 * Returns the location of this object as a GPoint.
 */

GPoint getLocation(GObject gobj);

/*
 * Function: setLocation
 * Usage: setLocation(gobj, x, y);
 * -------------------------------
 * Sets the location of this object to the specified coordinates.
 */

void setLocation(GObject gobj, double x, double y);

/*
 * Function: move
 * Usage: move(gobj, dx, dy);
 * --------------------------
 * Moves the object on the screen using the displacements dx and dy.
 */

void move(GObject gobj, double dx, double dy);

/*
 * Function: getWidth
 * Usage: width = getWidth(gobj);
 * ------------------------------
 * Returns the width of this object, which is defined to be the width of
 * the bounding box.
 */

double getWidthGObject(GObject gobj);

/*
 * Function: getHeight
 * Usage: height = getHeight(gobj);
 * --------------------------------
 * Returns the height of this object, which is defined to be the height of
 * the bounding box.
 */

double getHeightGObject(GObject gobj);

/*
 * Function: getSize
 * Usage: size = getSize(gobj);
 * ----------------------------
 * Returns the size of the object as a GDimension.
 */

GDimension getSize(GObject gobj);

/*
 * Function: getBounds
 * Usage: rect = getBounds(gobj);
 * ------------------------------
 * Returns the bounding box of this object, which is defined to be the
 * smallest rectangle that covers everything drawn by the figure.  The
 * coordinates of this rectangle do not necessarily match the location
 * returned by getLocation.  Given a GLabel object, for example,
 * getLocation returns the coordinates of the point on the baseline at
 * which the string begins; the getBounds method, by contrast, returns a
 * rectangle that covers the entire window area occupied by the string.
 */

GRectangle getBounds(GObject gobj);

/*
 * Function: setColor
 * Usage: setColor(gobj, color);
 * -----------------------------
 * Sets the color used to display this object.  The color string is usually
 * one of the predefined color names:
 *
 *    BLACK
 *    BLUE
 *    CYAN
 *    DARK_GRAY
 *    GRAY
 *    GREEN
 *    LIGHT_GRAY
 *    MAGENTA
 *    ORANGE
 *    PINK
 *    RED
 *    WHITE
 *    YELLOW
 *
 * The case of the individual letters in the color name is ignored, as are
 * spaces and underscores, so that the color DARK_GRAY can be written as
 * "Dark Gray".
 */

void setColorGObject(GObject gobj, string color);

/*
 * Function: getColor
 * Usage: color = getColor(gobj);
 * ------------------------------
 * Returns the color used to display this object.  This color is always
 * returned as a string in the form "#rrggbb", where rr, gg, and bb are the
 * red, green, and blue components of the color, expressed as two-digit
 * hexadecimal values.
 */

string getColorGObject(GObject gobj);

/*
 * Function: setVisible
 * Usage: setVisible(gobj, flag);
 * ------------------------------
 * Sets whether this object is visible.
 */

void setVisibleGObject(GObject gobj, bool flag);

/*
 * Function: isVisible
 * Usage: if (isVisible(gobj)) . . .
 * ---------------------------------
 * Returns true if this object is visible.
 */

bool isVisibleGObject(GObject gobj);

/*
 * Function: sendForward
 * Usage: sendForward(gobj);
 * -------------------------
 * Moves this object one step toward the front in the z dimension.  If it
 * was already at the front of the stack, nothing happens.
 */

void sendForward(GObject gobj);

/*
 * Function: sendToFront
 * Usage: sendToFront(gobj);
 * -------------------------
 * Moves this object to the front of the display in the z dimension.  By
 * moving it to the front, this object will appear to be on top of the
 * other graphical objects on the display and may hide any objects that are
 * further back.
 */

void sendToFront(GObject gobj);

/*
 * Function: sendBackward
 * Usage: sendBackward(gobj);
 * --------------------------
 * Moves this object one step toward the back in the z dimension.  If it
 * was already at the back of the stack, nothing happens.
 */

void sendBackward(GObject gobj);

/*
 * Function: sendToBack
 * Usage: sendToBack(gobj);
 * ------------------------
 * Moves this object to the back of the display in the z dimension.  By
 * moving it to the back, this object will appear to be behind the other
 * graphical objects on the display and may be obscured by other objects in
 * front.
 */

void sendToBack(GObject gobj);

/*
 * Function: contains
 * Usage: if (contains(gobj, x, y)) . . .
 * --------------------------------------
 * Returns true if the specified point is inside the object.
 */

bool containsGObject(GObject gobj, double x, double y);

/*
 * Function: getType
 * Usage: type = getType(gobj);
 * ----------------------------
 * Returns the subtype of the object as a string, as in "GOval" or "GRect".
 */

string getType(GObject gobj);

/*
 * Function: getParent
 * Usage: parent = getParent(gobj);
 * --------------------------------
 * Returns a pointer to the GCompound that contains this object.  Every
 * GWindow is initialized to contain a single GCompound that is aligned
 * with the window.  Adding objects to the window adds them to that
 * GCompound, which means that every object you add to the window has a
 * parent.  Calling getParent on the top-level GCompound returns NULL.
 */

GObject getParent(GObject gobj);

/* Functions that apply to several types */

/*
 * Function: setSize
 * Usage: setSize(gobj, width, height);
 * ------------------------------------
 * Changes the size of this object to the specified width and height.  This
 * method applies to the types GOval, GImage, and GRect (and its
 * subclasses).
 */

void setSize(GObject gobj, double width, double height);

/*
 * Function: setBounds
 * Usage: setBounds(gobj, x, y, width, height);
 * --------------------------------------------
 * Changes the bounds of this object to the specified values.  This method
 * applies to the types GOval, GImage, and GRect (and its subclasses).
 */

void setBounds(GObject gobj, double x, double y, double width, double height);

/*
 * Function: setFilled
 * Usage: setFilled(gobj, flag);
 * -----------------------------
 * Sets the fill status for gobj, where false is outlined and true is
 * filled.
 */

void setFilled(GObject gobj, bool flag);

/*
 * Function: isFilled
 * Usage: if (isFilled(gobj)) . . .
 * --------------------------------
 * Returns true if gobj is filled.
 */

bool isFilled(GObject gobj);

/*
 * Function: setFillColor
 * Usage: setFillColor(gobj, color);
 * ---------------------------------
 * Sets the color used to display the filled region of this rectangle.
 */

void setFillColor(GObject gobj, string color);

/*
 * Function: getFillColor
 * Usage: color = getFillColor(gobj);
 * ----------------------------------
 * Returns the color used to display the filled region of gobj.  rectangle.
 * If none has been set, getFillColor returns the empty string.
 */

string getFillColor(GObject gobj);

/*
 * Type: GRect
 * -----------
 * This type represents a graphical object whose appearance consists of a
 * rectangular box.  For example, the following code adds a filled, red,
 * 200x100 rectangle at the upper left corner of the graphics window:
 *
 *    main() {
 *       GWindow gw = newGWindow(500, 300);
 *       printf("This program draws a red rectangle at (0, 0).\n")
 *       GRect rect = newGRect(0, 0, 200, 100);
 *       setFilled(rect, true);
 *       setColor(rect, "RED");
 *       add(gw, rect);
 *    }
 */

typedef GObject GRect;

/*
 * Function: newGRect
 * Usage: rect = newGRect(x, y, width, height);
 * --------------------------------------------
 * Creates a new GRect with the specified bounds.  By default, the
 * rectangle is unfilled.
 */

GRect newGRect(double x, double y, double width, double height);

/*
 * Type: GRoundRect
 * ----------------
 * This type represents a rectangular box with rounded corners.
 */

typedef GRect GRoundRect;

/*
 * Function: newGRoundRect
 * Usage: GRoundRect rect = newGRoundRect(x, y, width, height, corner);
 * --------------------------------------------------------------------
 * Creates a new GRoundRect with the specified dimensions.  The corner
 * parameter specifies the diameter of the arc forming the corner.
 */

GRoundRect newGRoundRect(double x, double y, double width, double height,
                                             double corner);

/*
 * Type: G3DRect
 * -------------
 * This type represents a rectangular box that can appear raised or
 * lowered.
 */

typedef GRect G3DRect;

/*
 * Function: newG3DRect
 * Usage: G3DRect rect = newG3DRect(x, y, width, height, raised);
 * --------------------------------------------------------------
 * Creates a new G3DRect with the specified dimensions.  The corner
 * parameter specifies whether this rectangle should appear raised.
 */

G3DRect newG3DRect(double x, double y, double width, double height,
                                       bool raised);
/*
 * Function: setRaised
 * Usage: setRaised(rect, raised);
 * -------------------------------
 * Indicates whether this object appears raised.
 */

void setRaised(G3DRect rect, bool raised);

/*
 * Function: isRaised
 * Usage: if (isRaised(rect)) ...
 * ------------------------------
 * Returns true if this object appears raised.
 */

bool isRaised(G3DRect rect);

/*
 * Type: GOval
 * -----------
 * This type represents an oval inscribed in a rectangular box.  For
 * example, the following code displays a filled green oval inscribed in
 * the graphics window:
 *
 *    main() {
 *       GWindow gw = newGWindow(500, 300);
 *       printf("This program draws a green oval filling the window.\n");
 *       GOval oval = newGOval(getWidth(gw), getHeight(gw));
 *       setFilled(oval, true);
 *       setColor(oval, "GREEN");
 *       add(gw, oval);
 *    }
 */

typedef GObject GOval;

/*
 * Function: newGOval
 * Usage: oval = newGOval(x, y, width, height);
 * --------------------------------------------
 * Creates a new GOval with the specified bounds.  By default, the oval is
 * unfilled.
 */

GObject newGOval(double x, double y, double width, double height);

/*
 * Type: GLine
 * -----------
 * This type represents a line segment.  For example, the following code
 * adds lines that mark the diagonals of the graphics window:
 *
 *    main() {
 *       GWindow gw = newGWindow(500, 300);
 *       printf("This program draws the diagonals on the window.\n");
 *       add(gw, newGLine(0, 0, getWidth(gw), getHeight(gw)));
 *       add(gw, newGLine(0, getHeight(gw), getWidth(gw), 0));
 *    }
 */

typedef GObject GLine;

/*
 * Function: newGLine
 * Usage: line = newGLine(x0, y0, x1, y1);
 * ---------------------------------------
 * Creates a new graphical line connecting the points (x0, y0) and
 * (x1, y1).
 */

GObject newGLine(double x0, double y0, double x1, double y1);

/*
 * Function: setStartPoint
 * Usage: setStartPoint(gline, x, y);
 * ----------------------------------
 * Sets the start point for the line to (x, y), leaving the end point
 * unchanged.  This method is therefore different from setLocation, which
 * moves both components of the line segment.
 */

void setStartPoint(GLine line, double x, double y);

/*
 * Function: setEndPoint
 * Usage: setEndPoint(line, x, y);
 * -------------------------------
 * Sets the end point for the line to (x, y), leaving the start point
 * unchanged.
 */

void setEndPoint(GLine line, double x, double y);

/*
 * Function: getStartPoint
 * Usage: pt = getStartPoint(gobj);
 * --------------------------------
 * Returns the point at which a GLine or GArc starts.
 */

GPoint getStartPoint(GObject gobj);

/*
 * Function: getEndPoint
 * Usage: pt = getEndPoint(gobj);
 * ------------------------------
 * Returns the point at which a GLine or GArc ends.
 */

GPoint getEndPoint(GObject gobj);

/*
 * Type: GArc
 * ----------
 * This type represents an elliptical arc.  The arc is specified by the
 * following parameters:
 *
 * 
 *   The coordinates of the bounding rectangle (x,
 *       y, width, height)
 *   The angle at which the arc starts (start)
 *   The number of degrees that the arc covers (sweep)
 *
 * All angles in a GArc description are measured in degrees moving
 * counterclockwise from the +x axis.  Negative values for either start or
 * sweep indicate motion in a clockwise direction.
 */

typedef GObject GArc;

/*
 * Function: newGArc
 * Usage: arc = newGArc(x, y, width, height, start, sweep);
 * --------------------------------------------------------
 * Creates a new GArc consisting of an elliptical arc.
 */

GArc newGArc(double x, double y, double width, double height,
                                 double start, double sweep);

/*
 * Function: setStartAngle
 * Usage: setStartAngle(arc, start);
 * ---------------------------------
 * Sets the starting angle for this GArc object.
 */

void setStartAngle(GArc arc, double start);

/*
 * Function: getStartAngle
 * Usage: angle = getStartAngle(arc);
 * ----------------------------------
 * Returns the starting angle for this GArc object.
 */

double getStartAngle(GArc arc);

/*
 * Function: setSweepAngle
 * Usage: setSweepAngle(arc, start);
 * ---------------------------------
 * Sets the sweep angle for this GArc object.
 */

void setSweepAngle(GArc arc, double start);

/*
 * Function: getSweepAngle
 * Usage: angle = getSweepAngle(arc);
 * ----------------------------------
 * Returns the sweep angle for this GArc object.
 */

double getSweepAngle(GArc arc);

/*
 * Function: setFrameRectangle
 * Usage: setFrameRectangle(arc, x, y, width, height);
 * ---------------------------------------------------
 * Changes the boundaries of the rectangle used to frame the arc.
 */

void setFrameRectangle(GArc garc, double x, double y,
                                  double width, double height);

/*
 * Function: getFrameRectangle
 * Usage: rect = getFrameRectangle(arc);
 * -------------------------------------
 * Returns the boundaries of the rectangle used to frame the arc.
 */

GRectangle getFrameRectangle(GArc arc);

/*
 * Type: GLabel
 * ------------
 * This subtype represents a text string.  For example, the following code
 * adds a GLabel containing "hello, world" to the center of the window:
 *
 *    main() {
 *       GWindow gw;
 *       GLabel label;
 *       double x, y;
 *
 *       printf("This program draws the 'hello, world' message.\n");
 *       gw = newGWindow(600, 400);
 *       label = newGLabel("hello, world");
 *       setFont(label, "SansSerif-18");
 *       x = (getWidth(gw) - getWidth(label)) / 2;
 *       y = (getHeight(gw) + getFontAscent(label)) / 2;
 *       setLocation(label, x, y);
 *       add(gw, label);
 *    }
 *
 * Controlling the appearance and positioning of a GLabel depends on
 * understanding the following terms:
 *
 * 
 *   The baseline is the horizontal line on which the
 *       characters rest.
 *   The origin is the point on the baseline at which
 *       the label begins.
 *   The height is the distance that separate two
 *       successive lines.
 *   The ascent is the maximum distance a character
 *       in this font extends above the baseline.
 *   The descent is the maximum distance a character
 *       in this font extends below the baseline.
 */

typedef GObject GLabel;

/*
 * Function: newGLabel
 * Usage: label = newGLabel(str);
 * ------------------------------
 * Creates a GLabel object containing the specified string, positioned with
 * an origin of (0, 0).
 */

GLabel newGLabel(string str);

/*
 * Function: setFont
 * Usage: setFont(label, font);
 * ----------------------------
 * Changes the font used to display the GLabel as specified by the string
 * font, which has the following format:
 *
 *    family-style-size
 *
 * where both style and size are optional.  If any of these elements are
 * missing or specified as an asterisk, the existing value is retained.
 */

void setFont(GLabel label, string font);

/*
 * Function: getFont
 * Usage: font = getFont(label);
 * -----------------------------
 * Returns the current font for the GLabel.
 */

string getFont(GLabel label);

/*
 * Function: setLabel
 * Usage: setLabel(label, str);
 * ----------------------------
 * Changes the string stored within the GLabel object, so that a new text
 * string appears on the display.
 */

void setLabel(GLabel label, string str);

/*
 * Function: getLabel
 * Usage: str = getLabel(label);
 * -----------------------------
 * Returns the string displayed by this object.
 */

string getLabel(GLabel label);

/*
 * Function: getFontAscent
 * Usage: ascent = getFontAscent(label);
 * -------------------------------------
 * Returns the maximum distance strings in this font extend above the
 * baseline.
 */

double getFontAscent(GLabel label);

/*
 * Function: getFontDescent
 * Usage: descent = getFontDescent(label);
 * ---------------------------------------
 * Returns the maximum distance strings in this font descend below the
 * baseline.
 */

double getFontDescent(GLabel label);

/*
 * Type: GImage
 * ------------
 * This subtype represents an image from a file.  For example, the
 * following code adds a GImage containing the Stanford tree at the center
 * of the window, assuming that the image file StanfordTree.png exists,
 * either in the current directory or an images subdirectory:
 *
 *    main() {
 *       printf("This program draws the Stanford tree.\n");
 *       GWindow gw = newGWindow(600, 400);
 *       GImage tree = newGImage("StanfordTree.png");
 *       double x = (getWidth(gw) - getWidth(tree)) / 2;
 *       double y = (getHeight(gw) - getHeight(tree)) / 2;
 *       add(gw, tree, x, y);
 *    }
 */

typedef GObject GImage;

/*
 * Function: newGImage
 * Usage: GImage image = newGImage(filename);
 * ------------------------------------------
 * Constructs a new image by loading the image from the specified file,
 * which is either in the current directory or a subdirectory named images.
 * The upper left corner of the image is positioned at the origin.
 */

GImage newGImage(string filename);

/*
 * Type: GPolygon
 * --------------
 * This subtype represents a polygon bounded by line segments.  The
 * newGPolygon function creates an empty polygon.  To complete the figure,
 * you need to add vertices to the polygon using the functions addVertex,
 * addEdge, and addPolarEdge.  As an example, the following code adds a
 * filled red octagon to the center of the window:
 *
 *    main() {
 *       GWindow gw;
 *       GPolygon stopSign;
 *       double edge;
 *       int i;
 *
 *       printf("This program draws a red octagon.\n");
 *       gw = newGWindow(600, 400);
 *       edge = 75;
 *       stopSign = newGPolygon();
 *       addVertex(stopSign, -edge / 2, edge / 2 + edge / sqrt(2.0));
 *       for (i = 0; i < 8; i++) {
 *          addPolarEdge(stopSign, edge, 45 * i);
 *       }
 *       setFilled(stopSign, true);
 *       setColor(stopSign, "RED");
 *       add(gw, stopSign, getWidth(gw) / 2, getHeight(gw) / 2);
 *    }
 */

typedef GObject GPolygon;

/*
 * Function: newGPolygon
 * Usage: poly = newGPolygon();
 * ----------------------------
 * Constructs a new empty polygon.
 */

GPolygon newGPolygon(void);

/*
 * Function: addVertex
 * Usage: addVertex(poly, x, y);
 * -----------------------------
 * Adds a vertex at (x, y) relative to the polygon origin.
 */

void addVertex(GPolygon poly, double x, double y);

/*
 * Function: addEdge
 * Usage: addEdge(poly, dx, dy);
 * -----------------------------
 * Adds an edge to the polygon whose components are given by the
 * displacements dx and dy from the last vertex.
 */

void addEdge(GPolygon poly, double dx, double dy);

/*
 * Function: addPolarEdge
 * Usage: addPolarEdge(poly, r, theta);
 * ------------------------------------
 * Adds an edge to the polygon specified in polar coordinates.  The length
 * of the edge is given by r, and the edge extends in direction theta,
 * measured in degrees counterclockwise from the +x axis.
 */

void addPolarEdge(GPolygon poly, double r, double theta);

/*
 * Function: getVertices
 * Usage: vec = getVertices(poly);
 * -------------------------------
 * Returns a vector whose elements are pointers to the GPoint values that
 * represent the vertices.  This vector is shared with the internal data
 * structure of the GPolygon and must not be freed by the client.
 */

Vector getVertices(GPolygon poly);

/*
 * Type: GCompound
 * ---------------
 * This subtype consists of a collection of other graphical objects.  Once
 * assembled, the internal objects can be manipulated as a unit.  The
 * GCompound keeps track of its own position, and all items within it are
 * drawn relative to that location.
 */

typedef GObject GCompound;

/*
 * Function: newGCompound
 * Usage: comp = newGCompound();
 * -----------------------------
 * Creates a new graphical compound with no internal components.
 */

GObject newGCompound(void);

/*
 * Function: add
 * Usage: add(compound, gobj);
 * ---------------------------
 * Adds the object to the compound.
 */

void addGCompound(GCompound compound, GObject gobj);

/*
 * Function: add
 * Usage: add(compound, gobj);
 * ---------------------------
 * Removes the object from the compound.
 */

void removeGCompound(GCompound compound, GObject gobj);

/*
 * Friend function: getGObjectCompound
 * Usage: gobj = getGObjectCompound(GCompound compound, double x, double y);
 * -------------------------------------------------------------------------
 * Returns the topmost object covering x and y, or NULL if no such object
 * exists.
 */

GObject getGObjectCompound(GCompound compound, double x, double y);

/*
 * Friend type: ObjectTypeBits
 * ---------------------------
 * This enumeration identifies a GObject type in a way that simplifies
 * checking whether a particular function is legal on that object.
 */

typedef enum {
   GARC = 1<<0,
   GCOMPOUND = 1<<1,
   GIMAGE = 1<<2,
   GLABEL = 1<<3,
   GLINE = 1<<4,
   GOVAL = 1<<5,
   GPOLYGON = 1<<6,
   GRECT = 1<<7,
   G3DRECT = 1<<8,
   GROUNDRECT = 1<<9,
   GINTERACTOR = 0x1F<<10,
   GBUTTON = 1<<10,
   GCHECKBOX = 1<<11,
   GCHOOSER = 1<<12,
   GSLIDER = 1<<13,
   GTEXTFIELD = 1<<14
} GObjectTypeBits;

#endif
