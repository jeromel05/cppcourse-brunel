#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <string>
#include <cassert>

typedef double Time;

//-------CONSTANTS----------------------------------------------------//
//smallest time unit available is 1ms
constexpr Time h(0.1);
constexpr double threshold_potential(20.0);
constexpr Time tau(20.0);
constexpr Time refractory_period(0.2);
//doit etre a 0.0 car la formule le fait revenir à cette valeur, shift tout de +0.070
constexpr double resting_potential(0.0);
//capacitance = [Farad] = [Volt/Coulomb]
constexpr double C(1.0);
//membrane_resistance
constexpr double R(tau / C);

//J = EPSP Amplitude [mV]
constexpr double J(0.1);
//D = Delay (travel time of spike in axon) [ms]
constexpr int D(15.0); // [steps]

//2 constantes initialisées dns le constructeur
const double c1(std::exp(-h / tau));  
const double c2(1 - std::exp(-h / tau));

typedef std::array<double, D + 1> Buffer;




class Neuron
{
private:
	double membrane_potential_;
	std::vector<Time> spike_times_;
	bool refractory_;
	double input_current_;
	Time break_time_;
	Buffer buffer_;
	std::vector<Neuron*> synapses_post_;

public:

	double getMbPotential() const;
	double getNbSpikes() const;
	std::vector<Time> getTimeSpikes() const;
	Time getSingleSpikeTime(int i) const;
	bool isRefractory() const;
	std::vector<Neuron*> getSynapses() const;
	
	void setMbPotential(double potMb);
	void setNbspikes(double nbSp);
	void setRefractory(bool refrac);
	
	int idx(int i) const;
	double solveVoltEqu() const;
	void addSpike(Time temps);
	void receive_excitatory(int time_step);
	
	void rotateBuffer();
	void affiche_buffer() const;
	void fill_buffer(int local_steps, int delay = D, double EPSP_amp = J);
	void addTarget(Neuron* cible);
	
	bool update(int start_step, int simulation_steps, double courant);
	
	void reset();
	
	Neuron();
	~Neuron();

};

#endif
