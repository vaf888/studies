#include <cassert> // for assert()
#include <iostream>
 
using namespace std;

class Matrix
{
private:
    double m_data[4][4]{};
 
public:
    Matrix(){};
    double& operator()(int row, int col);
    double operator()(int row, int col) const; // for const objects
    void operator()(); // tests only
};
 
double& Matrix::operator()(int row, int col)
{
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);
 
    return m_data[row][col];
}

void Matrix::operator()()
{
    cout << "Tests Only !!!"  << endl;
}
 
double Matrix::operator()(int row, int col) const
{
    assert(col >= 0 && col < 4);
    assert(row >= 0 && row < 4);
 
    return m_data[row][col];
}

int main()
{
    Matrix matrix;
    matrix(1, 2) = 4.5;
    std::cout << matrix(1, 2) << '\n';
    matrix();

    return 0;
}
