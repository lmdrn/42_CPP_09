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

double strToDouble(const std::string& str)
{
	std::istringstream iss(str);
	double value;
	iss >> value;
	if (iss.fail())
		std::cerr << "Invalid argument for stod" << std::endl;
	return (value);
}

int strToInt(const std::string& str)
{
	std::istringstream iss(str);
	int	value;
	iss >> value;
	if (iss.fail())
		std::cerr << "Invalid argument for stoi" << std::endl;
	return (value);
}

bool	checkIntMinMax(const std::string& str)
{
	double value = strToDouble(str);
	if (value < INT_MIN || value > INT_MAX)
		return (false);
	return (true);
}


bool checkNeg(const std::string& str)
{
	double value = strToDouble(str);
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
		int convertInt = strToInt(str);
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
		//	std::cout << ORANGE << "Btc is: " << iter->second << RESET << std::endl;
		//	std::cout << GREEN <<  "Iz OK" << RESET << std::endl;
		}
	}
}

void		BitCoinExchange::exchangeBtc(std::multimap<std::string, std::string> BitCoinLine, std::multimap<std::string, std::string> ExchangeRate)
{
	std::multimap<std::string, std::string>::iterator iter1 = BitCoinLine.begin();
	std::multimap<std::string, std::string>::iterator iter2 = ExchangeRate.begin();
	while(iter1 != BitCoinLine.end() && iter2 != ExchangeRate.end())
	{
		if (iter1->first == iter2->first)
		{
			std::cout << GREEN << "Found similar date" << RESET << std::endl;
			int btcValue = strToInt(iter1->second);
			int exRate = strToInt(iter2->second);
			int res = btcValue * exRate;
			std::cout << GREEN << res << RESET << std::endl;
		}
		else if (iter1->first < iter2->first)
		{
			std::cout << "coucou2" << std::endl;
			iter1++;
		}
		else
		{
			std::cout << "coucou3" << std::endl;
			iter2++;
		}
		iter1++;
		iter2++;
	}
	while (iter1 != BitCoinLine.end())
	{
		std::cout << "coucou4" << std::endl;
		iter1++;
	}
	while (iter2 != ExchangeRate.end())
	{
		std::cout << "coucou5" << std::endl;
		iter2++;
	}
}
