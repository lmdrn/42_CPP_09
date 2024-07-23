/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:44:37 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/23 12:20:59 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		(void)av;
		std::cerr << RED << "ERROR: Could not open file." << RESET << std::endl;
		return (-1);
	}
	else
	{
		std::string infile = av[1];
		if (infile.substr(infile.find_last_of(".") + 1) != "txt")
			std::cout << RED << "ERROR: Wrong extension." << RESET << std::endl;
		BitCoinExchange	exchangeRates("data.csv");
		exchangeRates.exchangeBtc(av[1]);
	}
	return (0);
}
