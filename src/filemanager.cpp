#include "filemanager.hpp"

vector<string>* FileManager::get_home_dir() {
    return get_dir(HOME_DIR);
}

vector<string>* FileManager::get_dir(string curr_path) {
    auto directory = new vector<string>;
    auto dir = opendir(curr_path.data());
    dirent* entry = readdir(dir);
    while (entry != nullptr) {
        directory->push_back(entry->d_name);
        entry = readdir(dir);
    }
    closedir(dir);
    return directory;
}
