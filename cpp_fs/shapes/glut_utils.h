#ifndef __GLUT_UTILS__
#define __GLUT_UTILS__


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


enum COLORS
{
    COLOR_RED     = 0x010000,
    COLOR_GREEN   = 0x000100,
    COLOR_BLUE    = 0x000001,
    COLOR_YELLOW  = 0x010100,
    COLOR_MAGENTA = 0x010001,
    COLOR_CYAN    = 0x000101,
    COLOR_WHITE   = 0x010101,
    COLOR_BLACK   = 0x000000,
    COLOR_GRAY    = 0x4000000,
    COLOR_FILL    = 0x8000000
};

enum MOUSE_BUTTONS
{
    MOUSE_LEFT          = 0,
    MOUSE_MIDDLE        = 1,
    MOUSE_RIGHT         = 2,
    MOUSE_WHEEL_UP      = 3,
    MOUSE_WHEEL_DOWN    = 4
};

enum MOUSE_BUTTON_STATES
{
    BUTTON_DOWN = 0,
    BUTTON_UP   = 1
};

typedef void (*DRAW_FUNC_T)();
typedef int (*KEYBOARD_FUNC_T)(unsigned char key, int x, int y);
typedef int (*MOUSE_FUNC_T)(int button, int state, int x, int y);
typedef int (*MOTION_FUNC_T)(int x, int y);
typedef int (*TIMER_FUNC_T)();
typedef int (*MENU_FUNC_T)(int option);

void DrawInit(int argc, char** argv, int w, int h, DRAW_FUNC_T draw_func_p);
void DrawSetKeyboardFunc(KEYBOARD_FUNC_T kb_func_p);
void DrawSetMouseFunc(MOUSE_FUNC_T mouse_func_p);
void DrawSetMotionFunc(MOTION_FUNC_T motion_func_p);
void DrawSetTimerFunc(TIMER_FUNC_T timer_func_p, int msecs);
void DrawMainLoop();
void DrawCaptureOpen(const char* fname);
void DrawCaptureFrame();
void DrawCaptureClose();

void DrawCreateMenu();
void DrawSetMenuFunc(MENU_FUNC_T menu_func_p);
void DrawSetMousePosition(int x, int y);
int  DrawGetModifiers();
void DrawEnableTexture();

void DrawCircle(int color, int x, int y, int radius);
void DrawEllipse(int color, int x, int y, int xradius, int yradius, int num_segments);
void DrawPolygon(int color, int nPoints, ...);
void DrawTexture(int width, int height, void* data);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* __GLUT_UTILS__ */
