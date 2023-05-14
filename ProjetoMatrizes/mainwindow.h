#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <matriz.h>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_CriarMatrizA_clicked();

    void on_pushButton_CriarMatrizB_clicked();

    void on_pushButton_ApagarMatrizA_clicked();

    void on_pushButton_ApagarMatrizB_clicked();

    void on_pushButton_Adicao_clicked();

    void on_pushButton_ASubtracaoB_clicked();

    void on_pushButton_BSubtracaoA_clicked();

    void on_pushButton_AMultiplicacaoB_clicked();

    void on_pushButton_BMultiplicacaoA_clicked();

    void on_pushButton_AMultiplicacaoK_clicked();

    void on_pushButton_BMultiplicacaoK_clicked();

    void on_pushButton_TranspostaA_clicked();

    void on_pushButton_TranspostaB_clicked();

    void on_pushButton_PotenciacaoA_clicked();

    void on_pushButton_PotenciacaoB_clicked();

    void on_pushButtonExecutarGrid_clicked();


private:
    Ui::MainWindow *ui;
    ggs::Matriz *matrizA;
    ggs::Matriz *matrizB;
};
#endif // MAINWINDOW_H
