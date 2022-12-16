#include "shell.h"
#include "getkey.h"

void Shell::Parse(){
    command = "";
    args.clear();
    int i = 0;
    while(i < input.size() && input[i] == ' '){
        i++;
    }
    while(i < input.size() && input[i] != ' '){
        command += input[i];
        i++;
    }
    while(i < input.size()){
        while(i < input.size() && input[i] == ' '){
            i++;
        }
        std::string arg;
        while(i < input.size() && input[i] != ' '){
            arg += input[i];
            i++;
        }
        if(arg.size() > 0){
            args.push_back(arg);
        }
    }
}
void Shell::Run(){
    PrintHelp();
    while(true){
        Input();
        std::cout << std::endl;
        history.push_back(input);
        if(history.size() >= max_history){
            history.erase(history.begin());
        }
        Parse();
        if(command == "exit"){
            break;
        } else if(command == "help"){
            PrintHelp();
            continue;
        }
        if(commands.find(command) != commands.end()){
            commands[command](args);
        }else{
            std::cout << "command not found" << std::endl;
        }
    }
}

void Shell::SetMaxHistory(int max_history){
    this->max_history = max_history;
}

// 使用getch.h中的getkey()函数获取输入, 上下键翻阅历史
void Shell::Input(){
    input = "";
    std::cout << prompt;
    int c = getkey();
    int cur_history = history.size();
    while(c != KEY_ENTER){
        // std::cout << "!!" << c << "!!" << std::endl;
        if(c == KEY_UP){
            if(cur_history > 0){
                cur_history--;
                input = history[cur_history];
                std::cout << "\r" << prompt << input;
            }
        }else if(c == KEY_DOWN){
            if(cur_history < history.size()){
                cur_history++;
                if(cur_history == history.size()){
                    input = "";
                }else{
                    input = history[cur_history];
                }
                std::cout << "\r" << prompt << input;
            }
        } else if(c == KEY_BACKSPACE){
            if(input.size() > 0){
                input.pop_back();
                std::cout << "\b \b";
            }
        } else if(c == KEY_CTRL_C){
            std::cout << std::endl;
            input = "";
            std::cout << prompt;
        }
        else{
            input += (char)c;
            std::cout << (char)c;
        }
        c = getkey();
    }
}

void Shell::SetPrompt(const std::string& prompt){
    this->prompt = prompt;
}
void Shell::AddCommand(const Command& command){
    commands[command.name] = command.func;
    helps.push_back("    " + command.name + " : " + command.help);
}
void Shell::PrintHelp(){
    std::cout << "Commands:" << std::endl;
    std::cout << "    exit : exit the shell" << std::endl;
    std::cout << "    help : print help message" << std::endl;
    for(auto& help : helps){
        std::cout << help << std::endl;
    }
}

void Shell::AddCommand(const std::string& name, const std::string& help, const std::function<void(std::vector<std::string>&)>& func){
    Command command;
    command.name = name;
    command.help = help;
    command.func = func;
    AddCommand(command);
}