#pragma once

#include <QString>

namespace Wakatime {
namespace Constants {

constexpr char SETTINGS_GROUP[] = "Wakatime";
constexpr char OPTION_CATEGORY[] = "Wakatime";
constexpr char OPTION_ID[] = "Wakatime";
const QString WAKATIME_RELEASE_URL =
        "https://api.github.com/repos/wakatime/wakatime-cli/releases/latest";

namespace OSType{
    constexpr int WINDOWS=1,LINUX=2,MACOS=3,UNKOWN=4;
};

namespace OSArch{
    constexpr int AMD64=1,ARM64=2,ARM=3,I386=4;
};

struct OSInfo
{
    int _os;
    int _arch;

public:
    OSInfo(){}
    OSInfo(const int type, const int arch):_os(type),_arch(arch){}
};
} // namespace QtCreatorWakatime
} // namespace Constants
