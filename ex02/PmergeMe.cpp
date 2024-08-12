/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:35 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/12 17:23:13 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//TODO FORD-JOHNSON
//1. J'ai un tableau unsorted de numeros
//
//|| Z0 | Z1 | Z2 | Z3 | Z4 | Z5 ||
//
//2. je divise ce tableau en pairs toujours unsorted
//
//|| Z0,Z1 | Z2,Z3 | Z4,Z5 ||
//
//3. Je cherche le min et le max de chaque pair
//X1 = min(Z0,Z1) et Y1 = max(Z0,Z1)
//
//|| X1,Y1 | X2,Y2 | X3,Y3 | X4,Y4 | X5,Y5 ||
//
//4. Je dois m'assurer que Yi >= Xi ET QUE Yi <= Yi+1
//Donc je sorte les Yi et je peux mettre Xi en 1st parce que je sais qu'il est toujours plus petit que Yi.
//
//|| X1 | Y1 | Y2 | Y3 | Y4 | Y5 || <!!SORTED!!>>
//5. I apply FORD-JOHNSON by doing a binary search on my sorted array
//To do so, I Take my remaining Xi and divide them into groups following puissance de 2
//(2,4,8,16,32,64,.....)
//So my first group should be composed of 2 elements
//Then my second group should be == to the next puissance de 2, by additioning the previous group.
//Previous group is 2. Next puissance de 2 is 4. 4 - 2 = 2. The next group should be two elements.
//Next group: Prev group is 2. Next puissance is 8. 8 - 2 = 6. Next group is made of 6 elements.
//|| X2,X3 | X4,X5 | X6,X7,X8,X9,X10,X11 | .... || example of groups by power of 2 
//Then I should take each group, starting from the end and insert each Xi doing a binary search.
//So 1st I take X3, look for the middle of the Yi array. If it's in the 1st half, I cut the 1st half in 2 again and look for the number, etc..
//Until the array is sorted.

// ERROR MANAGEMENT
// Gerer les doublons
// Gerer les overflows (int_min/int_max)
// Test avec 3000 int
//

PmergeMe::PmergeMe(int ac, char **av)
{
	std::cout << ORANGE << "XX __ PmergeMe CREATED __ XX" << RESET << std::endl;

	if (ac > 2)
	{
		std::set<int>		doublonChecker;
		bool okay = true;
		for (int i = 1; i < ac; i++)
		{
			std::string token = av[i];
			if (checkNumber(av[i]) == false)
			{
				std::cerr << RED << "ERROR: Invalid Number! Insert a valid sequence" << RESET << std::endl;
				exit(-1);
			}
			okay = checkUnique(token, doublonChecker);
		}
		if (okay == false)
		{
			std::cerr << RED << "ERROR: Doublons! Insert valid number sequence." << RESET << std::endl;
			exit(-1);
		}
	}
	else
	{
		if (itTakesTwo(av[1]) == false)
		{
			std::cerr << RED << "ERROR: Less than 2 elements or empty sequence" << RESET << std::endl;
			exit(-1);
		}
		if (checkUniqueInStr(av[1]) == false)
		{
			std::cerr << RED << "ERROR: Doublons or Invalid number ! Insert valid number sequence." << RESET << std::endl;
			exit(-1);
		}
	}
}

PmergeMe::~PmergeMe()
{
	std::cout << ORANGE << "XX __ PmergeMe DESTROYED __ XX" << RESET << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	*this = copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& copy)
{
	if (this != &copy)
	{}
	return (*this);
}

//methods
void	PmergeMe::printElapsedTime(struct timeval start, struct timeval end) const
{
	long seconds = end.tv_sec - start.tv_sec;
	long useconds = end.tv_usec - start.tv_usec;
	double elapsed = seconds + useconds*1e-6;
	std::cout << PURPLE << "Time spent: " << std::fixed << std::setprecision(6) << elapsed << " secs" << RESET << std::endl;
}

