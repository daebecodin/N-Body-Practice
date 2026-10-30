#include <matplot/matplot.h>
#include <vector>
#include <cmath>

using namespace matplot;
using namespace std;


int main()
{
    vector<double> x = linspace(-10, 10, 1000);
    vector<double> y = transform(
            x, 
            [] (auto x) {return sin(x) + sin(2 * x);});
    plot(x, y , "-o");

    show();
    return 0;
}

