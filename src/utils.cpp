#include "utils.h"

namespace Mutiny {

    std::vector<std::string> split(const std::string &str, char splitter) {
        std::vector<std::string> results;
        std::string temp = "";

        for(char ch : str) {

            if(ch == ' ') {
                results.push_back(temp);
                temp = "";
                continue;
            }

            temp += ch;

        }

        if(temp.size() > 0)
            results.push_back(temp);


        return results;
    }

}