void	PmergeMe::printPairs() const
{
	if (_pair.empty())
		std::cout << RED << "EMPTY PAIRS" << RESET << std::endl;
	else
	{
		for (std::vector<std::pair<int, int> >::const_iterator iter = _pair.begin(); iter != _pair.end(); iter++)
		{
			std::cout << GREEN << "Pair is: " << iter->first << " , " << iter->second << RESET << std::endl;
		}
	}
}

bool PmergeMe::checkNumber(const std::string& args) const
{
	if (args.empty())
		return (false);
	for (size_t i = 0; i < args.size(); i++)
	{
		if (!std::isdigit(args[i]))
			return (false);
	}
	long long nbr = std::atoll(args.c_str());
	if (nbr < 0 || nbr > std::numeric_limits<int>::max())
		return (false);
	return (true);
}

bool	PmergeMe::checkUniqueInStr(const std::string& args) const
{
	std::istringstream	iss(args);
	std::string		token;
	std::set<int>		doublonChecker;

	while (iss >> token)
	{
		if (!checkNumber(token))
		{
			return (false);
		}
		int nbr = std::atoi(token.c_str());
		if (doublonChecker.find(nbr) != doublonChecker.end())
		{
			return (false);
		}
		doublonChecker.insert(nbr);
	}
	return (true);
}

bool PmergeMe::checkUnique(const std::string& args, std::set<int>& doublonChecker) const
{
	if (!checkNumber(args))
		return (false);
	int nbr = std::atoi(args.c_str());
	if (doublonChecker.find(nbr) != doublonChecker.end())
		return (false);
	doublonChecker.insert(nbr);
	return (true);
}


bool PmergeMe::itTakesTwo(const std::string& input) const
{
	std::istringstream iss(input);
	std::string token;
	int count = 0;

	while (iss >> token)
	{
		if (checkNumber(token))
		{
			count++;
			if (count >= 2)
				return (true);
		}
	}
	return (false);
}

//GETTERS

const std::vector<int>& PmergeMe::getSequence() const
{
	return (_sequence);
}

const std::vector<int>& PmergeMe::getMax() const
{
	return (_max);
}

const std::vector<int>& PmergeMe::getMin() const
{
	return (_min);
}

void	PmergeMe::parsing(int ac, char **av)
{
	if (ac > 2)
	{
		for (int i = 1; i < ac; i++)
		{
			std::string	arg = av[i];
			_sequence.push_back(std::atoi(arg.c_str()));
		}
	}
	else if (ac == 2)
	{
		
		std::string		arg = av[1];
		std::istringstream	iss(arg);
		std::string		token;
		while (iss >> token)
		{
			_sequence.push_back(std::atoi(token.c_str()));
		}
	}
}

void	PmergeMe::divideIntoPairs()
{
	for (size_t i = 0; i + 1 < _sequence.size(); i += 2)
	{
		_pair.push_back(std::make_pair(_sequence[i], _sequence[i + 1]));
	}
	if (_sequence.size() % 2 != 0)
	{
		_pair.push_back(std::make_pair(_sequence.back(), -1));
	}
}

std::pair<int, int>	PmergeMe::sortMinMaxPair(const std::pair<int, int>& pair) const
{
	if (pair.first > pair.second && pair.second != -1)
		return (std::make_pair(pair.second, pair.first));
	return (pair);
}

void	PmergeMe::insertSortedMinMax()
{
	for (std::vector<std::pair<int, int> >::iterator iter = _pair.begin(); iter != _pair.end(); iter++)
		*iter = sortMinMaxPair(*iter);
}

void	PmergeMe::maxArray()
{
	while (true)
	{
		int smallestMax = std::numeric_limits<int>::max();
		std::vector<std::pair<int, int> >::iterator pairIter = _pair.end();
		
		for (std::vector<std::pair<int, int> >::iterator iter = _pair.begin(); iter != _pair.end(); iter++)
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
		if (pairIter == _pair.end())
			break ;
		_max.push_back(smallestMax);
		pairIter->second = -1;
	}
}

