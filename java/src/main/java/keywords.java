
import java.util.*;

class keywords{

	private static String KEYWORDS[] = {
	    "var",
	    "loop",
		"if",
    	"else",
	    "in",
    	"or",
	    "and",
    	"serial",
    	"HIGH",
    	"LOW",
    	"return",
    	"fun",
    	"break",
    	"true",
    	"false",
		"LED",
		"SPEAKER",
		"LIGHT",
		"MIC",
		"TEMPARATURE",
		"ACCELEROMETER",
		"GYROSCOPE",
		"AIR_PRESSURE",
		"HUMIDITY",
		};

	private static ArrayList<String> KEYWORD_LIST = new ArrayList<String>(Arrays.asList(KEYWORDS));

	private boolean search_keyword(String identifier){
	
		for(int i = 0; i < 24; i++){
			
			if(KEYWORDS[i].equals(identifier)){
				return true;	
			}

		}

		return false;

	}

	public boolean is_keyword(String identifier){

		 return this.search_keyword(identifier);

	}

	public boolean is_num(String str) {
	    if (str == null) {
	        return false;
	    }
	    try {
	        double d = Double.parseDouble(str);
	    } catch (NumberFormatException e) {
	        return false;
	    }
	    return true;
	}

}

