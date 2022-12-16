#include "shell.h"

int main(void){
    Shell shell;
    shell.AddCommand("test", "test command", [](std::vector<std::string>& args) {
        std::cout << "test command" << std::endl;
    });
    shell.AddCommand("add", "add a and b", [](std::vector<std::string>& args) {
        int a = std::stoi(args[0]);
        int b = std::stoi(args[1]);
        std::cout << a + b << std::endl;
    });
    shell.AddCommand("sub", "sub a and b", [](std::vector<std::string>& args) {
        int a = std::stoi(args[0]);
        int b = std::stoi(args[1]);
        std::cout << a - b << std::endl;
    });
    shell.Run();
}