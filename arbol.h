#include<vector>
#include "alien.h"
//#include <string>
#ifndef ARBOL_H
#define ARBOL_H

#include <string>
#include <sstream>
#include <iostream>

 class SplayTree;


class Node {


private:

	//Valor del nodo, a veces nombrado como "key"

	//Apuntadores a nodos, como izquierda, derecha o al padre.

	Node* succesor();
  //Busca cual sera el sucesor, me parece que solo se usa en remove.
	Node* rot_right(Node*);

	//Las rotaciones son desde la perspectiva del padre.
	Node* rot_left(Node*);

public:
	Node(Alien);
  Alien alien;
  Node *left, *right, *parent;
	/*Constructor donde solo pasamos valor, resulta en un nodo
	que no tiene ningun hijo.*/
	Node(Alien, Node*, Node* ,Node*);
	//Constructor donde tambien asignamos hijos.
	Node* add(Alien);
	//Auxiliar de la funcion add del splay tree.
	Node* find(Alien);
	//Auxiliar de la funcion find del splay tree.
	Node* remove(Alien);
	//Auxiliar de la funcion remove del splay tree.
	void removeChilds();
	//Funcion auxiliar para el destructor?
	void inorder(std::stringstream&) /*const*/;

	void print_tree(std::stringstream&) /*const*/;
  //Puedo modificar la impresion del arbol para que imprima los nombres.
	void preorder(std::stringstream&) /*const*/;

	Node* splay(Node*, Node*);
  //raiz y el nodo que quieres llegar.

	friend class SplayTree;
};


Node::Node(Alien alien) : alien(alien), left(nullptr), right(nullptr),
parent(nullptr) {}


Node::Node(Alien alien, Node *le, Node *ri, Node *p)
	: alien(alien), left(le), right(ri), parent(p) {}


Node* Node::add(Alien alien) {
  int value = this->alien.getVecesElegido();
  int val = alien.getVecesElegido();
  //int value2 = getBatallasGanadas();
  //int val2 = alien.getBatallasGanadas();
  //int value3 = getTotal();
  //int val3 = alien.getTotal();

  if (value == val){
    value = this->alien.getBatallasGanadas();
    val = alien.getBatallasGanadas();
    if (value == val){
      value = this->alien.getTotal();
      val = alien.getTotal();
    }
  }


	if (val < value){
		//En la primera iteracion verifica si raiz es mas grande, en base a eso
		//sigue aplicando recursividad.
		if (left != nullptr){
			//Nos ayuda a encontrar un posible caso base.
			return left->add(alien);
			//Sea cual sea el return que se usara al final, se encadenaran para
			//regresar un apuntador del nuevo valor, el cual se usara el splay.
		}
		else {
			left = new Node (alien,nullptr,nullptr,this);
			return left;
		}
	}else {
		if(right != nullptr){
			return right->add(alien);
		}
		else {
			right = new Node(alien,nullptr,nullptr,this);
			return right;
		}
		}

	}



Node* Node::find(Alien alien) {
  //std::cout<<"Comparando a "<<this->alien.getNombre()<<" con "<<alien.getNombre()<<"\n\n";
  int value = this->alien.getVecesElegido();
  int val = alien.getVecesElegido();
  //std::cout<<"VecesElegido1: "<<value<<" y VE2: "<<val<<"\n\n";

  if (value == val){
    //std::cout<<"Igual numero de veces elegido\n\n";
    value = this->alien.getBatallasGanadas();
    val = alien.getBatallasGanadas();
    if (value == val){
      //std::cout<<"Igual numero de batallas ganadas\n\n";
      value = this->alien.getTotal();
      val = alien.getTotal();
    }
  }
  //std::cout<<"Comparando valor: "<<value<<" y val: "<<val<<"\n\n";
	//Va a regresar o un apuntador al nodo que busco o a donde debia estar.
	if (val == value && this->alien.getNombre() == alien.getNombre()){
    //std::cout<<"\n\nCoincidencia exacta: "<<this->alien.getNombre()<<"\n\n";
		return this;
	}
	else if(val < value){
		if(left != nullptr ){
			//Revisamos si llegamos al limite o si podiamos seguir.
			return left->find(alien);
		}
    //std::cout<<"\n\nRetornando a "<<this->alien.getNombre()<<"\n\n";
		return this;
	}
	else{
		if(right !=nullptr){
			return right->find(alien);
		}
    //std::cout<<"\n\nRetornando a "<<this->alien.getNombre()<<"\n\n";
		return this;
	}
  //std::cout<<"\n\nRetornando a "<<this->alien.getNombre()<<"\n\n";
}


