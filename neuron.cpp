#include <iostream>
#include "neuron.hpp"
#include <cmath>

using namespace std;

double Neuron::getMbPotential() const
{	return membrane_potential_;	}

double Neuron::getNbSpikes() const
{	return nb_spikes_;	}

vector<Time> Neuron::getTimeSpikes() const
{	return spike_times_;	}

bool Neuron::isRefractory() const
{	return refractory_;		}

void Neuron::setMbPotential(double potMb)
{
//mettre throw catch pour pas sortir du range
//if(potMb < -0.10 or potMb > 0.10){
		membrane_potential_ = potMb;
}

void Neuron::setNbspikes(double nbSp)
{
	nb_spikes_ = nbSp;
}

void Neuron::setRefractory(bool refrac)
{
	refractory_ = refrac;
}

double Neuron::solveVoltEqu() const
{
	return exp(-h / tau) * getMbPotential() + input_current_ * R * (1 - exp(-h / tau));
}

void Neuron::addSpike(Time temps)
{
	spike_times_.push_back(temps);
}

void Neuron::update(Time simtime, Time runTime, double courant)
{
	Time break_time(refractory_period);
	while(simtime < runTime)
		{	
			input_current_ = courant;
			if(isRefractory()){
					setMbPotential(resting_potential);
					if(break_time <= 0.0){
						setRefractory(false);
					}
					//on crée une var local break_time qui stocke le resting time et est décrementée à chaque passage dans la boucle
					break_time -= h;
					
			}else if(getMbPotential() >= threshold_potential){
				addSpike(simtime);
				setMbPotential(resting_potential);
				setRefractory(true);
				//on reset break_time à sa valeur initiale
				break_time = refractory_period;
			}
			//pas de nouveau calcul en periode refractaire
			if(!refractory_){
				setMbPotential(solveVoltEqu());
			}
			cerr << getMbPotential() << endl;
			simtime += h;
		};

}

Neuron::Neuron()
:membrane_potential_(resting_potential), nb_spikes_(0.0), refractory_(false), input_current_(0.0)
{}

Neuron::~Neuron(){}


