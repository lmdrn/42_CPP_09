/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:46:33 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/23 10:45:35 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

// Constructor with params
BitCoinExchange::BitCoinExchange(const std::string file)
{
	std::ifstream	infile(file);
	if (!infile.good())
	{
		std::cerr << RED << "ERROR: Could not open file." << RESET << std::endl;
	}
	int index = 0;
	for (std::string line; getline(infile, line);)
	{
		std::size_t comma = line.find(',');
		if (comma != std::string::npos)
			createMap(line, comma);
		index++;
	}
	std::cout << index << std::endl;
	if (_bitcoins.empty())
	{
		infile.close();
		std::cerr << RED << "ERROR: Empty CSV." << RESET << std::endl;
	}
	//printMap();
	//std::cout << _bitcoins.size() << std::endl;
	infile.close();
}

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

//TIPS:
//Year is leap year if % 4
//If also %100 and %400 Leap year
//If only %100 not leap year
bool	isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return (true);
			else
				return (false);
		}
		else
			return (true);
	}
	else
		return (false);
}

int	is30or31(int year, int month)
{
	if (month == 2)
		return (isLeapYear(year) ? 29 : 28);
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		return (30);
	else
		return (31);
}

int	BitCoinExchange::checkDate(const std::string &key)
{
	struct tm tm;
	if (strptime(key.c_str(), "%Y-%m-%d", &tm))
	{
		int year = tm.tm_year + 1900;
		if (year < 1900 | year > 2024)
		{
			std::cout << RED << "ERROR: bad input => " << key << RESET << std::endl;
			return (-1);
		}
		int month = tm.tm_mon + 1;
		if (month < 1 || month > 12)
		{
			std::cout << RED << "ERROR: bad input =>" << key << RESET << std::endl;
			return (-1);
		}
		int day = tm.tm_mday;
		int maxDays = is30or31(year, month);
		if (day < 1 || day > maxDays)
		{
			std::cout << RED << "ERROR: bad input => " << key << RESET << std::endl;
			return (-1);
		}
		return (0);
	}
	else
	{
		std::cout << RED << "ERROR : bad input => " << key << RESET << std::endl;
		return (-1);
	}
	return (-1);
}

void	BitCoinExchange::createMap(std::string line, std::size_t symbol)
{
	std::string key = line.substr(0, symbol);
	std::string value = line.substr(symbol + 1);

	checkDate(key);
	checkDigit
	std::istringstream iss(value);
	float newVal;
	if (!(iss >> newVal) || key == "date")
	{
		std::cerr << RED << "ERROR: bad input => " << newVal << RESET << std::endl;
		return ;
	}

	if (!_bitcoins.insert(std::make_pair(key, newVal)).second)
	{
		std::cout << RED << "ERROR: Missing a key or a value" << RESET << std::endl;
		std::cout << key << ", " << newVal << std::endl;
	}
	else
	{
		std::cout << GREEN << "SUCCESS: successful pairing" << RESET << std::endl;
		std::cout << key << ", " << value << std::endl;
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

int	BitCoinExchange::checkBtc(std::map<std::string, float> BitCoinLine)
{
	(void)BitCoinLine;
	return (0);
}

void		BitCoinExchange::printMap(void)
{
	std::cout << "PRINTING MAP X DEBUG" << std::endl;
	for (std::map<std::string, float>::iterator iter = _bitcoins.begin(); iter != _bitcoins.end(); iter++)
	{
			std::cout << iter->first << " -> " << iter->second << std::endl;
	}
}
