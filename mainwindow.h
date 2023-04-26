#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_openImageButton_clicked();

    void on_EncodeButton_clicked();

    void on_saveAsButton_clicked();

    void on_openImageButtonDecode_clicked();

    void on_DecodeButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
