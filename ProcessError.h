#pragma once
#ifndef PROCESS_ERROR_H
#define PROCESS_ERROR_H
#include <exception>
#include <string>
using namespace std;

class ProcessError : public exception {
private:
    /*��������*/
    string message;
public:
    ProcessError(const string& msg) : message(msg) {}

    const char* what() const noexcept override { return message.c_str(); }
};

#endif