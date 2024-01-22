#include "linkedlist.h"
#include <QDebug>
#include<QFile>
#include<hashtable.h>//
LinkedList::LinkedList()
{
    First = nullptr;
}

LinkedList::~LinkedList()
{
    Node* current = First;
    while (current != nullptr)
    {
        Node* ptr = current->next;
        delete current;
        current = ptr;
    }
}

void LinkedList::insertLL(const Task& task, HashTable& hashTable) {
    // Insert into linked list
    Node* newNode = new Node(task);
    newNode->next = First;
    First = newNode;

    // Sort the linked list by due date and priority
    SortPriority();

    // Insert into the provided hash table
    hashTable.insertH(task);

    // Append task details to "tasks.txt"
    QFile file("tasks.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Date: " << task.date << " Priority: " << task.priority << " Description: " << task.description << Qt::endl;
        file.close();
    } else {
        // Handle the case where the file couldn't be opened
        qDebug() << "Failed to open the file for writing: " << file.errorString();
    }
}




void LinkedList::printTasksLL()
{
    QFile file ("TasksH.txt");
    QFile Bfile("Tasks.bin");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)&&
        Bfile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        QTextStream out2(&Bfile);

        Node* current = First;
        while (current != nullptr)
        {
            out << "Date: " << current->task.date;out2<<current->task.date;
            out << " Priority: " << current->task.priority;out2<<current->task.priority;
            out<< " Description: " << current->task.description << Qt::endl;out2<<current->task.description;
            current = current->next;
        }
        file.close();
        Bfile.close();
    }
    else {
        // Handle the case where the file couldn't be opened
        qDebug() << "Failed to open the file for writing: " << file.errorString();
    }
}

void LinkedList::removeLL(const QString& date)
{
    Node* current = First;
    Node* prev = nullptr;

    while (current != nullptr && current->task.date != date) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev == nullptr) {
            First = current->next;
        }
        else {
            prev->next = current->next;
        }
        delete current;
    }
}

void LinkedList::SortPriority()
{
    if (First == nullptr || First->next == nullptr) return;
    Node* current = First;
    Node* nextNode = nullptr;

    while (current != nullptr)
    {
        nextNode = current->next;
        while (nextNode != nullptr)
        {
            if (current->task.priority < nextNode->task.priority)
            {
                std::swap(current->task, nextNode->task);
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}

bool LinkedList::isEmpty() const
{
    return First == nullptr;
}

Task LinkedList::searchLL(const QString& date) const
{
    Node* current = First;
    while (current != nullptr)
    {
        if (current->task.date == date)
        {
            return current->task; // Found the task
        }
        current = current->next;
    }
    return Task("", "", Priority());
}
void LinkedList::loadTasksFromFile()
{
    QFile file("Tasks.bin");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString description, date;
            int priority; // Read as int

            // Read the task details from the file
            in >> date >> priority >> description;

            // Create a Task object
            Task task(description, date, static_cast<Priority>(priority));

            // Insert the task into the linked list
            insertLL(task);
        }
        file.close();
    }
}
