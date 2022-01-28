/**
 * clocks, timepoints and durations
 * 
 * Clocks
 * - consists of starting point and a tick rate
 * - now() => time passed since starting point
 * - system_clock => time as held by the system
 * - stable_clock => monotonic (won't move forward or backward due to NTP or Daylight savings, etc. so its not synchronized with NTP server)
 * - high_resolution_clock => returns as precise time as possible
 * clock returns a timepoint from which we extract information
 * 
 * Timepoint
 * - duration since the start of the epoch of the clock (Unix epoch is the de facto standard (at least for system_clock))
 * 
 * Durations
 * - comprises of a ratio (1:1000 for milliseconds) and number of ticks
 * - duration object expresses a time span by means of a count and a period
 * - this is more like actual durations (seconds, minutes, etc.)
 * - you can cast values to more precise types
 * - std::chrono::duration_cast<>
 */

#include <iostream>
#include <chrono>

using namespace std::literals::chrono_literals;

int main()
{
	// Timepoint
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

	int64_t num = 179997;
	for (uint32_t i = 0; i < 100000000; i++)
		num *= num;

	std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
	std::cout << "Operation took: " 
			  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

	// Duration
	// Implicit casting
	auto hours = 24h;
	std::chrono::minutes minutes           = hours;
	std::chrono::seconds seconds           = hours;
	std::chrono::milliseconds milliseconds = hours;
	std::chrono::microseconds microsec     = hours;
	std::chrono::nanoseconds nanosec       = hours;
	
	std::cout << hours.count()    << "h\n"
			  << minutes.count()  << "min\n"
			  << seconds.count()  << "s\n"
			  << microsec.count() << "ms\n"
			  << nanosec.count()  << "ns\n\n";

	// Explicit casting
	std::chrono::seconds sec{2400};
	std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(sec);
	std::cout << min.count() << "min\n";

	// Duration arithmetic
	auto sum = 3h + 52min + 40s - 2ns; // will return ns as most precise
	std::cout << "3h + 52min + 40s - 2ns = " << sum.count() << "ns\n";

	//std::cin.get();
	return 0;
}
