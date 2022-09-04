#ifndef __NODE_T_HPP__
#define __NODE_T_HPP__


struct node_t {
	int time;           // start time
    int id;             // id of the transaction
    char op;            // operation of the transaction
    char attr;          // attribute of the transaction
};


#endif