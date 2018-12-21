#include "deviceproperties.hpp"

string DeviceProperties::get_device_model() {
    string result("Unknown device");
    auto d = read_data_from_file(MODEL_FNAME);
    if (d->success) {
        result = d->data;
    } else {
        std::cerr << "Access deny! path: " << MODEL_FNAME << std::endl;
    }
    delete d;
    return result.substr(0, result.length() - 1);
}

string DeviceProperties::get_temperature() {
    const string value = Utils::exec("vcgencmd measure_temp");
    return Utils::split(value, "=")[1];
}

string DeviceProperties::get_os_version() {
    string version("Unknown Linux");
    auto d = read_data_from_file(OS_V_FNAME);
    if (d->success) {
        version = d->data;
        version = Utils::split(Utils::split(version, "\n")[0], "=")[1];
        version = version.substr(1, version.length() - 2);
    }
    delete d;
    return version;
}

string DeviceProperties::get_device_name() {
    struct stat sb{};
    if (!(stat(DIR_PATH.data(), &sb) == 0 && S_ISDIR(sb.st_mode)))
        mkdir(DIR_PATH.data(), 0777);
    const auto device_name = DIR_PATH + "/" + DEVICE_NAME_FNAME;

    if (stat(device_name.data(), &sb) != 0) {
        std::ofstream fo(device_name.data());
        fo << "Raspberry";
        fo.close();
    }
    string result;
    auto d = read_data_from_file(device_name);
    if (d->success)
        result = d->data;
    delete d;
    return result;
}

void DeviceProperties::set_device_name(string name) {
    struct stat sb{};
    if (!(stat(DIR_PATH.data(), &sb) == 0 && S_ISDIR(sb.st_mode)))
        mkdir(DIR_PATH.data(), 0777);
    const string device_name = DIR_PATH + "/" + DEVICE_NAME_FNAME;

    std::ofstream fo(device_name.data(), std::ios_base::out | std::ios_base::trunc);
    fo << name;
    fo.close();
}

bool DeviceProperties::auth_user(string pwd) {
    struct stat sb{};
    if (!(stat(DIR_PATH.data(), &sb) == 0 && S_ISDIR(sb.st_mode)))
        mkdir(DIR_PATH.data(), 0777);
    const string pwd_name = DIR_PATH + "/" + DEVICE_PWD_FNAME;

    if (stat(pwd_name.data(), &sb) != 0) {
        std::ofstream fo(pwd_name.data(), std::ios_base::out | std::ios_base::trunc);
        fo.close();
        return true;
    } else {
        auto d = read_data_from_file(pwd_name);
        string _pwd = d->data;
        delete d;
        return (_pwd == pwd);
    }
}

bool DeviceProperties::set_new_pwd(string oldPwd, string newPwd) {
    struct stat sb{};
    if (!(stat(DIR_PATH.data(), &sb) == 0 && S_ISDIR(sb.st_mode)))
        mkdir(DIR_PATH.data(), 0777);
    const string pwd_name = DIR_PATH + "/" + DEVICE_PWD_FNAME;

    if (stat(pwd_name.data(), &sb) != 0) {
        std::ofstream fo(pwd_name.data(), std::ios_base::out | std::ios_base::trunc);
        fo << newPwd;
        fo.close();
        return true;
    } else {
        auto d = read_data_from_file(pwd_name);
        if (oldPwd == d->data) {
            std::ofstream fo(pwd_name.data(), std::ios_base::out | std::ios_base::trunc);
            fo << newPwd;
            fo.close();
            return true;
        }
        delete d;
    }
    return false;
}

FILE_READER* DeviceProperties::read_data_from_file(string filename) {
    auto reader = new FILE_READER;
    std::ifstream f(filename);
    string data;
    if (f.is_open()) {
        reader->success = true;
        string buffer;
        while (!f.eof()) {
            getline(f, buffer);
            data += buffer + "\n";
        }
        f.close();
        data = data.substr(0, data.length() - 1);
        reader->data = data;
    } else {
        reader->success = false;
        reader->data = "";
    }
    return reader;
}
