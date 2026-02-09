#include <iostream>
#include <unistd.h>
#include <iomanip>

#include "memory_monitor.h"
#include "cpu_monitor.h"

int main() {
    while (true) {
        float cpu = getCPUUsage();
        float ram = getRAMUsageMB();

        system("clear");

        std::cout << "📊 System Monitor (macOS)\n";
        std::cout << "-------------------------\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "CPU Usage : " << cpu << " %\n";
        std::cout << "RAM Usage : " << ram << " MB\n";

        sleep(1);
    }

    return 0;
}
