
/**
 * @file search_flowers.cpp
 * @brief ЛР2 — Алгоритмы поиска данных
 * @author Галицын Дмитрий Дмитриевич
 * @details Вариант 4: Массив данных по цветам. Ключ — name.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

struct Flower {
    string name;
    string color;
    string aroma;
    string regions;
};

static const char* NAMES[]   = {"Роза","Тюльпан","Орхидея","Лилия","Ромашка","Подсолнух","Гвоздика"};
static const char* COLORS[]  = {"Красный","Белый","Желтый","Розовый","Фиолетовый","Оранжевый","Синий"};
static const char* AROMAS[]  = {"сильный","умеренный","слабый"};
static const char* REGIONS[] = {"Европа","Азия","Северная Америка","Южная Америка","Африка"};

/**
 * @brief Генерация данных в памяти
 */
vector<Flower> generateData(int n) {
    vector<Flower> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        v.push_back({NAMES[rand()%7], COLORS[rand()%7], AROMAS[rand()%3], REGIONS[rand()%5]});
    }
    return v;
}

// ===========================
// Линейный поиск
// ===========================
/**
 * @brief Линейный поиск всех вхождений
 * @complexity O(n)
 */
vector<Flower> linearSearch(const vector<Flower>& arr, const string& key) {
    vector<Flower> result;
    for (const auto& f : arr)
        if (f.name == key) result.push_back(f);
    return result;
}

// ===========================
// BST
// ===========================
struct BSTNode {
    string key;
    vector<Flower> values;
    BSTNode* left  = nullptr;
    BSTNode* right = nullptr;
    BSTNode(const string& k, const Flower& v) : key(k), values({v}) {}
};

BSTNode* bstInsert(BSTNode* root, const string& key, const Flower& val) {
    if (!root) return new BSTNode(key, val);
    if (key < root->key) root->left  = bstInsert(root->left,  key, val);
    else if (key > root->key) root->right = bstInsert(root->right, key, val);
    else root->values.push_back(val);
    return root;
}

/**
 * @brief Поиск в BST
 * @complexity O(log n) avg, O(n) worst
 */
vector<Flower> bstSearch(BSTNode* root, const string& key) {
    if (!root) return {};
    if (key == root->key) return root->values;
    if (key < root->key) return bstSearch(root->left, key);
    return bstSearch(root->right, key);
}

void bstFree(BSTNode* root) {
    if (!root) return;
    bstFree(root->left);
    bstFree(root->right);
    delete root;
}

// ===========================
// RBT
// ===========================
enum Color { RED, BLACK };

struct RBNode {
    string key;
    vector<Flower> values;
    Color color = RED;
    RBNode* left = nullptr;
    RBNode* right = nullptr;
    RBNode* parent = nullptr;
    RBNode(const string& k, const Flower& v) : key(k), values({v}) {}
};

class RBTree {
    RBNode* root;
    RBNode* nil;

    void rotateLeft(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;
        if (y->right != nil) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixInsert(RBNode* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                RBNode* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) { z = z->parent; rotateLeft(z); }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateRight(z->parent->parent);
                }
            } else {
                RBNode* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) { z = z->parent; rotateRight(z); }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotateLeft(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void freeNode(RBNode* n) {
        if (n == nil) return;
        freeNode(n->left);
        freeNode(n->right);
        delete n;
    }

public:
    RBTree() {
        nil = new RBNode("", Flower{});
        nil->color = BLACK;
        nil->left = nil->right = nil->parent = nil;
        root = nil;
    }
    ~RBTree() { freeNode(root); delete nil; }

    /**
     * @brief Вставка в RBT
     * @complexity O(log n)
     */
    void insert(const string& key, const Flower& val) {
        RBNode* cur = root;
        RBNode* par = nil;
        while (cur != nil) {
            par = cur;
            if (key == cur->key) { cur->values.push_back(val); return; }
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        RBNode* z = new RBNode(key, val);
        z->parent = par;
        z->left = z->right = nil;
        z->color = RED;
        if (par == nil) root = z;
        else if (key < par->key) par->left = z;
        else par->right = z;
        fixInsert(z);
    }

    /**
     * @brief Поиск в RBT
     * @complexity O(log n)
     */
    vector<Flower> search(const string& key) const {
        RBNode* cur = root;
        while (cur != nil) {
            if (key == cur->key) return cur->values;
            cur = (key < cur->key) ? cur->left : cur->right;
        }
        return {};
    }
};

// ===========================
// Хеш-таблица
// ===========================
/**
 * @brief Хеш-таблица с разрешением коллизий цепочками
 */
class HashTable {
    int capacity;
    vector<vector<pair<string, Flower>>> table;
public:
    int collisions = 0;

    explicit HashTable(int cap) : capacity(cap), table(cap) {}

    /**
     * @brief Хеш-функция djb2
     */
    int hashFunc(const string& key) const {
        unsigned long h = 5381;
        for (unsigned char c : key) h = ((h << 5) + h) + c;
        return (int)(h % capacity);
    }

    void insert(const string& key, const Flower& val) {
        int idx = hashFunc(key);
        if (!table[idx].empty()) collisions++;
        table[idx].push_back({key, val});
    }

    /**
     * @brief Поиск по ключу
     * @complexity O(1) avg, O(n) worst
     */
    vector<Flower> search(const string& key) const {
        int idx = hashFunc(key);
        vector<Flower> result;
        for (const auto& p : table[idx])
            if (p.first == key) result.push_back(p.second);
        return result;
    }
};

template<typename Fn>
long long measureMicro(Fn fn) {
    auto t1 = high_resolution_clock::now();
    fn();
    auto t2 = high_resolution_clock::now();
    return duration_cast<microseconds>(t2 - t1).count();
}

int main() {
    srand(42);
    vector<int> sizes = {100, 500, 1000, 5000, 10000, 50000, 100000, 200000};
    string searchKey = "Роза";

    ofstream results("results_search.csv");
    results << "Size,Linear,BST,RBT,HashTable,Multimap,Collisions\n";

    for (int size : sizes) {
        vector<Flower> data = generateData(size);

        long long tLinear = measureMicro([&](){ linearSearch(data, searchKey); });

        BSTNode* bstRoot = nullptr;
        for (const auto& f : data) bstRoot = bstInsert(bstRoot, f.name, f);
        long long tBST = measureMicro([&](){ bstSearch(bstRoot, searchKey); });
        bstFree(bstRoot);

        RBTree rbt;
        for (const auto& f : data) rbt.insert(f.name, f);
        long long tRBT = measureMicro([&](){ rbt.search(searchKey); });

        HashTable ht(size * 2);
        for (const auto& f : data) ht.insert(f.name, f);
        long long tHash = measureMicro([&](){ ht.search(searchKey); });

        multimap<string, Flower> mm;
        for (const auto& f : data) mm.insert({f.name, f});
        long long tMM = measureMicro([&](){
            auto range = mm.equal_range(searchKey);
            vector<Flower> res;
            for (auto it = range.first; it != range.second; ++it) res.push_back(it->second);
        });

        results << size << "," << tLinear << "," << tBST << "," << tRBT << "," << tHash << "," << tMM << "," << ht.collisions << "\n";
        cout << size << " done\n";
    }
    return 0;
}
