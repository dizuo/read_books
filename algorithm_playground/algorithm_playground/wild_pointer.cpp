class MapTraffic
{

public:

	MapTraffic() { _ClearCache(); }
	
	~MapTraffic() { _ClearCache(); }
	
	void clear_traffic_data() {
		// free all of member pointers in m_queue.
		m_queue.clear();
		
		_ClearCache();	// 指向的实体已经不存在，否则wild pointer.
	}
	
	// 一个城市几千次访问. 如果每次都动态寻找城市指针，平均n/2次。
	// _lastTraffic使用，精髓！	
	char query_status(int,int,int);	// Read _lastTraffic or traverse m_queue.
	
	// Add new city traffic data.
	// If m_queue is full, first item will be evicted from queue.
	// 城市被从缓存中删除时候，需要处理_lastTraffic，否则wild pointer.
	void refresh_traffic(char* buffer, int size, char* city_name); 
	
private:

	void _ClearCache() { _lastCode = 0; _lastTraffic = NULL; } 
	
	CityTraffic* _lastTraffic;	// refer to m_queue member. 依附于m_queue,需要与之同步更新！
	int _lastCode;	
	
	Queue< CityTraffic* > m_queue;
	
};