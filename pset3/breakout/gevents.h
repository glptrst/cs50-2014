/*
 * File: gevents.h
 * ---------------
 * This interface defines the event structure used in the graphics
 * libraries.  The structure of this package is adapted from the Java event
 * model and is compatible with the C++ StanfordCPPLib package.
 */

#ifndef _gevents_h
#define _gevents_h

#include "cslib.h"
#include "generic.h"
#include "gtimer.h"
#include "gwindow.h"

/*
 * Type: EventClassType
 * --------------------
 * This enumeration type defines the event classes.  The element values are
 * each a single bit and can be added or ORed together to generate an event
 * mask.  The CLICK_EVENT class responds only to the MOUSE_CLICKED event
 * type.  The ANY_EVENT class selects any event.
 */

typedef enum {
   ACTION_EVENT = 0x010,
   KEY_EVENT    = 0x020,
   TIMER_EVENT  = 0x040,
   WINDOW_EVENT = 0x080,
   MOUSE_EVENT  = 0x100,
   CLICK_EVENT  = 0x200,
   ANY_EVENT    = 0x3F0
} EventClassType;

/*
 * Type: EventType
 * ---------------
 * This enumeration type defines the event types for all events.
 */

typedef enum {
   WINDOW_CLOSED    = WINDOW_EVENT + 1,
   WINDOW_RESIZED   = WINDOW_EVENT + 2,
   ACTION_PERFORMED = ACTION_EVENT + 1,
   MOUSE_CLICKED    = MOUSE_EVENT + 1,
   MOUSE_PRESSED    = MOUSE_EVENT + 2,
   MOUSE_RELEASED   = MOUSE_EVENT + 3,
   MOUSE_MOVED      = MOUSE_EVENT + 4,
   MOUSE_DRAGGED    = MOUSE_EVENT + 5,
   KEY_PRESSED      = KEY_EVENT + 1,
   KEY_RELEASED     = KEY_EVENT + 2,
   KEY_TYPED        = KEY_EVENT + 3,
   TIMER_TICKED     = TIMER_EVENT + 1
} EventType;

/*
 * Type: ModifierCodes
 * -------------------
 * This enumeration type defines a set of constants used to check whether
 * modifiers are in effect.
 */

typedef enum {
   SHIFT_DOWN     = 1 << 0,
   CTRL_DOWN      = 1 << 1,
   META_DOWN      = 1 << 2,
   ALT_DOWN       = 1 << 3,
   ALT_GRAPH_DOWN = 1 << 4,
   BUTTON1_DOWN   = 1 << 5,
   BUTTON2_DOWN   = 1 << 6,
   BUTTON3_DOWN   = 1 << 7
} ModifierCodes;

/*
 * Type: KeyCodes
 * --------------
 * This type defines the names of the key codes returned in a key event.
 */

typedef enum {
   BACKSPACE_KEY = 8,
   TAB_KEY = 9,
   ENTER_KEY = 10,
   CLEAR_KEY = 12,
   ESCAPE_KEY = 27,
   PAGE_UP_KEY = 33,
   PAGE_DOWN_KEY = 34,
   END_KEY = 35,
   HOME_KEY = 36,
   LEFT_ARROW_KEY = 37,
   UP_ARROW_KEY = 38,
   RIGHT_ARROW_KEY = 39,
   DOWN_ARROW_KEY = 40,
   F1_KEY = 112,
   F2_KEY = 113,
   F3_KEY = 114,
   F4_KEY = 115,
   F5_KEY = 116,
   F6_KEY = 117,
   F7_KEY = 118,
   F8_KEY = 119,
   F9_KEY = 120,
   F10_KEY = 121,
   F11_KEY = 122,
   F12_KEY = 123,
   DELETE_KEY = 127,
   HELP_KEY = 156
} KeyCodes;

/*
 * Type: GEvent
 * ------------
 * This abstract type is used to represent an event of any type.  This file
 * defines names for the subtypes, even though these types are identical in
 * C.  The functions that apply only to a specific event subtype generate
 * runtime errors if called on an event of the wrong type.
 *
 * The standard paradigm for using GEvent is illustrated by the following
 * program, which allows the user to draw lines on the graphics window:
 *
 *    main() {
 *       GWindow gw = newGWindow(600, 400);
 *       while (true) {
 *          GMouseEvent e = waitForEvent(MOUSE_EVENT);
 *          if (getEventType(e) == MOUSE_PRESSED) {
 *             GLine line = newGLine(getX(e), getY(e), getX(e), getY(e));
 *             add(gw, line);
 *          } else if (getEventType(e) == MOUSE_DRAGGED) {
 *             setEndPoint(line, getX(e), getY(e));
 *          }
 *       }
 *    }
 */

