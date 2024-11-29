#include <iostream>
#include <stack>
#include <algorithm>

template <typename T>
struct Node {
  Node* left;
  Node* right;
  Node* parent;
  T* key;

  Node(const T& key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}
  Node(): left(nullptr), right(nullptr), parent(nullptr) {}
};

class InOrder{

};

class PostOrder{

};

class PreOrder{

};

template <typename T, class Order, class Compare = std::less<T>,
    class Allocator = std::allocator<T> >
class BST {
 private:
  typedef Node<T> node;
  typedef T value_type;
  typedef const node &const_reference;
  typedef size_t size_type;
  typedef Allocator allocator_type;

  Order type_order;
  size_type size_ = 0;
  size_type max_size_ = 150;
  node *root = nullptr;
  Compare compare;
  allocator_type allocator;

 public:
  BST() : size_(0), root(nullptr) {}

  BST(const BST &other) : size_(other.size_) {
    Travel(root, other.root);
  }
  void Travel(node* set, node* get) {
    if (get != nullptr) {
      if (set == nullptr){
        set = new node[1];
      }
      set->key = allocator.allocate(1);
      *set->key = *get->key;
      if (get->left != nullptr) {
        set->left = new node[1];
        Travel(set->left, get->left);
      }
      if (get->right != nullptr) {
        set->right = new node[1];
        Travel(set->right, get->right);
      }
    }
  }

  BST(std::initializer_list<T> element) {
    this->insert(element);
  }

  BST& operator=(BST other) {
    Travel(root, other.root);
    size_ = other.size_;

    return *this;
  }

  class iterator {
   public:

    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef int difference_type;
    typedef const T *pointer;
    typedef T reference;

    iterator(Node<value_type>* node, Order temp_order, Node<value_type> *root)
        : now_node(node), now_order(temp_order), root(root) {}
    iterator(const iterator &right)
        : now_node(right.now_node),
          now_order(right.now_order),
          root(right.root) {}

    const iterator operator=(iterator right) {
      now_node = right.now_node;
      now_order = right.now_order;
      root = right.root;;

      return *this;
    }

    const iterator operator++() {
      return plus(now_order);
    }

    const iterator operator--() {
      return prev(now_order);
    }

    const iterator operator++(int i) {
      iterator current(*this);
      ++(*this);
      return current;
    }

    const iterator operator--(int i) {
      iterator current(*this);
      --(*this);
      return current;
    }

    void PreOrder_travel(node *&temp_node, std::vector<T> &res) {
      if (temp_node != nullptr) {
        res.push_back(*temp_node->key);
        PreOrder_travel(temp_node->left, res);
        PreOrder_travel(temp_node->right, res);
      }
    }

    void Find_Element(node *temp_node, const T &temp_key) {
      if (temp_node != nullptr) {
        if (*temp_node->key == temp_key) {
          now_node = temp_node;
        }
        Find_Element(temp_node->left, temp_key);
        Find_Element(temp_node->right, temp_key);
      }
    }

    iterator plus(PreOrder preorder) {
      std::vector<T> res;
      PreOrder_travel(root, res);
      size_type temp_index = -1;
      for (size_t i = 0; i < res.size(); i++) {
        if (res[i] == *now_node->key) {
          temp_index = i + 1;
        }
      }
      if (temp_index < res.size()) {
        Find_Element(root, res[temp_index]);
      } else {
        now_node = nullptr;
      }
      return *this;
    }

    void InOrder_travel(node *temp_node, std::vector<T> &res) {
      if (temp_node != nullptr) {
        InOrder_travel(temp_node->left, res);
        res.push_back(*temp_node->key);
        InOrder_travel(temp_node->right, res);
      }
    }

    iterator plus(InOrder in_order) {
      std::vector<T> res;
      InOrder_travel(root, res);
      size_type temp_index = -1;
      for (size_t i = 0; i < res.size(); i++) {
        if (res[i] == (*now_node->key)) {
          temp_index = i + 1;
        }
      }
      if (temp_index < res.size()) {
        Find_Element(root, res[temp_index]);
      } else {
        now_node = nullptr;
      }
      return *this;
    }

    void PostOrder_travel(node *&temp_node, std::vector<T> &res) {
      if (temp_node != nullptr) {
        PostOrder_travel(temp_node->left, res);
        PostOrder_travel(temp_node->right, res);
        res.push_back(*temp_node->key);
      }
    }

