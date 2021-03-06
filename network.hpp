#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include "neuron.hpp"
#include <cassert>
#include <random>
#include <deque>
#include <fstream>

/**
 * This class simulates en entire network of connected neurons
 */
class Network
{
private:
	std::array<Neuron*, nb_neurons> neurons_; 		   ///< list of all the neurons constituting the network
	std::array<std::deque<size_t>, nb_neurons> synapses_post_; ///< Two dimension table that stores the index of all the connections between neurons, one line correspond to the connections of one neuron
	
	/**
	 * initialize the connection matrix using a 10% probability of creating
	 * a connection between any two neurons in the network
	 */	
	void create_connections();
	
	 /**
	 * liberates all the memory allocated manually to attributes that are pointers and need to be freed
	 * also initializes the connection matrix to all 0 values
	 */
	 void reset();
	
	 
public:
		
	/**
	 * gives access to a single neuron at position index
	 * @param index: index of the neuron's place in the vector
	 * @return accessed neuron
	 */	
	Neuron getNeuron(unsigned int index) const;

	/**
	 * set the value of the external current for all the neurons in the network
	 * @param i_ext: value of external current
	 */						
	void net_set_i_ext(double i_ext);
	
	/**
	 * returns the indexes of all the neurons connected to the neuron of index "indiceNeuron"
	 * @param indiceNeuron: index of the neuron from which we want to get the connections
	 */
	std::deque<size_t> getConnections(unsigned int indiceNeuron) const;
	
	/**
	 * Adds a connection between two neurons, used only for testing
	 * @param indiceN1: index of the neuron receving the input
	 * @param indiceN2: index of the neuron giving the output
	 */
	void addConnection(unsigned int indiceN1, unsigned int indiceN2);
	
	/**
	 * calculates the average firing for the whole network per neuron per second
	 * @param total_steps: total number of steps that we ran in the simulation
	 * @return firing rate per neuron per second
	 */
	double calculateFiringRatePerSecond(unsigned int total_steps) const;
	
	/**
	 * updates all the neurons in the network using their own update function
	 * also take care of EPSPs of connected neurons
	 * @param simulation_steps: number of times we want to run the simulation
	 */
	void update(int simulation_steps);
	
	/**
	 * default constructor of Network
	 */
	Network();
	
	/**
	 * Destructor
	 */ 
	~Network();
	

};






#endif
