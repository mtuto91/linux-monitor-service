// src/monitor/temperature_reader.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
// TODO: dynamically discover thermal zones from /sys/class/thermal/
static std::vector<std::string> get_thermal_zones() {
    return {
        "/sys/class/thermal/thermal_zone0/temp",
        "/sys/class/thermal/thermal_zone1/temp",
        "/sys/class/thermal/thermal_zone2/temp"
    };
}

int read_temp(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return -1;

    int temp = 0;
    file >> temp;
    return temp / 1000;
}

int get_max_cpu_temp() {
    int max_temp = -1;

    for (const auto& path : get_thermal_zones()) {
        int t = read_temp(path);
        if (t > max_temp) max_temp = t;
    }

    return max_temp;
}

//test 
int main(int argc, char const *argv[])
{
    std::cout << "Max CPU Temperature: " << get_max_cpu_temp() << "°C" << std::endl;
    get_thermal_zones();
    std::vector<std::string> zones = get_thermal_zones();
    std::cout << "Thermal Zones:" << std::endl;
    for (const auto& zone : zones) {  
        std::cout << " - " << zone << std::endl;
    }
    std::cout << read_temp("/sys/class/thermal/thermal_zone0/temp") << "°C" << std::endl;
    return 0;
}
