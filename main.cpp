#include <iostream>
#include "neuron.cpp"
#include "network.cpp"


int main()
{
	Neuron n1(1);
	Neuron n2(2);
	Network net;
	
	net.addNeuron(&n1);
	net.addNeuron(&n2);
	net.addTarget(1, &n2);
	net.update(0.0, 200, 1.1);
	
	
return 0;
}

