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

struct participante {
	tint cantidad;
	bool esFabricante;
	tint precio;
	tint indice;
	
	bool operator < (const participante& p2 ) const {
		#define CMP(x) if (this->x != p2.x) {return (this->x < p2.x);}
		CMP(cantidad);
		CMP(esFabricante);
		CMP(precio);
		CMP(indice);
		return false; 
	}
};

int ganancia( int P, vector< PQ > fabricantes, vector< PQ > compradores, int & Fab, int & Comp )
{
	vector<participante> ps;
	for(tint i = 0; i < tint(fabricantes.size()); i++) {
		const PQ f = fabricantes[i];
		ps.push_back({f.cantidad, true, f.precio, i + 1});
	} 
	for(tint i = 0; i < tint(compradores.size()); i++) {
		const PQ c = compradores[i];
		ps.push_back({c.cantidad, false, c.precio, i + 1});
	}
	sort(ps.begin(), ps.end());
	assert(ps.size() == fabricantes.size() + compradores.size());
	
	tint res = -1;	
	Fab = 0;
	Comp = 0;
	auto minPrecio = make_pair(INF, -1ll);
	
	for (const auto& p : ps) {
		if (!p.esFabricante) {
			auto c = p;
			if (c.cantidad * minPrecio.first <= P) {
				auto ganancia = c.cantidad * (c.precio - minPrecio.first);
				if (res < ganancia) {
					res = ganancia;
					Fab = minPrecio.second;
					Comp = c.indice;
				}
			}
		} else {
			if (minPrecio.first > p.precio) {
				minPrecio = {p.precio, p.indice};
			} 
		}
	}
	
	auto minFabrica = make_pair(INF, -1ll);
	reverse(ps.begin(), ps.end());
		
	for (const auto& p : ps) {
		if (!p.esFabricante) {
			auto c = p;
			auto ganancia = c.cantidad * c.precio - minFabrica.first;
			if (ganancia > res) {
				res = ganancia;
				Fab = minFabrica.second;
				Comp = c.indice;
			} 
		} else {
			auto costo = p.precio * p.cantidad;
			if (costo <= P) {
				if (costo < minFabrica.first) {
					minFabrica = {costo, p.indice};
				} 
			}
		}
	}
	
	return res;
}
