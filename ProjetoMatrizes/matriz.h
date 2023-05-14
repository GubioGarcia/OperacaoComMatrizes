#ifndef MATRIZ_H
#define MATRIZ_H

#include <QString>
#include <QMessageBox>

namespace ggs{
    class Matriz
    {
    private:
        int quantidadeDeLinhas;
        int quantidadeDeColunas;
        int *pMatriz;
    public:
        Matriz(int quantLinhas, int quantColunas);
        ~Matriz();
        int getQuantidadeDeLinhas() const;
        int getQuantidadeDeColunas() const;
        void setElemento(int elemento, int linha, int coluna)const;
        int getElemento(int linha, int coluna)const;
        QString getMatriz()const;

        Matriz *adicionar(Matriz const*const objetoMatriz)const;
        Matriz *subtraiz(Matriz const*const objetoMatriz)const;
        Matriz *multiplicar(Matriz const*const objetoMatriz)const;
        Matriz *calcularPotencia(int expoente)const;
        Matriz *multiplicarPorK(int k)const;
        Matriz *gerarTransposta()const;

        bool eTriangularSuperior()const;
        bool eTriangularInferior()const;
        bool eIdentidade()const;
        bool eIgual(Matriz const*const objetoMatriz)const;
        bool eSimetrica(Matriz const*const objetoMatriz)const;
        bool eNula()const;
        bool eOrtogonal()const;
        bool eDePermutacao()const;

    };
}
#endif // MATRIZ_H
