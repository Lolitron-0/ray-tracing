#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer
{
   public:

        Timer()
        {
            start=clock();
        }

        Timer(double start)
        {
            this->start=start;
        }

        void restart()
        {
            start=clock();
        }

        //return elapsed time in ms
        double elapsedMs()
        {
            return (static_cast<double>(clock() - start) / CLOCKS_PER_SEC) * 1000.;
        }

private:

        double start;
};


#endif // TIMER_HPP
