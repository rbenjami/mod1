/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod1.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenjami <rbenjami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/26 15:36:36 by rbenjami          #+#    #+#             */
/*   Updated: 2015/01/26 16:31:58 by rbenjami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include "Core.hpp"

int main(void)
{
	Core *	core = new Core();

	core->createWindow( 850, 550, "Test" );

	// START INIT

	Object *	o = new Object();

	core->addObject( o );

	// END INIT

	core->start();

	delete core;

	exit( EXIT_SUCCESS );
}
