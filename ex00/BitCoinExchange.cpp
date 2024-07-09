/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitCoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmedrano <lmedrano@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:46:33 by lmedrano          #+#    #+#             */
/*   Updated: 2024/07/09 15:49:23 by lmedrano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitCoinExchange.hpp"

// Constructor
BitCoinExchange::BitCoinExchange()
{}

// Destructor
BitCoinExchange::~BitCoinExchange()
{}

// Copy Constructor
BitCoinExchange::BitCoinExchange(const BitCoinExchange& copy)
{
	*this = copy;
}

// Copy Assignment Operator
BitCoinExchange& BitCoinExchange::operator=(const BitCoinExchange& copy)
{
	if (this != &copy)
	{}
	return (*this);
}

