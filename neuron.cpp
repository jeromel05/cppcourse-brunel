#include <iostream>
#include "neuron.hpp"
#include <cmath>

using namespace std;

double Neuron::getMbPotential() const
{	return membrane_potential_;	}

double Neuron::getNbSpikes() const
{	return spike_times_.size();	}

vector<Time> Neuron::getTimeSpikes() const
{	return spike_times_;	}

bool Neuron::isRefractory() const
{	return refractory_;		}

int Neuron::getIndex() const
{	return index_;	}

void Neuron::setMbPotential(double potMb)
{
//mettre throw catch pour pas sortir du range
//if(potMb < 0.0 or potMb > 100){
		membrane_potential_ = potMb;
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

void Neuron::receive_excitatory(Time temps, double EPSP_amp)
{
	//temps pas necessaire pour resoudre equa dif??
	setMbPotential(solveVoltEqu() + EPSP_amp);
}

void Neuron::affiche_buffer() const
{
	for(auto i: buffer_){
		cerr << i;
	}
	cerr << endl;
}

void Neuron::fill_buffer(double delay, double EPSP_amp)
{
	buffer_[delay - 1] += EPSP_amp;
}
		
void Neuron::rotateBuffer()
{
	for(size_t i(0); i < buffer_.size(); ++i){
		buffer_[i] = buffer_[i + 1];
	}
	buffer_.back() = 0;
}


bool Neuron::update(Time start_time, int simulation_steps, double courant)
{
	if(simulation_steps < 1) return false;
	//tester d'abord si potentiel >= threshold -> passe moins souvent dans la boucle
	int step_count(start_time / h);
	int nb_spikes(0.0);
		
			input_current_ = courant;
			
			if(getMbPotential() >= threshold_potential){
				addSpike(step_count * h);
				setMbPotential(resting_potential);
				setRefractory(true);
				//on reset break_time à sa valeur initiale
				//break_time_ = refractory_period;
				++nb_spikes;
				cerr << "spike at:" << spike_times_[getNbSpikes() - 1] << " ms" << endl;
			
			}
			if(isRefractory()){
					setMbPotential(resting_potential);
					if(break_time_ <= 0.0){
						setRefractory(false);
						break_time_ = refractory_period;
					}
					//break_time stocke le resting time et est décrementée à chaque passage dans la boucle
					break_time_ -= h;
			}
			//pas de nouveau calcul en periode refractaire
			if(!refractory_){
				setMbPotential(solveVoltEqu());
			}
			++step_count;
			cerr << "pot de " << getIndex() << " : " << getMbPotential() << endl;
			
		rotateBuffer();
		if(buffer_[0] > 0.0){
			receive_excitatory(start_time, buffer_[0]);
		}		
			
	if(nb_spikes > 0.0) return true; else return false;
}

Neuron::Neuron(int index)
:membrane_potential_(resting_potential), refractory_(false), input_current_(0.0), index_(index), break_time_(refractory_period)
{
	for(auto& e: buffer_){
		e = 0.0;
	}
}

Neuron::~Neuron()
{}


