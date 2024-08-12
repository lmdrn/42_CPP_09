/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:52 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/12 12:05:21 by lmedrano         ###   ########.fr       */
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

		void 					printElapsedTime(struct timeval start, struct timeval end) const;
		void					printTotalTime(struct timeval start, struct timeval end) const;
		bool					checkNumber(const std::string& args) const;
		bool					checkUnique(const std::string& args, std::set<int>& doublonChecker) const;
		bool					itTakesTwo(const std::string& input) const;
		bool					checkUniqueInStr(const std::string& args) const;
		void					parsing(int ac, char **av);	
		void					divideIntoPairs();
		std::pair<int, int>			sortMinMaxPair(const std::pair<int, int>& pair) const;
		void					insertSortedMinMax();
		void					maxArray();
		void					insertMinInMaxArray();
		void					processMaxArray();
		void					minArray();
		void					groupMinArray();
		std::vector<int>::iterator		binarySearch(int val);
		void					processGroups();
	
	public:
		PmergeMe(int ac, char **av);
		~PmergeMe();
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& copy);
		void printVector() const;
		void printPairs() const;
		void clearInitialVector();
		void printMinMaxArrays();
		void printMinGrouped();
		void printContMin(const std::vector<int>& container);
};

#endif
