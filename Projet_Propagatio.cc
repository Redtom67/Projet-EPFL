///Projet Propagatio, Fischer Thomas, Mk II

#include <iostream>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

const string P1("P1 missing or incorrect");
const string WRONG_NB_COL_LGN("Nb columns and/or nb lines incorrect");
const string MATRIX_SQUARE("Matrix is not square");
const string IRREGULAR_CONTENT("Matrix description with incorrect content");
const string DISCONNECTED_GRAPH("Matrix corresponds to a disconnected graph");

typedef vector<double> Vecteur;
typedef vector<vector<double>> Matrice;
typedef vector<bool> Vector;

void projet_propagatio();

void tache1(Matrice& matAdj, int& n, string id, int n0);

void transformation (Matrice& matAdj, int& n);

void tache2(Matrice& matAdj, int& n);

Vector connexitee(Matrice& matAdj, int& n,int& ligne,Vector& visited, int& degre, 
                  Vecteur& classement_noeuds);

void tache3 (Matrice& matAdj, int& n);

void propagation(Matrice& matAdj, int n,int ligne,Vector& visited, int& degre,
                 Vecteur& depart, Vecteur& arrivee, Vecteur& stock, 
                 Matrice& propagatio, int& degre_max, int& noeud_suivant);

int recursion(Matrice& matAdj, int& n,int& ligne,Vector& visited, int& degre,
              Vecteur& depart, Vecteur& arrivee, Vecteur& stock,
              Matrice& propagatio, int& degre_max, int& noeud_suivant);

void tache4(Matrice& matAdj, int& n);


