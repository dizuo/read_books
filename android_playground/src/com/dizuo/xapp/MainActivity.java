package com.dizuo.xapp;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import android.app.ActionBar;
import android.app.FragmentTransaction;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.CheckBox;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;


public class MainActivity extends FragmentActivity implements
		ActionBar.TabListener {

	/**
	 * The {@link android.support.v4.view.PagerAdapter} that will provide
	 * fragments for each of the sections. We use a
	 * {@link android.support.v4.app.FragmentPagerAdapter} derivative, which
	 * will keep every loaded fragment in memory. If this becomes too memory
	 * intensive, it may be best to switch to a
	 * {@link android.support.v4.app.FragmentStatePagerAdapter}.
	 */
	SectionsPagerAdapter mSectionsPagerAdapter;

	/**
	 * The {@link ViewPager} that will host the section contents.
	 */
	ViewPager mViewPager;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.activity_main);	// 2 
				
		// Set up the action bar.
		final ActionBar actionBar = getActionBar();
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_TABS);

		// Create the adapter that will return a fragment for each of the three
		// primary sections of the app.
		mSectionsPagerAdapter = new SectionsPagerAdapter(
				getSupportFragmentManager(), this);

		// Set up the ViewPager with the sections adapter.
		mViewPager = (ViewPager) findViewById(R.id.pager);
		mViewPager.setAdapter(mSectionsPagerAdapter);

		// When swiping between different sections, select the corresponding
		// tab. We can also use ActionBar.Tab#select() to do this if we have
		// a reference to the Tab.
		mViewPager
				.setOnPageChangeListener(new ViewPager.SimpleOnPageChangeListener() {
					@Override
					public void onPageSelected(int position) {
						actionBar.setSelectedNavigationItem(position);
					}
				});

		// For each of the sections in the app, add a tab to the action bar.
		for (int i = 0; i < mSectionsPagerAdapter.getCount(); i++) {
			// Create a tab with text corresponding to the page title defined by
			// the adapter. Also specify this Activity object, which implements
			// the TabListener interface, as the callback (listener) for when
			// this tab is selected.
			actionBar.addTab(actionBar.newTab()
					.setText(mSectionsPagerAdapter.getPageTitle(i))
					.setTabListener(this));
		}
				
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onTabSelected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
		// When the given tab is selected, switch to the corresponding page in
		// the ViewPager.
		mViewPager.setCurrentItem(tab.getPosition());
	}

	@Override
	public boolean onMenuItemSelected(int featureId, MenuItem item) {
		switch (item.getItemId()) {	// process menu hit event.
		case R.id.action_settings:
			Log.i("dizuo", "setting item is hit...");
			break;			
		}
		
		return true;
	}
		
	@Override
	public void onTabUnselected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
	}

	@Override
	public void onTabReselected(ActionBar.Tab tab,
			FragmentTransaction fragmentTransaction) {
	}

	/**
	 * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
	 * one of the sections/tabs/pages.
	 */
	public class SectionsPagerAdapter extends FragmentPagerAdapter {

		private Context mContext;
				
		public SectionsPagerAdapter(FragmentManager fm, Context context) {
			super(fm);
			
			mContext = context;			
		}

		@Override
		public Fragment getItem(int position) {
			// getItem is called to instantiate the fragment for the given page.
			// Return a DummySectionFragment (defined as a s tatic inner class
			// below) with the page number as its lone argument.
			Fragment fragment = new DummySectionFragment(mContext);
			Bundle args = new Bundle();
			args.putInt(DummySectionFragment.ARG_SECTION_NUMBER, position + 1);
			fragment.setArguments(args);
			return fragment;
		}

		@Override
		public int getCount() {
			// Show 3 total pages.
			return 3;
		}

		@Override
		public CharSequence getPageTitle(int position) {
			Locale l = Locale.getDefault();
			switch (position) {
			case 0:
				return getString(R.string.title_section1).toUpperCase(l);
			case 1:
				return getString(R.string.title_section2).toUpperCase(l);
			case 2:
				return getString(R.string.title_section3).toUpperCase(l);
			}
			return null;
		}
	}

	/**
	 * A dummy fragment representing a section of the app, but that simply
	 * displays dummy text.
	 */
	public static class DummySectionFragment extends Fragment {
		/**
		 * The fragment argument representing the section number for this
		 * fragment.
		 */
		public static final String ARG_SECTION_NUMBER = "section_number";

		private static String [] strs = new String[] { "first", "second", "third" };
		
		private static Context mContext;
		
		public DummySectionFragment(Context context) {
			mContext = context;
		}

		@Override
		
		// TODO refactor: Use one ListView ...
		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
			View rootView = inflater.inflate(R.layout.fragment_main_dummy, container, false);
			
			// TextView dummyTextView = (TextView) rootView.findViewById(R.id.section_label);					
			// dummyTextView.setText(Integer.toString(getArguments().getInt(ARG_SECTION_NUMBER)));
			
			ListView listView = (ListView) rootView.findViewById(R.id.todo_list);
			
			String[] from = new String[] {"img", "title1", "title2", "time"};
			int[] to = new int[] {R.id.img, R.id.title1, R.id.title2, R.id.time};
			
			// DataItemStruct is Map<String, Object>
			List<Map<String, Object>> list = new ArrayList<Map<String, Object>>();	// Data of ListView
			Map<String, Object> map = null;
			
			for (int i = 0; i < 10; i++)
			{
				map = new HashMap<String, Object>();
				map.put("img", 0);
				map.put("title1", "标题");
				map.put("title2", "副标题");
				map.put("time", "2014-10-9 17:06");
				list.add(map);
			}
			
			SimpleAdapter adapter = new SimpleAdapter(mContext, list, R.layout.complex_list_item, from, to) {
				@Override
				public View getView(final int position, View convertView, ViewGroup parent) {
					View view = super.getView(position, convertView, parent);
					
					final HashMap<String, Object> map = (HashMap<String, Object>) this.getItem(position);
					
					CheckBox cb = (CheckBox) view.findViewById(R.id.checked);
					
					if (map.containsKey("checked")) {
						cb.setChecked( (Boolean) map.get("checked"));
					}
					
					if (cb != null) {
						cb.setOnClickListener(new View.OnClickListener(){
							@Override
							public void onClick(View view) {	// CheckBox hit event callback.
								map.put("checked", ((CheckBox)view).isChecked());
								Log.i("dizuo", "checkbox hit...");
							}
						});
					}

					TextView header = (TextView) view.findViewById(R.id.lv_header);
					View content = view.findViewById(R.id.lv_content);
					
					if (position == 0 || position == 4) {
						content.setVisibility(View.GONE);
						header.setVisibility(View.VISIBLE);
						header.setBackgroundColor(getResources().getColor(R.color.list_header_color));
						
						if (position == 0) {
							header.setText(getResources().getText(R.string.todo_text));
						}
					}
					else
					{
						content.setVisibility(View.VISIBLE);
						header.setVisibility(View.GONE);
					}
					
					return view;
				}
				
			};
			
			listView.setAdapter(adapter);
			
			AdapterView.OnItemClickListener listener = new AdapterView.OnItemClickListener() {
				public void onItemClick(AdapterView<?> parent, View view, int position, long id)
				{
					HashMap<String,Object> map = (HashMap<String, Object>) parent.getItemAtPosition(position);
					
					Log.i("dizuo",  "position:" + position + "  item:" + parent.getItemAtPosition(position).toString() );
				}
			};
			
			listView.setOnItemClickListener(listener);
						
			// lv.setAdapter(new ArrayAdapter<String>(mContext, R.layout.simple_list_item_1, strs));
			
			return rootView;
		}
	}

}
