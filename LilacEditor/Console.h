#ifndef _CONSOLE_H__
#define _CONSOLE_H__
#pragma once



#define LOG_ERROR "*"
#define LOG_WARNING "!"

class Console
{
public:
	Console();
	~Console();

	bool Draw();
};

#endif // !L_CONSOLE_H__
