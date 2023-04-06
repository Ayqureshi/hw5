#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool helper(const AvailabilityMatrix& avail,const unsigned int& w_availability, const unsigned int& shift_max, const unsigned int& day_need, const unsigned int& day_period, DailySchedule& sched, unsigned int row, unsigned int col);
bool valid(const AvailabilityMatrix& avail,const unsigned int& shift_max, const unsigned int& day_need, const unsigned int& day_period, const DailySchedule& sched, const Worker_T& worker,unsigned int row, unsigned int col, unsigned int counter);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    unsigned int w_availability = avail[0].size();//k
    unsigned int day_period = avail.size();// n
    unsigned int day_need = dailyNeed;//d
    unsigned int shift_max = maxShifts; //m
    unsigned int r = 0; 
    unsigned int c = 0; 

    for(unsigned int i = 0;i < day_period;i++){
        vector<Worker_T> container;
        sched.push_back(container);
        for(unsigned int l =0; l <day_need;l++){
            sched[i].push_back(INVALID_ID);
        }
		}
		
		bool retval;
    return retval = helper(avail, w_availability, shift_max, day_need, day_period, sched,r,c);
         
}

bool helper(const AvailabilityMatrix& avail,const unsigned int& w_availability, const unsigned int& shift_max, const unsigned int& day_need, const unsigned int& day_period, DailySchedule& sched, unsigned int row, unsigned int col){
	if(row == day_period-1){
		if(col == day_need){
			return true;
		}
	}
	if(col == day_need){
		row++;
		col = 0; 
	}
	for(Worker_T i=0; i <Worker_T(w_availability);i++){
		sched[row][col] = i;
		if(valid(avail, shift_max, day_need, day_period, sched,i, 0, 0, 0)==true){
			if(helper(avail, w_availability, shift_max, day_need, day_period, sched,row,col+1)==true){
				return true;
			}
		}
		else if (valid(avail, shift_max, day_need, day_period, sched,i, 0, 0, 0)==false || helper(avail, w_availability, shift_max, day_need, day_period, sched,row,col+1)==false){
			sched[row][col] = INVALID_ID;	
		}
	}
	return false;
}
bool valid(const AvailabilityMatrix& avail,const unsigned int& shift_max, const unsigned int& day_need, const unsigned int& day_period, const DailySchedule& sched, const Worker_T& worker, unsigned int row, unsigned int col,unsigned int counter){
	if(col >= day_need){
		row++;
		col = 0;
	}
	if(row >= day_period){
		return true;
	}
	if(sched[row][col] == worker){
				counter++;
				// go to the next day 
				if(avail[row][worker]==false){
					//if the matrix when factoring in the id is false return false
					return false;
				}
	}
	if(counter > shift_max){
		return false;
	}
	return valid(avail, shift_max, day_need, day_period, sched, worker, row, col+1, counter);				
}