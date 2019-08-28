#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QMessageBox>

#include <QInputDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QSpacerItem>

#include<iostream>
#include "struct.h"


List lst;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QStringList nameTablecolumn;
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows );
    nameTablecolumn << "Id" << "Имя" << "Количество" << "Цена" << "Дата" << "Срок службы" << "Цвет";
    ui->tableWidget->setHorizontalHeaderLabels(nameTablecolumn);

    ui->tableWidget->setCellWidget(1,1,ui->pushButton);
    ui->tableWidget->setSpan(ui->tableWidget->rowCount()-1,0,1,7);
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1,0,ui->pushButton);


    ui->listWidget->setCurrentRow(0);

    QMenu *menu = new QMenu();
    menu->setTitle("Файл");
    ui->menuBar->addMenu(menu);

    Action *create = new Action();
    create->setText("Создать файл");
    Action *save = new Action();
    save->setText("Сохранить файл");
    Action *open = new Action();
    open->setText("Открыть файл");

    menu->addAction(create);
    menu->addSeparator();
    menu->addAction(save);
    menu->addAction(open);

    list = menu->actions();
    list[2]->setEnabled(false);

    connect(open, SIGNAL(triggered()), save ,SLOT(push_slot_open()));
    connect(create, SIGNAL(triggered()), create, SLOT(push_slot_create()));
    connect(save, SIGNAL(triggered()), save, SLOT(push_slot_save()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow* MainWindow::mainInstance = 0;

MainWindow* MainWindow::GetInstance(QWidget *parent)
{
    if(mainInstance == NULL)
    {
     mainInstance = new MainWindow(parent);
    }
    return mainInstance;
}

QLineEdit* MainWindow::getInstanceLine(int index)
{
    if(index==1)
        return ui->lineEdit;
    if(index==2)
        return ui->lineEdit_2;
}
QListWidget* MainWindow::getInstanceListWidget()
{
    return  ui->listWidget;
}
QTableWidget* MainWindow::getInstanceTable()
{
    return ui->tableWidget;
}

void Action::push_slot_open()
{
    MainWindow *win = MainWindow::GetInstance();
    QTableWidget *table = win->getInstanceTable();
    lst.open_file();
    if(lst.filename_perem!=NULL)
        win->list[2]->setEnabled(true);

}

void Action::push_slot_create()
{
    MainWindow *win = MainWindow::GetInstance();
    lst.create_file();
    if(lst.filename_perem!=NULL)
        win->list[2]->setEnabled(true);
   //создать для создания файла
}

void Action::push_slot_save()
{
    lst.save_in_file();
}

void MainWindow::closeEvent(QCloseEvent *even)//Тут чт нибудь да сделать
{

}

void Widget_Form::push_button_clicked_ok()
{
    int condition[6]={0,0,0,0,0,0};
    //Попробовать сделать через layout
    QStringList str_list;
    str_list << "0" << "0" << "0" << "0" << "0" << "0";
//-------------------
    if(line_name->text()==NULL)
    {
        line_name->setStyleSheet("QLineEdit {border:2px solid red;}");
        condition[0]=1;
        str_list[0]=" Имя";
    }
    else
    {
        line_name->setStyleSheet("QLineEdit {border:2px solid green;}");
        condition[0]=0;
        str_list[0]="0";
    }
//----------------
    if(line_count->text()==NULL)
    {
        line_count->setStyleSheet("QLineEdit {border:2px solid red;}");
        condition[1]=1;
        str_list[1]=" Количество";
    }
    else
    {
        line_count->setStyleSheet("QLineEdit {border:2px solid green;}");
        condition[1]=0;
        str_list[1]="0";
    }
//----------------------
    if(line_price->text()==NULL)
    {
        line_price->setStyleSheet("QLineEdit {border:2px solid red;}");
        condition[2]=1;
        str_list[2]=" Цена";
    }
    else
    {
        line_price->setStyleSheet("QLineEdit {border:2px solid green;}");
        condition[2]=0;
        str_list[2]="0";
    }
//----------------------
    if(line_date->text()==NULL)
    {
        line_date->setStyleSheet("QLineEdit {border:2px solid red;}");
        condition[3]=1;
        str_list[3]=" Дата";
    }
    else
    {
        line_date->setStyleSheet("QLineEdit {border:2px solid green;}");
        condition[3]=0;
        str_list[3]="0";
    }
//---------------------
    if(line_srok->text()==NULL)
    {
        line_srok->setStyleSheet("QLineEdit {border:2px solid red;}");
        condition[4]=1;
        str_list[4]=" Срок службы";
    }
    else
    {
        line_srok->setStyleSheet("QLineEdit {border:2px solid green;}");
        condition[4]=0;
        str_list[4]="0";
    }
//---------------------
    if(line_color->text()==NULL)
    {
        line_color->setStyleSheet("QLineEdit {border:2px solid red;}");
        condition[5]=1;
        str_list[5]=" Цвет";
    }
    else
    {
        line_color->setStyleSheet("QLineEdit {border:2px solid green;}");
        condition[5]=0;
        str_list[5]="0";
    }

    QString str;
    bool cond = false;
    for (int i=0;i<str_list.count();i++)
    {
        if(str_list[i]!="0")
        {
            if(cond)
                str=str+","+str_list[i];
            else
                str=str + str_list[i];
            cond = true;
        }
    }
    str= "Не введены данные в поля: " +str;
    if(cond)
        QMessageBox::warning(this, "Ошибка при вводе!", str, QMessageBox::Ok);
    else
    {
        MainWindow *win = MainWindow::GetInstance();
        QStringList list_str;

        list_str.append(line_name->text());
        list_str.append(line_count->text());
        int count_line = line_count->text().toInt();
        list_str.append(line_price->text());
        int price_line = line_price->text().toInt();
        list_str.append(line_date->text());
        QDate date = QDate::fromString(line_date->text(),"dd.MM.yyyy");
        list_str.append(line_srok->text());
        list_str.append(line_color->text());

        lst.last_id++;
        win->ui->tableWidget->item(win->ui->tableWidget->rowCount()-2,0)->setText(QString::number(lst.last_id));

        for (int i=0;i<list_str.count();i++)
        {
            win->ui->tableWidget->item(win->ui->tableWidget->rowCount()-2,i+1)->setText(list_str[i]);
        }

        lst.Add(lst.last_id/*win->ui->tableWidget->item(win->ui->tableWidget->rowCount()-2,0)->text().toInt()*/,
                lst.name_categor[win->ui->listWidget->currentRow()],
                line_name->text(),
                price_line,
                count_line,
                line_color->text(),
                date.day(), date.month(), date.year(),
                line_srok->text());
        win->setEnabled(true);
        this->close();
    }

}

void Widget_Form::push_button_clicked_cancel()
{
    MainWindow *win = MainWindow::GetInstance();

    win->ui->tableWidget->removeRow(win->ui->tableWidget->rowCount()-2);
    this->close();
    win->setEnabled(true);

    win->ui->lineEdit_2->setText("Всего элементов в базе: "+ QString::number(lst.count_all---1));
    lst.count_in_cat[win->ui->listWidget->currentRow()]--;
    win->ui->lineEdit->setText("Всего элементов категории '"+ win->ui->listWidget->currentItem()->text() +"' : "
                          +QString::number(lst.count_in_cat[win->ui->listWidget->currentRow()]));

}

void Widget_Form::push_button_visible_calendar()
{
    if(!calendar->isVisible())
    {
        calendar->setVisible(true);
        btn_selected_date->setVisible(true);
        btn_calendar->setText("<-");
        this->setMinimumWidth(1000);
    }
    else
    {
        calendar->setVisible(false);
        btn_selected_date->setVisible(false);
        btn_calendar->setText("->");
        this->setMinimumWidth(500);
    }
}

void Widget_Form::click_calendar()
{
    QDate date;
    date=calendar->selectedDate();
    line_date->setText(date.toString("dd.MM.yyyy"));
}

void Widget_Form::create_window(MainWindow *main_win)
{
    main_win->setEnabled(false);
    Widget_Form *win = new Widget_Form;
    win->setWindowFlags(Qt::WindowSystemMenuHint);
    win->setMinimumWidth(500);
    QHBoxLayout *layout = new QHBoxLayout;
    QVBoxLayout *firs_column = new QVBoxLayout;
    QVBoxLayout *second_column = new QVBoxLayout;

    QLineEdit *_name = new QLineEdit(win);
    _name->setText("Имя: ");
    _name->setReadOnly(true);
    _name->setStyleSheet("QLineEdit {border:2px solid black;}");

    QLineEdit *_count = new QLineEdit;
    _count->setText("Количество: ");
    _count->setReadOnly(true);
    _count->setStyleSheet("QLineEdit {border:2px solid black;}");

    QLineEdit *_price = new QLineEdit;
    _price->setText("Цена: ");
    _price->setReadOnly(true);
    _price->setStyleSheet("QLineEdit {border:2px solid black;}");

    QLineEdit *_date = new QLineEdit;
    _date->setText("Дата: ");
    _date->setReadOnly(true);
    _date->setStyleSheet("QLineEdit {border:2px solid black;}");

    QLineEdit *_srok = new QLineEdit;
    _srok->setText("Срок службы: ");
    _srok->setReadOnly(true);
    _srok->setStyleSheet("QLineEdit {border:2px solid black;}");

    QLineEdit *_color = new QLineEdit;
    _color->setText("Цвет: ");
    _color->setReadOnly(true);
    _color->setStyleSheet("QLineEdit {border:2px solid black;}");

    win->line_name = new QLineEdit;
    win->line_name->setStyleSheet("QLineEdit {border:2px solid black;}");
    win->line_name->setMaxLength(22);
    win->line_count = new QLineEdit;
    win->line_count->setStyleSheet(win->line_name->styleSheet());
    win->line_count->setValidator(new QRegExpValidator(QRegExp("[0-9]{10}")));
    win->line_price = new QLineEdit;
    win->line_price->setStyleSheet(win->line_name->styleSheet());
    win->line_price->setValidator(new QRegExpValidator(QRegExp("[0-9]{11}")));
    win->line_date = new QLineEdit;
    win->line_date->setStyleSheet(win->line_name->styleSheet());
    win->line_date->setReadOnly(true);
    win->line_srok = new QLineEdit;
    win->line_srok->setStyleSheet(win->line_name->styleSheet());
    win->line_srok->setValidator(new QRegExpValidator(QRegExp("([0-9]|[ ]|[a-z]|[A-Z]){16}")));
    win->line_color = new QLineEdit;
    win->line_color->setStyleSheet(win->line_name->styleSheet());
    win->line_color->setValidator(new QRegExpValidator(QRegExp("([a-z]|[A-Z]){20}")));

    win->calendar = new QCalendarWidget;
    win->calendar->setVisible(false);
    QDate date_min(2000, 1, 1);
    QDate date_max = QDate::currentDate();
    win->calendar->setMinimumDate(date_min);
    win->calendar->setMaximumDate(date_max);

    win->line_color->setMaxLength(20);

    QPushButton *btn_ok = new QPushButton;
    btn_ok->setText("Ok");
    QPushButton *btn_cancel = new QPushButton;
    btn_cancel->setText("Cancel");
    win->btn_calendar = new QPushButton;
    win->btn_calendar->setText("->");
    win->btn_calendar->setMaximumHeight(23);
    win->btn_selected_date = new QPushButton;
    win->btn_selected_date->setText("Выбрать дату");
    win->btn_selected_date->setVisible(false);

    firs_column->addWidget(_name);
    second_column->addWidget(win->line_name);

    firs_column->addWidget(_count);
    second_column->addWidget(win->line_count);

    firs_column->addWidget(_price);
    second_column->addWidget(win->line_price);

    firs_column->addWidget(_date);
    QHBoxLayout *layout_date = new QHBoxLayout;
    layout_date->addWidget(win->line_date);
    layout_date->addWidget(win->btn_calendar);
    second_column->addLayout(layout_date);

    firs_column->addWidget(_srok);
    second_column->addWidget(win->line_srok);

    firs_column->addWidget(_color);
    second_column->addWidget(win->line_color);

    firs_column->addWidget(btn_ok);
    second_column->addWidget(btn_cancel);
    firs_column->setAlignment(Qt::AlignTop);
    second_column->setAlignment(Qt::AlignTop);

    layout->addLayout(firs_column);
    layout->addLayout(second_column);
    layout->addWidget(win->calendar);
    layout->addWidget(win->btn_selected_date);
    win->setLayout(layout);

    connect(btn_ok, SIGNAL(clicked()), win, SLOT(push_button_clicked_ok()));
    connect(btn_cancel, SIGNAL(clicked()), win, SLOT(push_button_clicked_cancel()));
    connect(win->btn_calendar, SIGNAL(clicked()), win, SLOT(push_button_visible_calendar()));
    connect(win->btn_selected_date, SIGNAL(clicked()),win, SLOT(click_calendar()));

    win->show();

}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount()-1);

    for (int i=0;i<ui->tableWidget->columnCount();i++)
    {
        QTableWidgetItem *_item = new QTableWidgetItem;
        _item->setFlags(_item->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-2,i,_item);
    }
    ui->lineEdit_2->setText("Всего элементов в базе: "+ QString::number(lst.count_all+++1));
    ui->tableWidget->item((ui->tableWidget->rowCount()-2),0)->setText(QString::number(lst.count_all));
    lst.count_in_cat[ui->listWidget->currentRow()]++;
    ui->lineEdit->setText("Всего элементов категории '"+ ui->listWidget->currentItem()->text() +"' : "
                          +QString::number(lst.count_in_cat[ui->listWidget->currentRow()]));

    Widget_Form *perem = new Widget_Form;
    perem->create_window(MainWindow::GetInstance());
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    lst.refresh_table(ui->tableWidget, ui->listWidget->currentRow());
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QMessageBox *quession = new QMessageBox(QMessageBox::Information, "Удаление", "Вы действиетльно хотите удалить элемент?",
                                            QMessageBox::Yes | QMessageBox::No);
    if(quession->exec()==QMessageBox::Yes)
    {
        int index;
        lst.cursor = lst.head;
        for (int i=0;i<row;i++)
            lst.cursor=lst.cursor->next;
        std::cout<<lst.cursor->id<<std::endl;
        for (index=0;index<6;index++) {
            if(strcmp(lst.cursor->name_categor, lst.name_categor[index])==0)
                break;
        }
        lst.count_in_cat[index]--;
        lst.count_all--;
        lst.DeleteElement(lst.cursor);
        lst.refresh_table(ui->tableWidget, 0);
    }
}
