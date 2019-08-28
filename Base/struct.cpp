#include "struct.h"
#include <string.h>
#include <cstring>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <QLineEdit>
#include "mainwindow.h"
#include <iostream>

using namespace std;

extern List lst;

List::~List()
{
    List::delete_all_elements();
}
void List::delete_all_elements()
{
    while(head)
    {
        cursor=head->next;
        delete head;
        head=cursor;
    }
    for (int i=0;i<6;i++)
    {
        count_in_cat[i]=0;
    }
    count_all=0;
}

void List::Add(int id, const char *name_categor, QString name, int price,
          int count, QString color, int day, int month, int year, QString life)
{

    data *peremen = new data;
    peremen->next = NULL;
    peremen->id=id;
//    peremen->name_categor = new char[22];
    strcpy(peremen->name_categor,name_categor);
//    strcpy(peremen->name,name);
    peremen->name = name;
    peremen->price=price;
    peremen->count=count;
//    strcpy(peremen->color,color);
    peremen->color = color;
    peremen->date.day=day;
    peremen->date.month=month;
    peremen->date.year=year;
//    strcpy(peremen->life,life);
    peremen->life = life;

    if(head!=NULL)
    {
        peremen->prev = cursor;
        cursor->next = peremen;
        cursor = peremen;
    }
    else
    {
        peremen->prev=NULL;
        head=cursor=peremen;
    }
}

void List::DeleteElement(data *element)
{
    if(element!=NULL)
    {
        if((element->next==NULL)&&(element->prev==NULL))
        {
            delete element;
            head=cursor=NULL;
        }
        else if(element->next==NULL)
        {
            data *prev = element->prev;
            prev->next=NULL;
            delete element;
        }
        else if(element->prev==NULL)
        {
            head=element->next;
            head->prev=NULL;
            delete element;
        }
        else
        {
            data *prev = element->prev, *next = element->next;
            next->prev=element->prev;
            prev->next=element->next;
            delete element;
        }
    };
}

void List::refresh_table(QTableWidget *table, int index_categor)
{
    int kol_vo_row = table->rowCount()-1;
    for (int i=0;i<kol_vo_row;i++)
        table->removeRow(0);

    MainWindow *win = MainWindow::GetInstance();
    QLineEdit *line = win->getInstanceLine(1);
    QListWidget *listWidget = win->getInstanceListWidget();
    line->setText("Всего элементов категории '"+ listWidget->currentItem()->text() +"' : "
                          +QString::number(count_in_cat[listWidget->currentRow()]));

    cursor = head;
    for (int i=0;i<count_in_cat[index_categor];i++)
    {
        while(strcmp(cursor->name_categor,name_categor[index_categor])!=0)
            cursor=cursor->next;
        table->insertRow(table->rowCount()-1);
        for (int b=0;b<table->columnCount();b++)
        {
            QTableWidgetItem *_item = new QTableWidgetItem;
            _item->setFlags(_item->flags() & ~Qt::ItemIsEditable);
            table->setItem(table->rowCount()-2,b,_item);
        }
        table->item(i,0)->setText(QString::number(cursor->id));
        table->item(i,1)->setText(cursor->name);
        table->item(i,2)->setText(QString::number(cursor->count));
        table->item(i,3)->setText(QString::number(cursor->price));
        QDate date(cursor->date.year, cursor->date.month, cursor->date.day);
        table->item(i,4)->setText(date.toString("dd.MM.yyyy"));
        table->item(i,5)->setText(cursor->life);
        table->item(i,6)->setText(cursor->color);

        cursor=cursor->next;
    }
}


void List::open_file()
{

    if(head!=NULL)
        delete_all_elements();
    int id, price, count, day, month, year, index;
    QString name, color, life;
    char *per_name_categor;

    QString file_name = QFileDialog::getOpenFileName(MainWindow::GetInstance(), "Открыть документ",
                                                    QDir::currentPath(), "Базы данных: (*.txt)");

    QString perem = file_name.section("/",-1,-1);
    filename = perem.toStdString().c_str();
    filename_perem = QString::fromUtf8(filename);

    QFile in(filename);
    if(in.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&in);
        stream >> count_all;
        last_id=count_all;
        for (int i=0;i<count_all;i++)
        {
            stream>>id>>per_name_categor>>name>>price>>count>>color>>day>>month>>year>>life;
            Add(id, per_name_categor, name, price, count, color, day, month, year, life);
            for(index=0; index<6; index++)
            {
                if(strcmp(per_name_categor, name_categor[index])==0)
                    break;
            }
            count_in_cat[index]++;
        }
        in.close();
    }
    MainWindow *win = MainWindow::GetInstance();
    QLineEdit *line = win->getInstanceLine(2);
    line->setText("Всего элементов в базе: "+ QString::number(count_all));
    QListWidget *widg = win->getInstanceListWidget();
    widg->setCurrentRow(0);
    refresh_table(win->getInstanceTable(), 0);
}
void List::create_file()
{
    QString file_name = QFileDialog::getSaveFileName(MainWindow::GetInstance(), "Создать документ",  QDir::currentPath(),"Базы данных: (*.txt)");
    QString perem = file_name.section("/",-1,-1);
    filename = perem.toStdString().c_str();
    filename_perem = QString::fromUtf8(filename);
    ofstream out(filename, ios::binary);
    out.close();
}
void List::save_in_file()
{
    data *perem = head;
    filename = filename_perem.toStdString().c_str();
    QFile out(filename);
    if(out.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&out);
        stream<<count_all;
        while(perem)
        {
            stream<<perem->id<<perem->name_categor<<perem->name<<perem->price<<perem->count<<
                    perem->color<<perem->date.day<<perem->date.month<<perem->date.year<<perem->life;
            perem=perem->next;
        }
        out.close();
    }
}
