#ifndef STRUCT_H
#define STRUCT_H

#include <QStringList>
#include <QTableWidget>
#include <QMainWindow>
#include <QFile>


/**
 * @brief Cтруктура, хранящая данные объекта
 */
struct data
{
    int id;                 ///< идентификационный номер
    char name_categor[25];  ///< наименование категории, к которой принадлежит объект
    QString name;           ///< наименование объекта
    int price;              ///< цена объекта
    int count;              ///< количество экземпляров объекта
    QString color;          ///< цвет объекта
/**
 * @brief Структура, которая хранит данные о дате изготовления объекта
 */
    struct _date
    {
        public:
            int day;        ///< день изготовления объекта
            int month;      ///< месяц изготовления объекта
            int year;       ///< год изготовления объекта
    }date;
    QString life;           ///< строк службы объекта

     data *next;            ///< указатель на следующую структуру в списке
     data *prev;            ///< указатель на предыдущую структуру в списке
};


/**
 * @brief Класс для работы со списком объектов
 * @detailed Осуществляет добавление, удаление одного элемента из списка,
 * удаление всех объектов из списка, сохрание списка в файл,
 * открытие файл и чтение списка(если тот существует в файле)
 */
class List
{
    const char *filename = new char[25];
    public:
        data *head,*cursor;                                     ///< Указатель на первый элемент, указатель на любой элемент списка
        int last_id=0;                                          ///< id последнего объекта
        QString filename_perem;
        const char *name_categor[6]={"Electronics",
                                     "Furniture",
                                     "Clothes",
                                     "Phones",
                                     "Computer equipment",
                                     "Toys"};
        int count_in_cat[6]={0, //Электроника
                             0, //Мебель
                             0, //Одежда
                             0, //Телефоны
                             0, //Компьютерные компоненты
                             0};//Игрушки
        int count_all;                                          ///< Количество всех элементов в списке
        List():head(nullptr),cursor(nullptr){};
/**
 * @brief Функция добавления объекта в список
 * @param id - идентификационный номер
 * @param name_categor - наименование категории, к которой принадлежит объект
 * @param name - наименование объекта
 * @param price - цена объекта
 * @param count - количество экземпляров объекта
 * @param color - цвет объекта
 * @param day - день изготовления объекта
 * @param month - месяц изготовления объекта
 * @param year - год изготовления объекта
 * @param life - строк службы объекта
 */
        void Add(int id, const char *name_categor, QString name, int price,
                 int count, QString color, int day, int month, int year, QString life);
/**
 * @brief Функция удаления объекта из списка
 * @param element - указатель на объект, который нужн удалить из списка
 */
        void DeleteElement(data *element);
        /**
 * @brief Функция обновления таблицы
 * @detailed Осуществляется обновление таблицы,
 * после которого отображаются только объекты выбранной категории
 * @param table - указатель на таблицу, которую нужно обновить
 * @param index_categor - номер выбранной категории
 */
        void refresh_table(QTableWidget *table, int index_categor);
/**
 * @brief Функция сохранения данный в файл
 * @detailed При вызове слота cписок объектов сохоаняется в файл,
 * который был ранее создан или открыт
 */
        void save_in_file();
/**
 * @brief Слот открытия файла
 * @detailed При вызове слота вызывается QFileDialog, в котором выбираем нужный файл,
 * который затем открывается и читается, если тот не пустой
 */
        void open_file();
/**
 * @brief Функция создания файла
 * @detailed При вызове слота вызывается QFileDialog, в котором вводим имя будущего файла
 */
        void create_file();
/**
 * @brief Функция удаления всех объектов из списка
 */
        void delete_all_elements();
/**
  @brief Деструктор
*/
        ~List();



};

#endif // STRUCT_H
