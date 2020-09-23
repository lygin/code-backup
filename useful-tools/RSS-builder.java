import java.io.*;
public class Creater {
	public static void main(String[] args) throws IOException {
		String[] s = new String[3];
		s[0]=CreateItem("标题1", "www.baidu1.com", "thanks1");
		s[1]=CreateItem("标题2", "www.baidu2.com", "thanks2");
		s[2]=CreateItem("标题3", "www.baidu3.com", "thanks3");
		String XML = CreateXML(s);
		File f = new File(args[0]);
		FileOutputStream fos = new FileOutputStream(f);
		fos.write(XML.getBytes());
	}
	public static String CreateTitle(String title) {//创建title标签
		String ans = new String();
		ans+="<title>";
		ans+=title;
		ans+="</title>\r\n";
		return ans;
	}
	public static String CreateLink(String link) {//创建link标签
		String ans = new String();
		ans+="<link>";
		ans+=link;
		ans+="</link>\r\n";
		return ans;
	}
	public static String CreateDescription(String description) {//创建一个description标签
		String ans = new String();
		ans+="<description>";
		ans+=description;
		ans+="</description>\r\n";
		return ans;
	}
	public static String CreateItem(String title, String link, String description) {//将三个标签整合为item
		String ans = new String();
		ans+="<item>\r\n";
		ans+=CreateTitle(title);
		ans+=CreateLink(link);
		ans+=CreateDescription(description);
		ans+="</item>\r\n";
		
		return ans;
	}
	public static String CreateXML(String [] Items) {//item整合为XML
		String ans = new String ();
		ans+="<?xml version=\"1.0\" encoding=\"gb2312\"?>\r\n";
		ans+="<rss version=\"2.0\">\r\n";
		ans+="<channel>\r\n";
		for(int i=0;i<Items.length;i++) {
			ans+=Items[i];
		}
		ans+="</channel>";
		return ans;
	}
}