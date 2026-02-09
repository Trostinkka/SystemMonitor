#include "memory_monitor.h"
#include <mach/mach.h>

float getRAMUsageMB() {
    mach_task_basic_info info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;

    kern_return_t kr = task_info(
        mach_task_self(),
        MACH_TASK_BASIC_INFO,
        (task_info_t)&info,
        &count
    );

    if (kr != KERN_SUCCESS) {
        return 0.0f;
    }

    return info.resident_size / 1024.0f / 1024.0f;
}
