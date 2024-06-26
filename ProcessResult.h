#pragma once
#include<string>
#include<iostream>
using namespace std;

template<typename T>
class ProcessResult {
public:
	/*返回结果类，工具类*/
	ProcessResult(bool result) { this->Result = result; }
	ProcessResult(bool result, T data) { this->Result = result; this->Data = data;}
	ProcessResult(bool result, string msg) { this->Result = result; this->ResultMsg = msg; }
	ProcessResult(bool result, string msg, T data) { this->Result = result; this->ResultMsg = msg; this->Data = data; }

	void setResult(bool result,string msg,T data) { this->Result = result; this->ResultMsg = msg; this->Data = data; }
	bool getResult() { return this->Result; }
	string getMessage() { return this->ResultMsg; }
	T getData() { return this->Data; }

private:
	bool Result;
	string ResultMsg;
	T Data;
};