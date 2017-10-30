#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include <cassert>
#include <random>

typedef double Time;

//-------CONSTANTS----------------------------------------------------//
constexpr Time h(0.1);													//smallest time unit available is 1ms
constexpr double threshold_potential(20.0);								//potential above which the neuron spikes [mV]
constexpr Time tau(20.0);
constexpr Time refractory_period(0.2);
constexpr double resting_potential(0.0);								//doit etre a 0.0 car la formule le fait revenir à cette valeur, shift tout de +0.070
constexpr double C(1.0);												//capacitance = [picoFarad]
constexpr double R(tau / C);											//membrane_resistance

constexpr int g(5);														//g = (J_I/J_E)
constexpr int C_E(1000);												//C_E = 0.1 * nb_excitateur
constexpr int C_I(C_E / 4);
constexpr double J_E(0.1);												//J_E = EPSP Amplitude [mV]
constexpr double J_I(- g * J_E);										//J_I = IPSP Amplitude [mV]
constexpr int D(15); 													//D = Delay (travel time of spike in axon) [steps]

const double c1(std::exp(-h / tau)); 									 //2 constantes initialisées dns le constructeur
const double c2(1 - std::exp(-h / tau));

constexpr double nu_thr(threshold_potential / (C_E * J_E * tau));		//frequence [Hz]
constexpr double nu_ext(2 * nu_thr);									//frequence ext [Hz]

typedef std::array<double, D + 1> Buffer;

/**
 * This class represents a single Neuron
 */

class Neuron
{
private:
	double membrane_potential_;											//Neuron Membrane potential
	double i_ext_;														//external current
	std::vector<Time> spike_times_;										//number of times this neuron has spiked
	bool refractory_;													//indicates if the neuron is in refractory state
	Time break_time_;													//time that the neuron spends in refractory state
	Buffer buffer_;														//buffer that stores that spike arriving to the neuron
	bool exitatory_;													//indicates the type of the neuron: excitatory or inhibitory
	double J_;															//Amplitude of the signal that this neuron sends to the ones downstream
	
	void set_J(double j);
	/**
	 * sets J, which is the strength of post synaptic potentiel sent by this neuron, depends on the type of the neuron
	 * @param j: the strength of post synaptic potentiel
	 */

public:

	double getMbPotential() const;
	/**
	 * @return Membrane potential
	 */
	double getNbSpikes() const;
	/**
	 * @return number of times this neuron has spiked
	 */
	std::vector<Time> getTimeSpikes() const;
	/**
	 * @return Vector storing all the spike times
	 */
	Time getSingleSpikeTime(int i) const;
	/**
	 * @param i: index of the spike
	 * @return returns a single spike time
	 */
	bool isRefractory() const;
	/**
	 * @return if the neuron is in a refractory period(true) or not(false)
	 */
	bool isExitatory() const;
	/**
	 * @return true if this neuron is an excitatory neuron, false if it is inhibitory
	 */
	
	void setMbPotential(double potMb);
	/**
	 * @param potMb: Membrane potential
	 */
	void setRefractory(bool refrac);
	/**
	 * sets the state of the neurn: refractory or not
	 * @param refrac: true to set the neuron to refractory, false to set it to normal
	 */
	void set_i_ext(double i_ext);
	/**
	 * sets the external current injected into the neuron
	 * @param i_ext: external current
	 */
	
	int idx(int i) const;
	/**
	 * calculates the index for the buffer
	 * @param i: time to be converted into index
	 * @return index
	 */
	double solveVoltEqu() const;
	/**
	 * calculates the new membrane potential for the neuron by solving the differential equation
	 * @return membrane potential
	 */
	void addSpike(Time temps);
	/**
	 * stores a spike that occured at a given time in spike_times_
	 * @param time at which the spike occured
	 */
	void rotateBuffer();
	/**
	 * shifts all the elements stored in the buffer one place to the right to simulate time passing
	 */
	void affiche_buffer() const;
	/**
	 * prints all the elements stored in the buffer, used verify that it functions correctly
	 */
	void fill_buffer(int local_steps, int delay = D);
	/**
	 * puts a new element into this neuron's buffer
	 * @param local_steps: time at which the pre-synaptic spike occured 
	 * @param delay: time that the spike takes to arrive to the soma
	 */
	bool update(int simulation_steps, int start_step = 0);
	/**
	 * updates the neuron: MbPotential, refractory state, Post Synaptic potentials, rotates buffer...
	 * @param simulation_steps: number of times that the neuron is updated
	 * @param start_step: time step at which we start
	 */	
	Neuron(bool excitatory = true);
	/**
	 * default constructor
	 * @param excitatory: indicates the type of the neuron: excitatory or inhibitory
	 */
	~Neuron();
	/**
	 * destructor
	 */

};

#endif
