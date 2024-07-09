/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:46:26 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/09 16:43:28 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BitCoinExchange_HPP
# define BitCoinExchange_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <map>

#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[38;5;208m"
#define RED "\x1b[31m"
#define PURPLE "\x1b[35m"

class BitCoinExchange
{
	private:
	    	// Private members

	public:
    		// Constructor
    		BitCoinExchange();

    		// Destructor
    		~BitCoinExchange();

    		// Copy Constructor
    		BitCoinExchange(const BitCoinExchange& copy);

    		// Copy Assignment Operator
    		BitCoinExchange& operator=(const BitCoinExchange& copy);
};

#endif /* BitCoinExchange_HPP */
