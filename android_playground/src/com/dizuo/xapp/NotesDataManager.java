package com.dizuo.xapp;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class NotesDataManager {
	
	public List<Map<String, Object>> mFinishedList = new LinkedList<Map<String, Object>>();	// Data of ListView

	public List<Map<String, Object>> mTodoList = new LinkedList<Map<String, Object>>();	// Data of ListView
	
	public static final int LV_NEAR_HEAD = 0;
	public static final int LV_FAR_HEAD = 1;
	public static final int LV_CONTENT = 2;
	
	public void addItemToFinishedList(Map<String, Object> item) {
		mFinishedList.add(item);	
	}
	
	public void addItemToTodoList(Map<String, Object> item) {
		mTodoList.add(item);		
	}
	
	// sort linkedlist 
	private void rearrangeList() {
		
	}
}
