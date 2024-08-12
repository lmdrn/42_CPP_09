/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:59:32 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/12 17:24:19 by lmedrano         ###   ########.fr       */
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

	std::cout << GREEN << "XX-------------------TEST WIH A VECTOR------------------XX" << RESET << std::endl;
	PmergeMe pm(ac, av);

	struct timeval start, end;
	
	gettimeofday(&start, NULL);

	pm.parsing(ac, av);
	std::cout << std::endl;
	pm.printContainer(pm.getSequence());

	pm.divideIntoPairs();
	pm.insertSortedMinMax();
	pm.insertMinInMaxArray();
	pm.maxArray();
	pm.minArray();
	pm.clearInitialVector();
	pm.groupMinArray();
	pm.processGroups();

	gettimeofday(&end, NULL);
	std::cout << std::endl;
	pm.printElapsedTime(start, end);
	std::cout << std::endl;
	
	std::cout << GREEN << "XX-------------------TEST WIH A LIST ------------------XX" << RESET << std::endl;
	return (0);
}
