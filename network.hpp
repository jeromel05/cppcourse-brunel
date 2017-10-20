#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include "neuron.hpp"
#include <cassert>


//Pas de ptr const car on doit les modifier

class Network
{
private:
	std::vector<Neuron*> neurons_;
	
public:
	
	Neuron getNeuron(int index) const;
	void addNeuron(Neuron* neuron);
	
	void update(int start_step, int simulation_steps, double courant_ext);
	void reset();
	
	Network();
	~Network();

};






#endif
