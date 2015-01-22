/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 12:12:13 by dsousa            #+#    #+#             */
/*   Updated: 2015/01/21 18:53:49 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP
# include <OpenGL/gl.h>
# include "IObject.hpp"
# include "Shader.hpp"
# include "Core.hpp"

class Triangle : public IObject
{
	public:
		Triangle( void );
		Triangle( Triangle const & src );
		~Triangle( void );

		Triangle &			operator=( Triangle const & rhs );

		// GETTER
		Matrix4f			getTranform( void ) const;

		virtual void		update( void );
		virtual void		render( Core const & core ) const;

	private:
		GLuint				_positionBuff;
		Shader *			_shader;
};

#endif
