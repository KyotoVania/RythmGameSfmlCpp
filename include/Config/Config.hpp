#include <string>
#include <map>
#include <libconfig.h++>

class Config {
public:
    static void load(const std::string& file);
    static void save(const std::string& file);
    static void print();

    // Function to set configuration values by key
    static bool set(const std::string& key, const std::string& value);

private:
    // Static members to store the configuration values
    static std::map<std::string, std::string> _configMap;
};
