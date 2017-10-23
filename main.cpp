#include <iostream>
#include "neuron.hpp"
#include "network.hpp"


int main()
{
	Network net;

	net.net_set_i_ext(1.01);

	net.update(1000);
	
return 0;
}


	
