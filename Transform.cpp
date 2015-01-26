/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 17:34:49 by rbenjami          #+#    #+#             */
/*   Updated: 2015/01/25 16:35:31 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Transform.hpp"

Transform::Transform() :
	_pos( 0, 0, 0 ),
	_rot( 0, 0, 0, 1 ),
	_scale( 1, 1, 1 ),
	_parent( 0 ),
	_parentMatrix( Matrix4f().initIdentity() ),
	_isInitialized( false )
{
	return ;
}

Transform::Transform( Vector3f const & pos, Quaternion4f const & rot, Vector3f const & scale ) :
	_pos( pos ),
	_rot( rot ),
	_scale( scale ),
	_parent( 0 ),
	_parentMatrix( Matrix4f().initIdentity() ),
	_isInitialized( false )
{
	return ;
}

Transform::Transform( Transform const & src )
{
	*this = src;
}

Transform::~Transform( void )
{
	return ;
}

Transform &	Transform::operator=( Transform const & rhs )
{
	if ( this != &rhs )
	{
		this->_parent = & rhs.getParent();
		this->_parentMatrix = rhs._parentMatrix;
		this->_pos = rhs.getPos();
		this->_rot = rhs.getRot();
		this->_scale = rhs.getScale();
		this->_oldPos = rhs._oldPos;
		this->_oldRot = rhs._oldRot;
		this->_oldScale = rhs._oldScale;
	}
	return ( *this );
}

void					Transform::update()
{
	if ( this->_isInitialized )
	{
		this->_oldPos = this->_pos;
		this->_oldRot = this->_rot;
		this->_oldScale = this->_scale;
	}
	else
	{
		this->_oldPos = Vector3f( this->_pos ) + Vector3f( 1, 1, 1 );
		this->_oldRot = Quaternion4f( this->_rot ) * 0.5f;
		this->_oldScale = Vector3f( this->_scale ) + Vector3f( 1, 1, 1 );
		this->_isInitialized = true;
	}
	if ( this->_parent != 0 && this->_parent->hasChanged() )
		this->_parentMatrix = this->_parent->getTransformation();
}

bool					Transform::hasChanged() const
{
	if ( this->_parent != 0 && this->_parent->hasChanged() )
		return ( true );
	return ( this->_pos != this->_oldPos || this->_rot != this->_oldRot || this->_scale != this->_oldScale );
}

void					Transform::translate( float x, float y, float z )
{
	this->_pos = this->_pos + Vector3f( x, y, z );
}

void					Transform::translate( Vector3f const & vec )
{
	this->_pos = this->_pos + vec;
}

void					Transform::rotate( Vector3f const & axis, float angle )
{
	this->_rot = ( ( Quaternion4f( axis, angle ) * this->_rot ).normalized() );
}

void					Transform::rotate( Quaternion4f const & rotation )
{
	this->_rot = Quaternion4f( ( rotation * this->_rot ).normalized() );
}

void					Transform::lookAt( Vector3f const & point, Vector3f up )
{
	this->_rot = this->getLookAtRotation( point, up );
}

Quaternion4f			Transform::getLookAtRotation( Vector3f const & point, Vector3f const & up )
{
	return ( Quaternion4f( Matrix4f().initRotation( ( point - this->_pos ).normalized(), up ) ) );
}

Matrix4f				Transform::getTransformation() const
{
	Matrix4f	translationMatrix;
	Matrix4f	scaleMatrix;

	translationMatrix.initTranslation( this->_pos );
	scaleMatrix.initScale( this->_scale );
	return ( this->getParentMatrix() * translationMatrix * this->_rot.toRotationMatrix() * scaleMatrix );
}

Vector3f				Transform::getTransformedPos() const
{
	return ( Vector3f( this->getParentMatrix().transform( this->_pos ) ) );
}

Quaternion4f			Transform::getTransformedRot() const
{
	Quaternion4f	parentRot;

	if ( this->_parent != 0 )
		parentRot = this->_parent->getTransformedRot();
	return ( parentRot * this->_rot );
}

// GETTER
Transform &				Transform::getParent() const
{
	return ( * this->_parent );
}

Matrix4f				Transform::getParentMatrix() const
{
	return ( this->_parentMatrix );
}

Vector3f				Transform::getPos() const
{
	return ( this->_pos );
}

Quaternion4f			Transform::getRot() const
{
	return ( this->_rot );
}

Vector3f				Transform::getScale() const
{
	return ( this->_scale );
}

// SETTER
void					Transform::setPos( Vector3f const & pos )
{
	this->_pos = pos;
}

void					Transform::setRot( Quaternion4f const & rot )
{
	this->_rot = rot;
}

void					Transform::setScale( Vector3f const & scale )
{
	this->_scale = scale;
}

