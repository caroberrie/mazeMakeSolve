#ifndef _PROJECT_4
#define _PROJECT_4

#include <iostream>
#include <cstdlib>

class Sampler{

private:
	int n;
	int *items;


public:
	Sampler(int x){
		int i;

		items = new int[x];
		n = x;

		for (i = 0; i < n; i++)
			items[i] = i;
	}

	~Sampler(){ delete[] items; }

	int getSample(){
	
		int i = rand() % n;
		int e;

		//i = rand % n;
		e = items[i];
		n = n - 1;

		items[i] = items[n];

		return e;
	}
};

class DisjointSet{

private:
	int 
	*elements,*rank;

public:
	DisjointSet(int n){

		elements = new int[n];
		rank = new int[n];

		int i;

		for (i=0;i<n;i++) {
			elements[i] = i;
			rank[i] = 0;
		}
	}

	~DisjointSet(){ delete[] elements; delete[] rank; }

	int find(int a){
		if (elements[a] != a)
	   		elements[a] = find(elements[a]);

		return elements[a];
	}

	void join(int a, int b){
		a = find(a);
		b = find(b);

		if (a != b){
	  		if (rank[a] < rank[b])
	       		elements[a] = b;
	  		else {
		    	if (rank[a] == rank[b])
	       			rank[a] = rank[a] + 1;
	  			elements[b] = a;
	  		}
	  	}
	}
};

#endif