Node* Node::succesor() {

	Node *le, *ri;

	le = left;
	//No se usa para nada?
	ri = right;


	if (right->left == nullptr) {
		right = right->right;
		//Como no hay sucesor a la izquierda, entonces el hijo de la derecha
		//es el succesor
		ri->right = nullptr;
		//Desconectamos de su sucesor a la derecha debido a que lo definiremos
		//fuera de esta funcion en el remove de SplayTree.
		return ri;
	}

	Node *parent, *child;
	//En caso de que si hubiera hijos, buscaremos llegar hasta el extremo
	//viajando en linea recta.
	parent = right;
	child = right->left;
	while (child->left != nullptr) {
		//Mientras no lleguemos hasta el extremo viajando siempre por la izquierda.
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = nullptr;
	//Desconectamos su hijo de la derecha.
	return child;
}


Node* Node::remove(Alien alien) {
    //Debo verificar el caso donde tiene ambos hijos.
    //En los demas, se que se debe mandar el padre o hipotetico padre al splay.

    bool encontrado = false;
		Node* found = this->find(alien);
		//std::cout<<"\n\naaaaa"<<found->alien.getNombre()<<"\n\n";
		//Node* root = splay(this,found);
    // Verificar si el valor a eliminar estaba en la lista y por lo tanto
		//ahora en la raiz.

    if (found->alien.getNombre() == alien.getNombre()) {
        encontrado = true;
        Node* toDelete = found;
				//std::cout<<"\n\neeeeee"<<toDelete->value<<"\n\n";
				//std::cout<<"Bandera\n\n";
				//Hacemos una especie de copia para tener algo que regresar al final.
				//Node* succ = found->succesor();


				if(found->left&&found->right){
					//Si el nodo a eliminar tiene ambos hijos
					found =toDelete->succesor();
					if (found != nullptr) {
							found->left = toDelete->left;
							found->right = toDelete->right;
							found->parent = nullptr;
							if(found->left)
								found->left->parent = found;
							if(found->right)
								found->right->parent = found;
					}

					//delete root;
					//root = succ;
					if(toDelete->parent->left&&
						toDelete->parent->left->alien.getNombre()==toDelete->alien.
            getNombre()){
						toDelete->parent->left = found;

					}
					else{
						toDelete->parent->right = found;

					}
				}
				else if(found->right){
					//Si solo tiene el hijo derecho
					found = toDelete->right;
					toDelete->right = 0;

					if(toDelete->parent->left&&
						toDelete->parent->left->alien.getNombre()==toDelete->alien.
            getNombre()){
						toDelete->parent->left = found;

					}
					else{
						toDelete->parent->right = found;

					}


				}
				else if(found->left){
					//std::cout<<"\n\nCaso correcto\n\n";
					//Si solo tiene el hijo izquierdo
					found = toDelete->left;
					//std::cout<<"\n\nNodo raiz = "<<found->value<<"\n\n";
					toDelete->left = 0;
					if(toDelete->parent->left&&
						toDelete->parent->left->alien.getNombre()==toDelete->alien.
            getNombre()){

						//std::cout<<"\n\nConfirmamos que era hijo izq\n\n";
						toDelete->parent->left = found;
					}
					else{
						toDelete->parent->right = found;
					}

				}
				else{
					//Si no tiene ningun hijo
					if(toDelete->parent->left&&
						toDelete->parent->left->alien.getNombre()==toDelete->alien.
            getNombre()){
						toDelete->parent->left = nullptr;
					}
					else{
						toDelete->parent->right = nullptr;
					}

				}
				if(toDelete->parent->right != nullptr ||
          toDelete->parent->left != nullptr){
					found->parent = toDelete->parent;
				}
				toDelete->parent = nullptr;



				delete toDelete;
				//found = 0;
				}

        // Caso 1: No tiene hijo izquierdo
        /*if (succ->left == 0) {

            if (root != 0) {
                root->parent = 0;
            }
        }
        // Caso 2: No tiene hijo derecho
        else if (root->right == 0) {
            root = root->left;
            if (root != 0) {
                root->parent = 0;
            }
        }*/



          //  succ->left = found->left;
            //if (found->left != 0) {
              //  found->left->parent = succ;
            //}
            //
            //if (succ != 0) {
                //root->parent = 0;
            //}

         // Eliminar el nodo
				 //std::cout<<"\n\nNodo devuelto: "<<found->value<<"\n\n";
         if(encontrado){
           return found->parent;
         }
         else{
           return found;
         }
     // "Devolver la nueva raíz después de la eliminación"
}
  // Devolver la nueva raíz después de la eliminación



void Node::removeChilds() {
	if (left != nullptr) {
		left->removeChilds();
		delete left;
		left = nullptr;
	}
	if (right != nullptr) {
		right->removeChilds();
		delete right;
		right = nullptr;
	}
}


Node* Node::rot_right(Node* x){

	//std::cout<<"\nHaciendo zig con "<<x->alien.getNombre()<<"\n";
	//std::cout<<"\n\n"<<splay&.print_tree()<<"\n\n";
	Node *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left &&
      y->parent->left->alien.getNombre() == x->alien.getNombre())
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}


Node* Node::rot_left(Node* x){
	//std::cout<<"\nHaciendo zag con "<<x->alien.getNombre()<<"\n";
	//std::cout<<"\n\n"<<splay&.print_tree()<<"\n\n";
	Node *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left &&
      y->parent->left->alien.getNombre() == x->alien.getNombre())
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}


