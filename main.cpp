#include <iostream>
#include "neuron.hpp"
#include "network.hpp"


int main()
{
	Neuron n1;
	Neuron n2;
	Network net;
	
	n1.addTarget(&n2);	
	
	net.addNeuron(&n1);
	net.addNeuron(&n2);
	net.update(0.0, 5000, 1.01);
	
	for(auto e: n1.getTimeSpikes())
	{
		std::cout << e << std::endl;
	}
	
return 0;
}


	
