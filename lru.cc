#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

template <typename K, typename V>
struct Node {
   K key;
   V val;
   struct Node *pNext;
   struct Node *pPrev;
};

template <typename K, typename V>
class LRUCache() {
   public:
      size_t size;
      void Set(K key, V val);
      struct Node * Get(K &key);
   private:
      void detach(Node<K,V>* node);
      void attach(Node<K,V>* node);

      unordered_map<K, Node<K,V>*> m_mHashMap;
      vector<Node<K,V>*> m_vFreeNode;

      Node<K,V> *m_pHead;
      Node<K,V> *m_pTail;
      Node<K,V> *m_pList;
};

template<typename K, typename K>
LRUCache::LRUCache(size_t size_) :size(size_){
   // 申请cache可用空间，
   m_pList = new Node<K,V>[size];
   for (auto idx = 0; idx < size; idx++) {
      m_vFreeNode.push_back(m_pList + idx);
   }

   m_pHead = new Node<K,V>;
   m_pTail = new Node<K,V>;
   m_pHead->pPrev = nullptr;
   m_pHead->pNext = m_pTail;

   m_pTail->pPrev = m_pHead;
   m_pTail->pNext = nullptr;

}

template<typename K, typename K>
LRUCache::~LRUCache() {
   delete m_pHead;
   delete m_pTail;
   delete[] m_pList;
}

template<typename K, typename K>
LRUCache::Set(K key, V val) {
   auto node = m_mHashMap[key];
   if (node) {
      detach(node);
      node->val = val;
      attach(node);
   } else {
      if (m_vFreeNode.empty()) {
         node = m_pTail->pPrev;
         detach(node);
         m_mHashMap.erase(node->key);
      } else {
         node = m_vFreeNode.back();
         m_vFreeNode.pop_back();
      }

      node->val = val;
      node->key = key;
      m_mHashMap[key] = node;
      attach(node);
   }
}

template<typename K, typename V>
V *LRUCache::get(K key) {
   Node<K, V> *node = m_mHashMap[key];
   if (node) {
      detach(node);
      attach(node);
      return node->val;
   }  else {
      return V();
   }
}

template<typename K, typename V>
void attach(Node<K, V> *node) {
   node->pPrev = m_pHead;
   node->pNext = m_pHead->pNext;
   m_pHead->pNext->pPrev = node;
   m_pHead->pNext = node;
}

void detach(Node<K, V> *node) {
   node->pPrev->pNext = node->pNext;
   node->pNext->pPrev = node->pPrev;
}

