/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:35 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/14 08:25:35 by lmedrano         ###   ########.fr       */
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
		for (int i = 1; i < ac; i++)
		{
			std::string token = av[i];
			if (checkNumber(av[i]) == false)
			{
				std::cerr << RED << "ERROR: Invalid Number! Insert a valid sequence" << RESET << std::endl;
				exit(-1);
			}
			if (checkUnique(token, doublonChecker) == false)
			{
				std::cerr << RED << "ERROR: Doublons! Insert valid number sequence." << RESET << std::endl;
				exit(-1);
			}
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

//TIME
void	PmergeMe::printElapsedTime(struct timeval start, struct timeval end) const
{
	long seconds = end.tv_sec - start.tv_sec;
	long useconds = end.tv_usec - start.tv_usec;
	double elapsed = seconds + useconds*1e-6;
	std::cout << PURPLE << "Time spent: " << std::fixed << std::setprecision(6) << elapsed << " secs" << RESET << std::endl;
}

//PARSING
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

//FCT TO DIVIDE THE VECTOR INTO PAIRS
void	PmergeMe::divideIntoPairsVec(std::vector<int> &container)
{
	for (size_t i = 0; i + 1 < container.size(); i += 2)
	{
		_pair.push_back(std::make_pair(container[i], container[i + 1]));
	}
	if (container.size() % 2 != 0)
	{
		_pair.push_back(std::make_pair(container.back(), -1));
	}
}

//FCT TO DIVIDE THE LIST INTO PAIRS
void	PmergeMe::divideIntoPairsList(std::list<int> &container)
{
	std::list<int>::iterator iter = container.begin();
	while (iter != container.end())
	{
		std::list<int>::iterator iter2 = iter;
		iter2++;
		if (iter2 != container.end())
		{
			_pairL.push_back(std::make_pair(*iter, *iter2));
			iter = iter2;
			iter++;
		}
		else
		{
			_pairL.push_back(std::make_pair(*iter, -1));
			iter++;
		}
	}
}

//FCT TO SORT EACH PAIR
std::pair<int, int>	PmergeMe::sortMinMaxPair(const std::pair<int, int>& pair) const
{
	if (pair.first > pair.second && pair.second != -1)
		return (std::make_pair(pair.second, pair.first));
	return (pair);
}


//FCT TO SORT EACH PAIR IN VECTOR
void	PmergeMe::insertSortedMinMaxVec()
{
	for (std::vector<std::pair<int, int> >::iterator iter = _pair.begin(); iter != _pair.end(); iter++)
		*iter = sortMinMaxPair(*iter);
}

//FCT TO SORT EACH PAIR IN LIST
void	PmergeMe::insertSortedMinMaxList()
{
	for (std::list<std::pair<int, int> >::iterator iter = _pairL.begin(); iter != _pairL.end(); iter++)
		*iter = sortMinMaxPair(*iter);
}


//FCT TO DIVIDE VECTOR INTO A MAX ARRAY AND MIN ARRAY
void	PmergeMe::CreateVec()
{
	insertMinInMaxArray(_pair);
	maxArray(_pair, _max);
	minArray(_pair, _min);

	std::vector<int> currentGroup;
	groupMinArray(_powerOfTwo, _min, currentGroup);
}

//FCT TO DIVIDE LIST INTO A MAX ARRAY AND MIN ARRAY
void	PmergeMe::CreateList()
{
	insertMinInMaxArray(_pairL);
	maxArray(_pairL, _maxL);
	minArray(_pairL, _minL);

	std::list<int> currentGroup;
	groupMinArray(_powerOfTwoL, _minL, currentGroup);
}

//FCT TO INSERT MIN ARRAY INTO MAX ARRAY WITH FORD JOHNSON FOR VECTOR
void	PmergeMe::processGroupsVec()
{
	processGroups(_powerOfTwo, _max);
}

//FCT TO INSERT MIN ARRAY INTO MAX ARRAY WITH FORD JOHNSON FOR LIST
void	PmergeMe::processGroupsList()
{
	processGroups(_powerOfTwoL, _maxL);
}
