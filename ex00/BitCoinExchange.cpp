/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:46:33 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/10 11:25:01 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

// Constructor
BitCoinExchange::BitCoinExchange()
{}

// Destructor
BitCoinExchange::~BitCoinExchange()
{}

// Copy Constructor
BitCoinExchange::BitCoinExchange(const BitCoinExchange& copy)
{
	*this = copy;
}

// Copy Assignment Operator
BitCoinExchange& BitCoinExchange::operator=(const BitCoinExchange& copy)
{
	if (this != &copy)
	{}
	return (*this);
}

void	BitCoinExchange::checkDate(std::multimap<std::string, std::string> BitCoinLine)
{
	for (std::multimap<std::string, std::string>::iterator iter = BitCoinLine.begin(); iter != BitCoinLine.end(); iter++)
	{
		struct tm tm;
		if (strptime(iter->first.c_str(), "%Y-%m-%d", &tm))
		{
			std::cout << ORANGE << "Date is: " << iter->first << RESET << std::endl;
			std::cout << GREEN << "SUCCESS : Date valid " << RESET << std::endl;
		}
		else
		{
			std::cout << ORANGE << "Date is: " << iter->first << RESET << std::endl;
			std::cout << RED << "ERROR : Date unvalid " << RESET << std::endl;
		}
	}
}

bool	checkDigit(const std::string& str)
{
	if (str.empty())
		return (false);
	size_t	start = 0;
	bool	isFloat = 0;
	if (str[0] == '-')
	{
		if (str.length() == 1)
			return (false);
		start = 1;
	}
	for (size_t i = start; i < str.length(); i++)
	{
		if (str[i] == '.')
		{
			if (isFloat)
				return (false);
			isFloat = true;
		}
		else if (!isdigit(str[i]))
			return (false);
	}
	return (true);
}

bool	checkIntMinMax(const std::string& str)
{
	double value = std::stod(str);
	if (value < INT_MIN || value > INT_MAX)
		return (false);
	return (true);
}

bool checkNeg(const std::string& str)
{
	double value = std::stod(str);
	if (value < 0)
		return (false);
	return (true);
}


int	customStoi(const std::string &str)
{
	if (str.empty())
	{
		std::cout << str << std::endl;
		std::cerr << RED << "ERROR: Empty string" << RESET << std::endl; 
		return (-1);
	}
	if (!checkDigit(str))
	{
		std::cout << str << std::endl;
		std::cerr << RED << "ERROR: Not a digit" << RESET << std::endl; 
		return (-1);
	}
	if (!checkIntMinMax(str))
	{
		std::cout << str << std::endl;
		std::cerr << RED << "ERROR: Int min or max" << RESET << std::endl; 
		return (-1);
	}
	if (!checkNeg(str))
	{
		std::cout << str << std::endl;
		std::cerr << RED << "ERROR: Value is negative" << RESET << std::endl; 
		return (-1);
	}
	else
	{
		int convertInt = stoi(str);
		return (convertInt);
	}
	return (0);
}

void	BitCoinExchange::checkBtc(std::multimap<std::string, std::string> BitCoinLine)
{
	for (std::multimap<std::string, std::string>::iterator iter = BitCoinLine.begin(); iter != BitCoinLine.end(); iter++)
	{
		int btc = customStoi(iter->second);
		if (btc >= 0 && btc <= 100)
		{
			std::cout << ORANGE << "Btc is: " << iter->second << RESET << std::endl;
			std::cout << GREEN <<  "Iz OK" << RESET << std::endl;
		}
	}
}
