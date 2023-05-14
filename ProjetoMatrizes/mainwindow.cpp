#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    matrizA = 0;
    matrizB = 0;
    ui->setupUi(this);
    ui->pushButton_Adicao->setEnabled(false);
    ui->pushButton_ASubtracaoB->setEnabled(false);
    ui->pushButton_BSubtracaoA->setEnabled(false);
    ui->pushButton_AMultiplicacaoK->setEnabled(false);
    ui->pushButton_BMultiplicacaoK->setEnabled(false);
    ui->pushButton_AMultiplicacaoB->setEnabled(false);
    ui->pushButton_BMultiplicacaoA->setEnabled(false);
    ui->pushButton_TranspostaA->setEnabled(false);
    ui->pushButton_TranspostaB->setEnabled(false);
    ui->pushButton_PotenciacaoA->setEnabled(false);
    ui->pushButton_PotenciacaoB->setEnabled(false);
    ui->pushButtonExecutarGrid->setEnabled(false);
    ui->textEdit_MatrizResultado->setEnabled(false);
    ui->textEdit_SaidaMatrizA->setEnabled(false);
    ui->textEdit_SaidaMatrizB->setEnabled(false);
    ui->tableWidget->setEnabled(false);
}

MainWindow::~MainWindow()
{
    if(matrizA) delete matrizA;
    if(matrizB) delete matrizB;
    delete ui;
}


void MainWindow::on_pushButton_CriarMatrizA_clicked()
{
    try {
        int numLinhas = ui->lineEdit_LinhasMatrizA->text().toInt();
        int numColunas = ui->lineEdit_ColunasMatrizA->text().toInt();
        matrizA = new ggs::Matriz(numLinhas, numColunas);

        for(int l=0; l < numLinhas ; l++){
            for(int c=0; c < numColunas; c++){
                int elemento =  QInputDialog::getInt(this, "Leitura",
                                "Matriz A ["+ QString::number(l) + ", "+
                                QString::number(c) + "] = ");
                matrizA->setElemento(elemento,l,c);
            }
        }

        ui->textEdit_SaidaMatrizA->setText(matrizA->getMatriz());
        ui->lineEdit_LinhasMatrizA->setEnabled(false);
        ui->lineEdit_ColunasMatrizA->setEnabled(false);
        ui->pushButton_AMultiplicacaoK->setEnabled(true);
        ui->pushButton_TranspostaA->setEnabled(true);
        ui->pushButton_PotenciacaoA->setEnabled(true);
        ui->pushButton_CriarMatrizA->setEnabled(false);
        ui->pushButton_ApagarMatrizA->setEnabled(true);
        if(matrizB!=0)ui->pushButtonExecutarGrid->setEnabled(true);
    }   catch(std::bad_alloc&){
        QMessageBox::information(this, "ERRO NO SISTEMA", "Matriz nao pode ser criada");
    }   catch(QString &erro){
        QMessageBox::information(this, "ERRO NO SISTEMA", erro);
    }
}


void MainWindow::on_pushButton_CriarMatrizB_clicked()
{
    try {
        int numLinhas = ui->lineEdit_LinhasMatrizB->text().toInt();
        int numColunas = ui->lineEdit_ColunasMatrizB->text().toInt();
        matrizB = new ggs::Matriz(numLinhas, numColunas);

        for(int l=0; l < numLinhas ; l++){
            for(int c=0; c < numColunas; c++){
                int elemento =  QInputDialog::getInt(this, "Leitura",
                                "Matriz B ["+ QString::number(l) + ", "+
                                QString::number(c) + "] = ");
                matrizB->setElemento(elemento,l,c);
            }
        }

        ui->textEdit_SaidaMatrizB->setText(matrizB->getMatriz());
        ui->lineEdit_LinhasMatrizB->setEnabled(false);
        ui->lineEdit_ColunasMatrizB->setEnabled(false);
        ui->pushButton_Adicao->setEnabled(true);
        ui->pushButton_ASubtracaoB->setEnabled(true);
        ui->pushButton_BSubtracaoA->setEnabled(true);
        ui->pushButton_BMultiplicacaoK->setEnabled(true);
        ui->pushButton_AMultiplicacaoB->setEnabled(true);
        ui->pushButton_BMultiplicacaoA->setEnabled(true);
        ui->pushButton_TranspostaB->setEnabled(true);
        ui->pushButton_PotenciacaoB->setEnabled(true);
        ui->pushButton_CriarMatrizB->setEnabled(false);
        ui->pushButton_ApagarMatrizB->setEnabled(true);
        if(matrizA!=0)ui->pushButtonExecutarGrid->setEnabled(true);
    }   catch(std::bad_alloc&){
        QMessageBox::information(this, "ERRO NO SISTEMA", "Matriz nao pode ser criada");
    }   catch(QString &erro){
        QMessageBox::information(this, "ERRO NO SISTEMA", erro);
    }
}


