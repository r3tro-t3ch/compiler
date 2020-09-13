
import java.util.regex.*; 
import java.util.*;
import java.util.List;


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
	
		boolean FLAG = false;

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


class lexer{

	private char current_char;
	private int index;
	private char code[];

	public char get_current_char(){

		return this.current_char;

	}

	//creating and initializaing a lexer
	public lexer(String code){

		this.index = 0;
		this.code = code.toCharArray();
		this.current_char = this.code[this.index];

	}

	public void next_char(){

		this.index++;
		this.current_char = this.code[this.index];
	
	} 

	public String get_string(){

		ArrayList<Character> identifier = new ArrayList<Character>();
		this.next_char();
		identifier.add(this.current_char);
		this.next_char();
		while( this.current_char != '"' ){
			
			identifier.add(this.current_char);
			this.next_char();

		}

		StringBuilder identifier_str = new StringBuilder();
	
		for(char i : identifier){

			identifier_str.append(String.valueOf(i));

		}

		return(identifier_str.toString());
	}

	public String get_identifier(){

		ArrayList<Character> identifier = new ArrayList<Character>();
		identifier.add(this.current_char);
		this.next_char();
		while( is_alpha_numeric( this.current_char )){

			identifier.add(this.current_char);
			this.next_char();

		}

		StringBuilder identifier_str = new StringBuilder();

		for(char i : identifier){

			identifier_str.append(String.valueOf(i));

		}

		return(identifier_str.toString());

	}

	public boolean is_alpha_numeric(char str)
    {
        String regex = "[a-zA-Z0-9]";

        Pattern p = Pattern.compile(regex);

        if (str == '\0') {
            return false;
        }

        Matcher m = p.matcher(String.valueOf(str));

        return m.matches();
    }

}

class token{
	
	private String type;
	private String content;

	public token(String type, String content){

		this.type = type;
		this.content = content;

	}

	public String get_type(){

		return this.type;

	}

	public String get_content(){

		return this.content;

	}

}
