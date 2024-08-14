/* ************************************************************************** */

/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:52 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/13 15:38:08 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <set>
#include <limits>
#include <vector>
#include <cstdlib>
#include <utility>
#include <sys/time.h>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <list>

#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[38;5;208m"
#define RED "\x1b[31m"
#define PURPLE "\x1b[35m"

class	PmergeMe
{
	private:
		//VECTORS
		std::vector<std::pair<int, int> >	_pair;
		std::vector<int>			_max;
		std::vector<int>			_min;
		std::vector<std::vector<int> >		_powerOfTwo;

		//LISTS
		std::list<std::pair<int, int> >		_pairL;
		std::list<int>				_maxL;
		std::list<int>				_minL;
		std::list<std::list<int> >		_powerOfTwoL;

		//CHECK AV FOR PARSING
		bool					checkNumber(const std::string& args) const;
		bool					checkUnique(const std::string& args, std::set<int>& doublonChecker) const;
		bool					itTakesTwo(const std::string& input) const;
		bool					checkUniqueInStr(const std::string& args) const;
	
	public:
		//CANONICAL
		PmergeMe(int ac, char **av);
		~PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& copy);

		//DEBUG
		template <typename Container>
		void					printContainer(const Container& container);

		//TIME
		void 					printElapsedTime(struct timeval start, struct timeval end) const;
		
		//PARSING
		template <typename Container>
		void					parsing(int ac, char **av, Container &container);	

		// PAIRING
		void					divideIntoPairsVec(std::vector<int> &container);
		void					divideIntoPairsList(std::list<int> &container);
		std::pair<int, int>			sortMinMaxPair(const std::pair<int, int>& pair) const;
		void					insertSortedMinMaxVec();
		void					insertSortedMinMaxList();

		// MAX ARRAY
		template <typename Container>
		void					insertMinInMaxArray(Container &container);
		void					CreateVec();
		void					CreateList();
		template <typename ContPair, typename ContMax>
		void					maxArray(ContPair &contPair, ContMax &maxArray);

		//MIN ARRAY
		template <typename ContPair, typename ContMin>
		void					minArray(ContPair &contPair, ContMin &minArray);
		template <typename Container>
		void					clearInitialVector(Container &container);

		// FORD JOHNSON + BINARY SEARCH + INSERT MIN TO MAX ARRAY
		template <typename ContPower, typename ContMin>
		void 					groupMinArray(ContPower &power, ContMin &min, ContMin &currentGroup);
		void					processGroupsVec();
		void					processGroupsList();
		template <typename Container>
		typename Container::iterator 		binarySearch(Container &container, int val);
		template <typename ContPower, typename ContMax>
		void					processGroups(ContPower &power, ContMax &max);

};


//TEMPLATES

//FCT TO PRINT A CONTAINER
template <typename Container>
void	PmergeMe::printContainer(const Container& container)
{
	if (container.empty())
	{
		std::cout << RED << "EMPTY CONTAINER" << RESET << std::endl;
		return ;
	}
	else
	{
		std::cout << RED << "Before:  "; 
		for (typename Container::const_iterator iter = container.begin(); iter != container.end(); iter++)
		{
			std::cout << *iter << " ";
		}
		std::cout << RESET << std::endl;
	}
}

template <typename Container>
void					printContainer(const Container& container);

//FCT TO PARSE MY AV PARAM INTO VECTOR OR LIST
template <typename Container>
void	PmergeMe::parsing(int ac, char **av, Container &container)
{
	if (ac > 2)
	{
		for (int i = 1; i < ac; i++)
		{
			std::string	arg = av[i];
			container.push_back(std::atoi(arg.c_str()));
		}
	}
	else if (ac == 2)
	{
		
		std::string		arg = av[1];
		std::istringstream	iss(arg);
		std::string		token;
		while (iss >> token)
		{
			container.push_back(std::atoi(token.c_str()));
		}
	}
}

template <typename Container>
void	parsing(int ac, char **av, Container &container);

//FCT TO INSERT MIN VALUE OF MAX VALUE INTO MAX ARRAY
template <typename Container>
void	PmergeMe::insertMinInMaxArray(Container &container)
{
	if (container.empty())
		return ;
	int smallestMax = std::numeric_limits<int>::max();
	int min = std::numeric_limits<int>::max();
	typename Container::iterator pairIter;
	typename Container::iterator iter;

	for (iter = container.begin(); iter != container.end(); iter++)
	{
		int currentMax = std::max(iter->first, iter->second);
		int currentMin = std::min(iter->first, iter->second);

		if (currentMin == -1 && currentMax == -1)
			continue ;
		if (currentMax < smallestMax && currentMin != -1)
		{
			smallestMax = currentMax;
			min = currentMin;
			pairIter = iter;
		}
		else if (currentMax == smallestMax)
		{
			if (currentMin < min && currentMin != -1)
			{
				min = std::min(min, currentMin);
				pairIter = iter;
			}
		}
	}
	if (typeid(container) == typeid(std::vector<std::pair<int, int> >))
	{
		_max.push_back(min);
		_max.push_back(smallestMax);
	}
	else if (typeid(container) == typeid(std::list<std::pair<int ,int> >))
	{
		_maxL.push_back(min);
		_maxL.push_back(smallestMax);
	}
	container.erase(pairIter);
}

