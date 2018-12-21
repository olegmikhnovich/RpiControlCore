#include "filemanager.hpp"

std::vector<std::string>* FileManager::get_home_dir() {
    return get_dir(HOME_DIR);
}

std::vector<std::string>* FileManager::get_dir(std::string curr_path) {
    auto directory = new std::vector<std::string>;
    auto dir = opendir(curr_path.data());
    dirent* entry = readdir(dir);
    while (entry != nullptr) {
        directory->push_back(entry->d_name);
        entry = readdir(dir);
    }
    closedir(dir);
    return directory;
}
