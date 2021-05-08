#include <YesNoValidator.h>

bool Validator::validate(const std::string& requestMsg){
    auto ans = std::string();
    auto ansIsStupid = true;
    while (ansIsStupid) {
        try {
            std::cout << requestMsg; 
            std::getline(std::cin, ans);
            if (ans != "y" && ans != "n") {
                throw std::invalid_argument("the requested answer is either y or n");
            }
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what();
            continue;
        }
        break;
    }
    return ans == "y";
}
