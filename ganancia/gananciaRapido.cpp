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
	auto maximaCompra = make_pair(-1ll, -1ll);
	auto minimoFabricante = make_pair(INF, -1ll);
	
	for (const auto& p : ps) {
		if (p.esFabricante ) {
			if (p.precio * p.cantidad > P) {
				continue;
			} 
			const tint posibleGanancia = maximaCompra.first - p.precio * p.cantidad; 
			if (res < posibleGanancia && posibleGanancia >= 0) {
				res = posibleGanancia;
				Fab = p.indice;
				Comp = maximaCompra.second;
			}
			if (p.precio < minimoFabricante.first) {
				minimoFabricante = {p.precio, p.indice};
			} 
		} else {
			const tint venta = p.precio * p.cantidad;
			if (maximaCompra.first < venta) {
				maximaCompra = {venta, p.indice};
			}
			if (p.cantidad * minimoFabricante.first <= P) {
				const tint posibleGanancia = venta - p.cantidad * minimoFabricante.first;
				if (res < posibleGanancia) {
					res = posibleGanancia;
					Fab = minimoFabricante.second;
					Comp = p.indice;
				}	
			}
		}
	}
	return res;
}
