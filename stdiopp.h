#ifndef LEARN_CPP_STDIO_H
#define LEARN_CPP_STDIO_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
#elif __linux__
    #include <unistd.h>
    #include <sys/resource.h>
#elif __APPLE__
    #include <mach/mach.h>
#endif

template <typename T>
inline void printf(const T& value) {
    std::cout << value;
}

template <typename T>
inline void scanf(T& value) {
    std::cin >> value;
}

// --- Module: knif (code size) ---
inline void knif() {
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::filesystem::path exePath(buffer);
#else
    std::filesystem::path exePath = std::filesystem::current_path();
#endif

    std::filesystem::path projectFolder = exePath.parent_path().parent_path();

    uintmax_t total = 0;
    int filesCount = 0;
    const std::vector<std::string> extensions = { ".cpp", ".h", ".hpp", ".c", ".inl" };

    for (auto& file : std::filesystem::recursive_directory_iterator(projectFolder)) {
        if (file.is_regular_file()) {
            auto ext = file.path().extension().string();
            for (auto& e : extensions) {
                if (ext == e) {
                    total += file.file_size();
                    filesCount++;
                    break;
                }
            }
        }
    }

    std::cout << "Code files: " << filesCount << " | Size: "
              << total / 1024.0 << " KB (" << total / 1024.0 / 1024.0 << " MB)\n";
}

// --- Module: memory (RAM usage) ---
static inline double memory_used_mb() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));
    return (double)info.WorkingSetSize / (1024.0 * 1024.0);
#elif __linux__
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return (double)usage.ru_maxrss / 1024.0;
#elif __APPLE__
    struct mach_task_basic_info info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
        (task_info_t)&info, &count) == KERN_SUCCESS) {
        return (double)info.resident_size / (1024.0 * 1024.0);
    }
    return 0;
#else
    return 0;
#endif
}

#define memory() printf("Memory used: %.2f MB\n", memory_used_mb())


inline void cpp_version() {
    std::cout << "C++ Version: ";
#if __cplusplus == 199711L
    std::cout << "C++98";
#elif __cplusplus == 201103L
    std::cout << "C++11";
#elif __cplusplus == 201402L
    std::cout << "C++14";
#elif __cplusplus == 201703L
    std::cout << "C++17";
#elif __cplusplus == 202002L
    std::cout << "C++20";
#elif __cplusplus == 202302L
    std::cout << "C++23";
#elif
    std::cout << "C++26";
#else
    std::cout << "Unknown (" << __cplusplus << ")";
#endif
    std::cout << "\n";
}

#endif
