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
		
	public NotesPagerAdapter(FragmentManager fm, Context context) {
		super(fm);
		
		mManager.addDataToList(mManager.mFinishedList, 0, NotesDataManager.HEADER_TAG,
				NotesDataManager.NEAR_TAG, "");
		
		mManager.addDataToList(mManager.mFinishedList, 0, "×Ô×¡·¿ÉêÇë", "test", "2014-10-14 18:17");
		
		mManager.addDataToList(mManager.mFinishedList, 0, NotesDataManager.HEADER_TAG,
				NotesDataManager.FAR_TAG, "");
		
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
			fragment = new NotesPagerFragment(mContext, mManager.mTodoList);
		}
		else {
			fragment = new NotesPagerFragment(mContext, mManager.mFinishedList);
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
			return mContext.getString(R.string.title_todo).toUpperCase(l);
		case 1:
			return mContext.getString(R.string.title_finished).toUpperCase(l);		
		}
		return null;
	}
	
}
