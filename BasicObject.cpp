/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BasicObject.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/24 16:31:09 by rbenjami          #+#    #+#             */
/*   Updated: 2015/01/26 10:52:31 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BasicObject.hpp"

BasicObject::BasicObject() :
	_mesh( 0 ),
	_shader( new Shader("Basic") )
{
	return ;
}

BasicObject::BasicObject( BasicObject const & src )
{
	*this= src;
}

BasicObject::~BasicObject( void )
{
	return ;
}

BasicObject &	BasicObject::operator=( BasicObject const & rhs )
{
	if ( this != &rhs )
	{

	}
	return ( *this );
}

void			BasicObject::update( void )
{

}

void			BasicObject::render( Core const & core )
{
	if ( this->_mesh )
		this->_mesh->render( core, * this->_shader, * getTransform() );
}

// SETTER
void			BasicObject::setMesh( Mesh * mesh )
{
	this->_mesh = mesh;
}
