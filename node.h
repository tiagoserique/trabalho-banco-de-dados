// Vinicius Tikara Venturi Date - GRR20190367
// Tiago Serique Valadares - GRR20195138

#ifndef __NODE_H__
#define __NODE_H__


struct node_t {
	int time;           // start time
    int id;             // id of the transaction
    char op;            // operation of the transaction
    char attr;          // attribute of the transaction
};


#endif