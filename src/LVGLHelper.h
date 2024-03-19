#ifndef __LVGLHelper_H__
#define __LVGLHelper_H__

#if __has_include(<lvgl.h>)
#include <functional>
#include <Arduino.h>
#include <lvgl.h>

extern QueueHandle_t xSafeUpdateQueue;
typedef std::function<void(void*)> TCodeBlockFunction;
typedef struct {
    TCodeBlockFunction cb;
    void * user_data;
    EventGroupHandle_t sync_event_group_handle;
} SafeUpdateParam_t;
void lv_safe_update(TCodeBlockFunction code_block, void * user_data = NULL, bool sync = false) ;

lv_timer_t * lv_timer_run_once(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data = NULL) ;

#endif
#endif