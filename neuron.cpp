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

Time Neuron::getSingleSpikeTime(int i) const
{	
	assert(i > 0.0 and i <= getTimeSpikes().size());
	return spike_times_[i -1];	
}
		
bool Neuron::isRefractory() const
{	return refractory_;		}

std::vector<Neuron*> Neuron::getSynapses() const
{
	return synapses_post_;
}

void Neuron::setMbPotential(double potMb)
{
	string s("Mb Potential out of bounds");
    //throw catch pour pas sortir du range
	try{
		if(potMb < 0.0 or potMb > 100){
			throw s;
		}
		membrane_potential_ = potMb;
	}
	catch(string a){
		cerr << a << endl;
		setMbPotential(resting_potential);	
	}
}

void Neuron::setRefractory(bool refrac)
{
	refractory_ = refrac;
}

int Neuron::idx(int i) const
{
	return i%(D+1);
}


double Neuron::solveVoltEqu() const
{
	return c1 * getMbPotential() + input_current_ * R * c2;
}

void Neuron::addSpike(Time temps)
{
	spike_times_.push_back(temps);
}

void Neuron::receive_excitatory(int time_step)
{
	setMbPotential(solveVoltEqu() + buffer_[0]);
	//on a utilisé le premier element du buffer donc on le remet à 0
	cerr << "recu a: " << time_step * h << endl;
	buffer_[0] = 0.0;
}

void Neuron::affiche_buffer() const
{
	for(auto i: buffer_){
		cout << i;
	}
	cout << endl;
}

void Neuron::fill_buffer(int local_steps, int delay, double EPSP_amp)
{
	buffer_[idx(delay + local_steps)] += EPSP_amp;
}
		
void Neuron::rotateBuffer()
{
	//buffer_.back() = 0.0;
	buffer_.back() = buffer_[0];										//similaire à la ligne d'en haut mais crée effet cyclique
	for(size_t i(0); i < buffer_.size(); ++i){
		buffer_[i] = buffer_[i + 1];
	}
}

void Neuron::addTarget(Neuron* cible)
{
	assert(cible != nullptr);
	synapses_post_.push_back(cible);
}


bool Neuron::update(int start_step, int simulation_steps, double courant)
{
	if(simulation_steps < 1) return false;
	int step_count(start_step);
	int nb_spikes(0.0);
		
		input_current_ = courant;
			
		if(getMbPotential() >= threshold_potential){					//on test d'abord si potentiel >= threshold -> passe moins souvent dans la boucle
				addSpike(step_count * h);
				setMbPotential(resting_potential);
				setRefractory(true);
				++nb_spikes;
				cerr << "spike at:" << spike_times_[getNbSpikes() - 1] << " ms" << endl;
			
		}
		if(isRefractory()){												//pas de nouveau calcul en période réfractaire
				setMbPotential(resting_potential);
					if(break_time_ <= 0.0){
						setRefractory(false);
						break_time_ = refractory_period;				//on reset breaktime à sa valeur initiale
					}
				break_time_ -= h;										//break_time stocke le resting time et est décrementée à chaque passage dans la boucle
				
		}else if(buffer_[0] <= 0.0){
					setMbPotential(solveVoltEqu());
				}else{
					receive_excitatory(start_step);
				}	
				
	if(nb_spikes > 0.0){
			for(auto& i: synapses_post_){
				i->fill_buffer(step_count);
			}
	}
	rotateBuffer();
	++step_count;
	
	if(nb_spikes > 0.0) return true; else return false;
}

Neuron::Neuron()
:membrane_potential_(resting_potential), refractory_(false), input_current_(0.0), break_time_(refractory_period)
{
	for(auto& e: buffer_){
		e = 0.0;
	}
}

Neuron::~Neuron()
{}

void Neuron::reset()
{
	for(auto& i: synapses_post_){
			delete i;
			i = nullptr;
		}
	synapses_post_.clear();
}