    iterator plus(PostOrder postorder) {
      std::vector<T> res;
      PostOrder_travel(root, res);
      size_type temp_index = -1;
      for (size_t i = 0; i < res.size(); i++) {
        if (res[i] == *now_node->key) {
          temp_index = i + 1;
        }
      }
      if (temp_index < res.size()) {
        Find_Element(root, res[temp_index]);
      } else {
        now_node = nullptr;
      }
      return *this;
    }

    iterator prev(InOrder in_order) {
      std::vector<T> res;
      InOrder_travel(root, res);
      long long temp_index = -1;
      for (size_t i = 0; i < res.size(); i++) {
        if (now_node != nullptr) {
          if (res[i] == *now_node->key) {
            temp_index = i - 1;
          }
        }
      }
      if (now_node == nullptr) {
        Find_Element(root, res[res.size() - 1]);
      } else if (temp_index != -1) {
        Find_Element(root, res[temp_index]);
      } else {
        now_node = nullptr;
      }
      return *this;
    }

    iterator prev(PreOrder preorder) {
      std::vector<T> res;
      PreOrder_travel(root, res);
      long long temp_index = -10;
      for (size_t i = 0; i < res.size(); i++) {
        if (now_node != nullptr) {
          if (res[i] == *now_node->key) {
            temp_index = i - 1;
          }
        }
      }
      if (now_node == nullptr) {
        Find_Element(root, res[res.size() - 1]);
      } else if (temp_index != -1) {
        Find_Element(root, res[temp_index]);
      } else {
        now_node = nullptr;
      }
      return *this;
    }

    iterator prev(PostOrder postorder) {
      std::vector<T> res;
      PostOrder_travel(root, res);
      long long temp_index = -1;
      for (size_t i = 0; i < res.size(); i++) {
        if (now_node != nullptr) {
          if (res[i] == *now_node->key) {
            temp_index = i - 1;
          }
        }
      }
      if (now_node == nullptr) {
        Find_Element(root, res[res.size() - 1]);
      } else if (temp_index != -1) {
        Find_Element(root, res[temp_index]);
      } else {
        now_node = nullptr;
      }
      return *this;
    }

    bool operator==(const iterator &right) {
      if (right.now_node == now_node) {
        return true;
      }
      return false;
    }

    bool operator!=(const iterator &right) {
      if (right.now_node != now_node) {
        return true;
      }
      return false;
    }

    value_type operator*() const {
      if (now_node != nullptr) {
        return *now_node->key;
      }
    }

    ~iterator() {

    }

    Node<value_type> *cur_node() const {
      return now_node;
    }

   private:
    Node<value_type> *now_node;
    Node<value_type> *root;
    Order now_order;
  };

  iterator begin() {
    if (size_ != 0) {
      return iterator(first_element(type_order), type_order, root);
    }
    return iterator(nullptr, type_order, nullptr);
  }

  const Compare key_comp(){
    return compare;
  }

  const Compare value_comp(){
    return compare;
  }

  const iterator end() {
    return iterator(nullptr, type_order, root);
  }

  size_t size() {
    return size_;
  }

  bool operator==(BST right) {
    return (size_ == right.size()) && std::equal(this->begin(), this->end(), right.begin());
  }

  bool operator!=(BST right) {
    if (*this == right) {
      return false;
    }
    return true;
  }

  bool empty() const {
    return size_ == 0;
  }

  template<class OtherIterator>
  BST(OtherIterator iterator_first, OtherIterator iterator_second) {
    this->insert<OtherIterator>(iterator_first, iterator_second);
  }

  template<class OtherIterator>
  void insert(OtherIterator iterator_first, OtherIterator iterator_second) {
    while (iterator_first != iterator_second) {
      this->insert(*iterator_first);
      ++iterator_first;
    }
  }

  template<class iterators>
  const iterator erase(iterators iterator_first, iterators iterator_second) {
    ++iterator_second;

    extract(iterator_first, iterator_second);
    return iterator_second;
  }

  template<class Iterators>
  const iterator extract(Iterators iterator_one, Iterators iterator_two) {
    while (iterator_one != iterator_two) {
      this->extract(*iterator_one);
      ++iterator_one;
    }
    return iterator(first_element(type_order), type_order, root);
  }

  void insert(std::initializer_list<value_type> iterators) {
    insert(iterators.begin(), iterators.end());
  }

