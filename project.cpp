#include "project.h"
#include "ui_project.h"
#include "newtask.h"
#include <QVBoxLayout>
#include <QFile>
#include <QDataStream>
#include<QCheckBox>//////>

project::project(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::project)
{
    ui->setupUi(this);

    // Load saved tasks when the GUI is created
    loadAndDisplayTasks();
}
project::~project()
{
    delete ui;
}

void project::on_btnAdd_clicked()
{
    newTask n(myLinkedList, myHashTable, this);
    n.setModal(true);
    n.exec();

    // Retrieve the Task object from newTask
    Task taskObject = n.getTaskObject();

    // Save the Task object to a binary file
    saveTask(taskObject);

    // Display the saved tasks on the GUI
    displayTasks();
}

void project::saveTask(const Task &task)
{
    QFile file("taskkk.bin");
    if (file.open(QIODevice::Append)) {
        QDataStream out(&file);
        out << task;
        file.close();
    }
}

void project::loadTasks()
{
    QFile file("taskkk.bin");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        while (!in.atEnd()) {
            QString description, date;
            Priority priority;
            in >> description >> date >> priority;

            // Create a Task object
            Task task(description, date, priority);

            // Insert the task into linked list
            myLinkedList.insertLL(task);

            // Insert the task into hash table
            myHashTable.insertH(task);
        }
        file.close();
    }
}


void project::displayTasks()
{
    // Clear existing layout
    QLayout *layout = ui->scrollArea->layout();
    if (layout) {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete layout;
    }

    // Create a new layout
    QVBoxLayout *newLayout = new QVBoxLayout(ui->scrollArea);

    // Load and display tasks from the binary file
    QFile file("taskkk.bin");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        while (!in.atEnd()) {
            QString description, date;
            Priority priority;

            // Read the task details from the file
            in >> description >> date >> priority;

            // Create a new QCheckBox with the task details
            QCheckBox *checkBox = new QCheckBox(
                QString("%1 - Date: %2").arg(description).arg(date),
                ui->scrollArea);

            // Apply style sheet to strike out text when checked
            checkBox->setStyleSheet("QCheckBox:checked { color: gray; text-decoration: line-through; }");

            // Connect a slot to handle the stateChanged signal
            connect(checkBox, &QCheckBox::stateChanged, [this, description, date, priority](int state) {
                handleCheckBoxStateChanged(description, date, priority, state);
            });

            newLayout->addWidget(checkBox);
        }
        file.close();
    }
}

void project::handleCheckBoxStateChanged(const QString& description, const QString& date, Priority priority, int state)
{
    if (state == Qt::Checked) {
        // Handle the checked state, e.g., update the underlying data structures
        // You may want to update the linked list or hash table based on the checked state
        // For demonstration purposes, I'm printing a message
        qDebug() << "Task Checked - Description: " << description << " Date: " << date << " Priority: " << priority;
    } else {
        // Handle the unchecked state, if needed
        qDebug() << "Task Unchecked - Description: " << description << " Date: " << date << " Priority: " << priority;
    }
}
void project::loadAndDisplayTasks()
{
    // Clear existing layout
    QLayout *layout = ui->scrollArea->layout();
    if (layout) {
        QLayoutItem *child;
        while ((child = layout->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
        delete layout;
    }

    // Create a new layout
    QVBoxLayout *newLayout = new QVBoxLayout(ui->scrollArea);

    // Load and display tasks from the binary file
    QFile file("taskkk.bin");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        while (!in.atEnd()) {
            QString description, date;
            Priority priority;

            // Read the task details from the file
            in >> description >> date >> priority;

            // Create a new QCheckBox with the task details
            QCheckBox *checkBox = new QCheckBox(
                QString("%1 - Date: %2").arg(description).arg(date),
                ui->scrollArea);

            // Apply style sheet to strike out text when checked
            checkBox->setStyleSheet("QCheckBox:checked { color: gray; text-decoration: line-through; }");

            // Connect a slot to handle the stateChanged signal
            connect(checkBox, &QCheckBox::stateChanged, [this, description, date, priority](int state) {
                handleCheckBoxStateChanged(description, date, priority, state);
            });

            newLayout->addWidget(checkBox);
        }
        file.close();
    }
}
