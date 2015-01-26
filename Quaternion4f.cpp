/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quaternion4f.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 10:00:41 by rbenjami          #+#    #+#             */
/*   Updated: 2015/01/25 16:35:36 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Quaternion4f.hpp"

Quaternion4f::Quaternion4f() :
	_x( 0 ),
	_y( 0 ),
	_z( 0 ),
	_w( 1 )
{
	return ;
}

Quaternion4f::Quaternion4f( float x, float y, float z, float w ) :
	_x( x ),
	_y( y ),
	_z( z ),
	_w( w )
{
	return ;
}

Quaternion4f::Quaternion4f( Vector3f const & axis, float angle )
{
	float	sinHalfAngle = sin( angle / 2 );
	float	cosHalfAngle = cos( angle / 2 );

	this->_x = axis.getX() * sinHalfAngle;
	this->_y = axis.getY() * sinHalfAngle;
	this->_z = axis.getZ() * sinHalfAngle;
	this->_w = cosHalfAngle;
}

Quaternion4f::Quaternion4f( Matrix4f const & m )
{
	float	trace = m[0][0] + m[1][1] + m[2][2];
	if ( trace > 0 )
	{
		float	s = 0.5f / sqrtf( trace + 1.0f );
		this->_w = 0.25f / s;
		this->_x = ( m[1][2] - m[2][1] ) * s;
		this->_y = ( m[2][0] - m[0][2] ) * s;
		this->_z = ( m[0][1] - m[1][0] ) * s;
	}
	else if ( m[0][0] > m[1][1] && m[0][0] > m[2][2] )
	{
		float	s = 2.0f * sqrtf( 1.0f + m[0][0] - m[1][1] - m[2][2] );
		this->_w = ( m[1][2] - m[2][1] ) / s;
		this->_x = 0.25f * s;
		this->_y = ( m[1][0] + m[0][1] ) / s;
		this->_z = ( m[2][0] + m[0][2] ) / s;
	}
	else if ( m[1][1] > m[2][2] )
	{
		float	s = 2.0f * sqrtf( 1.0f + m[1][1] - m[0][0] - m[2][2] );
		this->_w = ( m[2][0] - m[0][2] ) / s;
		this->_x = ( m[1][0] + m[0][1] ) / s;
		this->_y = 0.25f * s;
		this->_z = ( m[2][1] + m[1][2] ) / s;
	}
	else
	{
		float	s = 2.0f * sqrtf( 1.0f + m[2][2] - m[1][1] - m[0][0] );
		this->_w = ( m[0][1] - m[1][0] ) / s;
		this->_x = ( m[2][0] + m[0][2] ) / s;
		this->_y = ( m[1][2] + m[2][1] ) / s;
		this->_z = 0.25f * s;
	}
	float	length = this->length();
	this->_w = this->_w / length;
	this->_x = this->_x / length;
	this->_y = this->_y / length;
	this->_z = this->_z / length;
}

Quaternion4f::Quaternion4f( Quaternion4f const & src )
{
	*this= src;
}

Quaternion4f::~Quaternion4f( void )
{
	return ;
}

Quaternion4f &		Quaternion4f::operator=( Quaternion4f const & rhs )
{
	if ( this != &rhs )
	{
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_z = rhs.getZ();
		this->_w = rhs.getW();
	}
	return ( *this );
}

float				Quaternion4f::length() const
{
	return ( (float) sqrt( this->_x * this->_x + this->_y * this->_y + this->_z * this->_z + this->_w * this->_w ) );
}

Quaternion4f		Quaternion4f::normalized() const
{
	float		length = this->length();
	return ( Quaternion4f( this->_x / length, this->_y / length, this->_z / length, this->_w / length ) );
}

Quaternion4f		Quaternion4f::conjugate() const
{
	return ( Quaternion4f( -this->_x, -this->_y, -this->_z, this->_w ) );
}

float				Quaternion4f::dot( Quaternion4f r ) const
{
	return ( this->_x * r.getX() + this->_y * r.getY() + this->_z * r.getZ() + this->_w * r.getW() );
}

Matrix4f			Quaternion4f::toRotationMatrix() const
{
	Vector3f	forward = Vector3f( 2.0f * ( getX() * getZ() - getW() * getY() ), 2.0f * ( getY() * getZ() + getW() * getX() ), 1.0f - 2.0f * ( getX() * getX() + getY() * getY() ) );
	Vector3f	up = Vector3f( 2.0f * ( getX() * getY() + getW() * getZ() ), 1.0f - 2.0f * ( getX() * getX() + getZ() * getZ() ), 2.0f * ( getY() * getZ() - getW() * getX() ) );
	Vector3f	right = Vector3f( 1.0f - 2.0f * ( getY() * getY() + getZ() * getZ() ), 2.0f * ( getX() * getY() - getW() * getZ() ), 2.0f * ( getX() * getZ() + getW() * getY() ) );

	return ( Matrix4f().initRotation( forward, up, right ) );
}

Vector3f			Quaternion4f::getForward() const
{
	return ( Vector3f( 0, 0, 1 ).rotate( *this ) );
}

Vector3f			Quaternion4f::getBack() const
{
	return ( Vector3f( 0, 0, -1 ).rotate( *this ) );
}

Vector3f			Quaternion4f::getUp() const
{
	return ( Vector3f( 0, 1, 0 ).rotate( *this ) );
}

Vector3f			Quaternion4f::getDown() const
{
	return ( Vector3f( 0, -1, 0 ).rotate( *this ) );
}

Vector3f			Quaternion4f::getRight() const
{
	return ( Vector3f( 1, 0, 0 ).rotate( *this ) );
}

Vector3f			Quaternion4f::getLeft() const
{
	return ( Vector3f( -1, 0, 0 ).rotate( *this ) );
}

Quaternion4f		Quaternion4f::operator+( Quaternion4f const & r ) const
{
	return ( Quaternion4f( this->_x + r.getX(), this->_y + r.getY(), this->_z + r.getZ(), this->_w + r.getW() ) );
}

Quaternion4f		Quaternion4f::operator-( Quaternion4f const & r ) const
{
	return ( Quaternion4f( this->_x - r.getX(), this->_y - r.getY(), this->_z - r.getZ(), this->_w - r.getW() ) );
}

Quaternion4f		Quaternion4f::operator*( float r ) const
{
	return ( Quaternion4f( this->_x * r, this->_y * r, this->_z * r, this->_w * r ) );
}

bool				Quaternion4f::operator==( Quaternion4f const & rhs ) const
{
	return ( *this == rhs || ( this->_x == rhs.getX() && this->_y == rhs.getY() && this->_z == rhs.getZ() && this->_w == rhs.getW() ) );
}

bool				Quaternion4f::operator!=( Quaternion4f const & rhs ) const
{
	return ( this->_x != rhs.getX() || this->_y != rhs.getY() || this->_z != rhs.getZ() || this->_w != rhs.getW() );
}

Quaternion4f		Quaternion4f::operator*( Quaternion4f r ) const
{
	float	w = ( getW() * r.getW() ) - ( getX() * r.getX() ) - ( getY() * r.getY() ) - ( getZ() * r.getZ() );
	float	x = ( getX() * r.getW() ) + ( getW() * r.getX() ) + ( getY() * r.getZ() ) - ( getZ() * r.getY() );
	float	y = ( getY() * r.getW() ) + ( getW() * r.getY() ) + ( getZ() * r.getX() ) - ( getX() * r.getZ() );
	float	z = ( getZ() * r.getW() ) + ( getW() * r.getZ() ) + ( getX() * r.getY() ) - ( getY() * r.getX() );
	return ( Quaternion4f( x, y, z, w ) );
}

Quaternion4f		Quaternion4f::operator*( Vector3f r ) const
{
	float	w = - ( getX() * r.getX() ) - ( getY() * r.getY() ) - ( getZ() * r.getZ() );
	float	x = ( getW() * r.getX() ) + ( getY() * r.getZ() ) - ( getZ() * r.getY() );
	float	y = ( getW() * r.getY() ) + ( getZ() * r.getX() ) - ( getX() * r.getZ() );
	float	z = ( getW() * r.getZ() ) + ( getX() * r.getY() ) - ( getY() * r.getX() );
	return ( Quaternion4f( x, y, z, w ) );
}

std::ostream &		operator<<( std::ostream & lhs, Quaternion4f const & q )
{
	return ( lhs << "Quaternion4f( x: " << q.getX() << ", y: " << q.getY() << ", z: " << q.getZ() << ", w: " << q.getW() << ")" );
}

// GETTER
float				Quaternion4f::getX() const
{
	return ( this->_x );
}

float				Quaternion4f::getY() const
{
	return ( this->_y );
}

float				Quaternion4f::getZ() const
{
	return ( this->_z );
}

float				Quaternion4f::getW() const
{
	return ( this->_w );
}

// SETTER
void				Quaternion4f::setX( float x )
{
	this->_x = x;
}

void				Quaternion4f::setY( float y )
{
	this->_y = y;
}

void				Quaternion4f::setZ( float z )
{
	this->_z = z;
}

void				Quaternion4f::setW( float w )
{
	this->_w = w;
}

