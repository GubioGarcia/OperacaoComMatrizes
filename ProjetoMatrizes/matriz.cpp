#include "matriz.h"

namespace ggs{

    Matriz::Matriz(int quantLinhas, int quantColunas):
        quantidadeDeLinhas(0), quantidadeDeColunas(0), pMatriz(0)
        {
            if(quantLinhas<=0) throw QString("Quantidade de Linhas deve ser positiva");
            if(quantColunas<=0) throw QString("Quantidade de Colunas seve ser positiva");
            try{
                pMatriz = new int[quantLinhas*quantColunas];
            }catch(std::bad_alloc&){
                throw QString("Não há espaço na memória");
            }
            quantidadeDeLinhas = quantLinhas;
            quantidadeDeColunas = quantColunas;
        }


    Matriz::~Matriz(){
        if(pMatriz) delete[] pMatriz;
    }


    int Matriz::getQuantidadeDeLinhas() const
    {
        return quantidadeDeLinhas;
    }


    int Matriz::getQuantidadeDeColunas() const
    {
        return quantidadeDeColunas;
    }


    void Matriz::setElemento(int elemento, int linha, int coluna)const{
        if(linha<0 || linha>=quantidadeDeLinhas) throw QString("Linha fora do intervalo valido");
        if(coluna<0 || coluna>=quantidadeDeColunas) throw QString("Coluna fora do intervalo valido");
        int pos = linha*quantidadeDeColunas+coluna;
        *(pMatriz+pos) = elemento;
    }


    int Matriz::getElemento(int linha, int coluna)const{
        if(linha<0 || linha>=quantidadeDeLinhas) throw QString("Linha fora do intervalo valido");
        if(coluna<0 || coluna>=quantidadeDeColunas) throw QString("Coluna fora do intervalo valido");
        int pos = linha*quantidadeDeColunas+coluna;
        return *(pMatriz+pos);
    }

    QString Matriz::getMatriz()const{
        QString saida = "";
        for(int linha=0; linha < getQuantidadeDeLinhas(); linha++){
            for(int coluna = 0; coluna < getQuantidadeDeColunas(); coluna++){
                saida += QString::number(getElemento(linha,coluna));
                saida += "  ";
            }
            saida += "\n";
        }
        return saida;
    }