typedef struct GEventCDT *GEvent;

/*
 * Function: freeEvent
 * Usage: freeEvent(e);
 * --------------------
 * Releases the storage associated with the event.
 */

void freeEvent(GEvent e);

/*
 * Function: getEventClass
 * Usage: eventClass = getEventClass(e);
 * -------------------------------------
 * Returns the enumerated type constant indicating the class of the event.
 */

EventClassType getEventClass(GEvent e);

/*
 * Function: getEventType
 * Usage: eventType = getEventType(e);
 * -----------------------------------
 * Returns the enumerated constant indicating the specific class of the
 * event.
 */

EventType getEventType(GEvent e);

/*
 * Function: getGWindow
 * Usage: gw = getGWindow(e);
 * --------------------------
 * Returns the graphics window in which this event occurred.  This function
 * applies to the subtypes GMouseEvent, GKeyEvent, and GWindowEvent.
 */

GWindow getGWindow(GEvent e);

/*
 * Function: getEventTime
 * Usage: time = getEventTime(e);
 * ------------------------------
 * Returns the system time in milliseconds at which the event occurred.  To
 * ensure portability among systems that represent time in different ways,
 * the cslib package uses type double to represent time, which is always
 * encoded as the number of milliseconds that have elapsed since 00:00:00
 * UTC on January 1, 1970, which is the conventional zero point for
 * computer-based time systems.
 */

double getEventTime(GEvent e);

/*
 * Function: setEventTime
 * Usage: setEventTime(e, time);
 * -----------------------------
 * Sets the event time field for the event.
 */

void setEventTime(GEvent e, double time);

/*
 * Function: getModifiers
 * Usage: modifiers = getModifiers(e);
 * -----------------------------------
 * Returns an integer whose bits indicate what modifiers are in effect.  To
 * check whether the shift key is down, for example, clients can use the
 * following code:
 *
 *    if (getModifiers(e) 
 */

int getModifiers(GEvent e);

/*
 * Function: setModifiers
 * Usage: setModifiers(e, modifiers);
 * ----------------------------------
 * Sets the modifiers field for the event.
 */

void setModifiers(GEvent e, int modifiers);

/*
 * Function: waitForClick
 * Usage: waitForClick();
 * ----------------------
 * Waits for a mouse click to occur in any window, discarding any other
 * events.
 */

void waitForClick();

/*
 * Function: waitForEvent
 * Usage: e = waitForEvent(mask);
 * ------------------------------
 * Dismisses the process until an event occurs whose type is covered by the
 * event mask.  The mask parameter is a combination of the events of
 * interest.  For example, to wait for a mouse event or an action event,
 * clients can use the following call:
 *
 *    e = waitForEvent(MOUSE_EVENT + ACTION_EVENT);
 *
 * As a more sophisticated example, the following code is the canonical
 * event loop for an animated application that needs to respond to mouse,
 * key, and timer events:
 *
 *    GTimer timer;
 *    GEvent e;
 *
 *    timer = newGTimer(ANIMATION_DELAY_IN_MILLISECONDS);
 *    start(timer);
 *    while (true) {
 *       e = waitForEvent(TIMER_EVENT + MOUSE_EVENT + KEY_EVENT);
 *       switch (getEventClass(e)) {
 *        case TIMER_EVENT:
 *          takeAnimationStep();
 *          break;
 *        case MOUSE_EVENT:
 *          handleMouseEvent(e);
 *          break;
 *        case KEY_EVENT:
 *          handleKeyEvent(e);
 *          break;
 *       }
 *       freeEvent(e);
 *    }
 */

GEvent waitForEvent(int mask);

/*
 * Function: getNextEvent
 * Usage: e = getNextEvent(mask);
 * ------------------------------
 * Checks to see if there are any events of the desired type waiting on the
 * event queue.  If so, this function returns the event in exactly the same
 * fashion as waitNextEvent; if not, getNextEvent returns NULL.
 */

