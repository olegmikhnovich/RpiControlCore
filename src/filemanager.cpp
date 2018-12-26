#include "filemanager.hpp"

const char* dirent_type_to_str(unsigned char type) {
    switch (type) {
        case DT_DIR:
            return "Dir";
        case DT_REG:
            return "File";
        default:
            break;
    }
    return "Unknown";
}

std::vector<std::string>* FileManager::get_home_dir() {
    return get_dir(HOME_DIR);
}

std::vector<std::string>* FileManager::get_dir(std::string curr_path) {
    auto directory = new std::vector<std::string>;
    auto dir = opendir(curr_path.data());
    dirent* entry = readdir(dir);
    while (entry != nullptr) {
        std::string dat = entry->d_name;
        dat += "|";
        dat += dirent_type_to_str(entry->d_type);
        if (dat[0] != '.') directory->push_back(dat);
        entry = readdir(dir);
    }
    closedir(dir);
    return directory;
}
