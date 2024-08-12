/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:59:32 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/12 11:45:30 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << RED << "WRONG USAGE: ./PmergeMe <insert positive sequence int>" << RESET << std::endl;
		return (-1);
	}
	PmergeMe pm(ac, av);
	return (0);
}
