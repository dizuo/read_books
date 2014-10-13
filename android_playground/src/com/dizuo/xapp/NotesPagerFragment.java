package com.dizuo.xapp;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.CheckBox;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;

public class NotesPagerFragment extends Fragment {
	/**
	 * The fragment argument representing the section number for this
	 * fragment.
	 */
	public static final String ARG_SECTION_NUMBER = "section_number";
	
	private Context mContext;
	
	private List<Map<String, Object>> mList = null;
	
	private BaseAdapter mLVAdapter = null;
	
	private AdapterView.OnItemClickListener mListener = null;
	
	public NotesPagerFragment(Context context, List<Map<String, Object>> list) {
		mContext = context;
		mList = list;
	}
	
	public void onDataChanged() {
		mLVAdapter.notifyDataSetChanged();	// Call SimpleAdapter::getView function again.
	}

	@Override	
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		View rootView = inflater.inflate(R.layout.fragment_main_dummy, container, false);
		
		ListView listView = (ListView) rootView.findViewById(R.id.todo_list);
			
		String[] from = new String[] {"img", "title1", "title2", "time"};
		int[] to = new int[] {R.id.img, R.id.title1, R.id.title2, R.id.time};
		
		mLVAdapter = new SimpleAdapter(mContext, mList, R.layout.complex_list_item, from, to) {
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
								
				if (map.get("title1") == NotesPagerAdapter.HEADER_TAG) {
					content.setVisibility(View.GONE);
					header.setVisibility(View.VISIBLE);
					header.setBackgroundColor(getResources().getColor(R.color.list_header_color));
					
					if (map.get("title2") == NotesPagerAdapter.FAR_TAG) {
						header.setText(getResources().getText(R.string.far_week));
					}
					else {
						header.setText(getResources().getText(R.string.near_week));
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
		
		listView.setAdapter(mLVAdapter);
		listView.setOnItemClickListener(mListener);
		
		return rootView;
	}
	
	int getListItemKeyPos() {
		
		DateFormat df = new SimpleDateFormat("yyyy-MM-dd hh:mm");
		
		Calendar c = Calendar.getInstance();
		c.add(Calendar.WEEK_OF_MONTH, -1);
		Date dstDate = c.getTime();
		
		Log.i("dizuo", dstDate.toLocaleString());
		
		ArrayList<Map<String, Object>> list = (ArrayList<Map<String, Object>>)mList;
		
		for (int i = 0; i < list.size(); i++) {			
			Map<String, Object> item = (Map<String, Object>) list.get(i);
			
			String timeStr = ((String)item.get("time")).split(" ")[0];
			
			try {
				Date curDate = df.parse(timeStr);
				if (curDate.getTime() < dstDate.getTime()) {
					return i;
				}
			}
			catch (Exception exception) {
				exception.printStackTrace();
			}
			
		}		
		
		return -1;
	}
	
}
