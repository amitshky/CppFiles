#pragma once

/**
 * Insertion sort:
 * 
 * In the subarray A[0, ..., i-1], insert a single element A[i] in its correct place, such 
 * the subarray A[0, ..., i] is sorted.
 * 
 * Think of this as partitioning the given numbers into two groups - sorted and unsorted
 * Take an element from the unsorted partition and put it in order in the sorted partition
 * Initially only the first element is in the sorted partition
 **/

template<typename Iter, typename Compare>
inline void InsertionSort(const Iter first, const Iter last, Compare compare)
{
	// TODO: check range of first and last i.e., 
	// check if [first, last) forms range of iterator
	// maximum size for insertion sort = 32 // std::sort

	using ValueType = typename std::iterator_traits<Iter>::value_type; // to get the type of value stored in the container
	for (Iter it = first + 1; it != last; it++)
	{
		ValueType key = std::move(*it); // first element of the unsorted subarray
		for (Iter it2 = it - 1; it2 != first - 1 && compare(key, *it2); it2--)
		{
			// insert key to the correct order of the sorted subarray
			// swap
			*(it2 + 1) = std::move(*it2);
			*it2 = std::move(key);
		}
	}
}

template<typename Iter>
inline void InsertionSort(const Iter first, const Iter last)
{
	using ValueType = typename std::iterator_traits<Iter>::value_type; // to get the type of value stored in the container
	InsertionSort(first, last, [](ValueType left, ValueType right) { return left < right; });
}