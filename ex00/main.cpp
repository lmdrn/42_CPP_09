/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:44:37 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/09 16:47:40 by lmedrano         ###   ########.fr       */
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
		// Create container map
		std::multimap<std::string, std::string> bitCoinLine;
		// Check file line by line
		std::ifstream input(av[1]);
		for (std::string line; getline(input, line);)
		{
			line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
			std::cout << PURPLE << line << RESET << std::endl;
			std::size_t pipePos = line.find('|');
			if (pipePos != std::string::npos)
			{
				std::string key = line.substr(0, pipePos);
				std::string value = line.substr(pipePos + 1);
				bitCoinLine.insert(std::make_pair(key,value));
			}
			else
			{
				//throw error?
				std::cerr << RED << "ERROR: No pipe!" << RESET << std::endl;
			}
		}
		std::cout << GREEN << "PRINTING MAP CONTAINER" << RESET << std::endl;
		for (std::multimap<std::string, std::string>::iterator iter = bitCoinLine.begin(); iter != bitCoinLine.end(); iter++)
		{
			std::cout << iter->first << " -> " << iter->second << std::endl;
		}
		input.close();
		//MY FILE
		//store date(key) + bitcoin(value) value in <map>
		//check date
		//check bitcoin
		//SAME FOR FILE FROM SUBJECT
		//if dte OK but exist in SUBJECT FILE BUT NOT MINE
		//USE PREVIOUS CLOSEST DATE
		//Then compare both keys and multiply value x exchange rate
	}
	return (0);
}
