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

#define forn(i, n) for(int i =0; i < (n); i++)

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
    
    vector<pair<tint, tint>> minFabricaMenor(ps.size());
    vector<pair<tint, tint>> minFabricaMayor(ps.size());
    
 	forn(i, tint(ps.size())) {
        minFabricaMenor[i] = (i == 0) ? make_pair(INF, -1ll) : minFabricaMenor[i - 1];
        auto p = ps[i];
        if (p.esFabricante) {
            if (p.precio < minFabricaMenor[i].first) {
                minFabricaMenor[i].first = p.precio;
                minFabricaMenor[i].second = p.indice;
            }
        }
    }
    
    for(int i = tint(ps.size()) - 1; i >= 0; i--) {
        minFabricaMayor[i] = (i == tint(ps.size()) - 1) ? make_pair(INF, -1ll) : minFabricaMayor[i + 1];
        auto p = ps[i];
        if (p.esFabricante && p.precio * p.cantidad <= P) {
            if (p.precio * p.cantidad < minFabricaMayor[i].first) {
                minFabricaMayor[i].first = p.precio * p.cantidad;
                minFabricaMayor[i].second = p.indice;
            }
        }
    } 
    
    forn(i, tint(ps.size())) {
        auto p = ps[i];
        if (!p.esFabricante) {
            auto c = p;
            tint fabLocal, gananciaLocal;
            auto ganancia1 = -INF;
            if (minFabricaMenor[i].first * c.cantidad <= P) {
                ganancia1 = (c.precio - minFabricaMenor[i].first) * c.cantidad;
            }
            auto ganancia2 = c.cantidad * c.precio - minFabricaMayor[i].first;
            
            if (ganancia1 > ganancia2) {
                gananciaLocal = ganancia1;
                fabLocal = minFabricaMenor[i].second;
            } else {
                gananciaLocal = ganancia2;
                fabLocal = minFabricaMayor[i].second;
            }
            
            /*DEBUG(gananciaLocal);
            DEBUG(ganancia1);
            DEBUG(ganancia2);*/
            if (res < gananciaLocal) {
                Fab = fabLocal;
                Comp = p.indice;
                res = gananciaLocal;
            }
        } 
    }
    
    return res;

}