void	PmergeMe::insertMinInMaxArray()
{
	if (_pair.empty())
		return ;
	int smallestMax = std::numeric_limits<int>::max();
	int min = std::numeric_limits<int>::max();
	std::vector<std::pair<int, int> >::iterator pairIter;
	std::vector<std::pair<int, int> >::iterator iter;

	for (iter = _pair.begin(); iter != _pair.end(); iter++)
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
	_max.push_back(min);
	_max.push_back(smallestMax);
	_pair.erase(pairIter);
}

void	PmergeMe::minArray()
{
	std::vector<std::pair<int, int> >::const_iterator iter;
	for (iter = _pair.begin(); iter != _pair.end(); iter++)
	{
		if (iter->first != -1)
			_min.push_back(iter->first);
	}
}

void	PmergeMe::clearInitialVector()
{
	_pair.clear();
}

void	PmergeMe::printMinMaxArrays()
{
	std::cout << "Max" << std::endl;
	for (std::vector<int>::const_iterator iter = _max.begin(); iter != _max.end(); iter++)
		std::cout << *iter << " ";
	std::cout << RESET << std::endl;

	std::cout << "Min" << std::endl;
	for (std::vector<int>::const_iterator iter = _min.begin(); iter != _min.end(); iter++)
		std::cout << *iter << " ";
	std::cout << RESET << std::endl;
}

void PmergeMe::groupMinArray()
{
	_powerOfTwo.clear();

	std::vector<int>::iterator start = _min.begin();
	std::vector<int>::iterator end = _min.end();
	size_t	nextPowerOfTwo = 1;
	size_t	prevGroupSize = 1;
	size_t	groupSize = 1;
	
	while (start != end)
	{
		std::vector<int> currentGroup;
		std::vector<int>::iterator groupEnd = start;
		
		std::advance(groupEnd, std::min(groupSize, static_cast<size_t>(std::distance(start, end))));
		for (; start != groupEnd; start++)
			currentGroup.push_back(*start);

		if (currentGroup.size() < groupSize)
		{
			while (currentGroup.size() < groupSize)
				currentGroup.push_back(-1);
		}
		_powerOfTwo.push_back(currentGroup);
		nextPowerOfTwo *= 2;
		prevGroupSize = currentGroup.size();
		groupSize = nextPowerOfTwo - prevGroupSize;
	}

}

void PmergeMe::printMinGrouped() {
    for (std::vector<std::vector<int> >::const_iterator gIter = _powerOfTwo.begin(); gIter != _powerOfTwo.end(); ++gIter) {
        printContMin(*gIter);
    }
}

void PmergeMe::printContMin(const std::vector<int>& container) {
    for (std::vector<int>::const_iterator iter = container.begin(); iter != container.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

std::vector<int>::iterator PmergeMe::binarySearch(int val)
{
	std::vector<int>::iterator left = _max.begin();
	std::vector<int>::iterator right = _max.end();

	while (left < right)
	{
		std::vector<int>::iterator mid = left + (right - left) / 2;
		if (*mid < val)
			left = mid + 1;
		else
			right = mid;
	}
	return (left);
}

void PmergeMe::processGroups()
{
	for(std::vector<std::vector<int> >::const_iterator gIter = _powerOfTwo.begin(); gIter != _powerOfTwo.end(); gIter++)
	{
		const std::vector<int>& group = *gIter;
		for (std::vector<int>::const_reverse_iterator rIter = group.rbegin(); rIter != group.rend(); rIter++)
		{
			int val = *rIter;
			if (val == -1)
				continue ;
			std::vector<int>::iterator pos = binarySearch(val);
			_max.insert(pos, val);
		}
	}
	std::cout << PURPLE << "After:   ";
	for (std::vector<int>::const_iterator it = _max.begin(); it != _max.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << RESET << std::endl;
}
