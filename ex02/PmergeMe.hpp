/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:52 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/12 16:54:25 by lmedrano         ###   ########.fr       */
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
		std::vector<int> 			_sequence;
		std::vector<std::pair<int, int> >	_pair;
		std::vector<int>			_max;
		std::vector<int>			_min;
		std::vector<std::vector<int> >		_powerOfTwo;

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

		//GETTERS
		const std::vector<int>& 		getSequence() const;	
		const std::vector<int>& 		getMax() const;	
		const std::vector<int>& 		getMin() const;	
		
		//DEBUG
		template <typename Container>
		void					printContainer(const Container& container);
		void 					printPairs() const;
		void 					printMinMaxArrays();
		void 					printMinGrouped();
		void 					printContMin(const std::vector<int>& container);

		//TIME
		void 					printElapsedTime(struct timeval start, struct timeval end) const;
		
		//PARSING
		void					parsing(int ac, char **av);	

		// PAIRING
		void					divideIntoPairs();
		std::pair<int, int>			sortMinMaxPair(const std::pair<int, int>& pair) const;
		void					insertSortedMinMax();

		// MAX ARRAY
		void					insertMinInMaxArray();
		void					maxArray();

		//MIN ARRAY
		void					minArray();
		void					clearInitialVector();

		// FORD JOHNSON + BINARY SEARCH + INSERT MIN TO MAX ARRAY
		void					groupMinArray();
		std::vector<int>::iterator		binarySearch(int val);
		void					processGroups();

};

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
		std::cout << ORANGE << "Before:  "; 
		for (typename Container::const_iterator iter = container.begin(); iter != container.end(); iter++)
		{
			std::cout << *iter << " ";
		}
		std::cout << RESET << std::endl;
	}
}

template <typename Container>
void					printContainer(const Container& container);

#endif
