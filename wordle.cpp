#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordlehelper(std::set<std::string>& results, unsigned int position, unsigned int empty, std::string& inn,std::string& floatin, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
		std::set<std::string> results;
		std::string inn = in;
		std::string floatin = floating; 
		unsigned int position = 0;
		unsigned int fred = 0;
		for(unsigned int i =0; i< inn.size();i++){
			if( inn[i] == '-'){
				fred++;
			}
		}
		wordlehelper(results, position, fred, inn, floatin, dict);
		return results;
}

// Define any helper functions here
void wordlehelper(std::set<std::string>& results, unsigned int position, unsigned int fred, std::string& inn,std::string& floatin, const std::set<std::string>& dict){
	if(position == inn.length()){
		if(dict.find(inn) == dict.end()){
			return;
		}
		else if(dict.find(inn) != dict.end()){
			results.insert(inn);
			return;
		}		
	}
	else if(inn[position] != '-'){
		wordlehelper(results, position+1, fred, inn, floatin, dict);
		return;
	}
	else if(fred <= floatin.length()){
		if(floatin.length() > 0){
			for(auto i:floatin){
				std::string floaty = floatin;
				inn[position] = i;
				char eraser = floatin.find(i);
				floatin.erase(eraser,1);
				wordlehelper(results,position+1, fred-1,inn, floatin, dict);
				floatin = floaty;
			}
			inn[position] = '-';
		}
	}
	else{
			for(char i = 'a'; i <= 'z';i++){
				inn[position] = i;
				if(floatin.find(i) != floatin.npos){
					std::string floaty = floatin;
					inn[position] = i;
					char eraser = floatin.find(i);
					floatin.erase(eraser,1);
					wordlehelper(results,position+1, fred-1,inn, floatin, dict);
					floatin = floaty;
				}
				else if(floatin.find(i) == floatin.npos){
					// position++;
					wordlehelper(results,position+1, fred-1,inn, floatin, dict);
				}
			}
			inn[position] = '-';
		}
	return;
	}
	
