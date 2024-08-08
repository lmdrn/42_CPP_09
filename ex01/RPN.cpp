/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:55:24 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/08 11:42:35 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{
	std::cout << GREEN << "XX __ RPN CREATED __ XX" << RESET << std::endl;
}

RPN::~RPN()
{
	std::cout << RED << "XX __ RPN DESTROYED __ XX" << RESET << std::endl;
}

RPN::RPN(const RPN& copy)
{
	*this = copy;
}

RPN& RPN::operator=(const RPN& copy)
{
	if (this != &copy)
	{}
	return (*this);
}

bool	isToken(std::string arg)
{
	if (arg == "+" || arg == "-" || arg == "*" || arg == "/")
		return (true);
	return (false);
}

void	RPN::calculate(std::string args)
{
	std::istringstream iss(args);
	std::string parsed;
	std::stack<int> polishOp;

	while (iss >> parsed)
	{
		if (isToken(parsed) == true || (parsed.size() == 1 && std::isdigit(parsed[0])))
		{
			if (std::isdigit(parsed[0]))
			{
				int nbr = std::atoi(parsed.c_str());
				if (nbr > 9)
				{
					std::cerr << RED << "ERROR: Number should be smaller than 10" << RESET << std::endl;
					return ;
				}
				polishOp.push(nbr);
			}
			else
			{		
				if (polishOp.size() < 2)
				{
					std::cerr << RED << "ERROR: Need at least two numbers to calculate" << RESET << std::endl;
					return ;
				}
				int	nbr2 = polishOp.top();
				polishOp.pop();
				int	nbr1 = polishOp.top();
				polishOp.pop();

				int ret;
				if (parsed == "+")
					ret = nbr1 + nbr2;
				else if (parsed == "-")
					ret = nbr1 - nbr2;
				else if (parsed == "*")
					ret = nbr1 * nbr2;
				else if (parsed == "/")
				{
					if (nbr2 == 0)
					{
						std::cerr << RED << "ERROR: Cannot divide by zero" << RESET << std::endl;
						return ;
					}
					ret = nbr1 / nbr2;
				}
				polishOp.push(ret);
			}
		}
		else
		{
			std::cerr << RED << "ERROR: N'est ni un chiffre, ni un operator" << RESET << std::endl;
			return ;
		}
	}
	if (polishOp.size() == 1)
	{
		std::cout << GREEN << polishOp.top() << RESET << std::endl;
	}
	else
	{
		std::cerr << RED << "ERROR: Calculation went wrong. More than one result remaining" << RESET << std::endl;
		return ;
	}
}
