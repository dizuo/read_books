package com.dizuo.xapp;

import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class NotesDataManager {
	
	public List<Map<String, Object>> mFinishedList = new LinkedList<Map<String, Object>>();	// Data of ListView

	public List<Map<String, Object>> mTodoList = new LinkedList<Map<String, Object>>();	// Data of ListView
	
	public static final String HEADER_TAG = "header_tag";
	public static final String NEAR_TAG = "near_tag";
	public static final String FAR_TAG = "far_tag";
	
	// consistent with complex_list_item.xml
	private static String[] mKeyList = new String[] {"img", "content", "title", "time"};
	private static int[] mValueList = new int[] {R.id.lv_img, R.id.lv_note_content, R.id.lv_title, R.id.lv_time};

	// -----------------------------------------------static function-----------------------------------------------
	public static String[] getKeyList() {
		return mKeyList;
	}
	
	public static int[] getValueList() {
		return mValueList;
	}
	
	public static boolean isRecordContainHeadTag(NoteRecord record) {
		String key = mKeyList[1];
		return record.containsKey(key) && record.get(key) == HEADER_TAG;
	}
	
	public static boolean isRecordContainFarTag(NoteRecord record) {
		String key = mKeyList[2];
		return record.containsKey(key) && record.get(key) == FAR_TAG;
	}
	
	// -----------------------------------------------Object function-----------------------------------------------
	public void addDataToList(List<Map<String, Object>> list, int imgId, String content, String title, String time) {		
		Map<String, Object> map = new NoteRecord();
		map.put("img", imgId);
		map.put("content", content);
		map.put("title", title);
		map.put("time", time);
		list.add(map);		
	}
	
	public void addItemToFinishedList(Map<String, Object> item) {
		mFinishedList.add(item);	
	}
	
	public void addItemToTodoList(Map<String, Object> item) {
		mTodoList.add(item);		
	}
	
	// sort linkedlist 
	private void rearrangeList() {
		
	}
	
	// Like typedef in C/C++ 
	public static class NoteRecord extends HashMap<String, Object> {
		
	}
}
