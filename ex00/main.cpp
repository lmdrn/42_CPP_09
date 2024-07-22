/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:44:37 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/22 14:40:23 by lmedrano         ###   ########.fr       */
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
		BitCoinExchange	exchangeRates("data.csv");
		BitCoinExchange	retValues("input.txt");
		//BitCoinExchange::checkDate(bitcoinline);
		//BitCoinExchange::checkBtc(bitcoinline);
	}
	return (0);
}
