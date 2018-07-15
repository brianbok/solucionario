#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

// *********** IMPORTANTE!!!!!! ********************
// NO MODIFICAR DE NINGUNA MANERA ESTE STRUCT!!!!!**
struct PQ{ int precio, cantidad; } ; //  ***********
// *************************************************
// *************************************************

#define DEBUG(x) cout << #x << ": " << x << endl;

typedef long long int tint;

const tint INF = 9999999;

#define forn(i, n) for(tint i = 0; i < (n); i++)

int gananciaPar(PQ f, PQ c) {
  if (f.cantidad >= c.cantidad) {
    return c.precio * c.cantidad - f.precio * f.cantidad;
  } else {
    return c.cantidad * (c.precio - f.precio);
  }
}

int ganancia( int P, vector< PQ > fabricantes, vector< PQ > compradores, int & Fab, int & Comp )
{
  tint res = -1;
  Fab = 0;
  Comp = 0;
  forn(i, tint(fabricantes.size())) {
    forn (j, tint(compradores.size())){
      auto f = fabricantes[i];
      auto c = compradores[j];
      tint produccion = max(c.cantidad, f.cantidad);
      if (f.precio * produccion <= P) {			
	tint ganancia = gananciaPar(f, c);                
	if (ganancia > res) {
	  res = ganancia;
	  Fab = i + 1;
	  Comp = j + 1;
	}
					
      }
    }
  }
  return res;
}
