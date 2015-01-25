/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 13:24:11 by dsousa            #+#    #+#             */
/*   Updated: 2015/01/24 18:34:17 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Triangle.hpp"

Triangle::Triangle( void ) : _shader( new Shader("Basic2") )
{
	this->_matrix = glm::mat4( 1 );

	const float		vertexBuffer[] = {
		-0.5f, -0.5f, -1.0f,
		1.0f, 0.0, 0.0f,
		0.0f, 1.0, 0.0f,
		0.0f, 0.5f, -1.0f,
		0.0, 1.0f, 0.0f,
		0.0f, 1.0, 0.0f,
		0.5f, -0.5f, -1.0f,
		0.0, 0.0f, 1.0f,
		0.0f, 1.0, 0.0f,
	};

	const int		indexBuffer[] = {
		0, 1, 2
	};

	glGenBuffers( 1, &this->_vbo );

	glBindBuffer( GL_ARRAY_BUFFER, this->_vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertexBuffer ), vertexBuffer, GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	glGenBuffers( 1, &this->_ibo );

	glBindBuffer( GL_ARRAY_BUFFER, this->_ibo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( indexBuffer ), indexBuffer, GL_STATIC_DRAW );
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
	this->_vbo = rhs._vbo;

	return ( *this );
}

void				Triangle::update( void )
{

}

void				Triangle::render( Core const & core )
{
	this->_shader->bind();
	glBindBuffer( GL_ARRAY_BUFFER, this->_vbo );
	glEnableVertexAttribArray( 0 );
	glEnableVertexAttribArray( 1 );
	glEnableVertexAttribArray( 2 );

# ifdef __APPLE__
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 9 * 4, 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_TRUE, 9 * 4, (void *)12 );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 9 * 4, (void *)24 );
# else
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 9 * 4, 0 );
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_TRUE, 9 * 4, (void *)12 );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 9 * 4, (void *)24 );
# endif

	glm::mat4	worldMatrix = glm::mat4( 1 );
	glm::mat4	projectionMatrix = core.getCamera().getViewProjection();

	this->_shader->updateUniform( "T_Model", worldMatrix );
	this->_shader->updateUniform( "T_Projection", projectionMatrix );

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->_ibo );
	glDrawElements( GL_TRIANGLES, 3 /* nb vertex */, GL_UNSIGNED_INT, 0 );

	glDisableVertexAttribArray( 0 );
	glDisableVertexAttribArray( 1 );
	glDisableVertexAttribArray( 2 );
	glUseProgram( 0 );
}
