#ifndef RPICONTROL_FILEMANAGER_H
#define RPICONTROL_FILEMANAGER_H

#include <string>
#include <vector>
#include <dirent.h>

class FileManager {
private:
    const std::string HOME_DIR = "/home/pi/";

public:
    std::vector<std::string>* get_home_dir();
    std::vector<std::string>* get_dir(std::string curr_path);
};


#endif //RPICONTROL_FILEMANAGER_H
