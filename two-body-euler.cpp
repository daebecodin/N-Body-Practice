/*
 * 
 */

#include <matplot/matplot.h>
#include <cmath>
#include <vector>

using namespace std;
using namespace matplot;

int main() 
{
    // masses
    double mSun = 1;
    double mEarth = 1;

    // universal gravity constant
    double uGrav = 1;

    // position vectors
    vector<double> pSun {-1.0, 0.0, 0.0};
    vector<double> pEarth {1.0, 0.0, 0.0};

    // time step
    double dt = 0.01;
    double t_end = 100;

    // plot data buffers
    vector<double> pxEarth;
    vector<double> pyEarth;
    vector<double> pxSun;
    vector<double> pySun;

    // velocity vectors
    vector<double> vSun {0.0, -0.5, 0.0};
    vector<double> vEarth {0.0, 0.5, 0.0};


    const int numSteps = static_cast<int>(t_end / dt);
    for (int i = 0; i < numSteps; ++i)
    {

        // displacement vector
        vector<double> displacement 
        {
            pEarth[0] - pSun[0],
            pEarth[1] - pSun[1],
            pEarth[2] - pSun[2]

        };

        // resultant vector
        double r = std::sqrt (
                displacement[0] * displacement[0] +
                displacement[1] * displacement[1] +
                displacement[2] * displacement[2] 
                );

        // earth and sun acceleration do to gravity
        double earthFactor = -uGrav * mSun / (r * r * r);
        double sunFactor = uGrav * mEarth / (r * r * r);

        // acceleration
        vector<double> aEarth {
            earthFactor * displacement[0],
            earthFactor * displacement[1],
            earthFactor * displacement[2]

        };

        vector<double> aSun {
            sunFactor * displacement[0],
            sunFactor * displacement[1],
            sunFactor * displacement[2]
        };

        // forward euler
        // positions use the previous velocities
        for (int j = 0; j < 3; ++j)
        {
            // integration position
            pEarth[j] += vEarth[j] * dt;
            pSun[j] += vSun[j] * dt;

            // integration velocity
            vEarth[j] += aEarth[j] * dt;
            vSun[j] += aSun[j] * dt;

        }


        /*
         * without thus loop, matlib++ plots 1mil
         * points per body making the start up slow
         *
         * now we print 10,000 points per body
         */
        if (i % 100  == 0)
        {
            pxEarth.push_back(pEarth[0]);
            pyEarth.push_back(pEarth[1]);

            pxSun.push_back(pSun[0]);
            pySun.push_back(pSun[1]);
        }
    };

    auto fig = matplot::figure(true);
    fig->backend()->run_command("unset warnings");

    plot(pxEarth, pyEarth);
    hold(on);
    plot(pxSun, pySun);
    xlabel("x");
    ylabel("y");
    axis(matplot::equal);
    show();


    return 0;
}
