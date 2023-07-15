
#include <shared/Platform.h>
#include <cstdlib>

#ifdef __APPLE__

extern "C" {
    #include <CoreServices/CoreServices.h>
}

#endif // __APPLE__

namespace sh {
    
    std::filesystem::path get_data_path() {
#ifdef __linux__
        if (has_environment("XDG_DATA_HOME")) {
            return std::filesystem::path(get_environment("XDG_DATA_HOME")) / "modificate"; 
        } else if (has_environment("HOME")) {
            return std::filesystem::path(get_environment("HOME")) / ".local/share/modificate";
        } else {
            return "~/.local/share/modificate";
        }
#elif defined(_WIN32)
        if (has_environment("APPDATA")) {
            return std::filesystem::path(get_environment("XDG_DATA_HOME")) / "modificate";
        } else {
            return "C:\\modificate";
        }
#elif defined(__APPLE__)
        FSRef ref;
        OSType folderType = kApplicationSupportFolderType;
        char path[PATH_MAX];

        FSFindFolder(kUserDomain, folderType, kCreateFolder, &ref);
        FSRefMakePath(&ref, (UInt8 *) &path, PATH_MAX);
#endif // __APPLE__
    }
    
    bool has_environment(const char *name) {
        // TODO: compiles on Windows? macOS?
        return std::getenv(name) != nullptr;
    }

    char *get_environment(const char *name) {
        return std::getenv(name);
    }
}
