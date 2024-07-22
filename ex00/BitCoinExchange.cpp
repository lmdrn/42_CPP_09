/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:46:33 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/22 15:15:55 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

// Constructor with params
BitCoinExchange::BitCoinExchange(const std::string file)
{
	std::ifstream	infile(file);
	if (!infile.good())
	{
		std::cerr << RED << "ERROR: Could not open file" << RESET << std::endl;
	}
	int index = 0;
	for (std::string line; getline(infile, line);)
	{
		std::size_t comma = line.find(',');
		if (comma != std::string::npos)
			createMap(line, comma);
		else
			std::cout << RED << "ERROR: Wrong format" << RESET << std::endl;
		index++;
	}
	std::cout << index << std::endl;
	if (_bitcoins.empty())
	{
		infile.close();
		std::cerr << RED << "ERROR: Empty CSV" << RESET << std::endl;
	}
	printMap();
	std::cout << _bitcoins.size() << std::endl;
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

void	BitCoinExchange::createMap(std::string line, std::size_t symbol)
{
	std::string key = line.substr(0, symbol);
	std::string value = line.substr(symbol + 1);

	std::istringstream iss(value);
	float newVal;
	if (!(iss >> newVal))
	{
		std::cerr << RED << "ERROR: not a float" << RESET << std::endl;
		return ;
	}

	if (!_bitcoins.insert(std::make_pair(key, newVal)).second && key != "date")
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

int	BitCoinExchange::checkDate(std::map<std::string, float> BitCoinLine)
{
	for (std::map<std::string, float>::iterator iter = BitCoinLine.begin(); iter != BitCoinLine.end(); iter++)
	{
		struct tm tm;
		if (strptime(iter->first.c_str(), "%Y-%m-%d", &tm))
		{
			std::cout << ORANGE << "Date is: " << iter->first << RESET << std::endl;
			std::cout << GREEN << "SUCCESS : Date valid " << RESET << std::endl;
			return (0);
		}
		else
		{
			std::cout << ORANGE << "Date is: " << iter->first << RESET << std::endl;
			std::cout << RED << "ERROR : Date unvalid " << RESET << std::endl;
			return (-1);
		}
	}
	return (-1);
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
