#ifndef BLITZ_INCLUDE_CORE_DATA_HPP
#define BLITZ_INCLUDE_CORE_DATA_HPP

#include "internals/core_internals.hpp"

#include <deque>
#include <exception>
#include <iomanip>
#include <iostream>

#include "blitz.hpp"

namespace blitz {}
/*
template <typename T> class single_node {
public:
  single_node() : next(0), m_data({}) {}
  single_node(const T &_data) : next(0), m_data(_data) {}
  single_node(const single_node<T> &_node)
      : next(_node.next), m_data(_node.m_data) {}
  single_node(single_node<T> &&_node)
      : next(std::move(_node.next)), m_data(std::move(_node.m_data)) {}
  single_node<T> *next;
  T data() const { return m_data; }

private:
  T m_data;
};

template <typename T> class SinglyList {
  using node = single_node<T>;

public:
  SinglyList() {}

public:
  void insert(const T &_data) {
    auto _node = new node(_data);
    if (front == nullptr)
      front = _node;
    else {
      _node->next = front;
      front = _node;
    }
  }
  void insert(const T &_data, unsigned int position) {
    if (front == nullptr)
      insert(_data);
    else {
      auto _node = new node(_data);
      auto t_node = front;

      for (int i = 0; i < position; ++i) {
        t_node = t_node->next;
      }
      _node->next = t_node->next;
      t_node->next = _node;
    }
  }
  void remove(unsigned int position) {
    auto t_node = front;
    auto prev_node = t_node;
    for (int i = 0; i < position; ++i) {
      t_node = t_node->next;
    }
  }

  friend std::ostream &operator<<(std::ostream &strm,
                                  const SinglyList<T> &_list) {
    auto begin = _list.front;
    while (begin != nullptr) {
      strm << begin->data() << " ";
    }
    return strm << "\n";
  }

private:
  node *front;
  node *back;
  std::size_t m_size;
};

template <> class SinglyList<int> {

  using node = single_node<int>;

public:
  SinglyList() : front_(0), back_(0), size_(0) {}

public:
  unsigned int size() const { return size_; }

  void insert(const int &_data) {
    auto _node = new node(_data);
    if (front_ == nullptr) {
      front_ = _node;
      ++size_;
    } else {
      _node->next = front_;
      front_ = _node;
      ++size_;
    }
  }

  void insert(const int &_data, uint pos) {
    auto _node = new node(_data);
    auto t_node = front_;

    for (uint i = 1; i < pos; ++i) {
      if (t_node)
        t_node = t_node->next;
    }
    _node->next = t_node->next;
    t_node->next = _node;
    ++size_;
  }

  bool empty() { return size_ > 0 ? false : true; }

  void remove(const node &_node, uint position) {
    // auto _node = new no
  }

  void traverse() {
    auto begin = front_;
    if (!empty()) {
      while (begin != nullptr) {
        std::cout << begin->data() << " ";
        begin = begin->next;
      }
    }
  }

private:
  node *front_;
  node *back_;
  unsigned int size_;
};

template <typename T> class DoublyList {

  using node = DoubleNode<T>;

public:
  DoublyList() : head(0), tail(0) {}
  ~DoublyList() {}

public:
  int size() const { return size_; }
  void insert(const T &_data) {}
  void remove() {}
  void traverse() {}

private:
  node *head;
  node *tail;
  unsigned int size_{};
};

template <typename T, int _capacity> class Stack {
  using list = SinglyList<T>;

public:
  Stack() : capacity_(_capacity), top_(-1) { m_data = new list(); }

public:
  bool empty() const { return top_ < 0 ? true : false; }
  // T& top() const { return top_; }
  int size() const { return size_; }
  int capacity() const { return capacity_; }
  void resize(int _size) { capacity_ = _size; }
  void push(const T &_data) {
    if (top_ == capacity_ - 1) {
    } else {
      ++top_;
      ++size_;
      m_data->insert(_data);
    }
  }

  void traverse() const {
    if (!(empty())) {
      m_data->travese();
    }
  }

private:
  list *m_data;
  int top_{};
  int size_{};
  int capacity_{};
};

// Queue internally uses C-style array.
template <typename T, int N> class Queue {
public:
  Queue() {
    m_data = new T[N];
    front_ = 0;
    back_ = N - 1;
  }

private:
  T *m_data;
  T front_;
  T back_;
};

template <typename BufferValueType> class ring_buffer {
  using T = BufferValueType;

public:
  ring_buffer() = delete;
  ring_buffer(unsigned int size) : m_begin(0), m_end(0), m_size(size) {
    m_buffer = std::make_unique<T[]>(m_size);
  }

  T read() {
    T m_data = m_buffer[m_begin++];
    m_begin %= m_size;
    return m_data;
  }

  void write(const T &m_data) {
    m_buffer[m_end++] = m_data;
    m_end %= m_size;
  }

  unsigned int size() const { return m_size; }

private:
  std::unique_ptr<T[]> m_buffer;
  unsigned int m_size;
  int m_end;
  int m_begin;
};

template <typename K, typename E> class binary_search_tree {
public:
  using key_type = K;
  using value_type = E;
  using node = binary_node<key_type, value_type>;

  binary_search_tree() : root(0), node_count(0) {}
  ~binary_search_tree() { bst_clear(root); }

public:
  node *tree_root() const { return root; }

  // Resets the binary search tree
  void clear() {
    bst_clear(root);
    root = nullptr;
    node_count = 0;
  }

  void insert(const K &key, const E &value) {
    bst_insert(root, key, value);
    ++node_count;
  }
  E remove(const K &key) {
    auto tmp = bst_find(root, key);
    if (!tmp) {
      root = bst_remove(root, key);
      --node_count;
    }
    return tmp;
  }

  bool search(const K &key) { return bst_search(root, key); }

  unsigned int count() const { return node_count; }

private:
  void bst_clear(node *);
  node *bst_insert(node *, const K &, const E &);
  node *bst_delete_min(node *);
  node *bst_get_min(node *);
  node *bst_remove(node *, const K &);
  E bst_find(node *, const K &) const;
  void bst_print(node *, int) const;
  bool bst_search(node *, const K &);

  node *root;
  unsigned int node_count;
};

template <typename K, typename E>
bool binary_search_tree<K, E>::bst_search(node *_node, const K &_key) {
  if (!_node)
    return false;
  if (_node->key() == _key)
    return true;
  if (_key < _node->key())
    return bst_search(_node->left(), _key);
  else
    return bst_search(_node->right(), _key);
}

template <typename K, typename E>
E binary_search_tree<K, E>::bst_find(node *_node, const K &key) const {
  if (!_node)
    return nullptr;
  if (key < _node->key())
    return bst_find(_node->left(), key);
  else if (key > _node->key()) {
    return bst_find(_node->right(), key);
  } else
    return _node->key();
}

template <typename K, typename E>
core::binary_node<K, E> *binary_search_tree<K, E>::bst_insert(node *_node,
                                                        const K &key,
                                                        const E &value) {
  if (!_node)
    return new node(key, value);
  if (key < _node->key())
    _node->set_left(bst_insert(_node->left(), key, value));
  if (key > _node->key())
    _node->set_right(bst_insert(_node->right(), key, value));
  return _node;
}

template <typename K, typename E>
void binary_search_tree<K, E>::bst_clear(node *_node) {
  if (!_node)
    return;
  bst_clear(_node->left());
  bst_clear(_node->right());
  delete _node;
}

template <typename _Key, typename _Value> class complete_binary_tree;

template <typename _Key, typename _Value>
using kabh = complete_binary_tree<_Key, _Value>;

} // namespace blitz */

