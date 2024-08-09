/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:59:32 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/09 14:52:17 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool checkNumber(const std::string& args)
{
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

bool	checkUniqueInStr(const std::string& args)
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

bool checkUnique(const std::string& args, std::set<int>& doublonChecker)
{
	if (!checkNumber(args))
		return (false);
	int nbr = std::atoi(args.c_str());
	if (doublonChecker.find(nbr) != doublonChecker.end())
		return (false);
	doublonChecker.insert(nbr);
	return (true);
}

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << RED << "WRONG USAGE: ./PmergeMe <insert positive sequence int>" << RESET << std::endl;
		return (-1);
	}
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
				return (-1);
			}
			okay = checkUnique(token, doublonChecker);
		}
		if (okay == false)
		{
			std::cerr << RED << "ERROR: Doublons! Insert valid number sequence." << RESET << std::endl;
			return (-1);
		}
	}
	else
	{
		if (checkUniqueInStr(av[1]) == false)
		{
			std::cerr << RED << "ERROR: Doublons or Invalid number ! Insert valid number sequence." << RESET << std::endl;
			return (-1);
		}
	}
	return (0);
}
