#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <array>
#include "neuron.hpp"
#include <cassert>
#include <random>

//-------CONSTANTS----------------------------------------------------//

constexpr int nb_excitateur(1000);										//number of excitatory neurons
constexpr int nb_inhibiteur(nb_excitateur / 4);							//number of inhibitory neurons
constexpr int nb_neurons(nb_excitateur + nb_inhibiteur);				//total number of neurons

typedef std::array<std::array<int, nb_neurons>, nb_neurons> Matrice;	


/**
 * This class simulates en entire network of connected neurons
 */
class Network
{
private:
	std::array<Neuron*, nb_neurons> neurons_; ///list of all the neurons constituting the network
	Matrice	connections_;	///Matrix storing all the connections between neurons (on met des int car on peut avoir 2 connections du meme neurone)
	
public:
	
	Neuron getNeuron(int index) const;
	/**
	 * gives access to a single neuron at position index
	 * @param index: index of the neuron's place in the vector
	 * @return accessed neuron
	 */							
	void addNeuron(Neuron* neuron);
	/**
	 * gives access to a single neuron at position index
	 * @param neuron: pointer on the neuron that we want to add
	 */	
	void net_set_i_ext(double i_ext);
	/**
	 * set the value of the external current for all the neurons in the network
	 * @param i_ext: value of external current
	 */	
	void affiche_connections() const;
	/**
	 * shows the matrix of all the neural connections
	 */	
	void create_connections();
	/**
	 * initialize the connection matrix using a 10% probability of creating
	 * a connection between any two neurons in the network
	 */	
	
	void update(int simulation_steps);
	/**
	 * updates all the neurons in the network using their own update function
	 * also take care of EPSPs of connected neurons
	 * @param simulation_steps: number of times we want to run the simulation
	 */
	void reset();
	/**
	 * liberates all the memory allocated manually to attributes that are pointers and need to be freed
	 * also initializes the connection matrix to all 0 values
	 */
	
	Network();
	/**
	 * default constructor of Network
	 */
	~Network();
	/**
	 * Destructor
	 */ 

};






#endif
