// strc.h - simple string wrapper class

#ifndef __STRC_H_
#define  __STRC_H_

#include <cstddef>

constexpr const char * __strc_class = "strc";
constexpr const char * __strc_version = "1.1";
constexpr size_t MAXLEN = 10240;

class strc
{
public:
	strc();
	strc(const char *);
	strc(const strc &);
	strc(strc &&);
	~strc();

	strc & operator = (strc);
	const char * getData() const;
	operator const char * () const;
    void swap(strc &);	

private:
	char * _data = nullptr;
	void msg(const char *);
}; 

#endif




