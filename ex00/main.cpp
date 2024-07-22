/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:44:37 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/10 12:48:42 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		(void)av;
		std::cerr << RED << "Oops... you forgot the file" << RESET << std::endl;
		return (-1);
	}
	else
	{
		std::string infile = av[1];
		std::cout << infile << std::endl;
		if (infile.substr(infile.find_last_of(".") + 1) == "txt")
			std::cout << GREEN << "SUCCESS! Correct Extension" << RESET << std::endl;
		else
			std::cout << RED << "ERROR: Wrong extension" << RESET << std::endl;
		// create container map
		std::multimap<std::string, std::string> bitcoinline;
		// check file line by line
		std::ifstream input(av[1]);
		for (std::string line; getline(input, line);)
		{
			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
			std::cout << PURPLE << line << RESET << std::endl;
			std::size_t pipepos = line.find('|');
			if (pipepos != std::string::npos)
			{
				std::string key = line.substr(0, pipepos);
				std::string value = line.substr(pipepos + 1);
				if (bitcoinline.insert(std::make_pair(key,value)) == bitcoinline.end())
					std::cout << RED << "format error: missing a key or a value" << RESET << std::endl;
				else
					std::cout << GREEN << "successful pairing" << RESET << std::endl;
			}
			else
			std::cout << RED << "format error: missing a key or a value" << RESET << std::endl;
		}
		std::cout << GREEN << "printing map container" << RESET << std::endl;
		if (bitcoinline.empty())
			std::cerr << RED << "error: multimap is empty!" << RESET << std::endl;
		for (std::multimap<std::string, std::string>::iterator iter = bitcoinline.begin(); iter != bitcoinline.end(); iter++)
		{
				std::cout << iter->first << " -> " << iter->second << std::endl;
		}
		BitCoinExchange::checkDate(bitcoinline);
		BitCoinExchange::checkBtc(bitcoinline);
		
		input.close();
		// create container map
		std::multimap<std::string, std::string> exchangeline;
		// check file line by line
		std::ifstream input2("data.csv");
		for (std::string line2; getline(input2, line2);)
		{
			line2.erase(std::remove(line2.begin(), line2.end(), ' '), line2.end());
			//std::cout << PURPLE << line2 << RESET << std::endl;
			std::size_t pipepos = line2.find(',');
			if (pipepos != std::string::npos)
			{
				std::string key = line2.substr(0, pipepos);
				std::string value = line2.substr(pipepos + 1);
				if (exchangeline.insert(std::make_pair(key,value)) == exchangeline.end())
				{
					//std::cout << RED << "format error: missing a key or a value" << RESET << std::endl;
				}
				else
				{
					//std::cout << GREEN << "successful pairing" << RESET << std::endl;
				}
			}
			else
			{
				//std::cout << RED << "format error: missing a key or a value" << RESET << std::endl;
			}
		}
		std::cout << GREEN << "printing map container" << RESET << std::endl;
		if (exchangeline.empty())
			std::cerr << RED << "error: multimap is empty!" << RESET << std::endl;
		for (std::multimap<std::string, std::string>::iterator iter = exchangeline.begin(); iter != exchangeline.end(); iter++)
		{
			//	std::cout << iter->first << " -> " << iter->second << std::endl;
		}
		//BitCoinExchange::checkDate(exchangeline);
		//BitCoinExchange::checkBtc(exchangeline);
		input2.close();
		BitCoinExchange::exchangeBtc(bitcoinline, exchangeline);
	}
	return (0);
}
