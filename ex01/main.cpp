/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:56:22 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/08 11:09:51 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main (int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << RED << "ERROR" << RESET << std::endl;
		std::cerr << RED << "Usage: ./RPN <Expression to calculate>" << RESET << std::endl;
		return (-1);
	}
	std::stack<std::string> polish;
	RPN::calculate(av[1]);
	return (0);
}
