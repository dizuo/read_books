// ref: http://www.hawstein.com/posts/lru-cache-impl.html

template<class K, class T> struct Node
{
	// unsigned int timestamp;	// GetSystemTimeStamp(), LRU default compare key.
	
    K key;
    T data;
    Node* next;
	Node* pre;
};

template< class K, class T> class LRUCache
{
public:
	typedef Node<K, T> node_t;
	typedef node_t* node_ptr_t;
	
	LRUCache(size_t size);
	
	~LRUCache();	// destroy dlist_, destroy hash_map_.
	
	// if full : 
	//		1) evict from cache and reuse Node, 
	//		2) update dlist_,
	//		3) update hash_map(erase old and insert new one).
	// if exist : update Node:data and dlist_. // DONOT NEED UPDATE HASH_MAP
	// if not full and not exist : create Node and insert to hash_map.
	void put(const Key& key, const T& dat);	
	
	// if found return Node pointer, otherwise return NULL.
	T& get(const Key& key);

	node_ptr_t head_, tail_;
    map<K, node_ptr_t > hash_map_;
    int size_;
};
