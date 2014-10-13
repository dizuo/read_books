package com.dizuo.xapp;


import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

import android.content.Context;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;


public class NotesPagerAdapter extends FragmentPagerAdapter {

	private Context mContext;
	
	public NotesDataManager mManager = new NotesDataManager();
	
	public static final String HEADER_TAG = "header_tag";
	public static final String NEAR_TAG = "near_tag";
	public static final String FAR_TAG = "far_tag";
	
	public NotesPagerAdapter(FragmentManager fm, Context context) {
		super(fm);
		
		Map<String, Object> map = null;
		
		map = new HashMap<String, Object>();
		map.put("img", 0);
		map.put("title1", HEADER_TAG);
		map.put("title2", NEAR_TAG);
		map.put("time", "");
		mManager.mFinishedList.add(map);
		
		map = new HashMap<String, Object>();
		map.put("img", 0);
		map.put("title1", HEADER_TAG);
		map.put("title2", FAR_TAG);
		map.put("time", "");
		mManager.mFinishedList.add(map);
		
		mContext = context;			
	}

	@Override
	public Fragment getItem(int position) {
		
		// Fragment fragment = new DummySectionFragment(mContext);
		
		/*Bundle args = new Bundle();
		args.putInt(DummySectionFragment.ARG_SECTION_NUMBER, position + 1);
		fragment.setArguments(args);*/
		
		Fragment fragment = null;		
		if (position == 0) {
			fragment = new NotesPagerFragment(mContext, mManager.mFinishedList);
		}
		else {
			fragment = new NotesPagerFragment(mContext, mManager.mTodoList);
		}
		
		return fragment;
	}

	@Override
	public int getCount() {
		return 2;
	}

	@Override
	public CharSequence getPageTitle(int position) {
		Locale l = Locale.getDefault();
		switch (position) {
		case 0:
			return mContext.getString(R.string.title_section1).toUpperCase(l);
		case 1:
			return mContext.getString(R.string.title_section2).toUpperCase(l);
		case 2:
			return mContext.getString(R.string.title_section3).toUpperCase(l);
		}
		return null;
	}
	
}
