#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include "neuron.hpp"


//Pas de ptr const car on doit les modifier
//Pour l'instant array avec taille fixe pour eviter segfault mais apres vector
//typedef std::vector<std::vector<Neuron*>> Synapses;
typedef std::array<std::array<Neuron*, 1>, 2> Synapses;

class Network
{
private:
	std::vector<Neuron*> neurons_;
	Synapses synapses_post_;	
	
public:
	
	Neuron getNeuron(int index) const;
	void addTarget(int i, Neuron* cible);  
	void addNeuron(Neuron* neuron);
	
	void update(Time start_time, int simulation_steps, double courant_ext);
	void reset();
	
	Network();
	~Network();

};






#endif