  const iterator insert(const value_type value) {
    if (root == nullptr) {
      root = new node[1];
      root->key = allocator.allocate(1);
      *root->key = value;

      ++size_;
      return iterator(root, type_order, root);
    } else {
      node* element = find_position(value);

      if (*element->key == value) {
        return iterator(element, type_order, root);
      } else if (compare(value, *element->key)) {
        node* new_child = new node[1];
        new_child->key = allocator.allocate(1);

        *new_child->key = value;
        new_child->parent = element;
        element->right = new_child;


        ++size_;

        return iterator(new_child, type_order, root);
      }
      Node<T>* new_left = new Node<T>[1];
      new_left->key = allocator.allocate(1);

      (*new_left->key) = value;
      new_left->parent = element;
      element->left = new_left;

      ++size_;

      return iterator(new_left, type_order, root);
    }
  }

  size_type erase(const T& elem) {
    size_type res;
    if (find(elem)) {
      res = 1;
    } else{
      res = 0;
    }
    this->extract(elem);
    return res;
  }

  const iterator erase(node* now_node_) {
    iterator cur(now_node_, type_order, root);
    ++cur;

    this->extract(now_node_);

    return cur;
  }

  ~BST() {
    clear();
  }

  void clear() {
    del(root);
  }

  void del(node* temp){
    if (temp != nullptr) {
      del(temp->left);
      del(temp->right);
      allocator.deallocate(temp->key, 1);
      delete temp;
    }
  }

  node* find(value_type x) {
    node* element = root;
    while (element) {
      if (*element->key == x){
        return element;
      } else if (compare(x, *element->key)) {
        element = element->right;
      } else {
        element = element->left;
      }
    }
    return element;
  }

  node* minimum(node* x) {
    if (x->left == nullptr) {
      return x;
    }
    return minimum(x->left);
  }

  node* extract(node*& position, const T& x) {
    if (position == nullptr) {
      return position;
    }
    if (compare(*position->key, x)) {
      position->left = extract(position->left, x);
    } else if (compare(x, *position->key)) {
      position->right = extract(position->right, x);
    } else {
      if (position->left == nullptr) {
        node* new_node = position->right;
        delete[] position;
        --size_;
        return new_node;
      } else if (position->right == nullptr) {
        node* new_node = position->left;
        delete[] position;
        --size_;
        return new_node;
      }
      node* new_node = minimum(position->right);
      position->key = new_node->key;
      position->right = extract(position->right, *new_node->key);
    }
    return position;
  }

  void extract(iterator iterator_) {
    extract(iterator_.cur_node());
  }

  void extract(node* cur){
    if (cur) {
      root = extract(root, *cur->key);
    }
  }

  void extract(const value_type& elem) {
    node* current = find(elem);

    extract(current);
  }

  template <typename M, class Travelsar, class Compare_ = std::less<T>,
      class Allocator_ = std::allocator<T> >
  void merge(BST<M, Travelsar>& a){
    auto it_first = a.begin();
    auto it_second = a.end();
    while (it_first != it_second){
      this->insert(*it_first);
      ++it_first;
    }
  }

  void swap(BST right) {
    std::swap(allocator, right.allocator);
    std::swap(root, right.root);
    std::swap(type_order, right.type_order);
    std::swap(size_, right.size_);
  }

  node* first_element(PreOrder preorder) {
    return root;
  }

  node* first_element(InOrder inorder) {
    node* first_in_order = root;
    while (first_in_order->left) {
      first_in_order = first_in_order->left;
    }
    return first_in_order;
  }

  node* first_element(PostOrder postorder) {
    node* first_in_order = root;

    while (first_in_order->left or first_in_order->right) {
      if (first_in_order->left) {
        first_in_order = first_in_order->left;
      } else {
        first_in_order = first_in_order->right;
      }
    }
    return first_in_order;
  }

  size_t count(const value_type& value) {
    if (find(value)) return 1;
    return 0;
  }

  node* find_position(value_type value) {
    node* position = root;
    bool run = true;
    while (run) {
      if (*position->key == value) {
        return position;
      }
      else if(compare(value,*position->key)) {
        if (position->right != nullptr) {
          position = position->right;
        } else {
          return position;
        }
      } else if (!compare(value,*position->key)) {
        if (position->left) {
          position = position->left;
        } else {
          return position;
        }
      }
    }
    return position;
  }
};
