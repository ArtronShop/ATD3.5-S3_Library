#if defined(__has_include)
#if __has_include(<lvgl.h>)
#include <lvgl.h>
#define USE_LVGL
#endif
#else
#error "__has_include not work"
#endif
