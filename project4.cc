#include "project4.h"
#include "exceptions.h"
#include "pathfinder.h"
//#include "output.cpp"
#include <stack.h>

//#include <cstdlib>
#include <stdlib.h>
#include <iostream>

using namespace std;

//void GenerateMaze(int,int);
//void wallRemove();

int d[4] = {0,1,2,3};


void GenerateMaze(uint8_t Map[][50],int nR, int nC){
	int i = 0;

	for (int r = 0; r < nR; r++)
		for (int c = 0; c < nC; c++)
			Map[r][c] = 15;

	DisjointSet ds(nR*nC);
	Sampler sam(nR*(nC-1)+nC*(nR-1));
	
	i = 0;

	//decodeCell();
	 
	while(i < nR * nC - 1) { //wall remover
		int wall,r,c,r2,c2;
	
		wall = sam.getSample();

		if (wall < nR * (nC-1)){  // this for right wall
			 // find out what cell it is
			r = wall%nR;
			c = wall/nR;

			//cell to the right of it
			r2 = r;
			c2 = c + 1;

			if(ds.find(r*nC+c) != ds.find(r2*nC+c2)){
				Map[r][c] &= ~WALL_RIGHT; // constant in a header given to us

				Map[r2][c2] &= ~WALL_LEFT;

				ds.join(r*nC+c, r2*nC+c2);

				i++;
			}
		} else {
			wall = wall - nR*(nC-1);
			//down row
			r = wall/nC;
			c = wall%nC;

			r2 = r+1;
			c2 = c;

			if(ds.find(r*nC+c) != ds.find(r2*nC+c2)){
				Map[r][c] &= ~WALL_DOWN;
				Map[r2][c2] &= ~WALL_UP;

				ds.join(r*nC+c, r2*nC+c2);
				i++;
			}
		}

	}

}

void findPath(uint8_t Map[][50],int nR,int nC) {
// Find path
	Stack <int>s;

	//d + 5(c + n * r)
	int d = 0;

	
	s.push(d + 5*(0+nC*0));
	//mark 0 0 as visited
	Map[0][0] |= VISITED;
	int e, c, r, cprime,rprime;

	//e = d+5(c+nC·r);
	

	while(true){
		//decode
		e = s.peek();

		c = (e/5) % nC;
		r = (e/5) / nC;
		d = e % 5;

		if(r == nR - 1 && c == nC - 1)
			break;

		if(d == 4){

			Map[r][c] |= DEAD_END;
			s.pop();

		} else {

			rprime = r;
			cprime = c;

			if (d == 0)
				rprime--;
			if (d == 1)
				cprime++;
			if (d == 2)
				rprime++;
			if (d == 3)
				cprime--;
			//replace encodes
			s.pop();
			s.push((d + 1)+ 5*(c+nC*r));

			if ((Map[r][c] & (1 << d)) == 0 && (Map[rprime][cprime] & VISITED) == 0 )	{
				e = 0 + 5 * (cprime+nC*rprime);
				s.push(e);
				Map[rprime][cprime] |= VISITED;
			}	
		}
	}
}

//int main(int argc, char argv[]){
int main(int argc, char *argv[]){
int nR, nC;
uint8_t Map[50][50];
int i = 0;


srand(time(NULL));
nR = atol(argv[1]); // initialize nR
nC = atoi(argv[2]); 


int numWalls = (nC -1)*nR + nC*(nR - 1);

GenerateMaze(Map,nR, nC); // void to generate maze
findPath(Map,nR,nC);
printMaze(Map,nR,nC);

return 0;
}








