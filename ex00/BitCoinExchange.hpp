/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:46:26 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/23 11:49:29 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BitCoinExchange_HPP
# define BitCoinExchange_HPP

#include <string>
#include <map>
#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#define RESET "\x1b[0m"
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[38;5;208m"
#define RED "\x1b[31m"
#define PURPLE "\x1b[35m"

class BitCoinExchange
{
	private:
	    	// Private members
		std::map<std::string, float> _bitcoins;

	public:
    		// Constructor with file
    		BitCoinExchange(const std::string file);

    		// Destructor
    		~BitCoinExchange();

    		// Copy Constructor
    		BitCoinExchange(const BitCoinExchange& copy);

    		// Copy Assignment Operator
    		BitCoinExchange& operator=(const BitCoinExchange& copy);

		//METHODS
		int	checkDate(const std::string& key);
		int	checkDigit(const std::string& value);
		void	createMap(std::string line, std::size_t symbol);
};

#endif /* BitCoinExchange_HPP */
