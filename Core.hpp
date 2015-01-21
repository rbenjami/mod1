/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Core.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsousa <dsousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 10:17:54 by dsousa            #+#    #+#             */
/*   Updated: 2015/01/21 11:55:55 by dsousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_HPP
# define CORE_HPP
# include <iostream>
# include <SDL2/SDL.h>
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <vector>
# include "Window.hpp"
# include "Error.hpp"
# include "IObject.hpp"

class Core
{
	public:
		Core( void );
		Core( Core const & src );
		~Core( void );

		Core &					operator=( Core const & rhs );

		Window *				getWindow( void ) const;
		void					createWindow( std::string title, size_t width, size_t height );
		void					start( void );
		void					addObject( IObject * obj );

	private:
		Window *				_win;
		bool					_started;
		std::vector<IObject *>	_obj;

		bool					catchEvent( void ) const;
		void					updateAll( void );
		void					renderAll( void ) const;
};

#endif

