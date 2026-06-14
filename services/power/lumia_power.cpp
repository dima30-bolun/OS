#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdio>

struct LumiaPowerProfile {
    const char *device;
    uint32_t soc;
    uint32_t battery_mah;
    uint32_t display_mw;
    uint32_t radio_mw;
    uint32_t cpu_idle_mw;
};

static constexpr std::array<LumiaPowerProfile, 2> profiles{{
    {"Lumia 625H", 0x8930, 2000, 430, 760, 38},
    {"Lumia 520",  0x8227, 1430, 360, 620, 34},
}};

extern "C" uint32_t bolun_estimate_runtime_minutes(uint32_t soc, uint32_t battery_percent, uint32_t workload_mw) {
    auto it = std::find_if(profiles.begin(), profiles.end(), [soc](const LumiaPowerProfile &p) { return p.soc == soc; });
    const LumiaPowerProfile &p = it == profiles.end() ? profiles.front() : *it;
    uint32_t mw = std::max<uint32_t>(workload_mw + p.cpu_idle_mw, 1);
    uint32_t available_mwh = (p.battery_mah * 37u * battery_percent) / 1000u;
    return (available_mwh * 60u) / mw;
}

extern "C" void bolun_print_power_profile(uint32_t soc) {
    for (const auto &p : profiles) {
        if (p.soc == soc) {
            std::printf("%s msm=%x battery=%umAh display=%umW radio=%umW\n", p.device, p.soc, p.battery_mah, p.display_mw, p.radio_mw);
            return;
        }
    }
    std::printf("generic Lumia ARMv7 profile\n");
}
