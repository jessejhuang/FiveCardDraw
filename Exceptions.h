#pragma once
#ifndef Exception_h
#define Exception_h
#include <exception>

class instance_not_available : public std::exception {
public:
	virtual const char* what() const throw();
};
class game_already_started : public std::exception {
public:
	virtual const char* what() const throw();
};
class unknown_game :public std::exception {
public :
	virtual const char* what() const throw();
};

class no_game_in_progress : public std::exception {
public:
	virtual const char* what() const throw();
};

class already_playing : public std::exception {
public:
	virtual const char* what() const throw();
};

#endif // !Exception_h