Node* Node::splay(Node* root, Node* x){
  //std::cout<<"Haciendo splay con "<<x->alien.getNombre()<<"\n\n";
  //Todos los getNombre() son un reemplazo de ->value.
	while(x->parent != nullptr){
    //Mientras no lleguemos a la raiz.
		if(x->parent->alien.getNombre() == root->alien.getNombre()){
      //Aqui notamos que estamos justo debajo de la raiz.
			if(x->parent->left &&
         x->parent->left->alien.getNombre() == x->alien.getNombre()){
        //Usamos el valor booleano del puntero para ver si apunta a la nada o a
        //un hijo, que luego verificamos si es x.
        //Ya sabemos que es hijo directo, esto revisa cual de ambos.
				rot_right(x->parent);
        //Resulta ser el izquierdo.
			}else{
				rot_left(x->parent);
        //Es el derecho.
        //Es confuso, yo aprendi a rotar con el nodo a hacer splay como inicio.
        //no con el padre de este.
			}
		}else{
			Node*p = x->parent; // parent
			Node*g = p->parent; // granparent
			if(p->left && g->left &&
				x->alien.getNombre() == p->left->alien.getNombre() &&
         p->alien.getNombre() == g->left->alien.getNombre()){
        //Verifica si pueden avanzar de dos en dos revisando si el padre y
        //abuelo tienen hijos en la izquierda, los cuales usara el nodo que
        //estamos subiendo para avanzar.
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->alien.getNombre() == p->right->alien.getNombre() &&
         p->alien.getNombre() == g->right->alien.getNombre()){
        //Lo mismo pero del otro lado, no tener el caso anterior no implica
        //que forzosamente tengamos este, por eso hay que verificar.
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->alien.getNombre() == p->left->alien.getNombre() &&
         p->alien.getNombre() == g->right->alien.getNombre()){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}


void Node::inorder(std::stringstream &aux) /*const*/ {
	if (left != nullptr) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << this->alien.getNombre();
	if (right != 0) {
		right->inorder(aux);
	}
}


void Node::print_tree(std::stringstream &aux) /*const*/ {
  //Creo que estoy siendo redundante al incluir los this.
  aux <<this->alien.getNombre()<<";";
  if (this->parent != nullptr){
		//aux <<this->alien.getNombre()<<";";
		aux << this->parent->alien.getNombre()<<";";
	}else{
    aux << " " << ";";
  }

	if (this->left != nullptr){
    aux <<this->left->alien.getNombre()<<";";
  }
    else{
      aux<<" "<<";";
    }
	if (right != nullptr){
    aux << this->right->alien.getNombre();
  }

	else{
    aux<<" ";
  }
  aux<<";\n";

	if (left != nullptr) {
		left->print_tree(aux);
	}
	if (right != nullptr) {
		right->print_tree(aux);
	}
}


void Node::preorder(std::stringstream &aux) /*const*/ {
	aux << this->alien.getNombre();
	if (left != nullptr) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}


class SplayTree {
private:


public:
	SplayTree();
	~SplayTree();
  Node *root;
	bool empty() const;
	void add(Alien);
	bool find(Alien);
	void remove(Alien);
	void removeAll();
	std::string inorder() /*const*/;
	std::string print_tree() /*const*/;
	std::string preorder() /*const*/;
};


SplayTree::SplayTree() : root(nullptr) {}


SplayTree::~SplayTree() {
	removeAll();
}


bool SplayTree::empty() const {
	return (root == nullptr);
}


void SplayTree::add(Alien alien) {
  //std::cout<<"\n\nAniadiendo a "<<alien.getNombre()<<"\n\n";

	if (root != nullptr) {
			Node* added = root->add(alien);
			root = root->splay(root,added);
	} else {
		root = new Node(alien);
	}
}


void SplayTree::remove(Alien alien) {
  //std::cout<<"\n\nRemoviendo a "<<alien.getNombre()<<"\n\n";
	if (root != nullptr) {
		if (alien.getNombre() == root->alien.getNombre()) {
			Node *succ = root->succesor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
					//Crei que estaban mal, pero es como decir: si existe hijo izq.
					//Y esto es lo que tiene que hacer en caso de que si.
						succ->left->parent = succ;
					if(succ->right)
					//Lo mismo con la derecha.
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} else {
			Node* p = root->remove(alien);
			root = root->splay(root,p);
		}
	}
}


void SplayTree::removeAll() {
	if (root != nullptr) {
		root->removeChilds();
	}
	delete root;
	root = nullptr;

}


bool SplayTree::find(Alien alien){
  //std::cout<<"\n\nBuscando a "<<alien.getNombre()<<"\n\n";
	if (root != 0) {
		Node* found = root->find(alien);
		root = root->splay(root,found);
		return (root->alien.getNombre() == alien.getNombre());
	} else {
		return false;
	}
}


std::string SplayTree::inorder() /*const*/ {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}


std::string SplayTree::print_tree() /*const*/ {
	std::stringstream aux;

	//aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	//aux << " ================================ \n";
	return aux.str();
}




std::string SplayTree::preorder() /*const*/ {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif /* SplayTree_H_ */