    Matriz *Matriz::adicionar(Matriz const*const objetoMatriz)const{
        if(this->getQuantidadeDeLinhas() != objetoMatriz->getQuantidadeDeLinhas() ||
           this->getQuantidadeDeColunas() != objetoMatriz->getQuantidadeDeColunas())
            throw QString("Só é possível adição entre Matriz de mesma ordem");
        try {
            Matriz *aux = new Matriz(quantidadeDeLinhas, quantidadeDeColunas);
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                    int elemento = this->getElemento(linha, coluna) + objetoMatriz->getElemento(linha, coluna);
                    aux->setElemento(elemento, linha, coluna);
                }
            }
            return aux;
        } catch(std::bad_alloc&){
            throw QString("Não há espaço na memória");
        } catch(QString &erro){
            throw QString("Erro");
        }
    }


    Matriz *Matriz::subtraiz(Matriz const*const objetoMatriz)const{
        if(this->getQuantidadeDeLinhas() != objetoMatriz->getQuantidadeDeLinhas() ||
           this->getQuantidadeDeColunas() != objetoMatriz->getQuantidadeDeColunas())
            throw QString("Só é possível subtração entre Matriz de mesma ordem");
        try {
            Matriz *aux = new Matriz(quantidadeDeLinhas, quantidadeDeColunas);
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                    int elemento = this->getElemento(linha, coluna) - objetoMatriz->getElemento(linha, coluna);
                    aux->setElemento(elemento, linha, coluna);
                }
            }
            return aux;
        } catch(std::bad_alloc&){
            throw QString("Não há espaço na memória");
        } catch(QString &erro){
            throw QString("Erro");
        }
    }


    Matriz *Matriz::multiplicar(Matriz const*const objetoMatriz)const{
        if(this->getQuantidadeDeColunas() != objetoMatriz->getQuantidadeDeLinhas())
            throw QString("Não é possível multiplicação entre as matrizes");
        try {
            Matriz *aux = new Matriz(this->getQuantidadeDeLinhas(), objetoMatriz->getQuantidadeDeColunas());
            int elemento = 0;
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<objetoMatriz->quantidadeDeColunas; coluna++){
                    for(int i=0; i<this->quantidadeDeColunas; i++){
                        elemento = elemento + (this->getElemento(linha, i) * objetoMatriz->getElemento(i, coluna));
                        aux->setElemento(elemento, linha, coluna);
                    }
                    elemento = 0;
                }
            }
            return aux;
        } catch(std::bad_alloc&){
            throw QString("Não há espaço na memória");
        } catch(QString &erro){
            throw QString("Não é possível multiplicação entre as matrizes");
        }
    }


    Matriz *Matriz::calcularPotencia(int expoente)const{
        if(this->getQuantidadeDeLinhas() != this->getQuantidadeDeColunas())
            throw QString("Só é possível Potenciação com matriz quadrada");
        if(expoente < 0) throw QString("Expoente deve ser positivo");
        try {
            Matriz *aux = new Matriz(quantidadeDeColunas, quantidadeDeLinhas);
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                    int elemento = this->getElemento(linha, coluna);
                    aux->setElemento(elemento, linha, coluna);
                }
            }
            for(int i=1; i<expoente; i++){
                aux = aux->multiplicar(this);
            }
            return aux;
        } catch(std::bad_alloc&){
            throw QString("Não há espaço na memória");
        } catch(QString &erro){
            throw QString("Não é possível Potenciação");
        }
    }


    Matriz *Matriz::multiplicarPorK(int k)const{
        try {
            Matriz *aux = new Matriz(quantidadeDeLinhas, quantidadeDeColunas);
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                    int elemento = getElemento(linha, coluna) * k;
                    aux->setElemento(elemento, linha, coluna);
                }
            }
            return aux;
        } catch(std::bad_alloc&){
            throw QString("Não há espaço na memória");
        } catch(QString &erro){
            throw QString("Não é possível multiplicação");
        }
    }


    Matriz *Matriz::gerarTransposta()const{
        try {
            Matriz *aux = new Matriz(quantidadeDeColunas, quantidadeDeLinhas);
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                    int elemento = this->getElemento(linha, coluna);
                    aux->setElemento(elemento, coluna, linha);
                }
            }
            return aux;
        } catch(std::bad_alloc&){
            throw QString("Não há espaço na memória");
        } catch(QString &erro){
            throw QString("Não é possível gerar Transposta");
        }
    }


    bool Matriz::eTriangularSuperior()const{
        if(this->getQuantidadeDeLinhas()!= this->getQuantidadeDeColunas())
            throw QString("Não é possível verificar se é Triangular, matriz deve ser quadrada");
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                    int elemento = this->getElemento(linha, coluna);
                    if(linha <= coluna){
                        if(elemento==0) return false;
                    }
                    else{
                        if(elemento!=0) return false;
                    }
                }
            }
            return true;
    }


    bool Matriz::eTriangularInferior()const{
        if(this->getQuantidadeDeLinhas()!= this->getQuantidadeDeColunas())
            throw QString("Não é possível verificar se é Triangular, matriz deve ser quadrada");
            for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
                for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                    int elemento = this->getElemento(linha, coluna);
                    if(linha >= coluna){
                        if(elemento==0) return false;
                    }
                    else{
                        if(elemento!=0) return false;
                    }
                }
            }
            return true;
    }


    bool Matriz::eIgual(Matriz const*const objetoMatriz)const{
        if(this->getQuantidadeDeLinhas() != objetoMatriz->getQuantidadeDeLinhas() ||
           this->getQuantidadeDeColunas() != objetoMatriz->getQuantidadeDeColunas())
            return false;
        for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                if(this->getElemento(linha, coluna) != objetoMatriz->getElemento(linha, coluna)) return false;
            }
        }
        return true;
    }


    bool Matriz::eSimetrica(Matriz const*const objetoMatriz)const{
        try {
            if(this->eIgual(this->gerarTransposta())) return true;
            else return false;
        } catch(QString &erro){
            throw QString("Erro");
        }
    }


    bool Matriz::eIdentidade()const{
        for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                int elemento = this->getElemento(linha, coluna);
                if(linha == coluna){
                    if(elemento!=1) return false;
                }
                else{
                    if(elemento!=0) return false;
                }
            }
        }
        return true;
    }


    bool Matriz::eOrtogonal()const{
        //this*tranposta==identidade então é ortogonal/;
        Matriz *aux = new Matriz(this->getQuantidadeDeLinhas(), this->getQuantidadeDeColunas());
        aux = this->multiplicar(gerarTransposta());
        if(aux->eIdentidade()){
            delete aux;
            return true;
        } else{
            delete aux;
            return false;
        }
    }


    bool Matriz::eNula()const{
        for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                if(this->getElemento(linha, coluna)==1) return false;
            }
        }
        return true;
    }


    bool Matriz::eDePermutacao()const{
        if(this->eNula()) return false;
        for(int linha=0; linha<this->quantidadeDeLinhas; linha++){
            for(int coluna=0; coluna<this->quantidadeDeColunas; coluna++){
                if(this->getElemento(linha, coluna)==1){
                    for(int auxLinha = linha+1; auxLinha<this->quantidadeDeLinhas; auxLinha++){
                        if(this->getElemento(auxLinha, coluna)==1) return false;
                    }
                    for(int auxColuna = coluna+1; auxColuna<this->quantidadeDeColunas; auxColuna++){
                        if(this->getElemento(linha, auxColuna)==1) return false;
                    }
                };
            }
        }
        return true;
    }
}
