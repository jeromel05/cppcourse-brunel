#include "network.hpp"
#include "iostream"

using namespace std;


Neuron Network::getNeuron(int index) const
{
	assert(index > 0);
	return *neurons_[index - 1];
}

void Network::net_set_i_ext(double i_ext)
{
	assert(!neurons_.empty());
	for(auto& e: neurons_){
		assert(e != nullptr);
		e->set_i_ext(i_ext);
	}	
}
	
void Network::create_connections()
{
	//ou selectionner 1000 nb random des indices des excitateurs et 250 des inhibiteurs
	//ainsi on pourra avoir 2x le meme indice
	std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_int_distribution<> dis1(0, nb_excitateur);
    std::uniform_int_distribution<> dis2(nb_excitateur + 1, nb_neurons);
    int temp(0);
    
    //on reprend un autre nb tant que on a pris le meme que l'indice i pck pas de connection d'un neurone avec lui meme
     for(size_t i(0); i < nb_neurons; ++i){
		for(size_t j(0); j < (C_E + C_I); ++j){
			do{
				if(j < C_E){
					temp = dis1(gen);
				}else{
					temp = dis2(gen);
				}
			}while(temp == i);
				assert(neurons_[i] != nullptr);
				neurons_[i]->add_connection(neurons_[temp]);
		}
	}
}

void Network::update(int simulation_steps)
{
	assert(simulation_steps > 0);
	bool spike(false);
	int step_count(0);
	
	/* affiche nb spike par pas de temps
	array<int, 1000> res;
	int res1;
	for(int i(0); i < res.size(); ++i){
			res[i] = 0;
		}
	*/
	
	while(step_count < simulation_steps)
	{	
		assert(!neurons_.empty());
			for(auto& e: neurons_){
				assert(e != nullptr);
					spike = e->update(1, step_count);
					if(spike){
						//++res1;
						for(size_t y(0); y < (C_E + C_I); ++y){
								e->get_synapses_post()[y].fill_buffer(step_count);
							}
						}
					}
					
	//res[step_count] = res1;
	//res1 = 0;
	++step_count;
	};
	
	/*
	for(int i(0); i < res.size(); ++i){
			cout << res[i] << " " << endl;
		}	
	*/
}

void Network::reset()
{
	if(!neurons_.empty()){
		for(auto& c: neurons_){
			delete c;
			c = nullptr;
		}
	}
	//appel à reset() seulement necessaire si on crée des new neurones
}

Network::Network()
{		
	for(size_t i(0); i < nb_neurons; ++i){
	try{
		if(i < nb_excitateur){											//Comment mettre addresse/objet entier a la place de ptr?????????????????
				neurons_[i] = new Neuron(true);
			}else{
				neurons_[i] = new Neuron(false);
		}
	}
		catch (std::bad_alloc &e)
		{
			cerr << "new Failed";
		}
	}
	
	create_connections();
}

Network::~Network()
{
	reset();
}
