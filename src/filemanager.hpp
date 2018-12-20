#ifndef RPICONTROL_FILEMANAGER_H
#define RPICONTROL_FILEMANAGER_H

#include <string>
#include <vector>
#include <dirent.h>

using namespace std;

class FileManager {
private:
    const string HOME_DIR = "/home/pi/";

public:
    vector<string>* get_home_dir();
    vector<string>* get_dir(string curr_path);
};


#endif //RPICONTROL_FILEMANAGER_H
