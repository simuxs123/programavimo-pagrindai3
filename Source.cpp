#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
const int Cn = 50;
const char Ckain[] = "kainos.txt";
const char Cpard[] = "pardavimai.txt";
const char Crez[] = "ataskaita.txt";
struct Uzdarbis {
	double ukininkas;
	double jonas;
};
struct Prekes {
	string pv;
	int kiekis;
	double kaina;
	int parduota;
	int neparduota;
	Uzdarbis pelnas;
};

void ivedimas(const char fv[], Prekes sar[], int& n);
void isvedimas(const char fv[], Prekes sar[], int n);
void KiekParduotaIrUzdirbta(Prekes sar[], Prekes sarPard[], int n, int m);
void KiekNeparduota(Prekes sar[], int n);
int main() {
	Prekes prekes[Cn];
	Prekes parduotos[Cn];
	Uzdarbis pelnas;
	int kiek;
	int kiekPard;
	ivedimas(Ckain, prekes, kiek);
	ivedimas(Cpard, parduotos, kiekPard);
	KiekParduotaIrUzdirbta(prekes, parduotos, kiek, kiekPard);
	KiekNeparduota(prekes, kiek);
	isvedimas(Crez, prekes, kiek);
	return 0;
}

void ivedimas(const char fv[], Prekes sar[], int& n) {
	ifstream fd(fv);
	char pav[16];
	fd >> n;
	fd.ignore();
	for(int i=0; i<n && !fd.eof(); i++) {
		fd.get(pav, 16);
		sar[i].pv = pav;
		fd >> sar[i].kiekis >> sar[i].kaina;
		fd.ignore();
	}
	fd.close();
}
void isvedimas(const char fv[], Prekes sar[], int n) {
	ofstream fr(fv);
	double ukininkoPelnas = 0;
	double jonoPelnas = 0;
	fr << "Parduota:" << endl;
	for (int i = 0; i < n; i++) 
		fr <<sar[i].pv << " "<< sar[i].parduota<< endl;
	fr << "Liko neparduota:" << endl;
	for (int i = 0; i < n; i++) {
		if(sar[i].neparduota!=0)
			fr << sar[i].pv << " " << sar[i].neparduota << endl;
		ukininkoPelnas += sar[i].pelnas.ukininkas;
		jonoPelnas += sar[i].pelnas.jonas;
	}
	fr << fixed << setprecision(2);
	fr << "Ukininkas uzdirbo: " << ukininkoPelnas << endl;
	fr << "Jono pelnas: " << jonoPelnas << endl;
	fr.close();
}
void KiekParduotaIrUzdirbta(Prekes sar[], Prekes sarPard[], int n, int m) {
	int pardave = 0;
	for (int i = 0; i < n; i++) {
		sar[i].pelnas.jonas = 0;
		sar[i].pelnas.ukininkas = 0;
		for (int j = 0; j < m; j++) {
			if (sar[i].pv == sarPard[j].pv) {
				pardave += sarPard[j].kiekis;
				if (sar[i].kaina < sarPard[j].kaina) {
					sar[i].pelnas.jonas += (sarPard[j].kaina - sar[i].kaina) * sarPard[j].kiekis; //skaiciuoja Jono pelna uzdirbta uz kiekviena preke
					sar[i].pelnas.ukininkas += sar[i].kaina * sarPard[j].kiekis; //skaiciuoja ukininko pelna uz kiekviena preke, kur Jonas pardave uz didesne kaina
				}
				else sar[i].pelnas.ukininkas += sarPard[j].kaina*sarPard[j].kiekis;	//skaiciuoja ukininko pelna uz kiekviena preke, kur Jonas pardave uz ukininko kaina arba mazesne			
			}
		}
		sar[i].parduota = pardave;
		pardave = 0;
	}
}
void KiekNeparduota(Prekes sar[], int n) {
	for (int i = 0; i < n; i++) {
		sar[i].neparduota = sar[i].kiekis - sar[i].parduota;
	}
}

