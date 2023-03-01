#pragma once

#include <iostream>
#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>
#include <initializer_list>

template <typename Type>
class SingleLinkedList {
    // Узел списка

public:
    SingleLinkedList(){
    };
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };

    ~SingleLinkedList(){
        Clear();
    };


    SingleLinkedList(std::initializer_list<Type> values) {
    if (values.size() == 0) {return;}
        auto it = values.end();
        SingleLinkedList tmp;
        try{
        while (it != values.begin()){
            --it;
            tmp.PushFront(*it);

        }
                swap(tmp);
        // Реализуйте конструктор самостоятельно
    } catch(const std::bad_alloc&){
            tmp.Clear();
        throw "kon copy problem";
        }
        // Реализуйте конструктор самостоятельно

   }


    SingleLinkedList(const SingleLinkedList& other) {
        if (other.IsEmpty()){
            return ;}

        SingleLinkedList tmp;
               tmp = other;
                swap(tmp);

        // Реализуйте конструктор самостоятельно
    }

    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
       // assert(size_ == 0 && head_.next_node == nullptr);
        if (head_.next_node != rhs.head_.next_node) {
            SingleLinkedList tmp;
            SingleLinkedList tmp2;

       try{
            for (auto it = rhs.begin(); it != rhs.end(); ++it){
                tmp2.PushFront(*it);

            }

            for (auto it = tmp2.begin(); it != tmp2.end(); ++it){
                tmp.PushFront(*it);

            }

                swap(tmp);
            } catch(const std::bad_alloc&) {
                tmp.Clear();
                tmp2.Clear();
                throw;
            }


        }

        // Реализуйте присваивание самостоятельно
        return *this;
    }

    // Обменивает содержимое списков за время O(1)
    void swap(SingleLinkedList& other) noexcept {
        auto nn = head_.next_node;
        //Node head2 = other.head_;
        size_t size1 = size_;
        head_.next_node=other.head_.next_node;
        other.head_.next_node = nn;
        size_ = other.size_;
        other.size_ = size1;
        // Реализуйте обмен содержимого списков самостоятельно
    }


    // Возвращает количество элементов в списке за время O(1)
    [[nodiscard]] size_t GetSize() const noexcept {
        return size_;

    }

    // Сообщает, пустой ли список за время O(1)
    [[nodiscard]] bool IsEmpty() const noexcept {
        if (size_==0){return true;}
        // Заглушка. Реализуйте метод самостоятельно
        return false;
    }

    // Вставляет элемент value в начало списка за время O(1)
    void PushFront(const Type& value) {
        head_.next_node = new Node(value, head_.next_node);
        ++size_;
        // Реализуйте метод самостоятельно
    }

    // Очищает список за время O(N)
    void Clear() noexcept {

        while (head_.next_node != nullptr){
        Node* first = head_.next_node;
        head_.next_node = head_.next_node->next_node;
        delete first;
        }
        size_ = 0;
        // Реализуйте метод самостоятельно
    }

    // Шаблон класса «Базовый Итератор».
    // Определяет поведение итератора на элементы односвязного списка
    // ValueType — совпадает с Type (для Iterator) либо с const Type (для ConstIterator)
    template <typename ValueType>
    class BasicIterator {
        // Класс списка объявляется дружественным, чтобы из методов списка
        // был доступ к приватной области итератора
        friend class SingleLinkedList;

        // Конвертирующий конструктор итератора из указателя на узел списка
        explicit BasicIterator(Node* node): node_(node) {
        //    assert(false);
            // Реализуйте конструктор самостоятельно
        }

    public:
        // Объявленные ниже типы сообщают стандартной библиотеке о свойствах этого итератора

        // Категория итератора — forward iterator
        // (итератор, который поддерживает операции инкремента и многократное разыменование)
        using iterator_category = std::forward_iterator_tag;
        // Тип элементов, по которым перемещается итератор
        using value_type = Type;
        // Тип, используемый для хранения смещения между итераторами
        using difference_type = std::ptrdiff_t;
        // Тип указателя на итерируемое значение
        using pointer = ValueType*;
        // Тип ссылки на итерируемое значение
        using reference = ValueType&;

        BasicIterator() = default;

        // Конвертирующий конструктор/конструктор копирования
        // При ValueType, совпадающем с Type, играет роль копирующего конструктора
        // При ValueType, совпадающем с const Type, играет роль конвертирующего конструктора
        BasicIterator(const BasicIterator<Type>& other) noexcept {
            //assert(false);
            node_ = other.node_;
            // Реализуйте конструктор самостоятельно
        }


        // Чтобы компилятор не выдавал предупреждение об отсутствии оператора = при наличии
        // пользовательского конструктора копирования, явно объявим оператор = и
        // попросим компилятор сгенерировать его за нас
        BasicIterator& operator=(const BasicIterator& rhs) = default;

        // Оператор сравнения итераторов (в роли второго аргумента выступает константный итератор)
        // Два итератора равны, если они ссылаются на один и тот же элемент списка либо на end()
        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            //assert(false);
            return node_ == rhs.node_;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        // Оператор проверки итераторов на неравенство
        // Противоположен !=
        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
            //assert(false);
            return rhs.node_ != node_;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        // Оператор прединкремента. После его вызова итератор указывает на следующий элемент списка
        // Возвращает ссылку на самого себя
        // Инкремент итератора, не указывающего на существующий элемент списка, приводит к неопределённому поведению
        BasicIterator& operator++() noexcept {
            //assert(false);
            node_ = node_->next_node;
            return *this;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        // Оператор постинкремента. После его вызова итератор указывает на следующий элемент списка
        // Возвращает прежнее значение итератора
        // Инкремент итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        BasicIterator operator++(int) noexcept {
            //assert(false);
            BasicIterator old_node(*this);
            node_ = node_->next_node;
            return old_node;
            // Заглушка. Реализуйте оператор самостоятельно
        }

        // Операция разыменования. Возвращает ссылку на текущий элемент
        // Вызов этого оператора у итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        [[nodiscard]] reference operator*() const noexcept {
            //assert(false);
            // Не реализовано
            // Заглушка. Реализуйте оператор самостоятельно
            return node_->value;
        }

        // Операция доступа к члену класса. Возвращает указатель на текущий элемент списка
        // Вызов этого оператора у итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        [[nodiscard]] pointer operator->() const noexcept {
            //assert(false);
            return &node_->value;
            // Заглушка. Реализуйте оператор самостоятельно

        }



    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    // Итератор, допускающий изменение элементов списка
    using Iterator = BasicIterator<Type>;
    // Константный итератор, предоставляющий доступ для чтения к элементам списка
    using ConstIterator = BasicIterator<const Type>;

    // Возвращает итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    [[nodiscard]] Iterator begin() noexcept {
        return Iterator(head_.next_node);
        //assert(false);
        // Реализуйте самостоятельно

    }

    // Возвращает итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] Iterator end() noexcept {
        return {Iterator(nullptr)};
        //assert(false);
        // Реализуйте самостоятельно

    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    // Результат вызова эквивалентен вызову метода cbegin()
    [[nodiscard]] ConstIterator begin() const noexcept {
        //assert(false);
        // Реализуйте самостоятельно
        return {ConstIterator(head_.next_node)};
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    // Результат вызова эквивалентен вызову метода cend()
    [[nodiscard]] ConstIterator end() const noexcept {
        //assert(false);
        // Реализуйте самостоятельно
        return {ConstIterator(nullptr)};
    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен cend()
    [[nodiscard]] ConstIterator cbegin() const noexcept {
        //assert(false);
        // Реализуйте самостоятельно
        return {ConstIterator(head_.next_node)};
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator cend() const noexcept {
        //assert(false);
        // Реализуйте самостоятельно
        return {ConstIterator(nullptr)};
    }

    //--------------------------------------------------------------


        // Возвращает итератор, указывающий на позицию перед первым элементом односвязного списка.
        // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
        [[nodiscard]] Iterator before_begin() noexcept {
            // Реализуйте самостоятельно
            return {Iterator(&head_)};
        }

        // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
        // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
        [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
            // Реализуйте самостоятельно

            return {ConstIterator{const_cast<Node *>(&head_)}};
        }

        // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
        // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
        [[nodiscard]] ConstIterator before_begin() const noexcept {
        return {ConstIterator(&head_)};
        }

        /*
         * Вставляет элемент value после элемента, на который указывает pos.
         * Возвращает итератор на вставленный элемент
         * Если при создании элемента будет выброшено исключение, список останется в прежнем состоянии
         */
        Iterator InsertAfter(ConstIterator pos, const Type& value) {
            // Заглушка. Реализуйте метод самостоятельно
            Node* InNode = new Node(value, pos.node_->next_node);
            pos.node_->next_node = InNode;
            size_++;
            return {Iterator(InNode)};
        }

        void PopFront() noexcept {
           Node* a = head_.next_node;
           head_.next_node = a->next_node;
           delete a;
           size_--;
            // Реализуйте метод самостоятельно
        }

        /*
         * Удаляет элемент, следующий за pos.
         * Возвращает итератор на элемент, следующий за удалённым
         */
        Iterator EraseAfter(ConstIterator pos) noexcept {
            Node *Enode = pos.node_->next_node;
            pos.node_->next_node = Enode->next_node;
            delete Enode;
            // Заглушка. Реализуйте метод самостоятельно
            return {Iterator(pos.node_->next_node)};
        }

    //--------------------------------------------------------------



private:
    // Фиктивный узел, используется для вставки "перед первым элементом"
    Node head_;
    size_t size_ = 0;

};

//----------------------------------------------------

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    // Реализуйте обмен самостоятельно
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    bool e = std::equal(lhs.begin(), lhs.end(), rhs.begin());
   // if (e) {return false;}
    e = std::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
    // Заглушка. Реализуйте сравнение самостоятельно
    return e;
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    bool e = std::equal(lhs.begin(), lhs.end(), rhs.begin());
    if (e) {return true;}
    return std::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    bool e = std::equal(lhs.begin(), lhs.end(), rhs.begin());
    if (e) {return false;}
    return !std::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    bool e = std::equal(lhs.begin(), lhs.end(), rhs.begin());
    if (e) {return true;}
    return !std::lexicographical_compare(lhs.begin(), lhs.end(),rhs.begin(), rhs.end());
}
