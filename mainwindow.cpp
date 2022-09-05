#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QDebug>
#include <string>
#include <QMessageBox>
#include <iostream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::list<std::string> bones;

void MainWindow::on_pushButton_clicked()
{
    bones.clear();
    QString qs = ui->textEdit->toPlainText();
    std::string current_locale_text = qs.toLocal8Bit().constData();

    std::string line;
    std::istringstream input;
    input.str(current_locale_text);
    while(getline(input, line))
    {
        std::string arr[4];
        int i = 0;
        std::stringstream ssin(line);
        while (ssin.good() && i < 4){
            ssin >> arr[i];
            ++i;
        }

        if (arr[0] == "$definebone")
        {
            arr[1].erase(arr[1].find('"'), 1);
            arr[1].erase(arr[1].find('"'), arr[1].size()+1);
            bones.push_back(arr[1]);
        }
        if (arr[0] == "time")
            bones.push_back(arr[3]);
    }
     ui->textEdit->setText("");
    for (auto const& i : bones)
    {
        ui->textEdit->setText(ui->textEdit->toPlainText() + i.c_str() + "\n");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString qs = ui->textEdit_2->toPlainText();
    std::string current_locale_text = qs.toLocal8Bit().constData();

    ui->textEdit_3->setText("");
    for (auto const& i : bones)
    {
        std::string preset = "$jigglebone """+ i +"""\n {\nis_flexible\n{\n" + current_locale_text + "\n}\n}";
        ui->textEdit_3->setText(ui->textEdit_3->toPlainText() + preset.c_str() + "\n");
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    std::string preset = "$model \"faceacc\" \"faceacc.smd\" {\n\n\tflexfile ""toyosatomimi_01.vta""\n\t{\n\t\tdefaultflex frame 0\n";
    int count = 0;
    ui->textEdit_3->setText(preset.c_str());
    for (auto const& i : bones)
    {
        count += 1;
        ui->textEdit_3->setText(ui->textEdit_3->toPlainText() + "\t\tflex " + i.c_str() + " frame " + QString::number(count) + "\n");
    }
    ui->textEdit_3->setText(ui->textEdit_3->toPlainText() + "\t}\n\n");
    for (auto const& i : bones)
    {
        ui->textEdit_3->setText(ui->textEdit_3->toPlainText() + "\tflexcontroller" + i.c_str() +" 0 1 " + i.c_str() + "\n");
    }
    ui->textEdit_3->setText(ui->textEdit_3->toPlainText() + "\n");
    for (auto const& i : bones)
    {
        ui->textEdit_3->setText(ui->textEdit_3->toPlainText() + "\t%" + i.c_str() + " = " + i.c_str() + "\n");
    }
    ui->textEdit_3->setText(ui->textEdit_3->toPlainText() + "}");
}

