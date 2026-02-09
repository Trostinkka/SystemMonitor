#include "cpu_monitor.h"
#include <mach/mach.h>

float getCPUUsage() {
    host_cpu_load_info_data_t cpuinfo;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;

    static uint64_t prevTotal = 0;
    static uint64_t prevIdle = 0;

    kern_return_t kr = host_statistics(
        mach_host_self(),
        HOST_CPU_LOAD_INFO,
        (host_info_t)&cpuinfo,
        &count
    );

    if (kr != KERN_SUCCESS) {
        return 0.0f;
    }

    uint64_t user   = cpuinfo.cpu_ticks[CPU_STATE_USER];
    uint64_t system = cpuinfo.cpu_ticks[CPU_STATE_SYSTEM];
    uint64_t idle   = cpuinfo.cpu_ticks[CPU_STATE_IDLE];
    uint64_t nice   = cpuinfo.cpu_ticks[CPU_STATE_NICE];

    uint64_t total = user + system + idle + nice;

    uint64_t totalDiff = total - prevTotal;
    uint64_t idleDiff  = idle  - prevIdle;

    prevTotal = total;
    prevIdle  = idle;

    if (totalDiff == 0) {
        return 0.0f;
    }

    return (1.0f - (float)idleDiff / totalDiff) * 100.0f;
}
