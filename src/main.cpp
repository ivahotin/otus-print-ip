#include "lib.h"


int main() {

    ip::print_ip(char(-1));
    std::cout << std::endl;
    ip::print_ip(short(0));
    std::cout << std::endl;
    ip::print_ip(int(2130706433));
    std::cout << std::endl;
    ip::print_ip(long(8875824491850138409));
    std::cout << std::endl;
    ip::print_ip(std::string{"127.0.0.1"});
    std::cout << std::endl;
    ip::print_ip(std::vector{127, 0, 1, 1});
    std::cout << std::endl;
    ip::print_ip(std::list{127, 0, 1, 1});
    std::cout << std::endl;
    ip::print_ip(std::make_tuple(255, 255, 255, 255));
    std::cout << std::endl;

    return 0;
}