void MainWindow::on_pushButton_ApagarMatrizA_clicked()
{
    if(matrizA) delete matrizA;
    matrizA = 0;
    ui->lineEdit_ColunasMatrizA->clear();
    ui->lineEdit_LinhasMatrizA->clear();
    ui->textEdit_SaidaMatrizA->clear();
    ui->lineEdit_ColunasMatrizA->setEnabled(true);
    ui->lineEdit_LinhasMatrizA->setEnabled(true);
    ui->pushButton_CriarMatrizA->setEnabled(true);
    ui->pushButton_ApagarMatrizA->setEnabled(false);
    ui->pushButtonExecutarGrid->setEnabled(false);
}


void MainWindow::on_pushButton_ApagarMatrizB_clicked()
{
    if(matrizB) delete matrizB;
    matrizB = 0;
    ui->lineEdit_ColunasMatrizB->clear();
    ui->lineEdit_LinhasMatrizB->clear();
    ui->textEdit_SaidaMatrizB->clear();
    ui->lineEdit_ColunasMatrizB->setEnabled(true);
    ui->lineEdit_LinhasMatrizB->setEnabled(true);
    ui->pushButton_CriarMatrizB->setEnabled(true);
    ui->pushButton_ApagarMatrizB->setEnabled(false);
    ui->pushButtonExecutarGrid->setEnabled(false);
}



