#include <iostream>
#include "neuron.hpp"
#include "network.hpp"


int main()
{
	Network net;

	net.net_set_i_ext(1.1);
	

	net.update(500);
	
return 0;
}


	
