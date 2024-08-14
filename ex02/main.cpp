/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:59:32 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/14 08:22:01 by lmedrano         ###   ########.fr       */
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

	struct timeval start, end;
	
	gettimeofday(&start, NULL);

	PmergeMe pm(ac, av);
	std::vector<int> sequence;

	pm.parsing(ac, av, sequence);

	std::cout << std::endl;
	pm.printContainer(sequence);

	pm.divideIntoPairsVec(sequence);
	pm.insertSortedMinMaxVec();
	pm.CreateVec();
	pm.clearInitialVector(sequence);
	pm.processGroupsVec();

	gettimeofday(&end, NULL);
	std::cout << std::endl;
	pm.printElapsedTime(start, end);
	std::cout << std::endl;
	
	std::cout << GREEN << "XX-------------------TEST WIH A LIST ------------------XX" << RESET << std::endl;

	struct timeval start2, end2;
	
	gettimeofday(&start2, NULL);

	PmergeMe pm2(ac, av);
	std::list<int> seqList;

	pm2.parsing(ac, av, seqList);

	std::cout << std::endl;
	pm2.printContainer(seqList);

	pm2.divideIntoPairsList(seqList);
	pm2.insertSortedMinMaxList();
	pm2.CreateList();
	pm2.clearInitialVector(seqList);
	pm2.processGroupsList();

	gettimeofday(&end2, NULL);
	std::cout << std::endl;
	pm2.printElapsedTime(start2, end2);
	std::cout << std::endl;

	return (0);
}