void MainWindow::on_pushButton_Adicao_clicked()
{
    try {
        if(matrizA==0) throw QString("Operação de ADIÇÃO não pode ser executada");
        if(matrizB==0) throw QString("Operação de ADIÇÃO não pode ser executada");
        ggs::Matriz *matrizAux = matrizA->adicionar(matrizB);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_ASubtracaoB_clicked()
{
    try {
        if(matrizA==0) throw QString("Operação de SUBTRAÇÃO não pode ser executada");
        if(matrizB==0) throw QString("Operação de SUBTRAÇÃO não pode ser executada");
        ggs::Matriz *matrizAux = matrizA->subtraiz(matrizB);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_BSubtracaoA_clicked()
{
    try {
        if(matrizA==0) throw QString("Operação de SUBTRAÇÃO não pode ser executada");
        if(matrizB==0) throw QString("Operação de SUBTRAÇÃO não pode ser executada");
        ggs::Matriz *matrizAux = matrizB->subtraiz(matrizA);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_AMultiplicacaoB_clicked()
{
    try {
        if(matrizA==0) throw QString("Operação de MULTIPLICAÇÃO não pode ser executada");
        if(matrizB==0) throw QString("Operação de MULTIPLICAÇÃO não pode ser executada");
        ggs::Matriz *matrizAux = matrizA->multiplicar(matrizB);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_BMultiplicacaoA_clicked()
{
    try {
        if(matrizA==0) throw QString("Operação de MULTIPLICAÇÃO não pode ser executada");
        if(matrizB==0) throw QString("Operação de MULTIPLICAÇÃO não pode ser executada");
        ggs::Matriz *matrizAux = matrizB->multiplicar(matrizA);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_AMultiplicacaoK_clicked()
{
    try {
        if(matrizA==0) throw QString("Operação de MULTIPLICAÇÃO não pode ser executada");
        int k =  QInputDialog::getInt(this, "Leitura", "k =");
        ggs::Matriz *matrizAux = matrizA->multiplicarPorK(k);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_BMultiplicacaoK_clicked()
{
    try {
        if(matrizB==0) throw QString("Operação de MULTIPLICAÇÃO não pode ser executada");
        int k =  QInputDialog::getInt(this, "Leitura", "k =");
        ggs::Matriz *matrizAux = matrizB->multiplicarPorK(k);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_TranspostaA_clicked()
{
    try {
        if(matrizA==0) throw QString("Não é possível gerar Transposta");
        ggs::Matriz *matrizAux = matrizA->gerarTransposta();
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_TranspostaB_clicked()
{
    try {
        if(matrizB==0) throw QString("Não é possível gerar Transposta");
        ggs::Matriz *matrizAux = matrizB->gerarTransposta();
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_PotenciacaoA_clicked()
{
    try {
        if(matrizA==0) throw QString("Operação de POTENCIAÇÃO não pode ser executada");
        int expoente =  QInputDialog::getInt(this, "Leitura", "Expoente =");
        ggs::Matriz *matrizAux = matrizA->calcularPotencia(expoente);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}


void MainWindow::on_pushButton_PotenciacaoB_clicked()
{
    try {
        if(matrizB==0) throw QString("Operação de POTENCIAÇÃO não pode ser executada");
        int expoente =  QInputDialog::getInt(this, "Leitura", "Expoente =");
        ggs::Matriz *matrizAux = matrizB->calcularPotencia(expoente);
        ui->textEdit_MatrizResultado->setText(matrizAux->getMatriz());
        if(matrizAux) delete matrizAux;
    }
    catch(QString &erro){
        QMessageBox::information(this,"ERRO NO SISTEMA",erro);
    }
}

void MainWindow::on_pushButtonExecutarGrid_clicked()
{
    try {
        const QString strSim = "SIM";
        const QString strNao = "NÃO";

        //Triangular Superior
        if(matrizA->eTriangularSuperior()){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidget->setItem(0,0,item1);
        } else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidget->setItem(0,0,item2);
        }
        //Triangular Inferior
        if(matrizA->eTriangularInferior()){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidget->setItem(1,0,item1);
        } else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidget->setItem(1,0,item2);
        }
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }

    try {
        const QString strSim = "SIM";
        const QString strNao = "NÃO";

        //Triangular Superior
        if(matrizB->eTriangularSuperior()){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidget->setItem(0,1,item1);
        } else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidget->setItem(0,1,item2);
        }
        //Triangular Inferior
        if(matrizB->eTriangularInferior()){
            QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
            ui->tableWidget->setItem(1,1,item1);
        } else{
            QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
            ui->tableWidget->setItem(1,1,item2);
        }
    } catch (QString &erro) {
        QMessageBox::information(this, "ERRO DO SISTEMA", erro);
    }

    const QString strSim = "SIM";
    const QString strNao = "NÃO";

    //É Simetrica
    if(matrizA->eSimetrica(matrizA->gerarTransposta())){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(2,0,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(2,0,item2);
    }
    if(matrizB->eSimetrica(matrizB->gerarTransposta())){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(2,1,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(2,1,item2);
    }

    //É Identidade
    if(matrizA->eIdentidade()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(3,0,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(3,0,item2);
    }
    if(matrizB->eIdentidade()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(3,1,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(3,1,item2);
    }

    //São Iguais
    if(matrizA->eIgual(matrizB)){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(4,0,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(4,0,item2);
    }
    if(matrizB->eIgual(matrizA)){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(4,1,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(4,1,item2);
    }

    //São Diferentes
    if(!matrizA->eIgual(matrizB)){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(5,0,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(5,0,item2);
    }
    if(!matrizB->eIgual(matrizA)){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(5,1,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(5,1,item2);
    }

    //e Ortogonal
    if(matrizA->eOrtogonal()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(6,0,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(6,0,item2);
    }
    if(matrizB->eOrtogonal()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(6,1,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(6,1,item2);
    }

    //e Nula
    if(matrizA->eNula()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(7,0,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(7,0,item2);
    }
    if(matrizB->eNula()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(7,1,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(7,1,item2);
    }

    //e de Permutção
    if(matrizA->eDePermutacao()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(8,0,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(8,0,item2);
    }
    if(matrizB->eDePermutacao()){
        QTableWidgetItem *item1 = new QTableWidgetItem(strSim);
        ui->tableWidget->setItem(8,1,item1);
    } else{
        QTableWidgetItem *item2 = new QTableWidgetItem(strNao);
        ui->tableWidget->setItem(8,1,item2);
    }

}
