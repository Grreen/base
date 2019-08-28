#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QBoxLayout>
#include <QCalendarWidget>
#include <QListWidget>
#include <QPushButton>
#include <QMenu>


namespace Ui {
class MainWindow;
}

/**
 * @brief Класс для работы с графической частью
 * @detailed Осуществляет отображение графических элементов, является главной частью графики
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
/**
@brief Конструктор
@param parent - родитель
 */
    explicit MainWindow(QWidget *parent = nullptr);
/**
@brief Деструктор
*/
    ~MainWindow();
/**
 * @brief Функция полученя ссылки главного окна
 * @detailed Используется для получения ссылки главного окна
 * @param parent - родитель
 * @return Статичная ссылка на главное окно
 */
    static MainWindow* GetInstance(QWidget* parent = 0);

public slots:
/**
 * @brief Слот, вызываемый при нажатии на определенную кнопку
 * @detailed При вызове слота в таблицу добавляется новая строка и появляется окно ввода данных
*/
    void on_pushButton_clicked();
private slots:
/**
 * @brief Функция обновления таблицы
 * @detailed Осуществляется обновление таблицы, то есть в таблице отображаются лишь объекты,
 * которые принадлежат выбранной категории
 * @param item - выбранная категория объектов
 */
    void on_listWidget_itemClicked(QListWidgetItem *item);

/**
 * @brief Удаляет выбранный объект
 * @detailed Осуществляет удаление выбранного элемента из списка,
 * вызывается путем двойного клика на нужную строку
 * @param row - выбранная строка
 * @param column - выбраынный столбец
 */
    void on_tableWidget_cellDoubleClicked(int row, int column);

public:
    Ui::MainWindow *ui;
    static MainWindow* mainInstance;        ///< Указатель на главное окно
    void closeEvent(QCloseEvent *even);
    /**
     * @brief Функция для получения указателя на нужный QLineEdit
     * @param index - номер нужного QLineEdit
     * @return Указатель на QLineEdit
     */
    QLineEdit* getInstanceLine(int index);
    /**
     * @brief Функция для полусения указателя на QListWidget
     * @return Указатель на QListWidget
     */
    QListWidget* getInstanceListWidget();
    /**
     * @brief Функция получения указателя на QTable
     * @return Указатель на QTable
     */
    QTableWidget* getInstanceTable();
    QList<QAction*> list; ///< Список хранящий элементы QMenuBar
};

/**
 * @brief Класс объектов в QMenuBar
 */
class Action : public QAction
{
    Q_OBJECT
private slots:
/**
 * @brief Слот создания файла
 * @detailed При вызове слота вызывается QFileDialog, в котором вводим имя будущего файла
 */
    void push_slot_create();
/**
 * @brief Слот открытия файла
 * @detailed При вызове слота вызывается QFileDialog, в котором выбираем нужный файл,
 * который затем открывается и читается, если тот не пустой
 */
    void push_slot_open();
/**
 * @brief Слот сохранения данный в файл
 * @detailed При вызове слота cписок объектов сохоаняется в файл,
 * который был ранее создан или открыт
 */
    void push_slot_save();

};

/**
 * @brief Класс окна для ввода данных объекта
 * @detailed При добавлении нового элемента в список
 * с помощью этого класса создается новое окно
 * для ввода данных объекта
 */
class Widget_Form : public QWidget
{
    Q_OBJECT
    public:
        QLineEdit *line_name;                       /** < QLineEdit для ввода имени объекта*/
        QLineEdit *line_count;                      /** < QLineEdit для ввода количества экземпляров объекта*/
        QLineEdit *line_price;                      /** < QLineEdit для ввода цены объекта*/
        QLineEdit *line_date;                       /** < QLineEdit для ввода даты изготовления объекта*/
        QLineEdit *line_srok;                       /** < QLineEdit для ввода срока службы объекта*/
        QLineEdit *line_color;                      /** < QLineEdit для ввода цвета объекта*/
        QCalendarWidget *calendar;                  /** < Календарь для выбора даты изготовления объекта*/
        QPushButton *btn_selected_date;             /** < Кнопка для передачи выбранной даты в line_data*/
        QPushButton *btn_calendar;                  /** < Кнопка для появления(скрытия) календаря*/
/**
 * @brief Функция создания окна с вводом данных
 * @param main_win - главное окно
 */
        void create_window(MainWindow *main_win);
private slots:
/**
 * @brief Слот для проверки вводимых данных
 * @detailed Вызывается при нажатии на кнопку "Ok"б,
 * осуществляет проверку на пустоту всех QLineEdit,
 * если хотя бы 1 QLineEdit пустой то выводится
 * QMessegeBox с ошибкой о вводе данный,
 * если же все данный введены правильно,
 * то в список объектов добавляется объект с введёнными данными
 */
        void push_button_clicked_ok();
/**
 * @brief Слот отменяющий добавление объекта
 * @detailed При вызове слота прекращается ввод данных объекта,
 * закрывается окно для вводна дынных объекта
 */
        void push_button_clicked_cancel();
/**
 * @brief Слот для отображения(скрытия календаря)
 * @detailed При вызове слота календаот становится видимым,
 * если он был скрыт и наоборот невидимым, если был показан
 */
        void push_button_visible_calendar();
/**
 * @brief Слот выбора даты изготовления объекта
 * @detailed При вызове слота выбранная даты в календаре
 * переносится в line_date
 */
        void click_calendar();
};


#endif // MAINWINDOW_H
