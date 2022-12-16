#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <queue>

struct Command{
    std::string name;
    std::string help;
    std::function<void(std::vector<std::string>&)> func;  
};

class Shell{
public:
    Shell(){
        prompt = "shell> "; 
        max_history = 100;
    }
    ~Shell(){}
public:
    void Parse();
    void Run();
    void Input();
    void SetMaxHistory(int max_history);
    void SetPrompt(const std::string& prompt);
    void AddCommand(const Command& command);
    void AddCommand(const std::string& name, const std::string& help, const std::function<void(std::vector<std::string>&)>& func);
    void PrintHelp();
private:
    std::string prompt;
    std::string input;
    std::string command;
    std::vector<std::string> args;
    std::map<std::string, std::function<void(std::vector<std::string>&)>> commands; // command name -> command function 目标接受参数数组
    std::vector<std::string> helps;
    std::vector<std::string> history;
    int max_history;
};

