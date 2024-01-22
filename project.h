#ifndef PROJECT_H
#define PROJECT_H

#include <QMainWindow>
#include "linkedlist.h"
#include "hashtable.h" // Include the HashTable header if needed


QT_BEGIN_NAMESPACE
namespace Ui {
class project;
}
QT_END_NAMESPACE

class project : public QMainWindow
{
    Q_OBJECT

public:
    project(QWidget *parent = nullptr);
    ~project();
    void loadAndDisplayTasks();
    void handleCheckBoxStateChanged(const QString& description, const QString& date, Priority priority, int state);


private slots:
    void on_btnAdd_clicked();
    void saveTask(const Task &task);
    void loadTasks();
    void displayTasks();
private:
    Ui::project *ui;
    LinkedList myLinkedList;
    HashTable myHashTable;
};
#endif // PROJECT_H
