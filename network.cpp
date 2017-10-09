#include "network.hpp"
#include "iostream"

using namespace std;

void Network::addTarget(int i, Neuron* cible)
{
	if(!synapses_post_.empty()){
		synapses_post_[i - 1][i-1] = cible;
	}
}

void Network::addNeuron(Neuron* neuron)
{
	neurons_.push_back(neuron);
}

Neuron Network::getNeuron(int index) const
{
	if(index > 0){
		return *neurons_[index - 1];
	}else{
		return *neurons_[0];
	}
}

void Network::update(Time start_time, int simulation_steps, double courant_ext)
{
	bool spike(false);
	int step_count(start_time / h);
	
	while(step_count < simulation_steps)
	{	
		if(!neurons_.empty() and neurons_.front() != nullptr and !synapses_post_.empty() and synapses_post_.front()[0] != nullptr){
			for(auto& e: neurons_){
					//Ici seul le neurone 1 recoit le courant
					if(e->getIndex() < 2){
						spike = e->update(step_count * h, 1, courant_ext);
					}else{
						spike = e->update(step_count * h, 1, 0.0);
					}
					if(spike and synapses_post_.front()[0] != nullptr and !synapses_post_.empty()){
							for(auto& i: synapses_post_[e->getIndex() - 1]){
								i->fill_buffer();
							}
						}
					}
			}
	++step_count;
	};		
}

void Network::reset()
{
	/*
	Pour mettre un vector
	for(auto& f: synapses_post_){
		for(auto& i: f){
			delete i;
			i = nullptr;
		}
	}
	*/
	for(auto& c: neurons_){
		delete c;
		c = nullptr;
	}
	neurons_.clear();
	//synapses_post_.clear();
}

Network::Network()
{		
	reset();
}

Network::~Network()
{
	//appel à reset() cree memory freed was not allocated ??
	//reset();
}
