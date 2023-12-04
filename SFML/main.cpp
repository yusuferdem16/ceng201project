#include <iostream>
#include "Window.h"
#include "Level1.h"

int main(){
	Level1 l1;
	Window w(l1);
	w.run();
	
	return 0;
}