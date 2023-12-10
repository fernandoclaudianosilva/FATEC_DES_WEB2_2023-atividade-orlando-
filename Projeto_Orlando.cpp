#include <iostream>
#include <locale>
using namespace std;
	struct estoque{
int queijo;
int presunto;
int frango;
	};
	struct pedido{
		int numero_pedido=0;
		int pizza=0;
		int queijo=0;
		int frango=0;
		int vento=0;
		int coca=0;
		int pepsi=0;
	};
	struct node{
		node *proximo;
		node *anterior;
		pedido pedido;
	};
	struct fila{
		node *inicio;
		node *fim;
		int proxima_senha;
		int tamanho;
	};
	struct relatorio_vendas{
    int coca ;
    int pepsi;
    int pizza;
    int Frango;
    int Queijo;
    int vento;
};		
void inicializar(fila* fila, estoque* estoque,relatorio_vendas* relatorio) {
	relatorio->pizza=0;
	relatorio->coca=0;
    relatorio->pepsi=0;
    relatorio->Queijo=0;
    relatorio->Frango=0;
    relatorio->vento=0;
    fila->tamanho = 0;
    fila->proxima_senha = 1;
    fila->inicio = NULL;
    fila->fim = NULL;
    estoque->queijo = 50000;
    estoque->presunto = 20000;
    estoque->frango = 10000;
};
void adicionar_pedido(fila *fila){
	int rp,rp2;
	
	node *new_node = new node;
	
    if (new_node == NULL) {
        cerr << "Acabou a memoria. " << endl; 
        exit(1);
    }
		do
		{
				cout<<"Cardapio do Pastel:"<<endl;
				cout<<"1-Pizza"<<endl;
				cout<<"2-Queijo"<<endl;
				cout<<"3-Frango"<<endl;
				cout<<"4-Vento"<<endl;
				cout<<"5-Coca"<<endl;
				cout<<"6-pepsi"<<endl;
				cin>>rp;
				
			switch(rp){
			case 1:
					new_node->pedido.pizza++;
					break;
			
			case 2:
					new_node->pedido.queijo++;
					break;
			case 3:
					new_node->pedido.frango++;
					break;
			case 4:
					new_node->pedido.vento++;
					break;
			case 5:	
					new_node->pedido.coca++;
					break;
			case 6:
					new_node->pedido.pepsi++;
					break;
			}
			if (new_node->pedido.pizza + new_node->pedido.queijo + new_node->pedido.frango + new_node->pedido.vento< 1 )
       		{cout << "necessario pelo menos um pastel" << endl;
        	return;
        	};
        	
			cout<<"Quantidade de pedidos"<<endl;
			cout<<"Pizza "<<new_node->pedido.pizza<<endl;
			cout<<"Queijo "<<new_node->pedido.queijo<<endl;
			cout<<"Frango "<<new_node->pedido.frango<<endl;
			cout<<"Vento "<<new_node->pedido.vento<<endl;
			cout<<"Coca "<<new_node->pedido.coca<<endl;
			cout<<"Pepsi "<<new_node->pedido.pepsi<<endl;
			cout<<"Deseja finalizar(1)Deseja continuar seu pedido(2)"<<endl;
			cin>>rp2;
			}while(rp2 != 1);
	new_node->proximo = NULL;
    new_node->anterior = NULL;
    new_node->pedido.numero_pedido = fila->proxima_senha;
    fila->proxima_senha ++;
    cout<<"seu numero de pedido é: "<<new_node->pedido.numero_pedido	<<endl;
    
    if (fila->inicio == NULL) { //criando fila
        fila->inicio = new_node;
        fila->fim = new_node;
        fila->tamanho = fila->tamanho + 1;
        return;
    } 
    if (fila->tamanho == 1) {//adicionando um na fila
        fila->fim->proximo = new_node;
        new_node->anterior = fila->fim;
        fila->fim = new_node; 
        fila->tamanho = fila->tamanho + 1;
        return;
        
    } else {//chegando no ultumo
        node* aux = fila->fim;
        aux->proximo = new_node;
        new_node->anterior = aux;
        fila->fim = new_node; 
        fila->tamanho = fila->tamanho + 1;
        return;
    }
}
void finalizar_pedido (fila *fila, estoque* estoque){
	int senha = 0, qgdo = 0, confirmar = 0;
    bool encontrado = false;
    node *qgcliente = fila->inicio;

    cout << "digite a senha do cliente: ";
    cin >> senha;

    do
    {   
        if (senha == qgcliente->pedido.numero_pedido){
            encontrado = true;
            cout << "pastel de pizza: " << qgcliente->pedido.pizza << endl;
            cout << "pastel de queijo: " << qgcliente->pedido.queijo << endl;
            cout << "pastel de frango: " << qgcliente->pedido.frango << endl;
            cout << "pastel de vento: " << qgcliente->pedido.vento << endl;
            cout << "pepsi: " << qgcliente->pedido.pepsi << endl;
            cout << "coca_cola: " << qgcliente->pedido.coca << endl;

            cout << "digite 1 para confirmar / outro valor para voltar " << endl;
            cin >> confirmar;

            if (confirmar == 1)
            { 

                estoque->frango = estoque->frango - 50 * qgcliente->pedido.frango;
                estoque->presunto = estoque->presunto - 30 * qgcliente->pedido.pizza;
                estoque->queijo = estoque->queijo - (30 * qgcliente->pedido.pizza) - (50 * qgcliente->pedido.queijo);

                if (qgcliente == fila->inicio) {
                    fila->inicio = qgcliente->proximo;
                    if (fila->inicio != NULL) {
                        fila->inicio->anterior = NULL;
                    }
                } else if (qgcliente == fila->fim) {
                    fila->fim = qgcliente->anterior;
                    fila->fim->proximo = NULL;
                } else {
                    qgcliente->anterior->proximo = qgcliente->proximo;
                    qgcliente->proximo->anterior = qgcliente->anterior;
                }

                delete qgcliente;
                fila->tamanho--;
                
                return;

            }else{
                return;
            } 
            
        }

        qgcliente = qgcliente->proximo;
        qgdo ++;
        
    }while(qgdo < fila->tamanho);

    if (encontrado == false)
    {
        cout << "cliente nao existe" << endl << endl;
    }

    return;
};
void mostrar_estoque(estoque estoque){

    
    cout << "estoque atual" << endl;
    cout << "queijo: " << estoque.queijo <<  endl;
    cout << "presunto: " << estoque.presunto <<  endl;
    cout << "frango: " << estoque.frango <<  endl << endl;

    return;
    
};
void alterar_pedido(fila *fila){

    int senha = 0, resposta_alterar = 0;
    bool encontrado = false;
    node *qgcliente = fila->inicio;

    cout << "Digite a senha do cliente que deseja alterar o pedido: ";
    cin >> senha;

    while (qgcliente != NULL) {
        if (senha == qgcliente->pedido.numero_pedido) {
            do {
                encontrado = true;
                cout << "Alterar pedido:" << endl;
                
                cout << "1 pastel de pizza: "<< endl;
                cout << "2 pastel de queijo: "<< endl;
                cout << "3 pastel de frango: "<< endl;
                cout << "4 pastel de vento: " << endl;
                cout << "5 pepsi: " << endl;
                cout << "6 coca_cola: "<< endl;
                cout << "7 Confirmar" << endl;
                cin >> resposta_alterar;

                switch (resposta_alterar) {
                case 1:

                    cout << "você adicionou um pedido de pizza " << endl;
                    qgcliente->pedido.pizza++;

                    break;

                case 2:

                    cout << "você adicionou um pedido de queijo " << endl;
                    qgcliente->pedido.queijo++;

                    break;

                case 3:

                    cout << "você adicionou um pedido de frango " << endl;
                    qgcliente->pedido.frango++ ;

                    break;

                case 4:

                    cout << "você adicionou um pedido de vento "<< endl;
                    qgcliente->pedido.vento++ ;

                    break;
                case 5:
                    cout << "você adicionou uma pepsi "<<endl;
                    qgcliente->pedido.pepsi++ ;
                break;
            
                case 6:
                    cout << "você adicionou uma coca ";
                    qgcliente->pedido.coca++ ;
                break;

                }

            

        } while (resposta_alterar != 7);
        }

        qgcliente = qgcliente->proximo;
    }

    if (!encontrado) {
        cout << "Cliente não encontrado ou não existe" << endl << endl;
    }
}
void relatorio_final(fila* fila, estoque* estoque, relatorio_vendas* relatorio) {
    node* atual = fila->inicio;
    while (atual != NULL) {
        relatorio->coca += atual->pedido.coca;
        relatorio->pepsi += atual->pedido.pepsi;
        relatorio->Queijo += atual->pedido.queijo;
        relatorio->Frango += atual->pedido.frango;
        relatorio->pizza += atual->pedido.pizza;
        relatorio->vento += atual->pedido.vento;

        atual = atual->proximo;
    }
    cout << "BEBIDAS" << endl;
    cout << "========" << endl;
    cout << "Coca-cola " << relatorio->coca << " vendidas" << endl;
    cout << "Pepsi " << relatorio->pepsi << " vendidas" << endl;

    cout << "PASTEL" << endl;
    cout << "======" << endl;
    cout << "Pastel de Frango: " << relatorio->Frango << " pedidos no dia" << endl;
    cout << "Pastel de Queijo: " << relatorio->Queijo << " pedidos no dia" << endl;
    cout << "Pastel de Pizza: " << relatorio->pizza << " pedidos no dia" << endl;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	fila fila_pastel;
	node atual;
	estoque estoque_ingredientes;
	relatorio_vendas relatorio;
	int resposta;

	inicializar(&fila_pastel, &estoque_ingredientes,&relatorio);
	do{
		cout<<"Olá bem vindo a pastelario do marselão " << endl;
		cout<<"O que desejas?"<<endl;
		cout<<"1-fazer pedido"<<endl;
		cout<<"2-editar pedido"<<endl;
		cout<<"3-entregar pedido"<< endl;
		cout<<"4-mostrar estoque"<<endl;
		cout<<"5-relatorio"<<endl;
		cout<<"6-sair"<<endl;
		
		cin>>resposta;
	switch(resposta){
		case 1:{
		adicionar_pedido(&fila_pastel);
            break;

		}case 2:
						int teste,qgnumero_pedido,qgpizza,qgqueijo,qgfrango,qgvento,qgpepsi,qgcoca;//qg quebra galho kkkk obrigado pela dica orlando
			        cout << "Digite o numero do seu pedido";
                    cin >> qgnumero_pedido;
                    cout << "Digite a quantidade de pastel de piza";
                    cin >> qgpizza;
                    cout << "Digite a quantidade de pastel de queijo";
                    cin >> qgqueijo;
                    cout << "Digite a quantidade de pastel de frango";
                    cin >> qgfrango;
                    cout << "Digite a quantidade de pastel de vento";
                    cin >> qgvento;
                    cout << "Digite a quantidade de pepsi";
                    cin >> qgpepsi;
                    cout << "Digite a quantidade de coca";
                    cin >> qgcoca;
                    alterar_pedido(&fila_pastel);
                break;
            case 3:
				finalizar_pedido (&fila_pastel,&estoque_ingredientes);         
				break;
			case 4:
				mostrar_estoque(estoque_ingredientes);
				break;
			case 5:
				relatorio_final(&fila_pastel, &estoque_ingredientes,&relatorio);
				break;
			
			}
	}while(resposta != 6);
	return 0;
}
