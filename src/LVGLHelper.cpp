#if __has_include(<lvgl.h>)

#include <Arduino.h>
#include "LVGLHelper.h"

QueueHandle_t xSafeUpdateQueue = NULL;

void lv_safe_update(TCodeBlockFunction code_block, void * user_data, bool sync) {
    static const char * TAG = "lv_safe_update";

    if (!xSafeUpdateQueue) {
        xSafeUpdateQueue = xQueueCreate(20, sizeof(SafeUpdateParam_t));
    }
    SafeUpdateParam_t safe_update_item;
    safe_update_item.cb = code_block;
    safe_update_item.user_data = user_data;
    if (sync) {
        safe_update_item.sync_event_group_handle = xEventGroupCreate();
    } else {
        safe_update_item.sync_event_group_handle = NULL;
    }
    xQueueSend(xSafeUpdateQueue, (void *) &safe_update_item, pdMS_TO_TICKS(50));
    if (sync) {
        EventBits_t uxBits = xEventGroupWaitBits(safe_update_item.sync_event_group_handle, BIT0, pdFALSE, pdTRUE, pdMS_TO_TICKS(100));
        if ((uxBits & BIT0) == 0) {
            ESP_LOGE(TAG, "sync timeout");
        }
        vEventGroupDelete(safe_update_item.sync_event_group_handle);
    }
}

lv_timer_t * lv_timer_run_once(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data) {
    lv_timer_t * timer = lv_timer_create(timer_xcb, period, user_data);
    lv_timer_set_repeat_count(timer, 1);
    return timer;
}

#endif