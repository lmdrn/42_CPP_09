/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 09:56:43 by lmedrano          #+#    #+#             */
/*   Updated: 2024/08/08 10:59:26 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[38;5;208m"
#define RED "\x1b[31m"
#define PURPLE "\x1b[35m"

#include <string>
#include <iostream>
#include <stack>
#include <sstream>
#include <cstdlib>

class	RPN
{
	public:
    		// Constructor
    		RPN();

    		// Destructor
    		~RPN();

    		// Copy Constructor
    		RPN(const RPN& copy);

    		// Copy Assignment Operator
    		RPN& operator=(const RPN& copy);

		//METHODS
		static	void	calculate(std::string args);
};

#endif /* RPN_HPP */


