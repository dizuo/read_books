package com.dizuo.xapp;

import java.util.HashMap;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.Context;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteQueryBuilder;
import android.net.Uri;
import android.text.TextUtils;
import android.util.Log;

public class xxContentProvider extends ContentProvider {
	
	public static final String sTag = "dizuo";
	
	/** 
     * 定义规则 
     */  
    public static final UriMatcher uriMatcher;  
    public static final int USERS_COLLECTION = 1;//用于标记  
    public static final int USERS_SINGLE = 2;//用于标记  
    private DatabaseHelper databaseHelper;//这里的数据共享是共享Sqlite里的数据，当然，可以试用其他，如文本数据共享。  
    
    private static class DatabaseHelper extends SQLiteOpenHelper {
    	public DatabaseHelper(Context context) {
    		super(context, xxProviderMetaData.DATABASE_NAME, null, xxProviderMetaData.DATABASE_VERSION);
    	}
    	
    	public void onCreate(SQLiteDatabase db) {
    		Log.i(sTag, "create table: " + xxProviderMetaData.UserTableMetaData.SQL_CREATE_TABLE);
    		db.execSQL(xxProviderMetaData.UserTableMetaData.SQL_CREATE_TABLE);
    	}
    	
    	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
    		db.execSQL("DROP STABLE IF EXISTS " + xxProviderMetaData.UserTableMetaData.TABLE_NAME);
    		onCreate(db);
    	}
    	    	
    }
    
    static {  
        uriMatcher = new UriMatcher(UriMatcher.NO_MATCH);//试用一个没有规则的Uri。然后下面自己匹配。  
        uriMatcher.addURI(xxProviderMetaData.AUTHORIY, "/users",USERS_COLLECTION);//自己定义的规则，有点像路由器，是uri匹配的方案。  
        uriMatcher.addURI(xxProviderMetaData.AUTHORIY, "/users/#",USERS_SINGLE);//同上。  
    }  
  
    /** 
     * 为列定义别名 
     */  
    public static HashMap<String,String> usersMap;  
    static {  
        usersMap = new HashMap<String, String>();  
        usersMap.put(xxProviderMetaData.UserTableMetaData._ID, xxProviderMetaData.UserTableMetaData._ID);  
        usersMap.put(xxProviderMetaData.UserTableMetaData.USER_NAME, xxProviderMetaData.UserTableMetaData.USER_NAME);  
        usersMap.put(xxProviderMetaData.UserTableMetaData.USER_AGE, xxProviderMetaData.UserTableMetaData.USER_AGE);  
    }  
    
	@Override
	public boolean onCreate() {
		
		Log.i(sTag, "onCreate");
		databaseHelper = new DatabaseHelper(getContext());
		
		return false;
	}

	@Override
	public Cursor query(Uri uri, String[] projection, String selection,
			String[] selectionArgs, String sortOrder) {
		
		Log.i(sTag, "query");
		
		SQLiteQueryBuilder sqLiteQueryBuilder = new SQLiteQueryBuilder();//写入查询条件，有点像Hibernate。  
        switch (uriMatcher.match(uri)) {//判断查询的是单个数据还是多个数据。  
            case USERS_SINGLE:  
                sqLiteQueryBuilder.setTables(xxProviderMetaData.UserTableMetaData.TABLE_NAME);//需要查询的表  
                sqLiteQueryBuilder.setProjectionMap(usersMap);//列的别名定义  
                sqLiteQueryBuilder.appendWhere(xxProviderMetaData.UserTableMetaData._ID + "=" + uri.getPathSegments().get(1));  
                //查询条件，uri.getPathSegments().get(1)，getPathSegments是将内容根据／划分成list。  
                break;  
            case USERS_COLLECTION:  
                sqLiteQueryBuilder.setTables(xxProviderMetaData.UserTableMetaData.TABLE_NAME);  
                sqLiteQueryBuilder.setProjectionMap(usersMap);  
                break;  
        }  
        String orderBy;//判断sortOrder是否为空，加入默认。  
        if (TextUtils.isEmpty(sortOrder)) {  
            orderBy = xxProviderMetaData.UserTableMetaData.DEFAULT_SORT_ORDER;  
        } else {  
            orderBy = sortOrder;  
        }  
        SQLiteDatabase sqLiteDatabase = databaseHelper.getWritableDatabase();  
        Cursor cursor = sqLiteQueryBuilder.query(sqLiteDatabase, projection, selection, selectionArgs, null, null, sortOrder);   
        cursor.setNotificationUri(getContext().getContentResolver(),uri);  
        return cursor;
	}

	@Override
	public String getType(Uri uri) {
		Log.i(sTag, "getType");
		
        switch (uriMatcher.match(uri)) {//匹配uri的规则  
            case USERS_COLLECTION:  
                return xxProviderMetaData.UserTableMetaData.CONTENT_TYPE;  
            case USERS_SINGLE:  
                return xxProviderMetaData.UserTableMetaData.CONTENT_TYPE_ITEM;  
            default:  
                throw new IllegalArgumentException("Unknown URI" + uri);  
        }  
	}

	@Override
	public Uri insert(Uri uri, ContentValues values) {
		Log.i(sTag, "insert");
		
		if (uriMatcher.match(uri) != USERS_COLLECTION) {
			throw new IllegalArgumentException("Unknown URI " + uri);
		}
		
        SQLiteDatabase sqLiteDatabase = databaseHelper.getWritableDatabase(); 
        if (sqLiteDatabase == null) {
        	return null;
        }
        
        long rowId = sqLiteDatabase.insert(xxProviderMetaData.UserTableMetaData.TABLE_NAME, null, values);  
        if (rowId > 0) {  
            Uri insertUserUri = ContentUris.withAppendedId(xxProviderMetaData.UserTableMetaData.CONTENT_URI, rowId);  
            //通知监听器  
            getContext().getContentResolver().notifyChange(insertUserUri, null);  
            return insertUserUri;  
        }else  
            throw new IllegalArgumentException("Failed to insert row into" + uri);  
	}

	@Override
	public int delete(Uri uri, String selection, String[] selectionArgs) {
		Log.i(sTag, "delete"); 
		
		return 0;
	}

	@Override
	public int update(Uri uri, ContentValues values, String selection,
			String[] selectionArgs) {
		Log.i(sTag, "update");
		
		return 0;
	}

}
