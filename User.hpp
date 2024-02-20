/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-hach <zel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:12:24 by zel-hach          #+#    #+#             */
/*   Updated: 2023/08/09 12:20:28 by ssadiki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>

class User
{
private:
	std::string 	user;
	std::string 	mode;
	std::string 	unused;
	std::string 	realname;
public:
	User();
	~User();
	void 			setUser(const std::string );
	void 			setMode(const std::string );
	void 			setUnused(const std::string );
	void 			setRealname(const std::string );
	std::string 	&getUser(void);
	std::string 	&getMode(void);
	std::string 	&getUnused(void);
	std::string 	&getRealname(void);
};

#endif
