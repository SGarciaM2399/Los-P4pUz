
#pragma once
#include<functional>
#include<algorithm>
using namespace std;
namespace Pandas {
	namespace Structures {
		template <typename T, typename R = T>
		class AVLTree {
			struct Node {
				T e;
				Node* l;
				Node* r;
				int h;
				Node(T e) :e(e), l(nullptr), r(nullptr), h(0) {}
				static int height(Node* n) {
					return n == nullptr ? -1 : n->h;
				}
				void updateh() {
					h = std::max(Node::height(l), Node::height(r) + 1);
				}
			};
			Node* root;
			int length;
			std::function<R(T)> key;
			void destroy(Node* n) {
				if (n != nullptr) {
					destroy(n->l);
					destroy(n->r);
					delete n;
				}
			}
			void rotAB(Node*& n) {
				Node* aux = n->l;
				n->l = aux->r;
				n->updateh();
				aux->r = n;
				n = aux;
				n->updateh();
			}
			T enorden(Node* n, function<R(T)> key) {
				this->key(enorden(n->l));
				this->key(enorden(n));
				this->key(enorden(n->r));
			}
			void rotBA(Node*& n) {
				Node* aux = n->r;
				n->r = aux->l;
				n->updateh();
				aux->l = n;
				n = aux;
				n->updateh();
			}
			void balance(Node *& n) {//-1 es igual a no existe
				/*int hl = Node ::(h->l);
				int hr = Node ::(h->r);
				if(hl-hr<-1)*/
				int delta = Node::height(n->l) - Node::height(n->r);
				if (delta < -1) {
					if (Node::height(n->r->l) > Node::height(n->h->r->r)) {
						rotAB(n->r);
					}
					rotAB(n);
				}
				else if (delta > 1) {
					if (Node::height(n->l->r) > Node::height(n->h->l->l)) {
						rotAB(n->l);
					}
					rotAB(n);
				}
			}
			void add(Node*& n, T e) {
				if (n == nullptr) {
					n = new Node(e);
					return;
				}
				else if (key(e) < key(n->e)) {
					add(n->l, e);
				}
				else {
					add(n->r, e);
				}
				balance(n);
				n->updateh();
			}
		public:
			AVLTree(std::function<R(T)> key = [](T a) {return a; }) :root(nullptr), length(0), key(key) {}
			~AVLTree() { destroy(root); }
			int Height() {
				return Node::height(root);
			}
			int size() {
				return length;
			}
			void Add(T e) {
				add(root, e);
				++length;
			}
			void InOrder(function<R(T)> key = this->key) {
				enorden(root, key);
			}
		};

		class Col {
		public:
			string type;
			vector<string> data;
			string name;
			string getData(int idx) {
				return data[idx];
			}
			static float toFloat(string x) {
				return stof(x);
			}
			void Type(string f) {
				if (f == "float" || f == "string") {
					type = f;

				}

			}
			Col(string name, vector<string> data, string type = "string") :name(name), data(data), type(type) {  }
		};
		typedef map<string, Col*>colmap;
		class Row {
			int idx;
			map<string, Col*> cols;
		public:
			int Idx() {
				return idx;
			}
			string imprimir() {
				string aux;
				ostringstream o(aux);
				o << "Indice: " << "\t";
				for (auto f : cols)
				{
					o << f.first << "\t" << f.second->getData(idx);
				}
				aux = o.str();
				return aux;

			}
			Row(map<string, Col*>&cols, int idx) :cols(cols), idx(idx) {}
			string getData(string name) {
				//return cols[getID(name)][index];
				return cols[name]->getData(idx);
			}
		};
	}

};