/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 13:24:11 by dsousa            #+#    #+#             */
/*   Updated: 2015/01/22 18:28:39 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Triangle.hpp"

Triangle::Triangle( void ) : _shader( new Shader("Basic") )
{
	const float vertexPositions[] = {
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.0f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f,
		1.0f, 0.0, 0.0f, 1.0f,
		0.0, 1.0f, 0.0f, 1.0f,
		0.0, 0.0f, 1.0f, 1.0f
	};

	glGenBuffers( 1, &this->_positionBuff );

	glBindBuffer( GL_ARRAY_BUFFER, this->_positionBuff );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertexPositions ), vertexPositions, GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	return ;
}

Triangle::Triangle( Triangle const & src )
{
	*this = src;
}

Triangle::~Triangle( void )
{
	if ( this->_shader )
		delete this->_shader;
	return ;
}

Triangle &			Triangle::operator=( Triangle const & rhs )
{
	this->_positionBuff = rhs._positionBuff;

	return ( *this );
}

void				Triangle::update( void )
{

}

void				Triangle::render( Core const & core )
{
	(void)core;
	this->_shader->bind();
	glBindBuffer( GL_ARRAY_BUFFER, this->_positionBuff );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );

	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, 0 );
	glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, (void *)(12 * sizeof(float)) );

	this->_shader->updateUniform( "projection", core.getCamera().getViewProjection() );
	this->_shader->updateUniform( "modelview", this->getTransform()->getTransformation() );

	glDrawArrays( GL_TRIANGLES, 0, 3 );

	glDisableVertexAttribArray( 0 );
	glUseProgram( 0 );
}