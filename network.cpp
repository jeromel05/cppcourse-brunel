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

void Network::affiche_connections() const
{
	for(auto e: connections_){
		for(auto h: e){
			cout << h;
		}
		cout << endl;
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
				++connections_[i][temp];
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
			for(size_t i(0); i < nb_neurons; ++i){
				assert(neurons_[i] != nullptr);
					spike = neurons_[i]->update(1, step_count);
					if(spike){
						//++res1;
						for(size_t y(0); y < nb_neurons; ++y){
							if(connections_[i][y]){
								neurons_[y]->fill_buffer(step_count);
							}
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
	for(auto& e: connections_){
		for(auto& h: e){
			h = 0;
		}
	}
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
	reset();
	create_connections();

	for(size_t i(0); i < nb_neurons; ++i){
	try{
		if(i < nb_excitateur){
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
}

Network::~Network()
{
	reset();
}
