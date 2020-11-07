#include "vm_target.h"

const char* vm_target(uint16_t compile_version) {
    const char* java_version = "";

    switch (compile_version) {
    case 45:
        java_version = "1.1";
        break;
    case 46:
        java_version = "1.2";
        break;
    case 47:
        java_version = "1.3";
        break;
    case 48:
        java_version = "1.4";
        break;
    case 49:
        java_version = "1.5";
        break;
    case 50:
        java_version = "1.6";
        break;
    case 51:
        java_version = "1.7";
        break;
    case 52:
        java_version = "1.8";
        break;
    default:
        java_version = "Unknown";
    }

    return java_version;
}