template <typename Container>
void	insertMinInMaxArray(Container &container);

//FCT TO POPULATE AND SORT MAX ARRAY
template <typename ContPair, typename ContMax>
void	PmergeMe::maxArray(ContPair &contPair, ContMax &maxArray)
{
	while (true)
	{
		int smallestMax = std::numeric_limits<int>::max();
		typename ContPair::iterator pairIter = contPair.end();
		
		for (typename ContPair::iterator iter = contPair.begin(); iter != contPair.end(); iter++)
		{
			int currentMax = iter->second;
			if (currentMax == -1)
				continue ;
			if (currentMax < smallestMax)
			{
				smallestMax = currentMax;
				pairIter = iter;
			}
		}
		if (pairIter == contPair.end())
			break ;
		maxArray.push_back(smallestMax);
		pairIter->second = -1;
	}
}

template <typename ContPair, typename ContMax>
void	maxArray(ContPair &contPair, ContMax &maxArray);


//FCT TO POPULATE MIN ARRAY UNSORTED
template <typename ContPair, typename ContMin>
void	PmergeMe::minArray(ContPair &contPair, ContMin &minArray)
{
	typename ContPair::const_iterator iter;
	for (iter = contPair.begin(); iter != contPair.end(); iter++)
	{
		if (iter->first != -1)
			minArray.push_back(iter->first);
	}
}

template <typename ContPair, typename ContMin>
void	minArray(ContPair &contPair, ContMin &minArray);


//FCT TO CLEAR MY INITIAL VECTOR OR LIST 
template <typename Container>
void	PmergeMe::clearInitialVector(Container &container)
{
	container.clear();
}

template <typename Container>
void	clearInitialVector(Container &container);


//FCT TO GROUP MY MIN ARRAY ACCORDING TO POWER OF TWO
template <typename ContPower, typename ContMin>
void PmergeMe::groupMinArray(ContPower &power, ContMin &min, ContMin &currentGroup)
{
	power.clear();

	typename ContMin::iterator start = min.begin();
	typename ContMin::iterator end = min.end();
	size_t	nextPowerOfTwo = 1;
	size_t	prevGroupSize = 1;
	size_t	groupSize = 1;
	
	while (start != end)
	{
		currentGroup.clear();
		typename ContMin::iterator groupEnd = start;
		
		std::advance(groupEnd, std::min(groupSize, static_cast<size_t>(std::distance(start, end))));
		for (; start != groupEnd; start++)
			currentGroup.push_back(*start);

		if (currentGroup.size() < groupSize)
		{
			while (currentGroup.size() < groupSize)
				currentGroup.push_back(-1);
		}
		power.push_back(currentGroup);
		nextPowerOfTwo *= 2;
		prevGroupSize = currentGroup.size();
		groupSize = nextPowerOfTwo - prevGroupSize;
	}

}

template <typename ContPower, typename ContMin>
void groupMinArray(ContPower &power, ContMin &min, ContMin &currentGroup);

//FCT TO INSERT EACH MIN VALUE INTO MAX ARRAY SORTED BY DOING A BINARY SEARCH
template <typename ContPower, typename ContMax>
void PmergeMe::processGroups(ContPower &power, ContMax &max)
{
	for(typename ContPower::const_iterator gIter = power.begin(); gIter != power.end(); gIter++)
	{
		ContMax group;
		group = *gIter;
		for (typename ContMax::const_reverse_iterator rIter = group.rbegin(); rIter != group.rend(); rIter++)
		{
			int val = *rIter;
			if (val == -1)
				continue ;
			typename ContMax::iterator pos = binarySearch(max, val);
			max.insert(pos, val);
		}
	}
	std::cout << GREEN << "After:   ";
	for (typename ContMax::const_iterator it = max.begin(); it != max.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << RESET << std::endl;
 }

template <typename ContPower, typename ContMax>
void	processGroups(ContPower &power, ContMax &max);

//FCT BINARY SEARCH (START FROM MIDDLE THEN GO LEFT OR RIGHT AND REDUCE POSSIBILITIES)
template <typename Container>
typename Container::iterator PmergeMe::binarySearch(Container &container, int val)
{
    typename Container::iterator left = container.begin();
    typename Container::iterator right = container.end();

    while (left != right)
    {
        typename Container::iterator mid = left;
        std::advance(mid, std::distance(left, right) / 2);
        if (*mid < val)
            left = ++mid;
        else
            right = mid;
    }
    return left;
}

template <typename Container>
typename Container::iterator binarySearch(Container &container, int val);

#endif
