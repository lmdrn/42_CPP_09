/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:35 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/09 14:22:45 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

//TODO FORD-JOHNSON
//1. J'ai un tableau unsorted de numeros
//
//|| Z0 | Z1 | Z2 | Z3 | Z4 | Z5 ||
//
//2. je divise ce tableau en pairs toujours unsorted
//
//|| Z0,Z1 | Z2,Z3 | Z4,Z5 ||
//
//3. Je cherche le min et le max de chaque pair
//X1 = min(Z0,Z1) et Y1 = max(Z0,Z1)
//
//|| X1,Y1 | X2,Y2 | X3,Y3 | X4,Y4 | X5,Y5 ||
//
//4. Je dois m'assurer que Yi >= Xi ET QUE Yi <= Yi+1
//Donc je sorte les Yi et je peux mettre Xi en 1st parce que je sais qu'il est toujours plus petit que Yi.
//
//|| X1 | Y1 | Y2 | Y3 | Y4 | Y5 || <!!SORTED!!>>
//5. I apply FORD-JOHNSON by doing a binary search on my sorted array
//To do so, I Take my remaining Xi and divide them into groups following puissance de 2
//(2,4,8,16,32,64,.....)
//So my first group should be composed of 2 elements
//Then my second group should be == to the next puissance de 2, by additioning the previous group.
//Previous group is 2. Next puissance de 2 is 4. 4 - 2 = 2. The next group should be two elements.
//Next group: Prev group is 2. Next puissance is 8. 8 - 2 = 6. Next group is made of 6 elements.
//|| X2,X3 | X4,X5 | X6,X7,X8,X9,X10,X11 | .... || example of groups by power of 2 
//Then I should take each group, starting from the end and insert each Xi doing a binary search.
//So 1st I take X3, look for the middle of the Yi array. If it's in the 1st half, I cut the 1st half in 2 again and look for the number, etc..
//Until the array is sorted.

// ERROR MANAGEMENT
// Gerer les doublons
// Gerer les overflows (int_min/int_max)
// Test avec 3000 int
//

PmergeMe::PmergeMe()
{
	std::cout << GREEN << "XX __ PmergeMe CREATED __ XX" << RESET << std::endl;
}

PmergeMe::~PmergeMe()
{
	std::cout << RED << "XX __ PmergeMe DESTROYED __ XX" << RESET << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	*this = copy;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& copy)
{
	if (this != &copy)
	{}
	return (*this);
}
