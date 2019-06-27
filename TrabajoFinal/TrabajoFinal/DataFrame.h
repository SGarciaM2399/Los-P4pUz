#pragma once
#include<iostream>
#include <sstream>
#include <fstream>
#include<conio.h>
#include <vector>
#include<string>
#include<map>
#include "AVLTree.h"
namespace Pandas {

	typedef pair<string, Structures::Col*> par;
	class DF {
		Structures::colmap cols;
		Structures::AVLTree<Structures::Row*, string>* idx;
		vector<Structures::Row*> rows;
	public:
		void quicksort(int* v, int izq, int der) {
			int i = izq, j = der, aux, p = v[(izq + der) / 2];
			while (i <= j) {
				while (v[i] < p)i++;
				while (v[j] > p)j--;
				if (i <= j) {
					aux = v[i];
					v[i] = v[j];
					v[j] = aux;
					i++; j--;
				}
			}
			if (izq < j)
				quicksort(v, izq, j);
			if (i < der)
				quicksort(v, i, der);
		}
		void ordenar(string colname) {
			DF nDF = DF(cols);



		}
		Structures::Col*& operator[](string name) {
			return cols[name];
		}
		string operator [](int idx) {
			if (idx < rows.size()) {

				return rows[idx]->imprimir();
			}
			else return "Fila no encontrada.";
		}
		DF(Structures::colmap xd) {
			this->cols = xd;
			int length = xd.begin()->second->data.size();
			for (int i = 0; i < length; i++)
			{
				rows.push_back(new Structures::Row(cols, i));
			}
		}

		DF select(vector<string> colNames) {
			Structures::colmap nCols;
			for (auto cn : colNames) {
				nCols[cn] = cols[cn];
			}
			DF nDF = DF(nCols);
			nDF.rows = this->rows;
			return nDF;
		}
		bool comp(string nc1, string op1, string val, Structures::Row* r) {

			if (op1 == "<") {

				if (cols[nc1]->type == "float") {
					float j = Structures::Col::toFloat(r->getData(nc1));
					float v = Structures::Col::toFloat(val);
					return j < v;

				}
				if (cols[nc1]->type == "string") {
					return r->getData(nc1) < val;

				}

			}
			if (op1 == ">") {

				if (cols[nc1]->type == "float") {
					float j = Structures::Col::toFloat(r->getData(nc1));
					float v = Structures::Col::toFloat(val);
					return j > v;

				}
				if (cols[nc1]->type == "string") {
					return r->getData(nc1) > val;

				}

			}
			if (op1 == "=") {

				if (cols[nc1]->type == "float") {
					float j = Structures::Col::toFloat(r->getData(nc1));
					float v = Structures::Col::toFloat(val);
					return j == v;

				}
				if (cols[nc1]->type == "string") {
					return r->getData(nc1).compare(val) == 0;

				}

			}

			if (op1 == "!=") {

				if (cols[nc1]->type == "float") {
					float j = Structures::Col::toFloat(r->getData(nc1));
					float v = Structures::Col::toFloat(val);
					return j != v;

				}
				if (cols[nc1]->type == "string") {
					return r->getData(nc1).compare(val) != 0;

				}

			}

			if (op1 == "=") {

				if (cols[nc1]->type == "float") {
					float j = Structures::Col::toFloat(r->getData(nc1));
					float v = Structures::Col::toFloat(val);
					return j == v;

				}
				if (cols[nc1]->type == "string") {
					return strcmp(r->getData(nc1).c_str(), val.c_str());

				}

			}
			if (op1 == "/i") {
				char d1 = r->getData(nc1)[0];
				char d2 = val[0];
				return d1 == d2;
			}

			if (op1 == "/f") {
				char d1 = r->getData(nc1)[r->getData(nc1).size() - 1];
				char d2 = val[val.size() - 1];
				return d1 == d2;
			}
			if (op1 == "/c") {

				return r->getData(nc1).find(val) != string::npos;

			}
			if (op1 == "/nc") {
				return (r->getData(nc1).find(val) == string::npos);
			}


		}
		DF filter(string nc1, string op1, string val1, string nc2 = " ", string op2 = "", string val2 = "") {
			Structures::colmap nCols;
			nCols = this->cols;

			//vector<Row*> nRows;
			DF nDF = DF(nCols);

			for (auto r : this->rows) {
				if (comp(nc1, op1, val1, r) && comp(nc2, op2, val2, r)) {
					nDF.rows.push_back(r);
				}
			}
			return nDF;
		}


		DF sort(string colname) {
			Structures::colmap nCols;
			nCols = this->cols;
			DF nDF = DF(nCols);
			nDF.rows = this->rows;
			return nDF;
		}
		DF() {}
		void index(string colname) {
			//	AVLTree<Row*, string>* t = new AVLTree<Row*, string>();
			//	for (auto row : this->rows) {
			//		t->Add(row);
			//	}
			//	this->idx = t;

				//AVLTree<int, string>* t = new AVLTree<int, string>();

		}

		void imprimir() {
			cout << "indice\t";
			for (auto x : this->cols) {
				cout << x.first << "\t";
			}
			cout << endl;
			for (auto f : this->rows)
			{
				cout << f->Idx() << "\t";
				for (auto d : this->cols)
				{
					cout << f->getData(d.first) << "\t";
				}
				cout << endl;
			}

		}
		void save_datafile(string filename) {
			ofstream fout;
			fout.open(filename);
			if (fout.is_open()) {

				for (auto f : rows)
				{
					for (auto c : cols)
					{
						fout << f->getData(c.first) << ",";
					}
					fout << endl;
				}
			}
			fout.close();
		}

		static DF read_csv(string filename) {
			ifstream fin;
			string linea;
			string palabra;
			fin.open(filename.c_str());
			vector<string> l[1000];

			if (fin.fail()) {
				return DF();
			}

			else {
				const int ncol = nfilas_csv(filename);
				while (fin >> linea) {
					stringstream s(linea);
					int i = 0;

					while (getline(s, palabra, ',')) {

						l[i].push_back(palabra);
						i++;

					}
				}

				Structures::colmap pr;
				for (int i = 0; i < ncol; i++)
				{
					pr.insert(par(to_string(i), new Structures::Col(to_string(i), l[i])));
				}
				fin.close();
				return DF(pr);
			}
		}
	private:
		static int nfilas_csv(string filename) {
			ifstream fin;
			string linea, palabra;

			int cont = 0;
			fin.open(filename.c_str());
			if (fin.fail()) {

			}
			else {
				while (!fin.eof()) {
					cont++;
					getline(fin, palabra, '\n');

				}
			}
			fin.close();
			int cont2 = 0;
			fin.open(filename.c_str());

			if (fin.fail()) {

			}
			else {
				while (fin >> linea) {
					stringstream s(linea);

					while (getline(s, palabra, ',')) {
						cont2++;


					}
				}
			}
			return cont2 / cont;
		}
	};
};