GEvent getNextEvent(int mask);

/*
 * Type: GWindowEvent
 * ------------------
 * This event subtype represents a change in a window.
 */

typedef GEvent GWindowEvent;

/*
 * Function: newGWindowEvent
 * Usage: e = newGWindowEvent(type, gw);
 * -------------------------------------
 * Creates a new GWindowEvent.  The parameters are the specific type of
 * window event and the GWindow in which the event occurred.
 */

GWindowEvent newGWindowEvent(EventType type, GWindow gw);

/*
 * Type: GActionEvent
 * ------------------
 * This event subtype represents activation of an interactor.
 */

typedef GEvent GActionEvent;

/*
 * Function: newGActionEvent
 * Usage: e = newGActionEvent(type, source, actionCommand);
 * --------------------------------------------------------
 * Creates a new GActionEvent.  The parameters are the interactor that
 * generated the event and the associated action command.
 */

GActionEvent newGActionEvent(EventType type, GObject source,
                                             string actionCommand);

/*
 * Function: getSource
 * Usage: gobj = getSource(e);
 * ---------------------------
 * Returns the GObject that generated this event.
 */

GObject getSource(GActionEvent e);

/*
 * Function: getActionCommand
 * Usage: cmd = getActionCommand(arg);
 * -----------------------------------
 * Returns the action command associated with this event or interactor.
 */

string getActionCommand(void *arg);

/*
 * Type: GMouseEvent
 * -----------------
 * This event subtype represents a mouse action in a window.
 */

typedef GEvent GMouseEvent;

/*
 * Function: newGMouseEvent
 * Usage: e = newGMouseEvent(type, gw, x, y);
 * ------------------------------------------
 * Creates a new GMouseEvent.  The parameters are the specific event type,
 * the GWindow in which the event occurred, and the coordinates of the
 * mouse.
 */

GMouseEvent newGMouseEvent(EventType type, GWindow gw, double x, double y);

/*
 * Function: getX
 * Usage: x = getX(e);
 * -------------------
 * Returns the x coordinate at which the event occurred.
 */

double getXGEvent(GMouseEvent e);

/*
 * Function: getY
 * Usage: y = getY(e);
 * -------------------
 * Returns the y coordinate at which the event occurred.
 */

double getYGEvent(GMouseEvent e);

/*
 * Type: GKeyEvent
 * ---------------
 * This event subtype represents a key action in a window.
 */

typedef GEvent GKeyEvent;

/*
 * Function: newGKeyEvent
 * Usage: e = newGKeyEvent(type, gw, ch, code);
 * --------------------------------------------
 * Creates a new GKeyEvent.  The parameters are the specific event type,
 * the GWindow in which the event occurred, the character after taking into
 * account modifier keys, and the code for the specific key.
 */

GKeyEvent newGKeyEvent(EventType type, GWindow gw, int keyChar, int keyCode);

/*
 * Function: getKeyChar
 * Usage: ch = getKeyChar(e);
 * --------------------------
 * Returns the character represented by the keystroke, taking the modifier
 * keys into account.  For example, if the user types the 'a' key with the
 * shift key down, getKeyChar will return 'A'.  If the key code in the
 * event does not correspond to a character, getKeyChar returns the null
 * character.
 */

char getKeyChar(GKeyEvent e);

/*
 * Function: getKeyCode
 * Usage: key = getKeyCode(e);
 * ---------------------------
 * Returns the integer code associated with the key in the event.
 */

int getKeyCode(GKeyEvent e);

/*
 * Type: GTimerEvent
 * -----------------
 * This event subtype represents a tick from a GTimer.
 */

typedef GEvent GTimerEvent;

/*
 * Function: newGTimerEvent
 * Usage: e = newGTimerEvent(type, timer);
 * ---------------------------------------
 * Creates a new GTimerEvent.  The parameters are the specific event type
 * and the GTimer.
 */

GEvent newGTimerEvent(EventType type, GTimer timer);

/*
 * Function: getGTimer
 * Usage: timer = getGTimer(e);
 * ----------------------------
 * Returns the GTimer that generated this event.
 */

GTimer getGTimer(GTimerEvent e);

#endif
