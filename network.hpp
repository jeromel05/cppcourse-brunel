#ifndef NETWORK_H
#define NETWORK_H

#include <iostream>
#include <vector>
#include <array>
#include "neuron.hpp"
#include <cassert>
#include <random>

//Pas de ptr const car on doit les modifier
constexpr int nb_excitateur(100);
constexpr int nb_inhibiteur(25);
constexpr int nb_neurons(nb_excitateur + nb_inhibiteur);
typedef std::array<std::array<int, nb_neurons>, nb_neurons> Matrice;


class Network
{
private:
	std::array<Neuron*, nb_neurons> neurons_;
	//std::vector<Neuron*> neurons_;
	Matrice	connections_;												//on met des int car on peut avoir 2 connections du meme neurone
	
public:
	
	Neuron getNeuron(int index) const;
	void addNeuron(Neuron* neuron);
	void net_set_i_ext(double i_ext);
	void affiche_connections() const;
	void create_connections();
	
	void update(int simulation_steps);
	void reset();
	
	Network();
	~Network();

};






#endif
