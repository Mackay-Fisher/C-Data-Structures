#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {
    private:
    struct Node {
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() { node=nullptr; };
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            return node->data;
        }
        pointer operator->() const {
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() {
            node=node->next;
            return *this;
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            Node *temp = this->node;
            node=node->next;
            return basic_iterator(temp);
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
            node=node->prev;
            return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            Node *temp = this->node;
            node=node->prev;
            return basic_iterator(temp);
        }

        bool operator==(const basic_iterator& other) const noexcept {
            if (node==other.node)
            {
                return true;
            }
            else return false;
        }
        bool operator!=(const basic_iterator& other) const noexcept {
            if (node!=other.node)
            {
                return true;
            }
            else return false;
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() {
       head.next=&tail;
       tail.prev=&head;
       head.prev=nullptr;
       tail.next=nullptr;
       _size=0;
    }
    List( size_type count, const T& value ) {
        head.next=&tail;
        tail.prev=&head;
        head.prev=nullptr;
        tail.next=nullptr;
        Node *n=&head;
        for (int i = 0; i < count; i++)
        {
            Node *temp= new Node(T(value));
            n->next=temp;
            temp->prev=n;
            n=temp;
        }
        n->next=&tail;
        tail.prev=n;
        _size=count;
    }
    explicit List( size_type count ) {
        head.prev=nullptr;
        tail.next=nullptr;
        head.next=&tail;
        tail.prev=&head;
        Node *n=&head;
        for (int i = 0; i < count; i++)
        {
            Node *temp= new Node(T());
            n->next=temp;
            temp->prev=n;
            n=temp;
        }
        n->next=&tail;
        tail.prev=n;
        _size=count;
    }
    List(const List& other ) {
        head.prev=nullptr;
        tail.next=nullptr;
        head.next=&tail;
        tail.prev=&head;
        Node *a =&head;
        Node *b = other.head.next;
        for (int i = 0; i < other._size; i++)
        {
            Node *temp = new Node(b->data);
            a->next=temp;
            temp->prev=a;
            a=temp;
            b=b->next;
        }
        a->next=&tail;
        tail.prev=a;
        _size=other._size; 
    }
    List( List&& other ) {
        head.prev=nullptr;
        tail.next=nullptr;
        head.next=&tail;
        tail.prev=&head;
        Node *a =&head;
        Node *b = other.head.next;
        for (int i = 0; i < other._size; i++)
        {
            Node *temp = b;
            a->next=temp;
            temp->prev=a;
            a=temp;
            b=b->next;
        }
        a->next=&tail;
        tail.prev=a;
        _size=other._size;
        other._size=0;
        other.head.next=&other.tail;
        other.tail.prev=&other.head;
    }
    ~List() {
        Node *current = head.next;
        Node *movethr;
        while (current!=&tail)
        {
            movethr=current->next;
            delete current;
            current=movethr;
        }
        head.next=&tail;
        tail.prev=&head;
    }
    
    List& operator=( const List& other ) {
        if (this==&other)
        {
            return *this;
        }
        if (!this->empty())
        {
            this->~List();
        }
        Node *a =&head;
        Node *b = other.head.next;
        for (int i = 0; i < other._size; i++)
        {
            Node *temp = new Node(b->data);
            a->next=temp;
            temp->prev=a;
            a=temp;
            b=b->next;
        }
        a->next=&tail;
        tail.prev=a;
        _size=other._size; 
        return *this;
    }
    
    List& operator=( List&& other ) noexcept {
             if (this==&other)
        {
            return *this;
        }
        if (!this->empty())
        {
            this->~List();
        }
         Node *a =&head;
        Node *b = other.head.next;
        for (int i = 0; i < other._size; i++)
        {
            Node *temp = b;
            a->next=temp;
            temp->prev=a;
            a=temp;
            b=b->next;
        }
        a->next=&tail;
        tail.prev=a;
        _size=other._size;
        other._size=0;
        other.head.next=&other.tail;
        other.tail.prev=&other.head;
        return *this;
    }
    
    reference front() {
        return (head.next->data);
    }
    const_reference front() const {
        return (head.next->data);
    }
   
    reference back() {
        return (tail.prev->data);
    }
    
    const_reference back() const {
        return (tail.prev->data);
    }
    
    iterator begin() noexcept {
        return iterator(head.next);
    }
    
    const_iterator begin() const noexcept {
       return const_iterator(head.next);
    }
    
    const_iterator cbegin() const noexcept {
        return const_iterator(head.next);
    }
   
    iterator end() noexcept {
        return iterator (&tail);
    }
    
    const_iterator end() const noexcept {
        return const_iterator(&tail);
    }
    
    const_iterator cend() const noexcept {
        return const_iterator(&tail);
    }

    bool empty() const noexcept {
        if (_size==0)
        {
            return true;
        }
        return false;
    }

    size_type size() const noexcept {
        return _size;
    }

    void clear() noexcept {
        Node * current = head.next;
        Node *movethr;
        while (current!=&tail)
        {
            movethr=current->next;
            delete current;
            current=movethr;
        }
        _size=0;
        head.next=&tail;
        tail.prev=&head;
    }

    iterator insert( const_iterator pos, const T& value ) {
        Node *temp = new Node(value,pos.node->prev,pos.node);
        pos.node->prev=temp;
        temp->prev->next=temp;

        ++_size;
        return iterator(temp);
    }

    iterator insert( const_iterator pos, T&& value ) {

        Node *temp = new Node(std::move(value),pos.node->prev,pos.node);
        pos.node->prev=temp;
        temp->prev->next=temp;
        ++_size;
        return iterator(temp);
    }

    iterator erase( const_iterator pos ) {
        Node *temp = pos.node->prev;
        temp->next=pos.node->next;
        pos.node->next->prev=temp;
        delete pos.node;
        --_size;
        return iterator(pos.node->next);
    }

    void push_back( const T& value ) {
        Node *temp = new Node(value);
        tail.prev->next=temp;
        temp->prev=tail.prev;
        temp->next=&tail;
        tail.prev=temp;
        _size++;
    }

    void push_back( T&& value ) {
        Node *temp = new Node(std::move(value));
        tail.prev->next=temp;
        temp->prev=tail.prev;
        temp->next=&tail;
        tail.prev=temp;
        _size++;

    }

    void pop_back() {
        Node *a=tail.prev;
        tail.prev->prev->next=&tail;
        tail.prev=tail.prev->prev;
        delete a;
        _size--;
    }
	
    void push_front( const T& value ) {
        Node *temp = new Node(value);
        temp->next=head.next;
        temp->prev=&head;
        head.next->prev=temp;
        head.next=temp;
        _size++;
    }
	void push_front( T&& value ) {
        Node *temp = new Node(std::move(value));
        temp->next=head.next;
        temp->prev=&head;
        head.next->prev=temp;
        head.next=temp;
        _size++;
    }

    void pop_front() {
        delete head.next;
        head.next->next->prev=&head;
        head.next=head.next->next;
        _size--;
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}