int main()
{

projet_propagatio ();
	
return 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////:

void projet_propagatio ()
{
   string id("");
   cin >> id ;
   int n0 (0);
   cin >> n0 ;
   int n(0);
   cin >> n ;
   Matrice matAdj(n,vector<double>(n));
   for (int ligne (0); ligne < n; ++ligne) {
      for (int colonne (0); colonne < n; ++colonne) {
	     cin >> matAdj[ligne][colonne]; 
      }	
   }
 
   tache1 (matAdj,n,id,n0);
   tache2 (matAdj,n);
   tache3 (matAdj,n);
   tache4 (matAdj,n);
	
}

///////////////////////////////////////////////////////////////////////////////////////////////:

void tache1 (Matrice& matAdj, int& n, string id, int n0)
{
   if (n == 0){
      cout << WRONG_NB_COL_LGN << endl;
	  exit (0);
   }
   if (n == 1){
	  cout << 0 << endl;
	  cout << "0.000000" << endl;
	  exit (0);
   }
   if (id != "P1") {
      cout << P1 << endl;
      exit (0);
   }
   if (n != n0) {
      cout << MATRIX_SQUARE << endl;
      exit(0);	
   }
   for (int ligne (0); ligne < n; ++ligne) {
      for (int colonne (0); colonne < n; ++colonne) {
	     if ((matAdj [ligne][colonne] != 1) and (matAdj [ligne][colonne] != 0)) {
            cout << IRREGULAR_CONTENT << endl;
            exit (0);	
         }
      }	  
   }
   transformation (matAdj, n);
}

///////////////////////////////////////////////////////////////////////////////////////////////:

void transformation (Matrice& matAdj, int& n)
{
   for (int ligne (0); ligne < n; ++ligne) {
      for (int colonne (0); colonne < n; ++colonne) {
	     if (ligne == colonne) {
            matAdj[ligne][colonne] = 0; 	
         } 
      }	
   }
   for (int ligne (0); ligne < n; ++ligne) {
      for (int colonne (0); colonne < n; ++colonne) {
         if (matAdj[ligne][colonne] == 1) {
            matAdj[colonne][ligne] = 1;
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////:

void tache2 (Matrice& matAdj, int& n)
{	
   int degre(1);
   int ligne(0);
   Vecteur classement_noeuds(n);
   Vector visited(n-1);
   visited[0]=1;
   connexitee (matAdj, n, ligne, visited, degre, classement_noeuds);
   for(int ligne(0); ligne < n; ++ligne){
      if (visited[ligne] == 0){
	     cout << DISCONNECTED_GRAPH << endl;
		 exit(0);
	  }
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////:

Vector connexitee (Matrice& matAdj, int& n,int& ligne,Vector& visited, int& degre, 
                   Vecteur& classement_noeuds)
{
   for (int colonne(0); colonne < n; ++colonne){
      if (matAdj[ligne][colonne]==1){
	     if (visited[colonne]==1){
	        if (colonne < n-1){
	           continue;
		    }else {
		       if (ligne != 0){
				   ligne = classement_noeuds[degre-2];
				   degre = degre - 1;
			      connexitee (matAdj, n, ligne, visited, degre, classement_noeuds);
	           }else {
		          return visited;
		       }
		    }
	     }else if (visited[colonne]==0){
	        classement_noeuds[degre]=colonne;
		    visited[colonne]=1;
		    ligne = colonne;
		    degre = degre + 1;
		    connexitee (matAdj, n, ligne, visited, degre, classement_noeuds);
	     }
      }else if (matAdj[ligne][colonne]==0){
         if (colonne < n-1){
	        continue;
	     }else {
            if (ligne == 0) {
	        return visited;
	        }else {
				ligne =  classement_noeuds[degre-2];
				degre = degre - 1;
	           connexitee (matAdj, n, ligne, visited, degre, classement_noeuds);
            }	    
         }
      } 
   }
   return visited;
}

///////////////////////////////////////////////////////////////////////////////////////////////:

void tache3 (Matrice& matAdj, int& n)
{
   int degre(0);
   int ligne(0);
   int degre_max(0);
   int noeud_suivant(1);
   Vecteur depart(n, -1);
   Vecteur arrivee(n, -1);
   Vecteur stock(n);
   Matrice propagatio(n,vector<double>(n));
   Vector visited(n-1);
   visited[0]=1;

   propagation(matAdj, n, ligne, visited, degre, depart, arrivee, stock, propagatio,
               degre_max, noeud_suivant);
   cout << 0 << endl;
   for (int ligne (0); ligne < degre_max; ++ligne) {
      Vecteur transition(n);
      for (int colonne (0); colonne < n; ++colonne) {
	     if (propagatio[colonne][ligne] != 0){
            transition[colonne] = propagatio [colonne][ligne];
         }
      }
      sort(transition.begin(), transition.end());
      for (int rang(0); rang < n; ++rang) {
	     if ( transition[rang] != 0){
	        if (rang == n-1) {
		       cout << transition[rang];
			}else {
	           cout << transition[rang] << " " ;
	        }
         }
      }		
      cout << endl;
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////:

void tache4 (Matrice& matAdj, int& n)
{
   cout << setprecision(6);
   cout << fixed;
   double somme_moyenne(0);
	
   for (int ligne(0); ligne < n; ++ligne){
      int degre_max(0);
	  int degre(0);
      int noeud_suivant(1);
	  Vecteur depart(n, -1);
      Vecteur arrivee(n, -1);
      Matrice propagatio(n,vector<double>(n));
      Vecteur stock(n);
	  Vector visited(n-1);
	  visited[ligne]=1;
	  
      propagation(matAdj, n, ligne, visited, degre, depart, arrivee, stock, propagatio,
                  degre_max, noeud_suivant);
      for(int rang(0); rang < n; ++rang){
	     somme_moyenne = somme_moyenne + ((stock[rang]*(rang+1))/(n-1));
      }
   }
   cout << somme_moyenne/n << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////:

void propagation(Matrice& matAdj, int n,int ligne,Vector& visited, int& degre, 
                 Vecteur& depart,Vecteur& arrivee,Vecteur& stock, Matrice& propagatio,
                 int& degre_max, int& noeud_suivant)
{
   for (int colonne(0); colonne < n; ++colonne){
      if (colonne < n-1) {
	     if (matAdj[ligne][colonne] == 1){
			if (visited[colonne] == 1){
		       continue;
			}else {
			   arrivee[degre] = colonne;
			   visited[colonne] = 1;
			   propagatio[degre][degre_max] = colonne;
			   ++degre;
			}
		 }else {
	        continue;
		 }
	  }else {
	     if (matAdj[ligne][colonne] == 1){
		    if (visited[colonne] == 1){
			   recursion(matAdj, n, ligne, visited, degre, depart, arrivee,
			             stock, propagatio, degre_max, noeud_suivant);
			   if (n == -1) {
				  break;
			   }
			}else {
	           arrivee[degre] = colonne;
			   visited[colonne] = 1;
			   propagatio[degre][degre_max] = colonne;
			   ++degre;
			   recursion(matAdj, n, ligne, visited, degre, depart, arrivee,
			             stock, propagatio, degre_max, noeud_suivant);		 
			   if (n == -1) {
			      break;
			   }
			}
		 }else {
		    recursion(matAdj, n, ligne, visited, degre, depart, arrivee,
		              stock, propagatio, degre_max, noeud_suivant);
			if (n == -1) {
			   break;
			}
		 } 
	  }	 
   }
}

///////////////////////////////////////////////////////////////////////////////////////////////:

int recursion(Matrice& matAdj, int& n,int& ligne,Vector& visited, int& degre, 
              Vecteur& depart, Vecteur& arrivee, Vecteur& stock, Matrice& propagatio,
              int& degre_max, int& noeud_suivant)
{
   if (depart[noeud_suivant] == -1){
      if (arrivee[0] != -1){
	     stock[degre_max] = degre;
	     ligne = arrivee[0];
	     degre = 0;
	     ++degre_max;
	     noeud_suivant = 1;
		 Vecteur clearing(n, -1);
		 depart.swap(clearing);
		 propagation(matAdj, n, ligne, visited, degre, arrivee, depart, stock, propagatio, 
		             degre_max, noeud_suivant);
	  }else { 
	     n = -1;
		 return n;
	  }
   }else {
	  ligne = depart[noeud_suivant];
	  ++noeud_suivant;
	  propagation(matAdj, n, ligne, visited, degre, depart, arrivee, stock, propagatio,
	              degre_max, noeud_suivant);
   }	
   return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////:
