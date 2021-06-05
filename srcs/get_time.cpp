#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;

// A sample function whose time taken to
// be measured
void fun()
{
	for (int i=0; i<10; i++)
	{
	}
}

int main()
{
	/* The function gettimeofday() can get the time as
	well as timezone.
	int gettimeofday(struct timeval *tv, struct timezone *tz);
	The tv argument is a struct timeval and gives the
	number of seconds and micro seconds since the Epoch.
	struct timeval {
			time_t	 tv_sec;	 // seconds
			suseconds_t tv_usec; // microseconds
		}; */
	struct timeval start, end;

	// start timer.
	gettimeofday(&start, NULL);

	// unsync the I/O of C and C++.
	ios_base::sync_with_stdio(false);

	fun();

	// stop timer.
	gettimeofday(&end, NULL);

	// Calculating total time taken by the program.
	double time_taken;

	time_taken = (end.tv_sec - start.tv_sec) * 1e6;
	time_taken = (time_taken + (end.tv_usec -
							start.tv_usec)) * 1e-6;

	cout << "Time taken by program is : " << fixed
		<< time_taken << setprecision(6);
	cout << " sec" << endl;
	return 0;
}
