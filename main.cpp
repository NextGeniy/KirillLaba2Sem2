#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <chrono>
using namespace std;


struct Node//структура, описывающая 1 элемент списка
{
    int data;//данные
    Node* prev;//поле содеражащее адрес на предыдущий элемент
    Node* next;// поле содержащее адрес на след эл
    Node(int data)
    {
        this->data = data;//передаем данные и копируем их
        this->prev = this->next = NULL;
    }
    
};

struct TipList //структура для типовых операций при работе со списком
{
    Node* head, * tail; //указатели ссылаются на элементы списка
    TipList()//нет обьектов списка поэтому значения 0
    {
        head = tail = NULL;
    }
    ~TipList() {
        while (head!=NULL)
        {
            delete_felem();
        }
    }
    //добавление элемента в конец
    Node* add_elem(int data) 
    {
        Node* ptr = new Node(data);//указатель на новый обьект
        ptr->prev = tail;
        if (tail != NULL)
            tail->next = ptr;
        if (head == NULL)
            head = ptr;
        tail = ptr;
        return ptr;
    }
    Node* add_elem2(int data)
    {
        Node* ptr = new Node(data);//указатель на новый обьект
        ptr->next = head;
        if (head != NULL)
            head->prev = ptr;
        if (tail == NULL)
            tail = ptr;
        head = ptr;
        return ptr;
    }
    
    //удаление 1 элемента двусвязного списка
    void delete_felem()//удаляется только первый элемент
    {
        if (head == NULL)return;
        Node* ptr = head->next;
        if (ptr != NULL)
            ptr->prev = NULL;
        
        else 
            tail == ptr;
        
        delete head;
        head = ptr;
    }
    void delete_lelem()//удаляется только первый элемент
    {
        if (tail == NULL)return;
        Node* ptr = tail->prev;
        if (ptr != NULL)
            ptr->next = NULL;

        else
            head == ptr;

        tail = ptr;//при удаления 1 елемента только
    }
    void erase_elem(int index) 
    {
        Node* ptr = get_elem(index);
        if (ptr == NULL)return;

        if (ptr->prev == NULL)
        {
            delete_felem();
            return;
        }

        if (ptr->next == NULL)
        {
            delete_lelem();
            return;
        }
        Node* l = ptr->prev;
        Node* r = ptr->next;
        l->next = r;
        r->prev = l;
        delete ptr;

    }
    //получение элемента
    Node* get_elem(int index)
    {
        Node* ptr = head;
        int n = 0;
        while (n != index)
        {
            if (ptr == NULL)
                return ptr;
            ptr = ptr->next;
            n++;
        }
        return ptr;

    }
    Node* operator[] (int Index) {
        return get_elem(Index);
    }
    //вставка элемента
    Node* insert_elem(int index, int data)
    {
        Node* r = get_elem(index);
        if (r == NULL)
            return add_elem(data);
        Node* l = r->prev;
        if (r == NULL)
            return add_elem2(data);
        Node* ptr = new Node(data);
        ptr->prev = l;
        ptr->next = r;
        l->next = ptr;
        r->prev = ptr;
        return ptr;
    }
    
    void show()
    {
        Node* temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }

    }
    void swap(int index, int index2)
    {
        Node* temp = head;
        for (int i = 0; i < index; i++)
        {
            temp = temp->next;

        }
        Node* temp1 = head;
        for (int i = 0; i < index2; i++)
        {
            temp1 = temp1->next;
        }
        int k = temp->data;
        temp->data = temp1->data;
        temp1->data = k;
    }
};


int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    TipList spisok;
    int choose = 0;
    int deystv = 0;
    do {
        auto start = chrono::steady_clock::now();
        auto end = chrono::steady_clock::now();
        cout << "Выберите вариант: " << endl;
        cout << "1 - Введите количество элементов в списке" << endl;
        cout << "2 - введите в консоль элементы списка" << endl;
        cout << "3 - Работа со спиком" << endl;
        cout << "4 - Выход из программы" << endl;
        cin >> choose;
        int length = 0;
        switch (choose)
        {
            
        case 1:
            cout << "Введите длинну списка: " << endl;
            cin >> length;
            cout << "Список: " << endl;
            start = chrono::steady_clock::now();
            for (int i = 0; i < length; i++)
            {
                int data = rand() % 100;
                spisok.add_elem(data);

            }
            end = chrono::steady_clock::now();
            spisok.show();
            cout << "Время создания списка: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " наносекунд" << endl;
            system("pause");
            break;
        case 2:

            int data;
            cin >> data;
            while (data != -1)
            {
                spisok.add_elem(data);
                cin >> data;
            }
            system("pause");
            break;
        case 3:
            do
            {
                cout << endl << "Выберите действие со списком: " << endl;
                cout << "1 - Вывести элемент списка: " << endl;
                cout << "2 - Встваить элемент в любую позицию списка: " << endl;
                cout << "3 - Поменять 2 любых элемента в списке: " << endl;
                cout << "4 - Удалить любой элемент в списке: " << endl;
                cout << "5 - Выход из операций со списком: " << endl;


                cin >> deystv;
                switch (deystv)
                {
                case 1:
                    cout << "Введите индекс элемента, который хотите вывести" << endl;
                    int index;
                    cin >> index;
                    start = chrono::steady_clock::now();
                    cout << spisok[index]->data << endl;
                    end = chrono::steady_clock::now();
                    
                    cout << "Время получения элемента списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                    break;
                case 2:
                    int data, head;
                    cin >> index;
                    cin >> data;
                    start = chrono::steady_clock::now();
                    spisok.insert_elem(index, data);
                    end = chrono::steady_clock::now();
                    spisok.show();
                    cout << "Время вставки элемента списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                    break;
                case 3:
                    cout << "Исходный список" << endl;
                    spisok.show();
                    int index2;
                    cout << "Первый индекс" << endl;
                    cin >> index;
                    cout << "Второй индекс" << endl;
                    cin >> index2;
                    start = chrono::steady_clock::now();
                    spisok.swap(index, index2);
                    end = chrono::steady_clock::now();
                    cout << "Измененный список" << endl;
                    spisok.show();
                    cout << "Время обмена элементов списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                    break;
                case 4:
                {
                    int del;
                    cin >> del;
                    start = chrono::steady_clock::now();
                    spisok.erase_elem(del);
                    end = chrono::steady_clock::now();
                    spisok.show();
                    cout << "Время удаления элементов списка: "
                        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
                        << " наносекунд" << endl;
                    system("pause");
                }
                break;
                }
            } while (deystv != 5);
            break;
        }
        
    }while (choose != 4);
    return 0;
}