namespace core {

template <typename T> class stack {

protected:
  std::deque<T> _deque;

public:
  // Exception class for pop() and top() with empty stack.
  class empty_stack : public std::exception {
  public:
    virtual const char *what() const throw() { return "empty stack."; }
  };

public:
  void push(const T &item) { _deque.push_back(item); }

  T pop() {
    if (_deque.empty()) {
      throw empty_stack();
    }
    T elem(_deque.back());
    _deque.pop_back();
    return elem;
  }

  T &top() {
    if (_deque.empty()) {
      throw empty_stack();
    }
    return _deque.back();
  }

  typename std::deque<T>::size_type size() const { return _deque.size(); }

  bool empty() const { return _deque.empty(); }
};

template <typename T, unsigned N> class stack_v2 {

public:
  // Exception class for pop() and top() with empty stack.
  class empty_stack : public std::exception {
  public:
    virtual const char *what() const throw() { return "empty stack."; }
  };

public:
  stack_v2() : _size(-2), _data(new T[N]) {}
  void push(const T &item) {
    if (_size < N) {
      _data[_size] = item;
      ++_size;
    }
  }
  T pop() {
    if (_size < 0) {
      throw empty_stack();
    }
    T elem = _data[_size];
    return elem;
  }
  T &top();
  bool empty() const;
  int size() const;

private:
  T *_data;
  int _size;
  T *_top;
};



template <typename _Tp> class single_list {
public:
  using node = single_node<_Tp>;

  single_list() : head(0), _size(0) {}
  single_list(std::initializer_list<_Tp> coll) {
    for (auto const &elem : coll) {
      push_front(elem);
    }
  }
  single_list(const single_list &list) = delete;
  single_list(single_list &&list) = delete;

  single_list &operator=(const single_list &list) = delete;
  single_list &operator=(single_list &&list) = delete;
  ~single_list() { clear(); }

public:
  _Tp &operator[](int index) {
    if (!(0 <= index && index < _size)) {
      throw std::range_error("index is invalid.");
    } else {
      auto n0 = head;
      for (int i = 0; i < index - 1; ++i) {
        n0 = n0->next;
      }
      return n0->data;
    }
  }

  void insert(const _Tp &value, unsigned int index) {
    if (!(0 <= index && index < _size)) {
      throw std::range_error("index is invalid.");
    }
    node *n0 = new node(value);
    if (head == nullptr) {
      head == n0;
      ++_size;
    } else if (index == 0) {
      n0->next = head;
      head = n0;
      ++_size;
    } else {
      auto current_node = head;
      for (int i = 0; i < index - 1; ++i) {
        current_node = current_node->next;
      }
      n0->next = current_node->next;
      current_node->next = n0;
      ++_size;
    }
  }

  inline node &begin() const { return head; }

  _Tp front() const { return head->data; }

  void push_front(const _Tp &value) {
    node *n0 = new node(value);
    if (head == nullptr) {
      head = n0;
      ++_size;
    } else {
      n0->next = head;
      head = n0;
      ++_size;
    }
  }

  void pop_front() {
    if (head) {
      auto rnode = head;
      head = head->next;
      delete rnode;
      --_size;
    }
  }

  // Returns true is single_list is empty.
  inline bool empty() const noexcept { return _size == 0; }

  void clear() {
    if (head == nullptr)
      return;
    node *current;
    while (head != nullptr) {
      current = head;
      head = head->next;
      delete current;
    }
    _size = 0;
  }
  inline size_t size() const noexcept { return _size; }

  void traverse() noexcept {
    if (head == nullptr)
      return;

    node *_node = head;
    while (_node != nullptr) {
      std::cout << _node->data << " ";
      _node = _node->next;
    }
    std::cout << "\n";
  }

private:
  node *head;
  size_t _size;
};

template <typename T> class double_list;

template <typename E> void traverse(const double_list<E> &);

template <typename _Tp> class double_list {
public:
  using node = double_node<_Tp>;

  double_list() : head(nullptr), tail(head), _size(0) {}

  double_list(std::initializer_list<_Tp> coll) {
    for (auto const &elem : coll) {
      push_back(elem);
    }
  }

  _Tp &operator[](unsigned int index) {
    if (!(0 <= index && index < _size)) {
      throw std::range_error("index is invalid.");
    } else {
      auto n0 = head;
      for (int i = 0; i < index - 1; ++i) {
        n0 = n0->next;
      }
      return n0->data;
    }
  }

  ~double_list() { clear(); }

public:
  void push_back(const _Tp &value) {
    auto n0 = new node(value);
    if (head == nullptr) {
      head = tail = n0;
      ++_size;
    } else {
      n0->prev = tail;
      tail->next = n0;
      tail = n0;
      ++_size;
    }
  }

  void push_front(const _Tp &value) {
    node *n0 = new node(value);
    if (head == nullptr) {
      head = tail = n0;
      ++_size;
    } else {
      n0->next = head;
      head = n0;
      ++_size;
    }
  }

  void pop_back() noexcept {
    if (tail) {
      auto rnode = tail;
      tail = tail->prev;
      delete rnode;
      --_size;
    }
  }

  void pop_front() noexcept {
    if (head) {
      auto rnode = head;
      head = head->next;
      delete rnode;
      --_size;
    }
  }

  _Tp &front() const {
    if (!head) {
      throw std::runtime_error("trying to get _front from empty list.");
    }
    return head->data;
  }
  _Tp back() const {
    if (!tail) {
      throw std::runtime_error("trying to get _back from empty list.");
    }
    return tail->data;
  }

  void clear() {
    if (head == nullptr)
      return;

    node *current;
    while (head != nullptr) {
      current = head;
      head = head->next;
      delete current;
    }
    _size = 0;
  }

  bool empty() const { return _size == 0; }

  size_t size() const { return _size; }

  template <typename E> friend void core::traverse(const double_list<E> &);

  template <typename E>
  friend std::ostream &operator<<(std::ostream &, const double_list<E> &);

private:
  node *head;
  node *tail;
  size_t _size;
};

} // namespace core

namespace dsa {

template <typename E> class _list {
public:
  _list() {}

  virtual ~_list() {}

  virtual void clear() = 0;

  virtual void insert(const E &) = 0;

  virtual void append(const E &) = 0;

  virtual E remove() = 0;

  virtual void advance_begin() = 0;

  virtual void advance_end() = 0;

  virtual void prev() = 0;

  virtual void next() = 0;

  virtual int length() = 0;

  virtual int index() = 0;

  virtual void move() = 0;

  virtual const E &value() = 0;

private:
  // protect assingment operator and copy constructor
  void operator=(const _list &) {}
  _list(const _list &) {}
};

template <typename E> class array_list : public _list<E> {
public:
  array_list(int size = 8) {
    list_size = current_index = 0;
    max_size = size;
    data = new E[max_size];
  }

  ~array_list() { delete[] data; }

  void clear() {
    delete[] data;
    list_size = current_index = 0;
    data = new E[max_size];
  }

  void insert(const E &item) {
    if (list_size == max_size) {
      throw std::runtime_error("array_list: maximum capacity");
    }
    // for(i=list_size; )
  }

private:
  int max_size;
  int current_index;
  int list_size;
  E *data;
};

} // namespace dsa

#endif