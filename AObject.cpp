/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AObject.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 16:33:59 by rbenjami          #+#    #+#             */
/*   Updated: 2015/01/22 17:46:47 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AObject.hpp"

glm::mat4 *		AObject::getMatrix()
{
	return ( & this->_matrix );
}
