#include <iostream>
using namespace std;

struct No {
	float dado;
	struct No *prox;
};

struct Fila {
	No *ini;
	No *fim;
};

struct Guiche {
	int id;
	Fila *senhasAtendidas;
};

struct Lista {
	Guiche *dado;
	struct Lista *prox;
};

Lista* initL() {
	return NULL;
}

Lista* insert(Lista* lista, Guiche* i)
{
	Lista* novo = new Lista();
	novo->dado = i;
	novo->prox = lista;
	return novo;
}

int isEmpty(Lista* lista)
{
	return (lista == NULL);
}

void print(Lista* lista)
{
	Lista* aux = lista;
	
	while (aux != NULL)
	{
		cout << "Valor: " << aux->dado << endl;
		aux = aux->prox;
	}
}

int count(Lista* lista)
{
	Lista* aux = lista;
	int c = 0;
	
	while (aux != NULL)
	{
		c++;
		aux = aux->prox;
	}
	return c;
}

Lista* find(Lista* lista, int i)
{
	Lista* aux = lista;
	
	while (aux != NULL && aux->dado->id != i)
	{
		aux = aux->prox;
	}
	return aux;
}

Fila* init() {
	Fila *f = new Fila;
	f->ini = NULL;
	f->fim = NULL;
	return f;
}

int isEmpty(Fila *f) {
	return (f->ini == NULL);
}

int count(Fila *f) {
	int qtde = 0;
	No *no;
	no = f->ini;
	while(no != NULL) {
		qtde++;
		no = no->prox;
	}
	return qtde;
}

void print(Fila *f) {
	No *no;
	no = f->ini;
	cout << "------------" << endl;
	while(no != NULL) {
		cout << no->dado << endl;
		no = no->prox;
	}
	cout << "------------" << endl;
}

void freeFila(Fila *f) {
	No *no = f->ini;
	while (no != NULL) {
		No *temp = no->prox;
		free(no);
		no = temp;
	}
	free(f);
}

void enqueue(Fila *f, float v) {
	No *no = new No;
	no->dado = v;
	no->prox = NULL;
	if (isEmpty(f)) {
	   f->ini = no;
	}
	else {
		f->fim->prox = no;
	}
	f->fim = no;
}

float dequeue(Fila *f) {
	float ret;
	if (isEmpty(f)) {
		ret = -1;
	}
	else {
		No *no = f->ini;
		ret = no->dado;
		f->ini = no->prox;
		if (f->ini == NULL) {
			f->fim = NULL;
		}
		free(no);
	}
	return ret;
}

Guiche* criaGuiche(int id) {
	Guiche *g = new Guiche();
	Fila *f = new Fila();
	f = init();
	g->id = id;
	g->senhasAtendidas = f;
	return g;
}

int main(int argc, char** argv)
{
	int selected = 1;
	Fila *senhasGeradas;
	Lista *guiches;
	Guiche *guiche; 
	Lista *gFind;
	guiches = initL();
	senhasGeradas = init();
	int id;
	int total = 0;
	
	while(selected != 0){
		
		cout << "0| Sair" << endl;
		cout << "1| Gerar senha" << endl;
		cout << "2| Abrir guiche" << endl;
		cout << "3| Realizar atendimento" << endl;
		cout << "4| Listar senhas atendidas" << endl;
		cout << "Senhas esperando: " << count(senhasGeradas) << endl;
		cout << "Quantidade de guiches abertos: " << count(guiches) << endl;
		cin >> selected;
		system("cls");
		switch(selected)
		{
	   	case 0:
	   		if(!isEmpty(senhasGeradas)){
				   selected = 3;
				   cout << "Nao foi possivel sair, pois ainda existem senhas na fila" << endl;
				   break;
			   }
  	        cout << "Senhas atendidas: " << total << endl;
	  		cout << "Saindo..." << endl;
	  		break;
		case 1:
			if(isEmpty(senhasGeradas)){
				enqueue(senhasGeradas, 1);
				cout << "Senha: 1" << endl;
				break;
			}
			enqueue(senhasGeradas, senhasGeradas->fim->dado + 1);
			cout << "Senha: " << senhasGeradas->fim->dado << endl;
		   	break;
		case 2:
			if(isEmpty(guiches)){
				guiche = criaGuiche(1);
				guiches = insert(guiches, guiche);
				cout << "guiche criado com id: " << guiches->dado->id << endl;
				break;
			}
			guiche = criaGuiche(guiches->dado->id + 1);
			guiches = insert(guiches, guiche);
			cout << "guiche criado com id: " << guiches->dado->id << endl;
		   	break;
 		case 3:
 			if(!isEmpty(senhasGeradas)){
 				cout << "Coloque o id do guiche: " << endl;
 				cin >> id;
 				gFind = find(guiches, id);
 				if(gFind != NULL){
					enqueue(gFind->dado->senhasAtendidas, dequeue(senhasGeradas));
					cout << "Senha " << gFind->dado->senhasAtendidas->fim->dado << " Atendida" << endl;
					total++;
					break;
				 }
                cout << "Guiche nao foi encontrado" << endl;
				break;
			}
			cout << "Nenhuma senha para ser atendida" << endl;
		 	break;
		case 4:
			cout << "qual o id do seu guiche?" << endl;
 			cin >> id;
 			gFind = find(guiches, id);
 			if(gFind != NULL) {
				 cout << "Senhas atendidas:" << endl;
				 print(gFind->dado->senhasAtendidas);
				 cout << "Total de " << count(gFind->dado->senhasAtendidas) << " senhas atendidas" << endl;
				 break;
			}
			cout << "Guiche nao encontrado!" << endl; 
			break;   
		default:
		   	cout << "Erro! valor invalido" << endl;
		   	break;
		}
		system("pause");
		system("cls");
	}
	
	return 0;
}
