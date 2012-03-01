#ifndef __EXCEPTIONS_H_
#define __EXCEPTIONS_H_

#include <exception>

/*
 * General purpose quadris exception
 */
class QuadrisException : public std::exception
{
public:
    QuadrisException(const char * msg = "Quadris exception")
    : message(msg)
    {}

    const char * what() const throw() {
        return message;
    }

private:
    const char * message;
};

/*
 * File I/O related quadris exception
 *
 * Currently this exception is raised
 * when reading sequence.txt has a problem.
 */
class FileIOException : public QuadrisException
{
public:
    FileIOException(const char * cause = "")
    : QuadrisException(cause)
    {}
};

#endif // __EXCEPTIONS_H_
