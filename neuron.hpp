#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <vector>
#include <chrono>

typedef double Time;

//-------CONSTANTS----------------------------------------------------//
//smallest time unit available is 1ms
constexpr Time h(0.001);
constexpr double threshold_potential(0.2);
//membrane_resistance
constexpr double R(10000000.0);
constexpr Time tau(0.020);
constexpr Time refractory_period(0.001);
//doit etre a 0.0 car la formule le fait reveneir à cette valeur, shift tout de +0.070
constexpr double resting_potential(0.0);


class Neuron
{
private:
	double membrane_potential_;
	double nb_spikes_;
	std::vector<Time> spike_times_;
	bool refractory_;
	double input_current_;
	
public:

	double getMbPotential() const;
	double getNbSpikes() const;
	std::vector<Time> getTimeSpikes() const;
	bool isRefractory() const;
	
	void setMbPotential(double potMb);
	void setNbspikes(double nbSp);
	void setRefractory(bool refrac);
	
	double solveVoltEqu() const;
	void addSpike(Time temps);
	void update(Time simtime, double courant);
	
	Neuron();
	~Neuron();

};

#endif
