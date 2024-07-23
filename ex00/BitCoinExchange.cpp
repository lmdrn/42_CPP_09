/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:46:33 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/23 12:22:29 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

// Constructor with params
BitCoinExchange::BitCoinExchange(const std::string file)
{
	std::ifstream	infile(file);
	if (!infile.is_open())
	{
		std::cerr << RED << "ERROR: Could not open file." << RESET << std::endl;
	}
	for (std::string line; getline(infile, line);)
	{
		std::size_t comma = line.find(',');
		if (comma != std::string::npos)
			createMap(line, comma);
	}
	if (_bitcoins.empty())
	{
		infile.close();
		std::cerr << RED << "ERROR: Empty CSV." << RESET << std::endl;
	}
	//printMap();
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
			std::cerr << RED << "ERROR: bad input => " << key << RESET << std::endl;
			return (-1);
		}
		int month = tm.tm_mon + 1;
		if (month < 1 || month > 12)
		{
			std::cerr << RED << "ERROR: bad input =>" << key << RESET << std::endl;
			return (-1);
		}
		int day = tm.tm_mday;
		int maxDays = is30or31(year, month);
		if (day < 1 || day > maxDays)
		{
			std::cerr << RED << "ERROR: bad input => " << key << RESET << std::endl;
			return (-1);
		}
		return (0);
	}
	else
	{
		std::cerr << RED << "ERROR : bad input => " << key << RESET << std::endl;
		return (-1);
	}
	return (0);
}

int	BitCoinExchange::checkDigit(const std::string& value)
{
	if (value.empty())
		return (-1);
	float	newVal = std::atof(value.c_str());
	if (newVal < 0)
	{
		std::cerr << RED << "ERROR: not a postive number." << RESET << std::endl;
		return (-1);
	}
	if (newVal > 1000)
	{
		std::cerr << RED << "ERROR: too large a number." << RESET << std::endl;
		return (-1);
	}
	return (0);
}

void	BitCoinExchange::createMap(std::string line, std::size_t symbol)
{
	std::string key = line.substr(0, symbol);
	std::string value = line.substr(symbol + 1);

	if (line == "date,exchange_rate")
	{
		return ;
	}
	std::istringstream iss(value);
	float newVal;
	if (!(iss >> newVal) || key == "date")
	{
		std::cerr << RED << "ERROR: bad input => " << newVal << RESET << std::endl;
		return ;
	}

	if (!_bitcoins.insert(std::make_pair(key, newVal)).second)
	{
		std::cout << RED << "ERROR: bad input => " << newVal << RESET << std::endl;
	}
	else
	{
			std::cout << GREEN << key << " => " << newVal << RESET << std::endl;
	}
}

float	BitCoinExchange::findCorrectDate(const std::string& date)
{
	std::map<std::string, float>::iterator iter = _bitcoins.find(date);

	if (iter == _bitcoins.end())
	{
		iter = _bitcoins.upper_bound(date);
		if (iter != _bitcoins.begin())
			iter--;
	}
	return (iter->second);
}

void	BitCoinExchange::exchangeBtc(const std::string& fileArg)
{
	std::ifstream	infile(fileArg);
	if (!infile.is_open())
	{
		infile.close();
		std::cerr << RED << "ERROR: Could not open file." << RESET << std::endl;
	}
	if (infile.peek() == std::ifstream::traits_type::eof())
	{
		infile.close();
		std::cerr << RED << "ERROR: Empty CSV." << RESET << std::endl;
	}
	for (std::string line; getline(infile, line);)
	{
		if (line == "date | value")
			continue ;
		std::size_t pipe = line.find('|');
		if (pipe != std::string::npos)
		{
			std::string key = line.substr(0, pipe);
			std::string value = line.substr(pipe + 1);
			if (checkDate(key) != -1 && checkDigit(value) != -1)
			{
				float	checkDate = findCorrectDate(key);	
				float	checkDigit = std::atof(value.c_str());	
				float	ret = checkDate * checkDigit;
				std::cout << GREEN << key << " => " << value << " = " << ret << RESET << std::endl;
			}
		}
		else
			std::cerr << RED << "ERROR: Bad format." << RESET << std::endl;
	}
	infile.close();
}
