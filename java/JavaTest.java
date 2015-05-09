// http://www.w3cschool.cc/java/java-string.html

// One source file must contain one public class.

// One source file can contain multiple non-public class.

// Source file name is the same with public class name.

// Package is first line.

package dizuo.java;
# package refer : http://blog.sina.com.cn/s/blog_5163b2980100bocf.html

class Traffic {
	
	public Traffic(String name) {
		System.out.println("pass name = " + name);
	}
	
	enum STATUS {
		GREEN,
		YELLOW,
		RED,
		BLACK_RED
	}
	
	STATUS status = STATUS.RED;
}

public class JavaTest {
	
	public static void test() {
		Traffic traffic = new Traffic("dizuo");
		System.out.println("traffic = " + traffic.status);
		
		// Access enum.
		traffic.status = Traffic.STATUS.YELLOW;
		System.out.println("traffic = " + traffic.status);
		
	}
	
	// Main Entrances.
	public static void main(String [] args) {
		
		test();
		
		for (int $k = 0; $k < args.length; $k++) {
			System.out.println(args[$k]);
		}
	}
	
}
