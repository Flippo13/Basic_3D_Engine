#ifndef MYGAMEDEMO_HPP
#define MYGAMEDEMO_HPP

#include "mge/core/AbstractGame.hpp"

class DebugHud;

/**
 * An example subclass of AbstractGame showing how we can setup a scene.
 */
class MyGameDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MyGameDemo();
		virtual ~MyGameDemo();

        //override initialize so we can add a DebugHud
        virtual void initialize();

	protected:
	    //override so we can construct the actual scene
        virtual void _initializeScene();

	    //override render to render the hud as well.
	    virtual void _render();

	private:
		DebugHud* _hud;                   //hud display

        void _updateHud();

        MyGameDemo(const MyGameDemo&);
        MyGameDemo& operator=(const MyGameDemo&);
};

#endif // MGEDEMO_HPP
