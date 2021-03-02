//------------------------------------------------
// description..: finance - risk calculator
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <algorithm>	// for_each
#include <vector>
#include <cmath>		//pow
#include <memory>		// unique_ptr/shared ptr
#include <exception>  
#include <fstream>      //ifstream - file operations

using namespace std;

//----------------------------------------------------------------------------
enum class TransactionType 
{
    TRANSACTION_SELL,
    TRANSACTION_BUY,
    TRANSACTION_SHORT,
};

//----------------------------------------------------------------------------
class FileError : public std::runtime_error 
{
public:
    FileError(const std::string &s) : std::runtime_error(s)
    {
    }
};

//----------------------------------------------------------------------------
class TransactionTypeError : public std::runtime_error 
{
public:    
    TransactionTypeError(const std::string &s)  : std::runtime_error(s)
    {
    }
};


//----------------------------------------------------------------------------
class TransactionHandler 
{
public:   

    const std::string SELL_OP = "SELL";
    const std::string BUY_OP = "BUY";
    const std::string SHORT_OP = "SHORT";

    
    TransactionHandler(const std::string &fileName): m_fileName(fileName)
    {
    }    

    TransactionHandler(const TransactionHandler &a): m_fileName(a.m_fileName)
    {
    }

    ~TransactionHandler() = default;

    TransactionHandler &operator=(const TransactionHandler & other)
    {
        if (this != &other)
        {
            m_fileName = other.m_fileName;
        }
        return *this;

    }

    void handleTransactions()
    {
        std::ifstream file;

        file.open(m_fileName, std::ifstream::in);
        if (file.fail())
        {
            throw new FileError(std::string("error opening file ") + m_fileName);
        }

        std::string op;
        file >> op;
        while (file.good() && !file.eof())
        {
            if (op != SELL_OP && op != BUY_OP && op !=  SHORT_OP)
            {
                throw new TransactionTypeError(std::string("unknown transaction ") + op);
            }

            cout << "processing transaction=" << op << endl;

            file >> op;
        }        
    }

private:    
    std::string m_fileName;
};


//----------------------------------------------------------------------
int main(int argc, const char **argv)
{
    cout << "main - Starting..." << endl;

    if (argc < 1)
    {
        std::cerr << "usage: <progName> <fileName>\n";
        return 1;
    }

    std::string fileName = argv[1];
    try
    {
        TransactionHandler handler(fileName);
        handler.handleTransactions();
    }
    catch (FileError &e)
    {
        std::cerr << "received a file error: " << e.what() << std::endl;
    }
    catch (TransactionTypeError &e)
    {
        std::cerr << "received a transaction error: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "received an unknown error\n";
    }

    cout << "main - End !" << endl;

    return 0;
}



